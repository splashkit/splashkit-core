#include "window_manager.h"
#include "terminal.h"
#include "utility_functions.h"
#include "random.h"
#include "machine_learning.h"

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
using namespace splashkit_lib;

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
	OutputFormat format = OutputFormat(get_board_size());

	int get_current_player() override { return (int)current_player; }
	int get_max_board_index() override { return 2; } // O or X
	int get_board_size() override { return 9; }		 // 3x3 = 9
	OutputFormat *get_output_format() override { return &format; }
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
	int convert_output(QValue *output, bool random) override
	{
		return format.get_max_position(output, 0, get_possible_moves(), random);
	}
	void reset() override
	{
		board = {{{Cell::Empty, Cell::Empty, Cell::Empty},
				  {Cell::Empty, Cell::Empty, Cell::Empty},
				  {Cell::Empty, Cell::Empty, Cell::Empty}}};
		current_player = Player::X;
		state = GameState::Playing;
	}
	Game* clone() override
	{
		TicTacToe* game = new TicTacToe(); // Essential that the new keyword is used!!!
		game->board = board;
		game->current_player = current_player;
		game->state = state;
		game->format = format;
		return game;
	}
	bool is_finished() override
	{
		return state != GameState::Playing;
	}
	vector<float> score(Game *game) override
	{
		TicTacToe* t = (TicTacToe*)game;
		vector<float> scores(2);
		switch (t->state)
		{
		case GameState::Playing:
			throw logic_error("Cannot score a game in progress!");
		case GameState::X_Won:
			scores[0] = 1.0f;
			scores[1] = -1.0f;
			break;
		case GameState::O_Won:
			scores[0] = -1.0f;
			scores[1] = 1.0f;
			break;
		case GameState::Draw:
			scores[0] = -0.1f;
			scores[1] = -0.1f;
			break;
		}
		return scores;
	}

	TicTacToe()
	{
		reset();
		format.add_type(OutputFormat::Type::Position, get_board_size());

		// When passing to AI
		// convert board to int array
		// e.g. {X, O, X, 		{1, 2, 1,		{[0, 1], [1, 0], [0, 1],
		//		 _, O, _,  -> 	 0, 2, 0,  ->	 [0, 0], [1, 0], [0, 0],  ->	[01 10 01 | 00 10 00 | 00 00 00]
		//		 _, _, _}		 0, 0, 0}		 [0, 0], [0, 0], [0, 0]}
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
				if (board.cells[y][x] == Cell::Empty)
				{
					write("_");
				}
				else if (board.cells[y][x] == Cell::X)
				{
					write("X");
				}
				else if (board.cells[y][x] == Cell::O)
				{
					write("O");
				}
			}
			write_line();
		}
	}

	void draw_game()
	{
		draw_board();
		if (state == GameState::X_Won)
		{
			write_line("X Won!");
		}
		else if (state == GameState::O_Won)
		{
			write_line("O Won!");
		}
		else if (state == GameState::Draw)
		{
			write_line("Draw!");
		}
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
	}
};

int random_agent_play(int posb_moves)
{
	if (posb_moves < 1)
		throw logic_error("No moves available; Game over?");
	if (posb_moves == 1)
		return 0;
	return rnd(0, posb_moves - 1);
}

bool test_q_table()
{
	bool passes = true;

	TicTacToe game;
	QTable q_table = QTable(game.get_output_format());
	QValue *test = q_table.get_q_value(game.convert_board());
	if ((*test)[0] != 0.5f)
	{
		passes = false;
	}
	write("Initial QValues == 0.5? ");
	write((((*test)[0] == 0.5f) ? "true" : "false"));
	write_line(" (" + to_string((*test)[0]) + ")");
	write_line(test->to_string());

	return passes;
}


bool test_q_value()
{
	bool passes = true;
	const float F_ERR = 0.01f; // Float error for comparisons.

	// Consider a right hand turn represented with possible actions LEFT=0 CENTER=1 or RIGHT=2
	vector<float> val = {0, 0, 0};
	QValue test = QValue(val);

	// We take a left turn
	test.to_update(0);
	// We punish the left turn
	test.update(-1);
	if (abs(-1 - test[0]) > F_ERR || abs(0 - test[1]) > F_ERR || abs(0 - test[2]) > F_ERR)
	{
		passes = false;
		write("Expected: {-1, 0, 0}, Actual: ");
		write_line(test.to_string());
		// log(WARNING, "LEFT turn failed");
	}

	// We take a LEFT CENTER turn
	test.to_update(0);
	test.to_update(1);
	// We punish the center less
	test.update(-0.7);
	if (abs(-1.7 - test[0]) > F_ERR || abs(-0.7 - test[1]) > F_ERR || abs(0 - test[2]) > F_ERR)
	{
		passes = false;
		write("Expected: {-1.7, -0.7, 0}, Actual: ");
		write_line(test.to_string());
		// log(WARNING, "LEFT CENTER turn failed");
	}

	// We take a RIGHT CENTER turn
	test.to_update(1);
	test.to_update(2);
	// We reward a correct turn
	test.update(1);
	if (abs(-1.7 - test[0]) > F_ERR || abs(0.3 - test[1]) > F_ERR || abs(1 - test[2]) > F_ERR)
	{
		passes = false;
		write("Expected: {-1.7, 0.3, 1}, Actual: ");
		write_line(test.to_string());
		// log(WARNING, "RIGHT CENTER turn failed");
	}

	// We take no action
	test.update(999);
	if (abs(-1.7 - test[0]) > F_ERR || abs(0.3 - test[1]) > F_ERR || abs(1 - test[2]) > F_ERR)
	{
		passes = false;
		write("Expected: {-1.7, 0.3, 1}, Actual: ");
		write_line(test.to_string());
		// log(WARNING, "NULL update failed");
	}

	write("test_q_value: ");
	write_line(test.to_string());

	return passes;
}

