#ifndef machine_learning_h
#define machine_learning_h

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include "random.h"
#include "terminal.h"
using namespace std;

namespace splashkit_lib
{
	class QValue;
	class Game;

	class InputFormat
	{
	public:
		enum class Type
		{
			Board,
			Current_Player,
			Number, // generic integer
		};

	private:
		vector<Type> format;	 // size n
		vector<int> max_vals;	 // size n
		vector<int> sizes;		 // size n
		vector<int> indexes_in;	 // size n
		vector<int> indexes_out; // size n
		int input_width = 0;	 // sum sizes
		int output_width = 0;	 // sum (sizes * max_vals)

		// convert list of integers to categorical vector, assuming out starts as all 0/false
		void convert_int(vector<int> input, vector<bool> *out, int index) const
		{
			for (int i = 0; i < sizes[index]; i++)
			{
				if (input[i] != 0)
				{
					out->at(indexes_out[index] + i * max_vals[index] + input[i] - 1) = true;
				}
			}
		}

	public:
		/**
		 * @brief Returns the total number of sections in the InputFormat
		 *
		 * @return int the last type index + 1
		 */
		int size() const { return format.size(); }
		/**
		 * @brief Gets the total width of the inputted data. Data obtained from game.get_input() should always be this size.
		 *
		 * @return int game.get_input().size()
		 */
		int get_width() const { return input_width; }
		/**
		 * @brief Gets the total width of the outputted data. Data obtained from convert_input() should always be this size.
		 *
		 * @return int convert_input().size()
		 */
		int get_out_width() const { return output_width; }

		/**
		 * @brief Adds a section to the input format.
		 *
		 * @param type the type of the data (currently unused)
		 * @param size the length of the data
		 * @param max_val the maximum value (inclusive) that could be contained within the data.
		 * This should be the maximum value for all elements for the given data segment.
		 * @return int the type index to be used later on in other functions
		 */
		int add_type(Type type, int size, int max_val)
		{
			if (size < 1)
				throw invalid_argument("Size must be greater than 0!");
			if (max_val < 1)
				throw invalid_argument("Max Value must be greater than 0!");
			format.push_back(type);				 // How to interpret the data
			sizes.push_back(size);				 // How many values to read
			max_vals.push_back(max_val);		 // The range of the given values, with a domain of [0, max_val] inclusive
			indexes_in.push_back(input_width);	 // The starting index for the given data in int form
			indexes_out.push_back(output_width); // The starting index for the given data in bool form
			input_width += size;				 // The total width of the inputted data
			output_width += size * max_val;		 // The total width of the outputted data
			return format.size() - 1;
		}

		/**
		 * @brief Converts the input data into boolean format for ease of use in neural networks
		 *
		 * @param input game.get_input()
		 * @return vector<bool> a boolean representation of the input data
		 */
		vector<bool> convert_input(vector<int> input) const
		{
			vector<bool> out(output_width, false);
			for (int i = 0; i < format.size(); i++)
			{
				convert_int(input, &out, i);
			}
			return out;
		}

		/**
		 * @brief Gets the index of the data at the given type index. This is the index of the data in the inputted data.
		 *
		 * @param index type index: the number representing the order of when add_type was called starting at 0.
		 * @return int
		 */
		int get_index(int index) const { return indexes_out[index]; }

		/**
		 * @brief Gets the size of the data at the given type index
		 *
		 * @param index type index: the number representing the order of when add_type was called starting at 0
		 * @return int
		 */
		int get_size(int index) const { return sizes[index]; }
	};

	class OutputFormat
	{
	public:
		enum class Type
		{
			Position,
			Number,
			Category
		};

	private:
		vector<Type> format;
		vector<int> f_data;
		vector<int> indexes;
		int output_width = 0;

	public:
		int size() { return format.size(); }
		int get_width() { return output_width; }

		void add_type(Type type, int data)
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
		}

		int get_max_position(QValue *data, int index, vector<int> filter, bool random);

