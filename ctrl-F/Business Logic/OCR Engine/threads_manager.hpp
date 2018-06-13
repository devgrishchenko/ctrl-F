//
//  threads_manager.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-13.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#ifndef threads_manager_h
#define threads_manager_h

#include <stdio.h>
#include <pthread.h>
#include <functional>

using namespace std;

class ThreadsManager {
    
private:
    
    static pthread_mutex_t _mutexForCount;
    static pthread_attr_t _attr;
    static pthread_t *_threads;
    static int _threadsCount;
    static int _threadsNum;
    static ThreadsManager *_sharedInstance;
    
    ThreadsManager(const int threadsCount);

public:
    
    
    static ThreadsManager *Instance(const int threadsCount = NULL);
    static void *Manage(void *arg);
    static void *ParallelLoop(void *threadId);
    static function<void(long)> loopBody;
    void ScheduleThreads();
};
#endif 
