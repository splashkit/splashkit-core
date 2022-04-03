#include "window_manager.h"
#include "terminal.h"
#include "random.h"

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
using namespace splashkit_lib;

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

	vector<float> process_output_position(vector<float> output, int index)
	{
		if (format[index] != Type::Position) throw invalid_argument("Format at index is not of type Position!");
		vector<float> result(f_data[index]);
		for (int i = 0; i < f_data[index]; i++)
		{
			result[i] = output[indexes[index] + i];
		}
		return result;
	}

	int get_max_position(QValue position_data, vector<int> filter, bool random) 
	{
		if (random) {
			int out = filter[rnd(filter.size())];
			// update q_table
			position_data.to_update(out);
			return out;
		}
		float max = position_data[filter[0]];
		int max_pos = filter[0];
		for (int i = 1; i < filter.size(); i++)
		{
			if (position_data[filter[i]] > max)
			{
				max = position_data[filter[i]];
				max_pos = filter[i];
			}
		}
		position_data.to_update(max_pos);
		return max_pos;
	}

	float process_output_number(vector<float> output, int index)
	{
		if (format[index] != Type::Number) throw invalid_argument("Format at index is not of type Number!");
		int out_index = indexes[index];
		return output[out_index] * f_data[index];
	}
};

class Game
{
public:
	virtual int get_current_player() { return 0; }

	// The number of different 'pieces' that can exist on the field throughout any game
	// e.g. Tic-Tac-Toe [Empty + O + X = 2], Chess [Empty + (Pawn + Bishop + Knight + Rook + Queen + King) * 2 Players = 12]
	// Pong [Empty + Ball/Paddle = 1]
	virtual int get_max_board_index() { throw logic_error("get_max_board_index(): Function needs to be overridden; should return the highest number possible in get_board()"); }

	// The number of tiles on the board e.g. Tic-Tac-Toe = 3*3 = 9, Chess = 8*8 = 64
	virtual int get_board_size() { throw logic_error("get_board_size(): Function needs to be overridden; should return the length of get_board()"); }

	virtual OutputFormat get_output_format() { throw logic_error("get_output_format(): Function needs to be overridden; should return an OutputFormat that can represent any possible move"); }
	virtual vector<int> get_board() { throw logic_error("get_board(): Function needs to be overridden; should return a vector of all the tiles on the board"); }

	virtual vector<int> get_possible_moves() { throw logic_error("get_possible_moves(): Function needs to be overridden; should return a vector of all the possible moves"); }
	virtual void make_move(int move) { throw logic_error("make_move(): Function needs to be overridden; should take a move and update the board"); }
	virtual bool step() { throw logic_error("step(): Function needs to be overridden; should return false if the game is over"); }
	virtual int convert_output(QValue output, bool random) { throw logic_error("convert_output(): Function needs to be overridden; should return the index of the move that the output represents"); }

	// convert board to categorical vector
	vector<bool> convert_board() {
		vector<int> board = get_board();
		vector<bool> new_board(board.size() * get_max_board_index(), false);
		for (int i = 0; i < board.size(); i++) {
			if (board[i] != 0) {
				new_board[i * get_max_board_index() + board[i] - 1] = true;
			}
		}
		return new_board;
	}
};

class TicTacToe : public Game
{
public:
	enum class Cell
	{
		Empty,
		X,
		O
	};

	struct Board
	{
		Cell cells[3][3];
	};

	enum class GameState
	{
		Playing,
		X_Won,
		O_Won,
		Draw
	};

	enum class Player
	{
		X,
		O
	};

	struct Move
	{
		int row;
		int col;
	};

	Board board;
	Player current_player;
	GameState state;
	OutputFormat format;

