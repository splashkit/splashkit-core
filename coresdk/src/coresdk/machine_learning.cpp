#include "machine_learning.h"
using namespace std;

namespace splashkit_lib
{
	// Late declaration of OutputFormat functions that require QValue
	int OutputFormat::get_max_position(QValue &data, int index, vector<int> filter, bool random)
	{
		if (format[index] != Type::Position)
			throw invalid_argument("Format at index is not of type Position!");
		index = indexes[index]; // Grab the starting index for the given position data
		if (random)
		{
			int out = filter[rnd(filter.size())];
			// update q_table
			data.to_update(out);
			return out;
		}
		float max = data[index + filter[0]];
		int max_pos = filter[0];
		for (int i = 1; i < filter.size(); i++)
		{
			if (data[index + filter[i]] > max)
			{
				max = data[index + filter[i]];
				max_pos = filter[i];
			}
		}
		data.to_update(max_pos);
		return max_pos;
	}

	class QAgent
	{
	private:
		OutputFormat *out_format;
		float learning_rate = 0.1f;
		float discount_factor = 0.9f;
		float epsilon = 0.1f;

		QTable *q_table;

	public:
		vector<QValue> q_history; // Store the q_values used for the last game

		QAgent(QTable *q_table, OutputFormat *out_format)
		{
			this->q_table = q_table;
			this->out_format = out_format;
		}

		int get_move(Game &game)
		{
			vector<bool> input = game.convert_board();
			QValue q_output = q_table->get_q_value(input);
			return game.convert_output(q_output, rnd() < epsilon);
		}

		void reward(float score)
		{
			for (QValue &q : q_history)
			{
				q.update(score);
			}
			q_history.clear();
		}
	};

	class QTrainer
	{
		QTable *q_table;
		OutputFormat *out_format;

		QTrainer(Game game)
		{
			OutputFormat format = game.get_output_format();
			QTable _q_table = QTable(&format);
			q_table = &_q_table;
			out_format = &format;
		}

		void train(int player_count, int iterations)
		{
			for (int i = 0; i < iterations; i++)
			{
				Game cur_game;		   // generate the game
				vector<QAgent> agents; // generate the agents to play the game
				for (int i = 0; i < player_count; i++)
				{
					agents.push_back(QAgent(q_table, out_format));
				}
				while (cur_game.step())
				{
					int move = agents[cur_game.get_current_player()].get_move(cur_game);
					cur_game.make_move(move);
				}
				// Update q_table
				vector<float> scores = cur_game.score();
				for (int i = 0; i < scores.size(); i++)
				{
					float score = scores[i];
					agents[i].reward(score);
				}
			}
		}
	};

}