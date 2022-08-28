#include "game_learning.h"
using namespace std;

namespace splashkit_lib
{
	void InputFormat::convert_int(std::vector<int> input, std::vector<bool> *out, int index)
	{
		for (int i = 0; i < sizes[index]; i++)
		{
			if (input[i] != 0)
			{
				(*out)[indexes_out[index] + i * max_vals[index] + input[indexes_in[index] + i] - 1] = true;
			}
		}
	}

	int InputFormat::add_type(Type type, int size, int max_val)
	{
		if (size < 1)
			LOG(WARNING) << "Size must be greater than 0!";
		if (max_val <= 1)
			LOG(WARNING) << "Max Value must be greater than 1!";
		format.push_back(type);				  // How to interpret the data
		sizes.push_back(size);				  // How many values to read
		max_vals.push_back(max_val - 1);	  // The range of the given values, with a domain of [0, max_val) exclusive
		indexes_in.push_back(input_width);	  // The starting index for the given data in int form
		indexes_out.push_back(output_width);  // The starting index for the given data in bool form
		input_width += size;				  // The total width of the inputted data
		output_width += size * (max_val - 1); // The total width of the outputted data
		return format.size() - 1;
	}

	std::vector<bool> InputFormat::convert_input(std::vector<int> input)
	{
		std::vector<bool> out(output_width, false);
		for (int i = 0; i < format.size(); i++)
		{
			convert_int(input, &out, i);
		}
		return out;
	}

	bool InputFormat::operator==(const InputFormat &other) const
	{
		return input_width == other.input_width && output_width == other.output_width && format == other.format && sizes == other.sizes && max_vals == other.max_vals && indexes_in == other.indexes_in && indexes_out == other.indexes_out;
	}

	int OutputFormat::add_type(Type type, int data)
	{
		format.push_back(type);
		f_data.push_back(data);
		indexes.push_back(output_width);
		switch (type)
		{
		case Type::Number:
			output_width++;
			break;
		case Type::Position:
		case Type::Category:
			output_width += data;
			break;
		}
		return format.size() - 1;
	}

	OutputValue::OutputValue(int width)
	{
		value = std::vector<float>(width, 0.5f);
	}

	int OutputValue::get_max_position(OutputFormat format, int index, const std::vector<int> filter, bool random)
	{
		if (format.get_type(index) != OutputFormat::Type::Position && format.get_type(index) != OutputFormat::Type::Category)
			LOG(WARNING) << "Format at index is not of type Position!";
		index = format.get_output_index(index); // Grab the starting index for the given position data
		if (random)
		{
			int out = filter[rnd(filter.size())];
			// update reward_table
			to_update(out);
			return out;
		}
		int initial_index = rnd(filter.size()); // Set the initial index to a random position, this prevents the AI from always playing the first move when all equal
		float max = value[index + filter[initial_index]];
		int max_pos = filter[initial_index];
		for (int i = 0; i < filter.size(); i++)
		{
			if (value[index + filter[i]] > max)
			{
				max = value[index + filter[i]];
				max_pos = filter[i];
			}
		}
		to_update(max_pos);
		return max_pos;
	}

	float OutputValue::process_output_number(OutputFormat format, int index, bool random)
	{
		if (format.get_type(index) != OutputFormat::Type::Number)
			LOG(WARNING) << "Format at index is not of type Number!";
		to_update(format.get_output_index(index));														 // Tells the AI that the number was retrieved and should be updated during reward/punishment
		return (random ? rnd() : value[format.get_output_index(index)] * format.get_output_info(index)); // Scale the number to the previously given range [0, f_data[index]]
	}

	void OutputValue::update(float learning_rate, float discount_factor, float reward, OutputValue *next_move)
	{
		for (int i = 0; i < indexes.size(); i++)
		{
			if (next_move == nullptr)
			{
				value[indexes[i]] += learning_rate * reward; // Next move is game over with this reward. i.e. instant win/instant loss
				continue;
			}

			float max_future;
			if (indexes.size() != next_move->indexes.size())
			{
				max_future = next_move->value[indexes[i]]; // Fall-back to this to ensure index is in bounds
			}
			else
			{
				max_future = next_move->value[next_move->indexes[i]];
			}

			// QLearning method, using the next move as future reward
			value[indexes[i]] += learning_rate * (reward + discount_factor * max_future - value[indexes[i]]);
		}
	}

	string OutputValue::to_string() const
	{
		std::stringstream ss;
		ss << "[ ";
		for (float v : value)
		{
			ss << v << " ";
		}
		ss << "]";
		return ss.str();
	}

	RewardTable::RewardTable(int width)
	{
		this->width = width;
	}

	OutputValue &RewardTable::get_value(std::vector<bool> &key)
	{
		// log(INFO, "RewardTable::get_value");
		if (reward_table.find(key) == reward_table.end()) // key not found
		{
			// log(INFO, "RewardTable::get_value - creating new q_value");
			reward_table[key] = OutputValue(width);
		}
		return reward_table[key];
	}

