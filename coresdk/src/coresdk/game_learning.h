#ifndef game_learning_h
#define game_learning_h

#include "random.h"
#include "utility_functions.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

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
			Player,
			Number, // generic integer
		};

	private:
		std::vector<Type> format;	 // size n
		std::vector<int> max_vals;	 // size n
		std::vector<int> sizes;		 // size n
		std::vector<int> indexes_in;	 // size n
		std::vector<int> indexes_out; // size n
		int input_width = 0;	 // sum sizes
		int output_width = 0;	 // sum (sizes * max_vals)

		// convert list of integers to categorical std::vector, assuming out starts as all 0/false
		void convert_int(std::vector<int> input, std::vector<bool> *out, int index);
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
		 * Example Tic-Tac-Toe: 
		 * Add Board type of 
		 * - size = 3*3 = 9
		 * - max_val = Empty + O + X = 3
		 * Add player type of
		 * - size = 1, Player is almost always represented by 1 number
		 * - max_val = O + X = 2
		 * 
		 * Example Chess:
		 * Add Board type of
		 * - size = 8*8 = 64
		 * - max_val = Empty + (Pawn + Bishop + Knight + Rook + Queen + King) * 2 Players = 12
		 * Add player type of
		 * - size = 1
		 * - max_val = White or Black = 2
		 *
		 * @param type the type of the data (currently unused)
		 * @param size the length of the data
		 * @param max_val the maximum value (exclusive) that could be contained within the data.
		 * This should be the maximum value for all elements for the given data segment.
		 * @return int the format index to be used later on in other functions
		 */
		int add_type(Type type, int size, int max_val);

		/**
		 * @brief Converts the input data into boolean format for ease of use in neural networks
		 *
		 * @param input game.get_input()
		 * @return std::vector<bool> a boolean representation of the input data
		 */
		std::vector<bool> convert_input(std::vector<int> input);

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

		bool operator==(const InputFormat &other) const;
		bool inline operator!=(const InputFormat &other) const { return !(*this == other); };
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
			Category,
		};

	private:
		std::vector<Type> format;
		std::vector<int> f_data;
		std::vector<int> indexes;
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
		int add_type(Type type, int data);

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
		 * @return int output index: the first index corresponding to the given format index
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
		std::vector<float> value;

		// reward/punishment
		std::vector<int> indexes; // indexes to affect during reward/punishment
	public:
		/// Not to be used, only for std::vector initialisation.
		OutputValue() {}

		OutputValue(int width);

		/**
		 * @brief Gets the index of the maximum reward value for the given format index.
		 *
		 * @param index The format index indicating which subsection of the reward values to consider.
		 * @param filter A whitelist filter to filter the reward values based on the valid indexes to consider. TODO: allow none or null values
		 * @param random The global random to be passed down, determines if the move should be randomly chosen.
		 * @return int The index of the maximum reward value.
		 */
		int get_max_position(OutputFormat format, int index, const std::vector<int> filter, bool random);

		/**
		 * @brief Gets the number in the data at the given format index.
		 *
		 * @param data The AI data to retrieve the number from.
		 * @param index The format index indicating which subsection of values the number is located
		 * @param random The global random passed down, determines if the number should be randomly chosen.
		 * @return float
		 */
		float process_output_number(OutputFormat format, int index, bool random);

		/**
		 * @brief adds an index to be updated during reward/punishment
		 * 
		 * TODO: add the ability to determine the format index of this output index
		 * TODO: make private as it should not be accessed elsewhere
		 * 
		 * @param index output index
		 */
		void to_update(int index) { indexes.push_back(index); }

		/**
		 * @brief Performs an update on the reward values, uses Q-Learning algorithm to calculate the new reward values.
		 * 
		 * Uses temporal difference to obtain a reward value after the game is finished.
		 * 
		 * @param learning_rate
		 * @param discount_factor
		 * @param reward 
		 * @param next_move 
		 */
		void update(float learning_rate, float discount_factor, float reward, OutputValue *next_move);

		/**
		 * @brief Resets the tracked reward values for use in temporal difference.
		 * 
		 * This needs to be called sometime between one game finishing and another starting.
		 */
		void reset() { indexes.clear(); }

		float at(int index) const { return value[index]; }
		float operator[](int index) const { return value[index]; }
		string to_string() const;
	};

	/**
	 * @brief A HashMap wrapper that allows game states to be mapped to reward values.
	 *
	 * TODO: Consider moving InputFormat and OutputFormat into this class as subclasses as they used exclusively to facilitate this class right now.
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
		std::unordered_map<std::vector<bool>, OutputValue> reward_table;

		float learning_rate;
		float discount_rate;
		int width;
	public:
		RewardTable(int width);

		/**
		 * @brief Gets the q value object at the given game state or generates a new one if it doesn't exist.
		 *
		 * @see InputFormat
		 * @param key the converted game state, generated by `InputFormat::convert_input()`
		 *
		 * @see OutputFormat
		 * @return OutputValue* the AI reward values for the given board state in the requested OutputFormat
		 */
		OutputValue &get_value(std::vector<bool> &key);

		/// used for testing should not be called on the hot path
		OutputValue &get_value(Game *game);
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
		virtual int get_current_player() { throw std::logic_error("get_current_player(): Function needs to be overridden; should return the current player or 0 if single player"); }

		/**
		 * @brief Get the score of the game for each player. Negative scores for losing players, positive scores for winning. Draws are 0.
		 *
		 * @return std::vector<float> the score of each player retrieved by their player index
		 */
		virtual std::vector<float> score() { throw std::logic_error("score(): Function needs to be overridden; should return a vector with player indexes mapped to score at the end of the game"); }

		/**
		 * @brief Returns an InputFormat that can be used by an agent to understand the current state of the game
		 *
		 * @see InputFormat
		 * @return InputFormat the format of information given to the AI to play its next move
		 */
		virtual InputFormat &get_input_format() { throw std::logic_error("get_input_format(): Function needs to be overridden; should return an InputFormat that can be used by a player to understand the current state of the game"); }

		/**
		 * @brief Returns an OutputFormat that can represent any possible move
		 *
		 * @see OutputFormat
		 * @return OutputFormat the format of information produced by the AI to play its next move
		 */
		virtual OutputFormat &get_output_format() { throw std::logic_error("get_output_format(): Function needs to be overridden; should return an OutputFormat that can represent any possible move"); }

		/**
		 * @brief Gets the list possible moves that can be played in the current state of the game
		 *
		 * @return std::vector<int> list of possible move indexes
		 */
		virtual vector<int> get_possible_moves() { throw std::logic_error("get_possible_moves(): Function needs to be overridden; should return a vector of all the possible moves"); }

		/**
		 * @brief Plays a move on the board.
		 *
		 * Moves should always be retrieved from `get_possible_moves()` before calling this function.
		 *
		 * @param move the move index to play
		 */
		virtual void make_move(int move) { throw std::logic_error("make_move(): Function needs to be overridden; should take a move and update the board"); }

		/**
		 * @brief Checks if the game is finished
		 *
		 * @return true if the game is over
		 * @return false if moves can still be played
		 */
		virtual bool is_finished() { throw std::logic_error("is_finished(): Function needs to be overridden; should return true if the game is over"); }

		/**
		 * @brief Resets the game state to the initial state. Used during AI self-play, must be robust to many calls.
		 *
		 */
		virtual void reset() { throw std::logic_error("reset(): Function needs to be overridden; should reset the game to its initial state"); }

		/**
		 * @brief Creates a new Game object of the super type. The new object should be a deep copy of the current game with the same board state, current players, and random seed (if used).
		 *
		 * Object is deleted after use, use `new SuperTypeGame()` to create the pointer.
		 * Used with Minimax Agent to check future possible moves, override not required for other agents.
		 *
		 * @return Game*
		 */
		virtual Game *clone() { throw std::logic_error("clone(): Function needs to be overridden; should create a new game object copying the current state"); }

		/**
		 * @brief Function used to convert AI move data into move index.
		 * Must utilise OutputFormat functions to decode OutputValue into int.
		 *
		 * Used by QAgent, override not required for other agents.
		 *
		 * @see OutputFormat
		 * @param output to be passed into OutputFormat functions contains the move data
		 * @param random to be passed into OutputFormat functions determines if the move is random (during learning to explore possible options)
		 * @return int the move value to be played, must return a value of get_possible_moves()
		 */
		virtual int convert_output(OutputValue &output, bool random) { throw std::logic_error("convert_output(): Function needs to be overridden; should return the index of the move that the output represents"); }

		/**
		 * @brief Get the current game state based on InputFormat.
		 *
		 * Will be later converted to a machine readable format using InputFormat.
		 *
		 * @see InputFormat
		 * @return std::vector<int> the current game state
		 */
		virtual std::vector<int> get_input() { throw std::logic_error("get_input(): Function needs to be overridden; should return a vector following the submitted input format"); }
	};

	struct Agent
	{
		virtual int get_move(Game *game) = 0;
		virtual void train(Game *game, int player_count, int iterations) {};
	};

	/**
	 * @brief Uses a reward table to determine the best move for the current state of the game.
	 * The table is generated based on wins and losses, if the agent wins a game, all the moves it played are given a reward and are played more often in the future.
	 *
	 * The agent uses Reinforcement Learning concepts and is based on QLearning, it plays random games to attempt to find optimal moves.
	 * The agent may not converge to the optimal move, but will eventually reach a point where it has a good understanding of the game.
	 *
	 * This agent may not know what to do in all situations, it will play randomly in obscure positions.
	 *
	 * Agent Information
	 * Training: Very High. It is recommended to train over game amounts in units of millions of games.
	 * Memory: Very High. It stores all board states it has ever encountered.
	 * Move Time: Very Fast. It can compute it's move in O(1) time.
	 * Performance: Unknown. TODO: more testing required
	 * Complexity: Very High. Requires most API functions to be implemented
	 */
	class QAgent : public Agent
	{
	private:
		class SelfPlay; // Internally used class for training

		float learning_rate = 0.1f;	  // How much to change the q_value
		float discount_factor = 0.9f; // Used for future state predictions
	public:
		RewardTable *reward_table;
		int total_iterations = 0;

		QAgent(OutputFormat &out_format);

		/**
		 * @brief Get the best move based on the previous training.
		 *
		 * @param game The current game state
		 * @return int the move value to play, used by game.make_move()
		 */
		int get_move(Game *game) override;

		void train(Game *game, int player_count, int iterations) override;
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
	class MinimaxAgent : public Agent
	{
	private:
		InputFormat input_format;

		std::unordered_map<std::vector<bool>, std::vector<float>> cache; // transposition/memoisation table

		/**
		 * @brief Find the best move for the current game state.
		 * 
		 * @param game 
		 * @param best_move 
		 * @return std::vector<float> 
		 */
		std::vector<float> search_move(Game *game, int &best_move);
	public:
		MinimaxAgent(InputFormat input_format);

		int get_move(Game *game) override;
	};

	class RandomAgent : public Agent
	{
		int prev_move = 0;
		float prob = 0; // probability of playing the same move again
	public:
		RandomAgent(float prob = 0.0f) { this->prob = prob; }

		int get_move(Game *game) override
		{
			std::vector<int> moves = game->get_possible_moves();
			if (moves.size() == 1)
				return moves[0];
			if (rnd() < prob || moves.size() <= prev_move)
				prev_move = rnd(0, moves.size());
			return moves[prev_move];
		}
	};
}

#endif