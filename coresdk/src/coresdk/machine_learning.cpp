#include "machine_learning.h"
using namespace std;

namespace splashkit_lib
{
	OutputValue *RewardTable::get_value(Game *game)
	{
		return get_value(game->get_input_format().convert_input(game->get_input()));
	}
}