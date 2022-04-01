#include "window_manager.h"
#include "terminal.h"
#include "random.h"

#include <iostream>
#include <vector>
using namespace std;
using namespace splashkit_lib;

namespace tic_tac_toe {
	enum class Cell {
		Empty,
		X,
		O
	};

	enum class GameState {
		Playing,
		X_Won,
		O_Won,
		Draw
	};

	enum class Player {
		X,
		O
	};

	struct Board {
		Cell cells[3][3];
	};

	struct Game {
		Board board;
		Player current_player;
		GameState state;
	};

	struct Move {
		int row;
		int col;
	};

	void init(Game &game) {
		game.board = {{
			{Cell::Empty, Cell::Empty, Cell::Empty},
			{Cell::Empty, Cell::Empty, Cell::Empty},
			{Cell::Empty, Cell::Empty, Cell::Empty}
		}};

		// When passing to AI
		// convert board to int array
		// e.g. {X, O, X, 		{1, 2, 1,		{[0, 1], [1, 0], [0, 1],
		//		 _, O, _,  -> 	 0, 2, 0,  ->	 [0, 0], [0, 1], [0, 0],  ->	[01 10 01 | 00 01 00 | 00 00 00]
		//		 _, _, _}		 0, 0, 0}		 [0, 0], [0, 0], [0, 0]}

		game.current_player = Player::X;
		game.state = GameState::Playing;
	}

	// Checks whether the board is won or drawn
	void update_state(Game &game) {
		// Check rows
		for (int y = 0; y < 3; y++) {
			if (game.board.cells[y][0] != Cell::Empty &&
				game.board.cells[y][0] == game.board.cells[y][1] &&
				game.board.cells[y][1] == game.board.cells[y][2]) {
				game.state = game.board.cells[y][0] == Cell::X ? GameState::X_Won : GameState::O_Won;
				return;
			}
		}

		// Check columns
		for (int x = 0; x < 3; x++) {
			if (game.board.cells[0][x] != Cell::Empty &&
				game.board.cells[0][x] == game.board.cells[1][x] &&
				game.board.cells[1][x] == game.board.cells[2][x]) {
				game.state = game.board.cells[0][x] == Cell::X ? GameState::X_Won : GameState::O_Won;
				return;
			}
		}

		// Check diagonals
		if (game.board.cells[0][0] != Cell::Empty &&
			game.board.cells[0][0] == game.board.cells[1][1] &&
			game.board.cells[1][1] == game.board.cells[2][2]) {
			game.state = game.board.cells[0][0] == Cell::X ? GameState::X_Won : GameState::O_Won;
			return;
		}

		if (game.board.cells[0][2] != Cell::Empty &&
			game.board.cells[0][2] == game.board.cells[1][1] &&
			game.board.cells[1][1] == game.board.cells[2][0]) {
			game.state = game.board.cells[0][2] == Cell::X ? GameState::X_Won : GameState::O_Won;
			return;
		}

		// Check draw
		bool found_empty = false;
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				if (game.board.cells[y][x] == Cell::Empty) {
					found_empty = true;
					break;
				}
			}
		}
		if (!found_empty) { game.state = GameState::Draw; }
	}

	void draw_board(Game &game) {
		write_line();
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				if (game.board.cells[y][x] == Cell::Empty) {
					write("_");
				} else if (game.board.cells[y][x] == Cell::X) {
					write("X");
				} else if (game.board.cells[y][x] == Cell::O) {
					write("O");
				}
			}
			write_line();
		}
	}

	void draw_game(Game &game) {
		draw_board(game);
		if (game.state == GameState::X_Won) {
			write_line("X Won!");
		} else if (game.state == GameState::O_Won) {
			write_line("O Won!");
		} else if (game.state == GameState::Draw) {
			write_line("Draw!");
		}
	}

	vector<Move> get_possible_moves(Game &game) {
		vector<Move> moves = {};
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				if (game.board.cells[y][x] == Cell::Empty) {
					Move move = {y, x};
					moves.push_back(move);
				}
			}
		}
		return moves;
	}

	void submit_move(Game &game, Move move) {
		game.board.cells[move.row][move.col] = game.current_player == Player::X ? Cell::X : Cell::O;
		game.current_player = game.current_player == Player::X ? Player::O : Player::X;
		update_state(game);
		draw_game(game);
	}
}

void run_machine_learning_test() { 
	tic_tac_toe::Game game;
	tic_tac_toe::init(game);
	tic_tac_toe::draw_game(game);
	while (game.state == tic_tac_toe::GameState::Playing) {
		vector<tic_tac_toe::Move> moves = tic_tac_toe::get_possible_moves(game);
		int move_index = rnd(0, moves.size() - 1);
		tic_tac_toe::submit_move(game, moves[move_index]);
	}
}
