#include "window_manager.h"
#include "terminal.h"
#include "random.h"

#include <iostream>
#include <vector>
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

	vector<Type> format;
	vector<int> f_data;
	int board_size;
	int output_width = 0;

	void add_type(Type type, int data)
	{
		format.push_back(type);
		f_data.push_back(data);
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

	void process_category(vector<float> output, int start, int size)
	{
		cout << "Category: [ ";
		for (int i = start; i < start + size; i++)
		{
			cout << output[i] << " ";
		}
		cout << "]" << endl;
	}

	void process_output(vector<float> output)
	{
		int cur_index = 0;
		for (int i = 0; i < format.size(); i++)
		{
			switch (format[i])
			{
			case Type::Number:
				cout << "Number: " << output[cur_index] * f_data[i] << endl;
				cur_index++;
				break;
			case Type::Position:
			case Type::Category:
				process_category(output, cur_index, f_data[i]);
				cur_index += f_data[i];
				break;
			}
		}
	}
};

class Game
{
public:
	// The number of different 'pieces' that can exist on the field throughout any game
	// e.g. Tic-Tac-Toe [Empty + O + X = 2], Chess [Empty + (Pawn + Bishop + Knight + Rook + Queen + King) * 2 Players = 12]
	// Pong [Empty + Ball/Paddle = 1]
	virtual int get_max_board_index() { throw logic_error("Function needs to be overridden; should return the highest number possible in get_board()"); };

	// The number of tiles on the board e.g. Tic-Tac-Toe = 3*3 = 9, Chess = 8*8 = 64
	virtual int get_board_size() { throw logic_error("Function needs to be overridden; should return the length of get_board()"); };

	virtual OutputFormat get_output_format() { throw logic_error("Function needs to be overridden; should return an OutputFormat that can represent any possible move"); };
	virtual vector<int> get_board() { throw logic_error("Function needs to be overridden; should return a vector of all the tiles on the board"); };

	// convert board to categorical vector
	/*
	vector<int> convert_board(vector<int> board) {
		vector<int> new_board(board.size() * get_max_board_index());
		fill(new_board.begin(), new_board.end(), 0);
		for (int i = 0; i < board.size(); i++) {
			if (board[i] != 0) {
				new_board[i * get_max_board_index() + board[i] - 1] = 1;
			}
		}
		return new_board;
	} */
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

	int get_max_board_index() { return 2; } // O or X
	int get_board_size() { return 9; }		// 3x3 = 9
	OutputFormat get_output_format() { return format; }
	vector<int> get_board()
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

		format = OutputFormat();
		format.add_type(OutputFormat::Type::Position, get_board_size());

		// When passing to AI
		// convert board to int array
		// e.g. {X, O, X, 		{1, 2, 1,		{[0, 1], [1, 0], [0, 1],
		//		 _, O, _,  -> 	 0, 2, 0,  ->	 [0, 0], [0, 1], [0, 0],  ->	[01 10 01 | 00 01 00 | 00 00 00]
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

	vector<Move> get_possible_moves()
	{
		vector<Move> moves = {};
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (board.cells[y][x] == Cell::Empty)
				{
					Move move = {y, x};
					moves.push_back(move);
				}
			}
		}
		return moves;
	}

	void make_move(Move move)
	{
		board.cells[move.row][move.col] = current_player == Player::X ? Cell::X : Cell::O;
		current_player = current_player == Player::X ? Player::O : Player::X;
		update_state();
		draw_game();
	}
};

int random_agent_play(int posb_moves)
{
	if (posb_moves < 1) throw logic_error("No moves available; Game over?");
	if (posb_moves == 1) return 0;
	return rnd(0, posb_moves - 1);
}

void run_machine_learning_test()
{
	TicTacToe game;
	game.init();
	game.draw_game();
	while (game.state == TicTacToe::GameState::Playing)
	{
		vector<TicTacToe::Move> moves = game.get_possible_moves();
		game.make_move(moves[random_agent_play(moves.size())]);
	}
}