	OutputValue &RewardTable::get_value(Game *game)
	{
		vector<bool> game_state = game->get_input_format().convert_input(game->get_input());
		return get_value(game_state);
	}

	class QAgent::SelfPlay
	{
	private:
		RewardTable *reward_table;
		std::vector<OutputValue *> move_history; // Store the q_values used for the last game
	public:
		float learning_rate = 0.1f;
		float discount_factor = 0.9f;
		float epsilon = 0.1f;

		SelfPlay(RewardTable *reward_table)
		{
			this->reward_table = reward_table;
		}

		/**
		 * @brief Get the move this agent wishes to play.
		 *
		 *
		 *
		 * @param game
		 * @return int
		 */
		int get_move(Game *game)
		{
			std::vector<bool> input = game->get_input_format().convert_input(game->get_input()); // convert input to boolean for neural networks / ease of hashing
			OutputValue &output = reward_table->get_value(input);								 // get the q_value for the current state
			move_history.push_back(&output);													 // remember that we took this move for reward if we win or lose
			return game->convert_output(output, rnd() < epsilon);								 // convert the q_value into a move, if epsilon take a random move (e.g. take the highest value (best) move)
		}

		/**
		 * @brief Rewards all the moves taken in the game. If we won the game we give a reward so that we try to take that move again.
		 *
		 * @param score The total score of this agent
		 */
		void reward(float score)
		{
			move_history[move_history.size() - 1]->update(learning_rate, discount_factor, score, nullptr); // Special case for first instance
			for (int i = move_history.size() - 2; i >= 0; i--)
			{
				move_history[i]->update(learning_rate, discount_factor, score, move_history[i + 1]);
				move_history[i + 1]->reset();
			}
			move_history[0]->reset();
			move_history.clear();
		}
	};

	QAgent::QAgent(OutputFormat &out_format)
	{
		reward_table = new RewardTable(out_format.get_width());
	}

	int QAgent::get_move(Game *game)
	{
		std::vector<bool> input = game->get_input_format().convert_input(game->get_input());
		OutputValue &output = reward_table->get_value(input);
		return game->convert_output(output, false);
	}

	void QAgent::train(Game *game, int player_count, int iterations)
	{
		int bar_length = 50;					 
		int percentage = 0, progress = 0;		 // current percentage of training // how many bar units achieved
		char bar = '#';							 // character used to fill bar
		int bar_units = iterations / bar_length; // calculates how many iterations account for each bar

		cout << "Training QAgent for " << iterations << " iterations" << endl;
		std::vector<QAgent::SelfPlay> agents;
		for (int i = 0; i < player_count; i++)
		{
			agents.push_back(QAgent::SelfPlay(reward_table)); // generate the agents to play the game
		}

		cout << "  0 % [";
		for (int i = 0; i <= bar_length; i++)
		{
			cout << "_";
		}
		cout << "]";
		cout << "\r";
		for (int i = 0; i < iterations; i++)
		{
			while (!game->is_finished())
			{
				int move = agents[game->get_current_player()].get_move(game);
				game->make_move(move);
			}
			// Update reward_table
			std::vector<float> scores = game->score();
			for (int i = 0; i < scores.size(); i++)
			{
				float score = scores[i];
				agents[i].reward(score);
			}
			game->reset();
			//
			cout << "\r";
			if (i % bar_units == 0)
			{
				progress += 1;
				percentage += 2;
				cout << "  " << percentage << "% "
					 << "[" << string(progress, bar);
			}
		}
		cout << "  100%" << endl;
		total_iterations += iterations;
	}

	MinimaxAgent::MinimaxAgent(InputFormat input_format)
	{
		this->input_format = input_format;
	}

	std::vector<float> MinimaxAgent::search_move(Game *game, int &best_move)
	{
		// TODO: Research Alpha Beta pruning for multiple players

		if (game->is_finished())
		{
			return game->score(); // TODO: Maybe AI gets stuck if scores are not normalised
		}

		int next_best_move = 0;
		int cur_player = game->get_current_player();
		std::vector<float> best_score(cur_player + 1, -999999); // TODO: Better default
		int temp;

		std::vector<int> all_moves = game->get_possible_moves();
		for (int move : all_moves)
		{
			Game *new_position = game->clone();
			new_position->make_move(move);

			std::vector<bool> new_game_state = input_format.convert_input(new_position->get_input());

			if (true || cache.find(new_game_state) == cache.end()) // TODO: produces sub-optimal outputs?
			{
				cache[new_game_state] = search_move(new_position, temp);
			}
			std::vector<float> score = cache[new_game_state];
			delete new_position;

			if (score[cur_player] > best_score[cur_player])
			{
				best_score = score;
				next_best_move = move;
			}
		}

		best_move = next_best_move;
		return best_score;
	}

	int MinimaxAgent::get_move(Game *game)
	{
		if (input_format != game->get_input_format())
		{
			throw invalid_argument("Input format of game and agent do not match");
		}

		int move = -1;
		search_move(game, move);
		return move;
	}
}