QTrainer *test_q_trainer()
{
	bool passes = true;

	TicTacToe game;
	QTrainer *trainer = new QTrainer(&game);

	write_line("Training for 1,000,000 iterations. Please wait...");
	trainer->train(2, 1000000);
	write_line("Training complete.");

	game.draw_game();
	write_line(trainer->q_table->get_q_value(game.convert_board())->to_string());

	return trainer;
}

string to_string(vector<int> vec)
{
	stringstream ss;
	ss << "[ ";
	for (float v : vec)
	{
		ss << v << " ";
	}
	ss << "]";
	return ss.str();
}

void play_games(QTrainer *trainer)
{
	TicTacToe game;
	QAgent agent = QAgent(trainer->q_table, game.get_output_format());
	agent.epsilon = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		write("AI vs Random GAME ");
		write_line(i);
		game.draw_game();
		while (game.state == TicTacToe::GameState::Playing)
		{
			if (game.current_player == TicTacToe::Player::X)
			{
				write_line(trainer->q_table->get_q_value(game.convert_board())->to_string());
				int ai_move = agent.get_move(&game);
				game.make_move(ai_move);
			}
			else
			{
				vector<int> moves = game.get_possible_moves();
				game.make_move(moves[random_agent_play(moves.size())]);
			}
			game.draw_game();
		}
		game.reset();
	}
	write_line("AI vs AI GAME");
	game.draw_game();
	while (game.state == TicTacToe::GameState::Playing)
	{
		write_line(trainer->q_table->get_q_value(game.convert_board())->to_string());
		game.make_move(agent.get_move(&game));
		game.draw_game();
	}
	do
	{
		game.reset();
		write_line("\nAI vs Human GAME");
		write_line("Do you want to start first? (Y/N)");
		if (read_line() == "Y")
		{
			game.current_player = TicTacToe::Player::X;
		}
		else
		{
			game.current_player = TicTacToe::Player::O;
		}
		game.draw_game();
		while (game.state == TicTacToe::GameState::Playing)
		{
			if (game.current_player == TicTacToe::Player::O)
			{
				write_line(trainer->q_table->get_q_value(game.convert_board())->to_string());
				int ai_move = agent.get_move(&game);
				game.make_move(ai_move);
			}
			else
			{
				vector<int> moves = game.get_possible_moves();
				write_line("Your move: ");
				write_line(to_string(moves));
				int move;
				while(!try_str_to_int(read_line(), move));
				game.make_move(moves[move]);
			}
			game.draw_game();
		}
		write_line("Do you want to go again? (Y/N)");
	} while (read_line() == "Y");

	game.reset();
}

void run_machine_learning_test()
{
	// log_mode _log_mode = LOG_CONSOLE;
	// init_custom_logger(_log_mode);

	test_q_table();
	test_q_value();
	// QTrainer *trainer = test_q_trainer();

	// play_games(trainer);

	TicTacToe game;
	do
	{
		game.reset();
		write_line("\nAI vs Human GAME");
		write_line("Do you want to start first? (Y/N)");
		if (read_line() == "Y")
		{
			game.current_player = TicTacToe::Player::X;
		}
		else
		{
			game.current_player = TicTacToe::Player::O;
		}
		game.draw_game();
		while (game.state == TicTacToe::GameState::Playing)
		{
			if (game.current_player == TicTacToe::Player::O)
			{
				int ai_move = MiniMax::get_move(&game);
				game.make_move(ai_move);
			}
			else
			{
				vector<int> moves = game.get_possible_moves();
				write_line("Your move: ");
				write_line(to_string(moves));
				int move;
				while(!try_str_to_int(read_line(), move));
				game.make_move(moves[move]);
			}
			game.draw_game();
		}
		write_line("Do you want to go again? (Y/N)");
	} while (read_line() == "Y");
}
