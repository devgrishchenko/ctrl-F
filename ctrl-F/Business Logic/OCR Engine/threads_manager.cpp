//
//  threads_manager.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-07.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "threads_manager.hpp"


ThreadsManager::ThreadsManager(const int &threadsCount) {
    
    _mutexForCount = PTHREAD_MUTEX_INITIALIZER;
    _threads = new pthread_t[threadsCount];
    _threadsCount = threadsCount;
    _threadsNum = threadsCount;
    pthread_attr_init(&_attr);
    pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED);
}


void *ThreadsManager::Manage(void *arg) {
    
    pthread_mutex_lock(&_mutexForCount);
    _threadsCount--;
    
    if (_threadsCount <= _threadsNum) {
        
        pthread_t temp;
        pthread_create(&temp, &_attr, this->ParallelLoop, arg);
        _threadsCount++;
    }
    
    pthread_mutex_unlock(&_mutexForCount);
    
    return NULL;
}


void *ThreadsManager::ParallelLoop(void *threadId) {
    
    return NULL;
}


void ThreadsManager::ScheduleThreads() {
    
    
}
