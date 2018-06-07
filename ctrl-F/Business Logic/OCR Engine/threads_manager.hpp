//
//  threads_manager.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-07.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#ifndef threads_manager_hpp
#define threads_manager_hpp

#include <stdio.h>
#include <pthread.h>

class ThreadsManager {

private:
    
    pthread_mutex_t _mutexForCount;
    pthread_attr_t _attr;
    pthread_t *_threads;
    int _threadsCount;
    int _threadsNum;
    
public:
    
    ThreadsManager(const int &threadsCount);
    void *Manage(void *arg);
    void *ParallelLoop(void *threadId);
    void ScheduleThreads();
};
#endif
