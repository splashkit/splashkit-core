#include "sk_clib.h"

#include <iostream>
using namespace std;

int main()
{
    __sklib__open_audio();
    cout << "HELLO" << __sklib__audio_ready() << endl;
    __sklib__close_audio();

    return 0;
}
