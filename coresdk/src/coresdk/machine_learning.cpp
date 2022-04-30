#include "machine_learning.h"
using namespace std;

namespace splashkit_lib
{
	// Late declaration of OutputFormat functions that require QValue

	/**
	 * @brief Gets the index of the maximum reward value for the given format index.
	 * 
	 * @param data The reward values.
	 * @param index The format index indicating which subsection of the reward values to consider.
	 * @param filter A whitelist filter to filter the reward values based on the valid indexes to consider. TODO: allow none or null values
	 * @param random The global random to be passed down, determines if the move should be randomly chosen.
	 * @return int The index of the maximum reward value.
	 */
	int OutputFormat::get_max_position(QValue *data, int index, vector<int> filter, bool random)
	{
		if (format[index] != Type::Position)
			throw invalid_argument("Format at index is not of type Position!");
		index = indexes[index]; // Grab the starting index for the given position data
		if (random)
		{
			int out = filter[rnd(filter.size())];
			// update q_table
			data->to_update(out);
			return out;
		}
		float max = data->at(index + filter[0]);
		int max_pos = filter[0];
		for (int i = 1; i < filter.size(); i++)
		{
			if (data->at(index + filter[i]) > max)
			{
				max = data->at(index + filter[i]);
				max_pos = filter[i];
			}
		}
		data->to_update(max_pos);
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
	float OutputFormat::process_output_number(QValue *data, int index, bool random)
	{
		if (format[index] != Type::Number) throw invalid_argument("Format at index is not of type Number!");
		data->to_update(indexes[index]); // Tells the AI that the number was retrieved and should be updated during reward/punishment
		return (random ? rnd() : data->at(indexes[index])) * f_data[index]; // Scale the number to the previously given range [0, f_data[index]]
	}

	QValue *QTable::get_q_value(Game *game)
	{
		return get_q_value(game->get_input_format()->convert_input(game->get_input()));
	}
}