		float process_output_number(QValue *data, int index, bool random);
	};

	class QValue
	{
	private:
		vector<float> value;
		vector<int> indexes; // indexes to affect during reward/punishment
							 // vector<float> reward_mod; // reward method for each index
	public:
		QValue() {}
		QValue(OutputFormat *format)
		{
			value = vector<float>(format->get_width(), 0.5f);
		}

		QValue(vector<float> value)
		{
			this->value = value;
		}

		// adds an index to be updated during reward/punishment
		void to_update(int index)
		{
			indexes.push_back(index);
		}

		void update(float reward)
		{
			for (int i = 0; i < indexes.size(); i++)
			{
				value[indexes[i]] += reward;
			}
			indexes.clear();
		}

		float operator[](int index) const { return value[index]; }
		float at(int index) const { return value[index]; }
		string to_string() const
		{
			stringstream ss;
			ss << "[ ";
			for (float v : value)
			{
				ss << v << " ";
			}
			ss << "]";
			return ss.str();
		}
	};

	class QTable
	{
	private:
		OutputFormat *format;
		unordered_map<vector<bool>, QValue> q_table;

	public:
		QTable(OutputFormat *format)
		{
			this->format = format;
		}

		QValue *get_q_value(vector<bool> key)
		{
			// log(INFO, "QTable::get_q_value");
			if (q_table.find(key) == q_table.end()) // key not found
			{
				// log(INFO, "QTable::get_q_value - creating new q_value");
				q_table[key] = QValue(format);
			}
			return &q_table[key];
		}

		QValue *get_q_value(Game *game);
	};

	class Game
	{
	public:
		virtual int get_current_player() { throw logic_error("get_current_player(): Function needs to be overridden; should return the current player or 0 if single player"); }
		virtual vector<float> score() { throw logic_error("score(): Function needs to be overridden; should return a vector with player indexes mapped to score at the end of the game"); }

		// The number of different 'pieces' that can exist on the field throughout any game
		// e.g. Tic-Tac-Toe [Empty + O + X = 2], Chess [Empty + (Pawn + Bishop + Knight + Rook + Queen + King) * 2 Players = 12]
		// Pong [Empty + Ball/Paddle = 1]
		// virtual int get_max_board_index() { throw logic_error("get_max_board_index(): Function needs to be overridden; should return the highest number possible in get_board()"); }

		// The number of tiles on the board e.g. Tic-Tac-Toe = 3*3 = 9, Chess = 8*8 = 64
		// virtual int get_board_size() { throw logic_error("get_board_size(): Function needs to be overridden; should return the length of get_board()"); }

		virtual InputFormat *get_input_format() { throw logic_error("get_input_format(): Function needs to be overridden; should return an InputFormat that can be used by a player to understand the current state of the game"); }
		virtual OutputFormat *get_output_format() { throw logic_error("get_output_format(): Function needs to be overridden; should return an OutputFormat that can represent any possible move"); }
		// virtual vector<int> get_board() { throw logic_error("get_board(): Function needs to be overridden; should return a vector of all the tiles on the board"); }

		virtual vector<int> get_possible_moves() { throw logic_error("get_possible_moves(): Function needs to be overridden; should return a vector of all the possible moves"); }
		virtual void make_move(int move) { throw logic_error("make_move(): Function needs to be overridden; should take a move and update the board"); }

		virtual bool is_finished() { throw logic_error("is_finished(): Function needs to be overridden; should return true if the game is over"); }
		virtual void reset() { throw logic_error("reset(): Function needs to be overridden; should reset the game to its initial state"); }
		virtual Game *clone() { throw logic_error("clone(): Function needs to be overridden; should create a new game object copying the current state"); }
		virtual int convert_output(QValue *output, bool random) { throw logic_error("convert_output(): Function needs to be overridden; should return the index of the move that the output represents"); }
		virtual vector<int> get_input() { throw logic_error("get_input(): Function needs to be overridden; should return a vector following the submitteed input format"); }
	};

	class QAgent
	{
	private:
		InputFormat *input_format;
		OutputFormat *out_format;

		QTable *q_table;
		vector<QValue *> q_history; // Store the q_values used for the last game
	public:
		float learning_rate = 0.1f;
		float discount_factor = 0.9f;
		float epsilon = 0.1f;

		QAgent(QTable *q_table, InputFormat *input_format, OutputFormat *out_format)
		{
			this->q_table = q_table;
			this->input_format = input_format;
			this->out_format = out_format;
		}

		int get_move(Game *game)
		{
			vector<bool> input = input_format->convert_input(game->get_input());
			QValue *q_output = q_table->get_q_value(input);
			q_history.push_back(q_output);
			return game->convert_output(q_output, rnd() < epsilon);
		}

		void reward(float score)
		{
			for (QValue *q : q_history)
			{
				q->update(score);
			}
			q_history.clear();
		}
	};

	class QTrainer
	{
	private:
		Game *game;

	public:
		QTable *q_table;

		QTrainer(Game *game)
		{
			this->game = game;
			q_table = new QTable(game->get_output_format());
		}

		void train(int player_count, int iterations)
		{
			for (int i = 0; i < iterations; i++)
			{
				vector<QAgent> agents;
				for (int i = 0; i < player_count; i++)
				{
					agents.push_back(QAgent(q_table, game->get_input_format(), game->get_output_format())); // generate the agents to play the game

					// agents[i].epsilon = 0.3f; // Agents have high chance of playing random move while training
				}
				while (!game->is_finished())
				{
					int move = agents[game->get_current_player()].get_move(game);
					game->make_move(move);
				}
				// Update q_table
				vector<float> scores = game->score();
				for (int i = 0; i < scores.size(); i++)
				{
					float score = scores[i];
					agents[i].reward(score);
				}
				game->reset();
			}
		}
	};

	class MiniMax
	{
	public:
		static int get_move(Game *game)
		{
			int move = -1;
			search_move(game, move);
			return move;
		}

		static vector<float> search_move(Game *game, int &best_move)
		{
			// TODO: Research Alpha Beta pruning for multiple players

			if (game->is_finished())
			{
				return game->score(); // TODO: Maybe AI gets stuck in cooperation trap
			}							  // Convert to relative score?? Index in sorted array of scores?

			int next_best_move = 0;
			int cur_player = game->get_current_player();
			vector<float> best_score(cur_player + 1, -999999); // TODO: Better default
			int temp;

			vector<int> all_moves = game->get_possible_moves();
			for (int move : all_moves)
			{
				Game *new_position = game->clone();
				new_position->make_move(move);
				vector<float> score = search_move(new_position, temp);
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
	};
}

#endif