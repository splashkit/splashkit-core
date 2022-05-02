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
	class OutputValue;
	class Game;

	/**
	 * @brief The format of information given to the AI to play its next move
	 *
	 */
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
		void convert_int(vector<int> input, vector<bool> *out, int index)
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
		 * @return int the last format index + 1
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
		 * @return int the format index to be used later on in other functions
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
		vector<bool> convert_input(vector<int> input)
		{
			vector<bool> out(output_width, false);
			for (int i = 0; i < format.size(); i++)
			{
				convert_int(input, &out, i);
			}
			return out;
		}

		/**
		 * @brief Gets the index of the data at the given format index. This is the index of the data in the inputted data.
		 *
		 * @param index format index: the number representing the order of when add_type was called starting at 0.
		 * @return int
		 */
		int get_index(int index) const { return indexes_out[index]; }

		/**
		 * @brief Gets the size of the data at the given format index
		 *
		 * @param index format index: the number representing the order of when add_type was called starting at 0
		 * @return int
		 */
		int get_size(int index) const { return sizes[index]; }
	};

	/**
	 * @brief The format of information produced by the AI to play its next move
	 *
	 * @see Game
	 */
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
		/**
		 * @brief Returns the total number of sections in the OutputFormat
		 *
		 * @return int the last format index + 1
		 */
		int size() { return format.size(); }

		/**
		 * @brief Gets the total expected width of the OutputValue data. Data obtained from RewardTable.get_value() should always be this size.
		 *
		 * @return int size of OutputValue
		 */
		int get_width() { return output_width; }

		/**
		 * @brief Adds a section to the output format.  \n
		 *
		 * For types Position or Category data is the length or size of the data to be outputted.  \n
		 * For Number data is the range of the number to be outputted, [0, data].  \n
		 *
		 * @param type the type of the data
		 * @param data the data for the given type, size (Position, Category) or max_val (Number)
		 * @return int the format index to be used later on in other functions
		 */
		int add_type(Type type, int data)
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

		/**
		 * @brief Get the format type at the given format index.
		 * 
		 * @param index format index: the number representing the order of when add_type was called starting at 0
		 * @return Type format type: meta data detailing how that index should be interpreted
		 */
		Type get_type(int index) const { return format[index]; }

		/**
		 * @brief Get the output index of the data at the given format index.
		 * 
		 * @param index format index: the number representing the order of when add_type was called starting at 0
		 * @return int output index: the first index correspoding to the given format index
		 */
		int get_output_index(int index) const { return indexes[index]; }

		/**
		 * @brief Get the output info of the data at the given format index.
		 * 
		 * For Position or Category types output info is the length or size of the data to be outputted.  \n
		 * For Number type output info is the range of the number to be outputted, [0, data].  \n
		 * 
		 * @param index format index: the number representing the order of when add_type was called starting at 0
		 * @return int the data for the given type, size (Position, Category) or max_val (Number)
		 */
		int get_output_info(int index) const { return f_data[index]; }
	};

	/**
	 * @brief The set of reward values produced by an AI, detailing what it thinks about each possible move.
	 *
	 * @see OutputFormat
	 */
	class OutputValue
	{
	private:
		OutputFormat *format;

		vector<float> value;
		vector<int> indexes; // indexes to affect during reward/punishment

		float learning_rate = 0.1f; // learning rate, how fast the ai learns
		float discount_rate = 0.9f; // discount rate, how much future reward is considered
	public:
		/// Not to be used, only for vector initialisation.
		OutputValue() {}

		OutputValue(OutputFormat *format)
		{
			this->format = format;
			value = vector<float>(format->get_width(), 0.5f);
		}

		OutputValue(OutputFormat *format, vector<float> value)
		{
			this->format = format;
			this->value = value;
		}

		/**
		 * @brief Gets the index of the maximum reward value for the given format index.
		 *
		 * @param index The format index indicating which subsection of the reward values to consider.
		 * @param filter A whitelist filter to filter the reward values based on the valid indexes to consider. TODO: allow none or null values
		 * @param random The global random to be passed down, determines if the move should be randomly chosen.
		 * @return int The index of the maximum reward value.
		 */
		int get_max_position(int index, vector<int> filter, bool random)
		{
			if (format->get_type(index) != OutputFormat::Type::Position)
				throw invalid_argument("Format at index is not of type Position!");
			index = format->get_output_index(index); // Grab the starting index for the given position data
			if (random)
			{
				int out = filter[rnd(filter.size())];
				// update reward_table
				to_update(out);
				return out;
			}
			float max = value[index + filter[0]];
			int max_pos = filter[0];
			for (int i = 1; i < filter.size(); i++)
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

		/**
		 * @brief Gets the number in the data at the given format index.
		 *
		 * @param data The AI data to retrieve the number from.
		 * @param index The format index indicating which subsection of values the number is located
		 * @param random The global random passed down, determines if the number should be randomly chosen.
		 * @return float
		 */
		float process_output_number(int index, bool random)
		{
			if (format->get_type(index) != OutputFormat::Type::Number)
				throw invalid_argument("Format at index is not of type Number!");
			to_update(format->get_output_index(index));									// Tells the AI that the number was retrieved and should be updated during reward/punishment
			return (random ? rnd() : value[format->get_output_index(index)] * format->get_output_info(index)); // Scale the number to the previously given range [0, f_data[index]]
		}

		// adds an index to be updated during reward/punishment, TODO: extra directional information
		void to_update(int index)
		{
			indexes.push_back(index);
		}

		void update(float reward, OutputValue *next_move)
		{
			for (int i = 0; i < indexes.size(); i++)
			{
				if (next_move == NULL) {
					value[indexes[i]] = reward; // Next move is game over with this reward. i.e. instant win/instant loss
					continue;
				}

				// QLearning method, using the next move as future reward
				value[indexes[i]] += learning_rate * (reward + discount_rate * next_move->value[indexes[i]] - value[indexes[i]]);
			}
			indexes.clear();
		}

		float at(int index) const { return value[index]; }
		float operator[](int index) const { return value[index]; }
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

	/**
	 * @brief A HashMap wrapper that allows game states to be mapped to reward values.
	 *
	 * TODO: Consider moving InputForamt and OutputFormat into this class as subclasses as they used exclusively to facilitate this class right now.
	 * Keys should be created using InputFormat
	 * Values should be created using OutputFormat
	 *
	 * This class also allows OutputFormat to provide extra meta data after the reward value is retrieved.
	 * This information is used to determine which values are used to determine the final AI move, and reward them accordingly.
	 *
	 * @see InputFormat
	 * @see OutputFormat
	 */
	class RewardTable
	{
	private:
		OutputFormat out_format;
		unordered_map<vector<bool>, OutputValue> reward_table;

	public:
		RewardTable(OutputFormat out_format)
		{
			this->out_format = out_format;
		}

		/**
		 * @brief Gets the q value object at the given game state or generates a new one if it doesn't exist.
		 *
		 * @see InputFormat
		 * @param key the converted game state, generated by `InputFormat::convert_input()`
		 *
		 * @see OutputFormat
		 * @return OutputValue* the AI reward values for the given board state in the requested OutputFormat
		 */
		OutputValue *get_value(vector<bool> key)
		{
			// log(INFO, "RewardTable::get_value");
			if (reward_table.find(key) == reward_table.end()) // key not found
			{
				// log(INFO, "RewardTable::get_value - creating new q_value");
				reward_table[key] = OutputValue(&out_format);
			}
			return &reward_table[key];
		}

		/// used for testing should not be called on the hot path
		OutputValue *get_value(Game *game);
	};

	/**
	 * @brief The Game API to be implemented by the user so that their Game can utilise the Agents
	 *
	 */
	class Game
	{
	public:
		/**
		 * @brief Get the current player's index. Each player has a unique index from `[0, max_players)`
		 *
		 * @return int player index
		 */
		virtual int get_current_player() { throw logic_error("get_current_player(): Function needs to be overridden; should return the current player or 0 if single player"); }

		/**
		 * @brief Get the score of the game for each player. Negative scores for losing players, positive scores for winning. Draws are 0.
		 *
		 * @return vector<float> the score of each player retrieved by their player index
		 */
		virtual vector<float> score() { throw logic_error("score(): Function needs to be overridden; should return a vector with player indexes mapped to score at the end of the game"); }

		/// TODO: Move to documentation of InputFormat as example
		// The number of different 'pieces' that can exist on the field throughout any game
		// e.g. Tic-Tac-Toe [Empty + O + X = 2], Chess [Empty + (Pawn + Bishop + Knight + Rook + Queen + King) * 2 Players = 12]
		// Pong [Empty + Ball/Paddle = 1]
		// virtual int get_max_board_index() { throw logic_error("get_max_board_index(): Function needs to be overridden; should return the highest number possible in get_board()"); }

		/// TODO: move comment to documentation of InputFormat as example
		// The number of tiles on the board e.g. Tic-Tac-Toe = 3*3 = 9, Chess = 8*8 = 64
		// virtual int get_board_size() { throw logic_error("get_board_size(): Function needs to be overridden; should return the length of get_board()"); }

		/**
		 * @brief Returns an InputFormat that can be used by an agent to understand the current state of the game
		 *
		 * @see InputFormat
		 * @return InputFormat the format of information given to the AI to play its next move
		 */
		virtual InputFormat get_input_format() { throw logic_error("get_input_format(): Function needs to be overridden; should return an InputFormat that can be used by a player to understand the current state of the game"); }

		/**
		 * @brief Returns an OutputFormat that can represent any possible move
		 *
		 * @see OutputFormat
		 * @return OutputFormat the format of information produced by the AI to play its next move
		 */
		virtual OutputFormat get_output_format() { throw logic_error("get_output_format(): Function needs to be overridden; should return an OutputFormat that can represent any possible move"); }

		/**
		 * @brief Gets the list possible moves that can be played in the current state of the game
		 *
		 * @return vector<int> list of possible move indexes
		 */
		virtual vector<int> get_possible_moves() { throw logic_error("get_possible_moves(): Function needs to be overridden; should return a vector of all the possible moves"); }

		/**
		 * @brief Plays a move on the board.
		 *
		 * Moves should always be retrieved from `get_possible_moves()` before calling this function.
		 *
		 * @param move the move index to play
		 */
		virtual void make_move(int move) { throw logic_error("make_move(): Function needs to be overridden; should take a move and update the board"); }

		/**
		 * @brief Checks if the game is finished
		 *
		 * @return true if the game is over
		 * @return false if moves can still be played
		 */
		virtual bool is_finished() { throw logic_error("is_finished(): Function needs to be overridden; should return true if the game is over"); }

		/**
		 * @brief Resets the game state to the initial state. Used during AI self-play, must be robust to many calls.
		 *
		 */
		virtual void reset() { throw logic_error("reset(): Function needs to be overridden; should reset the game to its initial state"); }

		/**
		 * @brief Creates a new Game object of the super type. The new object should be a deep copy of the current game with the same board state, current players, and random seed (if used).
		 *
		 * Object is deleted after use, use `new SuperTypeGame()` to create the pointer.
		 * Used with Minimax Agent to check future possible moves, override not required for other agents.
		 *
		 * @return Game*
		 */
		virtual Game *clone() { throw logic_error("clone(): Function needs to be overridden; should create a new game object copying the current state"); }

		/**
		 * @brief Function used to convert AI move data into move index.
		 * Must utilise OutputFormat functions to decode OutputValue into int.
		 *
		 * Used by TableAgent, override not required for other agents.
		 *
		 * @see OutputFormat
		 * @param output to be passed into OutputFormat functions contains the move data
		 * @param random to be passed into OutputFormat functions determines if the move is random (during learning to explore possible options)
		 * @return int the move value to be played, must return a value of get_possible_moves()
		 */
		virtual int convert_output(OutputValue *output, bool random) { throw logic_error("convert_output(): Function needs to be overridden; should return the index of the move that the output represents"); }

		/**
		 * @brief Get the current game state based on InputFormat.
		 *
		 * Will be later converted to a machine readable format using InputFormat.
		 *
		 * @see InputFormat
		 * @return vector<int> the current game state
		 */
		virtual vector<int> get_input() { throw logic_error("get_input(): Function needs to be overridden; should return a vector following the submitteed input format"); }
	};

	/**
	 * @brief Uses a reward table to determine the best move for the current state of the game.
	 * The table is generated based on wins and losses, if the agent wins a game, all the moves it played are given a reward and are played more often in the future.
	 *
	 * The agent uses Reinforcement Learning concepts and is based on QLearning, it plays random games to attempt to find optimal moves.
	 * The agent may not converge to the optimal move, but will eventually reach a point where it has a good understanding of the game.
	 *
	 * Agent Information
	 * Training: Very High. It is recommended to train over game amounts in units of millions of games.
	 * Memory: Very High. It stores all board states it has ever encountered.
	 * Move Time: Very Fast. It can compute it's move in O(1) time.
	 * Performance: Unknown. TODO: more testing required
	 * Complexity: Very High. Requires most API functions to be implemented
	 */
	class TableAgent
	{
	public:
		class SelfPlay
		{
		private:
			InputFormat *input_format;
			OutputFormat *out_format;

			RewardTable *reward_table;
			vector<OutputValue *> move_history; // Store the q_values used for the last game
		public:
			float learning_rate = 0.1f;	  // How much to change the q_value
			float discount_factor = 0.9f; // Used for future state predictions
			float epsilon = 0.1f;
			int depth = 0; // The number of moves to look ahead

			SelfPlay(RewardTable *reward_table, InputFormat *input_format, OutputFormat *out_format)
			{
				this->reward_table = reward_table;
				this->input_format = input_format;
				this->out_format = out_format;
			}

			int get_move(Game *game)
			{
				vector<bool> input = input_format->convert_input(game->get_input()); // convert input to boolean for neural networks / ease of hashing
				OutputValue *output = reward_table->get_value(input);				 // get the q_value for the current state
				move_history.push_back(output);										 // remember that we took this move for reward if we win or lose
				return game->convert_output(output, rnd() < epsilon);				 // convert the q_value into a move, if epsilon take a random move (e.g. take the highest value (best) move)
			}

			/**
			 * @brief Rewards all the moves taken in the game. If we won the game we give a reward so that we try to take that move again.
			 *
			 * @param score The total score of this agent
			 */
			void reward(float score)
			{
				for (int i = 0; i < move_history.size(); i++)
				{
					move_history[i]->update(score, i == move_history.size() - 1 ? NULL : move_history[i + 1]);
				}
				move_history.clear();
			}
		};

	private:
		Game *game;
		InputFormat input_format;
		OutputFormat out_format;

	public:
		RewardTable *reward_table;

		TableAgent(Game *game)
		{
			this->game = game;
			input_format = game->get_input_format();
			out_format = game->get_output_format();
			reward_table = new RewardTable(out_format);
		}

		/**
		 * @brief Get the best move based on the previous training.
		 *
		 * @param game The current game state
		 * @return int the move value to play, used by game.make_move()
		 */
		int get_move(Game *game)
		{
			vector<bool> input = input_format.convert_input(game->get_input());
			OutputValue *output = reward_table->get_value(input);
			return game->convert_output(output, false);
		}

		void train(int player_count, int iterations)
		{
			for (int i = 0; i < iterations; i++)
			{
				vector<TableAgent::SelfPlay> agents;
				for (int i = 0; i < player_count; i++)
				{
					agents.push_back(TableAgent::SelfPlay(reward_table, &input_format, &out_format)); // generate the agents to play the game
				}
				while (!game->is_finished())
				{
					int move = agents[game->get_current_player()].get_move(game);
					game->make_move(move);
				}
				// Update reward_table
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

	/**
	 * @brief Uses brute force to compute the optimal move. This agent will always perform the optimal move. You may use it for small games that require strong AI's.
	 *
	 * Agent Information
	 * Training: None
	 * Memory: Medium-High. It will store game states it encounters during computation (not yet implemented). TODO: Add transposition tables
	 * Move Time: Very Slow. It can take O(n*m) time to compute a move, where n is the number of moves available per step, and m is the step count of the game.
	 * Performance: Optimal. recommended for impossible AI
	 * Complexity: Very Low. Requires clone(), score(), is_finished(), get_current_player(), get_possible_moves(), and make_move() to be implemented.
	 *
	 * TODO: add global option for transposition tables. Where the table is stored between move calcs.
	 */
	class MiniMaxAgent
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
				return game->score(); // TODO: Maybe AI gets stuck if scores are not normalised
			}

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