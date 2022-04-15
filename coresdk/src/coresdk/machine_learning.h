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

	// InputFormat

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
		int board_size;
		vector<Type> format;
		vector<int> f_data;
		vector<int> indexes;
		int output_width = 0;

	public:
		OutputFormat(int board_size)
		{
			this->board_size = board_size;
		}

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

		/*
		float process_output_number(QValue &output, int index)
		{
			if (format[index] != Type::Number)
				throw invalid_argument("Format at index is not of type Number!");
			int out_index = indexes[index];
			return output[out_index] * f_data[index];
		} //*/
	};

	class QValue
	{
	private:
		vector<float> value;
		vector<int> indexes; // indexes to affect during reward/punishment
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

		float operator[](int index) { return value[index]; }
		float at(int index) { return value[index]; }
		string to_string()
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
	};

	class Game
	{
	public:
		virtual int get_current_player() { return 0; }
		virtual inline vector<float> score() { return score(this); }
		virtual vector<float> score(Game* game) { throw logic_error("score(): Function needs to be overridden; should return a vector with player indexes mapped to score at the end of the game"); }

		// The number of different 'pieces' that can exist on the field throughout any game
		// e.g. Tic-Tac-Toe [Empty + O + X = 2], Chess [Empty + (Pawn + Bishop + Knight + Rook + Queen + King) * 2 Players = 12]
		// Pong [Empty + Ball/Paddle = 1]
		virtual int get_max_board_index() { throw logic_error("get_max_board_index(): Function needs to be overridden; should return the highest number possible in get_board()"); }

		// The number of tiles on the board e.g. Tic-Tac-Toe = 3*3 = 9, Chess = 8*8 = 64
		virtual int get_board_size() { throw logic_error("get_board_size(): Function needs to be overridden; should return the length of get_board()"); }

		virtual OutputFormat *get_output_format() { throw logic_error("get_output_format(): Function needs to be overridden; should return an OutputFormat that can represent any possible move"); }
		virtual vector<int> get_board() { throw logic_error("get_board(): Function needs to be overridden; should return a vector of all the tiles on the board"); }

		virtual inline vector<int> get_possible_moves() { return get_possible_moves(get_board(), get_current_player()); }
		virtual vector<int> get_possible_moves(vector<int> board, int cur_player) { throw logic_error("get_possible_moves(): Function needs to be overridden; should return a vector of all the possible moves"); }
		virtual void make_move(int move) { throw logic_error("make_move(): Function needs to be overridden; should take a move and update the board"); }
		
		virtual bool is_finished() { throw logic_error("is_finished(): Function needs to be overridden; should return true if the game is over"); }
		virtual void reset() { throw logic_error("reset(): Function needs to be overridden; should reset the game to its initial state"); }
		virtual Game* clone() { throw logic_error("clone(): Function needs to be overridden; should create a new game object copying the current state"); }
		virtual int convert_output(QValue *output, bool random) { throw logic_error("convert_output(): Function needs to be overridden; should return the index of the move that the output represents"); }

		// convert board to categorical vector
		vector<bool> convert_board()
		{
			vector<int> board = get_board();
			vector<bool> new_board(board.size() * get_max_board_index(), false);
			for (int i = 0; i < board.size(); i++)
			{
				if (board[i] != 0)
				{
					new_board[i * get_max_board_index() + board[i] - 1] = true;
				}
			}
			return new_board;
		}
	};

	class QAgent
	{
	private:
		OutputFormat *out_format;

		QTable *q_table;
		vector<QValue *> q_history; // Store the q_values used for the last game
	public:
		float learning_rate = 0.1f;
		float discount_factor = 0.9f;
		float epsilon = 0.1f;

		QAgent(QTable *q_table, OutputFormat *out_format)
		{
			this->q_table = q_table;
			this->out_format = out_format;
		}

		int get_move(Game *game)
		{
			vector<bool> input = game->convert_board();
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
					agents.push_back(QAgent(q_table, game->get_output_format())); // generate the agents to play the game
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
			int move;
			search_move(game, move);
			return move;
		}

		static vector<float> search_move(Game *game, int &best_move)
		{
			// TODO: Research Alpha Beta pruning for multiple players

			if (game->is_finished())
			{
				return game->score(game); // TODO: Maybe AI gets stuck in cooperation trap
			} // Convert to relative score?? Index in sorted array of scores?

			int next_best_move = 0;
			int cur_player = game->get_current_player();
			vector<float> best_score(cur_player + 1, -999999); // TODO: Better default
			int temp;

			vector<int> all_moves = game->get_possible_moves();
			for (int move : all_moves)
			{
				Game* new_position = game->clone();
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