	int get_current_player() override { return (int)current_player; }
	int get_max_board_index() override { return 2; } // O or X
	int get_board_size() override { return 9; }		// 3x3 = 9
	OutputFormat get_output_format() override { return format; }
	vector<int> get_board() override
	{
		vector<int> board_data(9);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				board_data[i * 3 + j] = (int)board.cells[i][j];
			}
		}
		return board_data;
	}

	void init()
	{
		board = {{{Cell::Empty, Cell::Empty, Cell::Empty},
				  {Cell::Empty, Cell::Empty, Cell::Empty},
				  {Cell::Empty, Cell::Empty, Cell::Empty}}};

		format = OutputFormat(get_board_size());
		format.add_type(OutputFormat::Type::Position, get_board_size());

		// When passing to AI
		// convert board to int array
		// e.g. {X, O, X, 		{1, 2, 1,		{[0, 1], [1, 0], [0, 1],
		//		 _, O, _,  -> 	 0, 2, 0,  ->	 [0, 0], [1, 0], [0, 0],  ->	[01 10 01 | 00 10 00 | 00 00 00]
		//		 _, _, _}		 0, 0, 0}		 [0, 0], [0, 0], [0, 0]}

		current_player = Player::X;
		state = GameState::Playing;
	}

	// Checks whether the board is won or drawn
	void update_state()
	{
		// Check rows
		for (int y = 0; y < 3; y++)
		{
			if (board.cells[y][0] != Cell::Empty &&
				board.cells[y][0] == board.cells[y][1] &&
				board.cells[y][1] == board.cells[y][2])
			{
				state = board.cells[y][0] == Cell::X ? GameState::X_Won : GameState::O_Won;
				return;
			}
		}

		// Check columns
		for (int x = 0; x < 3; x++)
		{
			if (board.cells[0][x] != Cell::Empty &&
				board.cells[0][x] == board.cells[1][x] &&
				board.cells[1][x] == board.cells[2][x])
			{
				state = board.cells[0][x] == Cell::X ? GameState::X_Won : GameState::O_Won;
				return;
			}
		}

		// Check diagonals
		if (board.cells[0][0] != Cell::Empty &&
			board.cells[0][0] == board.cells[1][1] &&
			board.cells[1][1] == board.cells[2][2])
		{
			state = board.cells[0][0] == Cell::X ? GameState::X_Won : GameState::O_Won;
			return;
		}

		if (board.cells[0][2] != Cell::Empty &&
			board.cells[0][2] == board.cells[1][1] &&
			board.cells[1][1] == board.cells[2][0])
		{
			state = board.cells[0][2] == Cell::X ? GameState::X_Won : GameState::O_Won;
			return;
		}

		// Check draw
		bool found_empty = false;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (board.cells[y][x] == Cell::Empty)
				{
					found_empty = true;
					break;
				}
			}
		}
		if (!found_empty)
		{
			state = GameState::Draw;
		}
	}

	void draw_board()
	{
		write_line();
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (board.cells[y][x] == Cell::Empty) { write("_"); }
				else if (board.cells[y][x] == Cell::X) { write("X"); }
				else if (board.cells[y][x] == Cell::O) { write("O"); }
			}
			write_line();
		}
	}

	void draw_game()
	{
		draw_board();
		if (state == GameState::X_Won) { write_line("X Won!"); }
		else if (state == GameState::O_Won) { write_line("O Won!"); }
		else if (state == GameState::Draw) { write_line("Draw!"); }
	}

	vector<int> get_possible_moves() override
	{
		vector<int> moves = {};
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (board.cells[y][x] == Cell::Empty)
				{
					moves.push_back(y * 3 + x);
				}
			}
		}
		return moves;
	}

	void make_move(int move) override
	{
		board.cells[move / 3][move % 3] = current_player == Player::X ? Cell::X : Cell::O;
		current_player = current_player == Player::X ? Player::O : Player::X;
		update_state();
		draw_game();
	}
};

class QValue
{
private:
	vector<float> value;
	vector<int> indexes; // indexes to affect during reward/punishment
public:
	QValue(OutputFormat format)
	{
		value = vector<float>(format.get_width(), 0.5f);
	}

	// adds an index to be updated during reward/punishment
	void to_update(int index)
	{
		indexes.push_back(index);
	}

	float operator[](int index) { return value[index]; }
};

class QAgent 
{
private:
	OutputFormat out_format;
	float learning_rate = 0.1f;
	float discount_factor = 0.9f;
	float epsilon = 0.1f;

	unordered_map<vector<bool>,QValue> q_table;
public:
	vector<QValue> q_history; // Store the q_values used for the last game

	QAgent(unordered_map<vector<bool>,QValue> q_table, OutputFormat out_format)
	{
		this->q_table = q_table;
		this->out_format = out_format;
	}

	QValue get_q_value(vector<bool> key)
	{
		if (q_table.find(key) == q_table.end())
		{
			q_table[key] = QValue(out_format);
		}
		return q_table[key];
	}

	int get_move(Game& game)
	{
		if (rnd() < epsilon)
		{
			vector<int> moves = game.get_possible_moves();
			vector<bool> input = game.convert_board();
			QValue q_output = get_q_value(input);
			return game.convert_output(q_output, true);
			return moves[rnd(moves.size())];
		} // else {
		vector<bool> input = game.convert_board();
		QValue q_output = get_q_value(input);
		return game.convert_output(q_output, false);
	}
};

class QTrainer {
	unordered_map<vector<bool>,QValue> q_table;

	void train(Game game, int iterations)
	{ 
		for (int i = 0; i < iterations; i++)
		{
			Game game; // generate the game
			vector<QAgent> agents; // generate the agents to play the game
			while (game.step())
			{
				int move = agents[game.get_current_player()].get_move(game);
				game.make_move(move);
			}
			// Update q_table
			/*
			vector<float> scores = game.score();
			for (int i = 0; i < scores.size(); i++) {
				float score = scores[i];
				agents[i].reward(score);
			} //*/
		}
	}
};

int random_agent_play(int posb_moves)
{
	if (posb_moves < 1) throw logic_error("No moves available; Game over?");
	if (posb_moves == 1) return 0;
	return rnd(0, posb_moves - 1);
}

vector<float> q_agent_play(Game &game) {
	OutputFormat format = game.get_output_format();
	vector<bool> input = game.convert_board();

	// vector<float> q_output = q_learning(input)
	vector<float> q_output = {0.2, 0.9, 0, 0, 1, 0, 0, 0.9, 0.3};

	vector<float> position_data = format.process_output_position(q_output, 0);

	return position_data;
}

void run_machine_learning_test()
{
	TicTacToe game;
	game.init();
	game.draw_game();
	while (game.state == TicTacToe::GameState::Playing)
	{
		vector<int> moves = game.get_possible_moves();
		if (game.current_player == TicTacToe::Player::X)
		{
			OutputFormat format = game.get_output_format();
			vector<float> moves_weight = q_agent_play(game);
			int ai_move = format.get_max_position(moves_weight, moves);
			game.make_move(ai_move);
		} else {
			game.make_move(moves[random_agent_play(moves.size())]);
		}
	}
}
