#include "terminal.h"
#include "utility_functions.h"
#include "random.h"
#include "utils.h"
#include "window_manager.h"
#include "graphics.h"
#include "text.h"
#include "rectangle_drawing.h"
#include "rectangle_geometry.h"
#include "input.h"

#include "game_learning.h"
#include "machine_learning.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <cmath>
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
	static inline InputFormat input_format = InputFormat();
	static inline OutputFormat out_format = OutputFormat();

	int get_current_player() override { return (int)current_player; }
	// int get_max_board_index() override { return 2; }	// O or X
	// int get_board_size() override { return 9; }		// 3x3 = 9
	InputFormat &get_input_format() override { return TicTacToe::input_format; }
	OutputFormat &get_output_format() override { return TicTacToe::out_format; }
	vector<int> get_input() override
	{
		vector<int> board_data(10);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				board_data[i * 3 + j] = (int)board.cells[i][j];
			}
		}
		board_data[9] = (int)current_player;
		return board_data;
	}
	int convert_output(OutputValue &output, bool random) override
	{
		return output.get_max_position(TicTacToe::out_format, 0, get_possible_moves(), random);
	}
	void reset() override
	{
		board = {{{Cell::Empty, Cell::Empty, Cell::Empty},
				  {Cell::Empty, Cell::Empty, Cell::Empty},
				  {Cell::Empty, Cell::Empty, Cell::Empty}}};
		current_player = (Player)rnd(2);
		state = GameState::Playing;
	}
	Game *clone() override
	{
		TicTacToe *game = new TicTacToe(); // New keyword must be used
		game->board = board;
		game->current_player = current_player;
		game->state = state;
		return game;
	}
	bool is_finished() override
	{
		return state != GameState::Playing;
	}
	vector<float> score() override
	{
		vector<float> scores(2);
		switch (state)
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
		if (TicTacToe::input_format.get_width() == 0) // uninitialized
		{
			TicTacToe::input_format.add_type(InputFormat::Type::Board, 9, 3);	// 9 is board size, 3 is player count [Empty, X, O]
			TicTacToe::input_format.add_type(InputFormat::Type::Player, 1, 2);	// 1 is player dim, 2 is player count [X, O]
		}

		if (TicTacToe::out_format.get_width() == 0) // uninitialized
		{
			TicTacToe::out_format.add_type(OutputFormat::Type::Position, 9);	// 3*3 = 9
		}

		reset();

		// When passing to AI
		// convert board to int array
		// e.g. {X, O, X, 		{1, 2, 1,		{[1, 0], [0, 1], [1, 0],
		//		 _, O, _,  -> 	 0, 2, 0,  ->	 [0, 0], [0, 1], [0, 0],  ->	[10 01 10 | 00 01 00 | 00 00 00] -> [100110000100000000]
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
		vector<int> moves;
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

class Pong : public Game
{
public:
	struct Ball
	{
		float x;
		float y;
		float vx;
		float vy;
	};

	struct Player
	{
		float x;
		float y;
		float score;
	};

	enum class GameState
	{
		Playing,
		Player1_Won,
		Player2_Won
	};

	Ball ball;
	Player player1;
	Player player2;
	GameState state;
	bool is_player1 = true;
	vector<int> moves;
	int play_to;

	#define PONG_BALL_SPEED 0.1f
	#define PONG_PLAYER_SPEED 0.1f

	// Drawing options
	#define PONG_GAME_WIDTH 20
	#define PONG_GAME_HEIGHT 10
	#define PONG_SCALE 50.0f
	#define PONG_PADDLE_WIDTH 1.0f
	#define PONG_PADDLE_HEIGHT 3.0f
	#define PONG_MARGIN 1.0f
	#define PONG_BALL_RADIUS 0.5f
	bool silent = false;
	window win;

	// Game API Objects
	static inline InputFormat input_format = InputFormat();
	static inline OutputFormat output_format = OutputFormat();

	Pong(int play_to = 3)
	{
		this->play_to = play_to;
		if (Pong::input_format.get_width() == 0) // uninitialized
		{
			Pong::input_format.add_type(InputFormat::Type::Player, 1, 2); // which side the player is controlling
			Pong::input_format.add_type(InputFormat::Type::Board, PONG_GAME_WIDTH * PONG_GAME_HEIGHT, 2); // paddle/player and board information
		}
		if (Pong::output_format.get_width() == 0) // uninitialized
		{
			Pong::output_format.add_type(OutputFormat::Type::Category, 3); // stay still, move up, move down
		}

		moves.push_back(0);
		moves.push_back(1);
		moves.push_back(2);
		
		reset();
	}

	void open_window()
	{
		silent = true;
		win = splashkit_lib::open_window("Pong", PONG_GAME_WIDTH * PONG_SCALE, PONG_GAME_HEIGHT * PONG_SCALE);
	}

	void new_round()
	{
		ball.x = PONG_GAME_WIDTH / 2.0f;
		ball.y = PONG_GAME_HEIGHT / 2.0f;
		ball.vx = PONG_BALL_SPEED;
		ball.vy = (rnd() - 0.5f) * PONG_BALL_SPEED;

		player1.x = PONG_MARGIN;
		player1.y = PONG_GAME_HEIGHT / 2.0f - PONG_PADDLE_HEIGHT / 2.0f;

		player2.x = PONG_GAME_WIDTH - PONG_MARGIN - PONG_PADDLE_WIDTH;
		player2.y = PONG_GAME_HEIGHT / 2.0f - PONG_PADDLE_HEIGHT / 2.0f;
	}

	void reset() override
	{
		new_round();
		player1.score = 0;
		player2.score = 0;
		state = GameState::Playing;
	}

	void update_state()
	{
		// Update ball position
		ball.x += ball.vx;
		ball.y += ball.vy;

		// Check if ball is out of bounds
		if (ball.x < 0.0f)
		{
			player2.score++;
			if (player2.score >= play_to)
			{
				state = GameState::Player2_Won;
				return;
			}
			new_round();
			return;
		}
		else if (ball.x > PONG_GAME_WIDTH)
		{
			player1.score++;
			if (player1.score >= play_to)
			{
				state = GameState::Player1_Won;
				return;
			}
			new_round();
			return;
		}

		// Check if ball is hitting a paddle
		if (ball.x - PONG_BALL_RADIUS < player1.x + PONG_PADDLE_WIDTH && // hitting front of paddle
			ball.x + PONG_BALL_RADIUS > player1.x && // not behind paddle
			ball.y + PONG_BALL_RADIUS > player1.y && // below top of the paddle
			ball.y - PONG_BALL_RADIUS < player1.y + PONG_PADDLE_HEIGHT && // above bottom of the paddle
			ball.vx < 0.0f) // ball going towards paddle 1
		{
			ball.vx = -ball.vx;
			ball.vy = (ball.y - (player1.y + PONG_PADDLE_HEIGHT / 2.0f)) * PONG_BALL_SPEED;
		}
		else if (ball.x + PONG_BALL_RADIUS > player2.x && // hitting front of paddle
				 ball.x - PONG_BALL_RADIUS < player2.x + PONG_PADDLE_WIDTH && // not behind paddle
				 ball.y + PONG_BALL_RADIUS > player2.y && // below top of the paddle
				 ball.y - PONG_BALL_RADIUS < player2.y + PONG_PADDLE_HEIGHT && // above bottom of the paddle
				 ball.vx > 0.0f) // ball going towards paddle 2
		{
			ball.vx = -ball.vx;
			ball.vy = (ball.y - (player2.y + PONG_PADDLE_HEIGHT / 2.0f)) * PONG_BALL_SPEED;
		}

		// Check if ball is hitting a wall
		if (ball.y < PONG_BALL_RADIUS || ball.y > PONG_GAME_HEIGHT - PONG_BALL_RADIUS)
		{
			ball.vy = -ball.vy;
		}
	}

	void draw_game()
	{
		clear_window(win, COLOR_BLACK);

		// Draw ball
		draw_circle_on_window(win, COLOR_WHITE, ball.x * PONG_SCALE, ball.y * PONG_SCALE, PONG_BALL_RADIUS * PONG_SCALE);

		// Draw paddles
		draw_rectangle_on_window(win, COLOR_WHITE, player1.x * PONG_SCALE, player1.y * PONG_SCALE, PONG_PADDLE_WIDTH * PONG_SCALE, PONG_PADDLE_HEIGHT * PONG_SCALE);
		draw_rectangle_on_window(win, COLOR_WHITE, player2.x * PONG_SCALE, player2.y * PONG_SCALE, PONG_PADDLE_WIDTH * PONG_SCALE, PONG_PADDLE_HEIGHT * PONG_SCALE);

		// Draw score
		string score = to_string((int)player1.score) + " - " + to_string((int)player2.score);
		draw_text_on_window(win, score, COLOR_WHITE, ((PONG_GAME_WIDTH - 1) / 2.0f) * PONG_SCALE, (PONG_MARGIN / 2.0f) * PONG_SCALE);

		refresh_window(win, 30);
	}

	/**
	 * @brief Get the possible moves.
	 * 
	 * vector will be reused, should be immutable.
	 * 
	 * @return vector<int> 
	 */
	vector<int> get_possible_moves() override
	{
		return moves;
	}

	void make_move(int move) override
	{
		float action;
		if (move == 0)
			action = 0.0f;
		else if (move == 1)
			action = -PONG_PLAYER_SPEED;
		else if (move == 2)
			action = PONG_PLAYER_SPEED;
		
		if (is_player1)
		{
			player1.y = MAX(0, MIN(player1.y + action, PONG_GAME_HEIGHT - PONG_PADDLE_HEIGHT));
		}
		else
		{
			player2.y = MAX(0, MIN(player2.y + action, PONG_GAME_HEIGHT - PONG_PADDLE_HEIGHT));
			update_state();
		}
		is_player1 = !is_player1;
	}

	// misc Game API
	int get_current_player() override { return is_player1 ? 0 : 1; }
	InputFormat &get_input_format() override { return Pong::input_format; }
	OutputFormat &get_output_format() override { return Pong::output_format; }
	int convert_output(OutputValue &output, bool random) override 
	{ 
		return output.get_max_position(Pong::output_format, 0, get_possible_moves(), random);
	}
	vector<float> score() override { return { player1.score, player2.score }; }
	bool is_finished() override { return state != GameState::Playing; }
	Game *clone() override {  return new Pong(*this); }
	vector<int> get_input() override { 
		vector<int> input(PONG_GAME_WIDTH * PONG_GAME_HEIGHT + 1);
		input[0] = is_player1 ? 0 : 1;
		for (int i = 0; i < PONG_GAME_WIDTH; i++)
		{
			for (int j = 0; j < PONG_GAME_HEIGHT; j++)
			{
				int temp = 0;
				if (((int)ball.x) == i && ((int)ball.y) == j)
					temp = 1;
				else if (((int)player1.x) == i && ((int)player1.y) == j)
					temp = 1;
				else if (((int)player2.x) == i && ((int)player2.y) == j)
					temp = 1;
				input[i * PONG_GAME_HEIGHT + j + 1] = temp;
			}
		}
		return input;
	}
};

int random_agent_play(int posb_moves)
{
	if (posb_moves < 1)
		throw logic_error("No moves available; Game over?");
	if (posb_moves == 1)
		return 0;
	return rnd(0, posb_moves);
}

bool test_reward_table()
{
	bool passes = true;

	TicTacToe game;
	RewardTable reward_table = RewardTable(game.get_output_format().get_width());
	vector<bool> game_state = game.get_input_format().convert_input(game.get_input());
	OutputValue &test = reward_table.get_value(game_state);
	if (test[0] != 0.5f)
	{
		passes = false;
	}
	write("Initial OutputValues == 0.5? ");
	write(((test[0] == 0.5f) ? "true" : "false"));
	write_line(" (" + to_string(test[0]) + ")");
	write_line(test.to_string());

	return passes;
}

bool test_output_value()
{
	bool passes = true;
	const float F_ERR = 0.01f; // Float error for comparisons.

	OutputFormat format = OutputFormat();
	format.add_type(OutputFormat::Type::Category, 3);
	OutputValue test = OutputValue(format.get_width()); // expected starting state = {0.5, 0.5, 0.5}

	// We increase the first value
	test.to_update(0);
	test.update(1, 0, 1, nullptr); // We give absolute reward of 1
	if (abs(1 - test[0]) > F_ERR || abs(0.5 - test[1]) > F_ERR || abs(0.5 - test[2]) > F_ERR)
	{
		passes = false;
		write("Expected: {1, 0.5, 0.5}, Actual: ");
		write_line(test.to_string());
	}

	return passes;
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

bool ask(string question)
{
	write(question + "? (Y/N) ");
	string answer = read_line();
	return answer == "Y" || answer == "y";
}

void play_tictactoe(QAgent *q_agent)
{
	TicTacToe game;
	for (int i = 0; i < 5; i++)
	{
		write("AI vs Random GAME ");
		write_line(i);
		game.draw_game();
		while (game.state == TicTacToe::GameState::Playing)
		{
			if (game.current_player == TicTacToe::Player::X)
			{
				write_line(q_agent->reward_table->get_value(&game).to_string());
				int ai_move = q_agent->get_move(&game);
				game.make_move(ai_move);
			}
			else
			{
				const vector<int> moves = game.get_possible_moves();
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
		write_line(q_agent->reward_table->get_value(&game).to_string());
		game.make_move(q_agent->get_move(&game));
		game.draw_game();
	}
	do
	{
		game.reset();
		write_line("\nAI vs Human GAME");
		if (ask("Do you want to start first"))
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
				write_line(q_agent->reward_table->get_value(&game).to_string()); // print ai 'thoughts' on best move
				int ai_move = q_agent->get_move(&game);
				game.make_move(ai_move);
			}
			else
			{
				const vector<int> moves = game.get_possible_moves();
				write_line("Your move: ");
				write_line(to_string(moves));
				int move;
				while (!try_str_to_int(read_line(), move));
				game.make_move(move);
			}
			game.draw_game();
		}
	} while (ask("Do you want to go again"));

	game.reset();
}

class PongKeyAgent : public Agent
{
	key_code up_key;
	key_code down_key;
public:
	PongKeyAgent(key_code up_key, key_code down_key)
	{
		this->up_key = up_key;
		this->down_key = down_key;
	}

	int get_move(Game *game)
	{
		if (key_down(up_key))
			return 1;
		if (key_down(down_key))
			return 2;
		return 0;
	}
};

bool play_pong(Agent *p1_agent, Agent *p2_agent, bool silent=false)
{
	Pong game;
	if (!silent)
		game.open_window();
	bool ready = false;
	while (!ready && !silent)
	{
		game.draw_game();
		process_events();
		if (key_down(W_KEY) || key_down(S_KEY) || key_down(UP_KEY) || key_down(DOWN_KEY))
			ready = true;
	}
	while (game.state == Pong::GameState::Playing)
	{
		if (!silent)
		{
			game.draw_game();
			process_events(); // check keypresses
		}

		game.make_move(p1_agent->get_move(&game));
		game.make_move(p2_agent->get_move(&game));
	}
	if (!silent)
	{
		if (game.state == Pong::GameState::Player1_Won)
			write_line("Player 1 Wins!");
		else if (game.state == Pong::GameState::Player2_Won)
			write_line("Player 2 Wins!");
		delay(5);
		close_window(game.win);
	}
	return game.state == Pong::GameState::Player1_Won;
}

void test_pong()
{
	Pong *trainer = new Pong(1);

	Agent *ws = new PongKeyAgent(W_KEY, S_KEY);
	Agent *ud = new PongKeyAgent(UP_KEY, DOWN_KEY);
	Agent *rnd1 = new RandomAgent(0.07f);
	Agent *rnd2 = new RandomAgent(0.07f);
	Agent *q_agent = new QAgent(Pong::output_format);

	if (ask("Human (W/S) vs Human (Up/Dn) Game"))
		play_pong(ws, ud);

	if (ask("Human (W/S) vs Random Game"))
		play_pong(ws, rnd1);

	if (ask("Random vs Random Visible Game"))
		play_pong(rnd1, rnd2);

	if (ask("Random vs Random Batch Games"))
	{
		const int pong_games = 1000;
		int wins = 0;
		auto start = chrono::high_resolution_clock::now();
		for (int i = 0; i < pong_games; i++)
		{
			if (play_pong(rnd1, rnd2, true))
				wins++;
		}
		auto time = chrono::high_resolution_clock::now() - start;
		write_line(to_string(pong_games) + " pong games in " + to_string(chrono::duration_cast<chrono::milliseconds>(time).count()) + "ms, " + to_string(wins) + "/" + to_string(pong_games-wins) + " p1/p2 wins.");
	}
	
	int q_agent_itr = 10000;
	if (ask("Human (W/S) vs QAgent Game"))
	{
		q_agent->train(trainer, 2, q_agent_itr);
		play_pong(ws, q_agent);
	}

	if (ask("QAgent vs QAgent Game"))
	{
		if (((QAgent*)q_agent)->total_iterations == 0) q_agent->train(trainer, 2, q_agent_itr);
		play_pong(q_agent, q_agent);
	}

	delete trainer;
}

void test_minimax(TicTacToe *game)
{
	MinimaxAgent minimax = MinimaxAgent(game->get_input_format());
	do
	{
		game->reset();
		write_line("\nAI vs Human GAME");
		write_line("Do you want to start first? (Y/N)");
		if (read_line() == "Y")
		{
			game->current_player = TicTacToe::Player::X;
		}
		else
		{
			game->current_player = TicTacToe::Player::O;
		}
		game->draw_game();
		while (game->state == TicTacToe::GameState::Playing)
		{
			if (game->current_player == TicTacToe::Player::O)
			{
				int ai_move = minimax.get_move(game);
				game->make_move(ai_move);
			}
			else
			{
				const vector<int> moves = game->get_possible_moves();
				write_line("Your move: ");
				write_line(to_string(moves));
				int move;
				while (!try_str_to_int(read_line(), move));
				game->make_move(move);
			}
			game->draw_game();
		}
		write_line("Do you want to go again? (Y/N)");
	} while (read_line() == "Y");
}

void evaluate_agents_random(TicTacToe *game, QAgent *q_agent)
{
	MinimaxAgent minimax = MinimaxAgent(game->get_input_format());

	write_line("Evaluating agents... Playing 20,000 random games to test performance");
	enum class Agent
	{
		QLearning,
		MiniMax, // SLOW
	};
	const int agent_count = 1; // only test QLearning due to extremely slow Minimax
	vector<string> agent_names = { "QLearning", "MiniMax" };
	int games_played[2] = {10000, 100};

	int games_won;
	int games_drawn;

	for (int cur_agent = 0; cur_agent < agent_count; cur_agent++)
	{
		games_won = 0; games_drawn = 0;
		for (int i = 0; i < games_played[cur_agent]; i++)
		{
			while (game->state == TicTacToe::GameState::Playing)
			{
				if (game->current_player == TicTacToe::Player::X)
				{
					int ai_move;
					switch (cur_agent)
					{
					case (int)Agent::MiniMax:
						ai_move = minimax.get_move(game);
						break;
					case (int)Agent::QLearning:
						ai_move = q_agent->get_move(game);
						break;
					}
					
					game->make_move(ai_move);
				}
				else
				{
					const vector<int> moves = game->get_possible_moves();
					game->make_move(moves[random_agent_play(moves.size())]);
				}
			}
			if (game->state == TicTacToe::GameState::X_Won)
			{
				games_won++;
			}
			if (game->state == TicTacToe::GameState::Draw)
			{
				games_drawn++;
			}
			game->reset();
		}

		stringstream ss;
		ss << agent_names[cur_agent] << " Evaluation\n";
		ss << "Games played: " << games_played[cur_agent] << "\n";
		ss << "Games won: " << games_won << " (" << games_won * 100 / games_played[cur_agent] << "%)" << "\n";
		ss << "Games drawn: " << games_drawn << " (" << games_drawn * 100 / games_played[cur_agent] << "%)" << "\n";
		write(ss.str());
	}
}

matrix_2d load_iris()
{
	string path = path_to_resource("iris_training.txt", resource_kind::OTHER_RESOURCE);

	ifstream ifs(path);
	string line;
	vector<string> lines;
	while(getline(ifs, line))
	{
		lines.push_back(line);
	}
	
	size_t width = count(lines[0].begin(), lines[0].end(), '\t') + 1;

	matrix_2d result(lines.size(), width);
	for (size_t i = 0; i < lines.size(); i++)
	{
		stringstream ss(lines[i]);
		string item;
		size_t j = 0;
		while(ss >> item) {
			result[i][j] = stod(item);
			j++;
		}
	}

	return result;
}

Dense *test_dense(matrix_2d &input, matrix_2d &target)
{
	Dense *dense = new Dense(input.y, 4, Sigmoid);
	matrix_2d output = dense->forward(matrix_slice(input, 0, 0));
	write_line(matrix_to_string(output));
	return dense;
}

void test_ann(matrix_2d &data)
{
	matrix_2d input = matrix_slice(data, 0, -1, 0, -4); // remove last 3 columns from dataset
	matrix_2d target = matrix_slice(data, 0, -1, -3, -1); // take last 3 columns from dataset
	write_line(matrix_to_string(input));
	write_line(matrix_to_string(target));

	Model model(MSE, 0.1);
	Dense *l1 = test_dense(input, target);
	matrix_2d initial = l1->forward(matrix_slice(input, 0, 0));
	matrix_2d initial_weights = matrix_2d(l1->get_weights());

	model.add_layer(l1);
	model.add_layer(new Dense(4, 3, Sigmoid));

	vector<double> loss;
	for (size_t i = 0; i < 1000; i++)
	{
		auto temp = model.train(input, target);
		loss.push_back(std::accumulate(temp.begin(), temp.end(), 0.0) / temp.size()); // Store average loss of epoch
		write_line("Loss: " + to_string(loss.back()));
	}

	matrix_2d result = model.predict(input);
	write_line(matrix_to_string(matrix_horizontal_concat(data, result)));

	matrix_2d trained = l1->forward(matrix_slice(input, 0, 0));
	
	if ((initial_weights == l1->get_weights()).all()) { write_line("WARNING: Training should change weights"); }
	if ((initial == trained).all()) { write_line("WARNING: Training should change output"); }

	write_line(matrix_to_string(matrix_horizontal_concat(matrix_horizontal_concat(input, to_categorical(target)), to_categorical(result))));
}

void run_machine_learning_test()
{
	if (ask("Run ANN test"))
	{
		matrix_2d iris_data = load_iris();
		write_line(matrix_to_string(iris_data));
		test_ann(iris_data);
	}

	if (ask("Run Pong test"))
	{
		test_pong();
	}

	if (ask("Run TicTacToe test"))
	{
		TicTacToe *game = new TicTacToe();

		test_reward_table();
		test_output_value();
		
		if (ask("Run QAgent test"))
		{
			// Test RL components
			QAgent *q_agent = new QAgent(game->get_output_format());

			write_line("Training for 100,000 iterations. Please wait...");
			q_agent->train(game, 2, 100000);
			write_line("Training complete.");

			play_tictactoe(q_agent);

			if (ask("Evaluate QAgent against minimax (slow)"))
			{
				// Test all agents against random agent
				evaluate_agents_random(game, q_agent);
			}
		}

		if (ask("Run minimax test"))
		{
			// Test minimax
			test_minimax(game);
		}
	}
}
