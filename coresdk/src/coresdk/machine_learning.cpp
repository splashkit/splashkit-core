#include "machine_learning.h"
using namespace std;

namespace splashkit_lib
{
	// Late declaration of OutputFormat functions that require QValue
	int OutputFormat::get_max_position(QValue* data, int index, vector<int> filter, bool random)
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

}