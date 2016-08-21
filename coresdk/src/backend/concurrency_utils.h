//
//  concurrency_driver.h
//  splashkit
//
//  Created by James Armstrong on 21/08/2016
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef sgsdl2_SGSDL2ConcurrencyUtils_h
#define sgsdl2_SGSDL2ConcurrencyUtils_h

#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

class semaphore {
private:
    mutex mut;
    condition_variable condition;
    int tokens;

public:
    semaphore()
    {
        tokens = 0;
    }

    semaphore(int tokens)
    {
        this->tokens = tokens;
    }

    void acquire()
    {
        unique_lock<mutex> lock(mut);
        while (tokens <= 0)
        {
            condition.wait(lock);
        }
        tokens--;
    }

    void release(int num = 1)
    {
        lock_guard<mutex> lock(mut);
        tokens += num;
        condition.notify_all();
    }
};

#endif // sgsdl2_SGSDL2ConcurrencyUtils_h
