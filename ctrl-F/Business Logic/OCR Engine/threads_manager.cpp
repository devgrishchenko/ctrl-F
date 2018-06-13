//
//  threads_manager.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-07.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "threads_manager.hpp"


pthread_mutex_t ThreadsManager::_mutexForCount;
pthread_attr_t ThreadsManager::_attr;
pthread_t *ThreadsManager::_threads;
int ThreadsManager::_threadsCount;
int ThreadsManager::_threadsNum;
ThreadsManager *ThreadsManager::sharedInstance;
function<void(long)> ThreadsManager::loopBody;


ThreadsManager::ThreadsManager(const int threadsCount) {
    
    _mutexForCount = PTHREAD_MUTEX_INITIALIZER;
    _threads = new pthread_t[threadsCount];
    _threadsCount = threadsCount;
    _threadsNum = threadsCount;
    
    pthread_attr_init(&_attr);
    pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED);
}


ThreadsManager *ThreadsManager::Instance(const int threadsCount) {
    
    if (!sharedInstance) {
        
        sharedInstance = new ThreadsManager(threadsCount);
    }
    
    return sharedInstance;
}


void *ThreadsManager::Manage(void *arg) {
    
    pthread_mutex_lock(&_mutexForCount);
    _threadsCount--;
    
    if (_threadsCount <= _threadsNum) {
        
        pthread_t temp;
        
        pthread_create(&temp, &_attr, ParallelLoop, arg);
        _threadsCount++;
    }
    
    pthread_mutex_unlock(&_mutexForCount);
    
    return NULL;
}


void *ThreadsManager::ParallelLoop(void *threadId) {
    
    loopBody((long)threadId);
    
    return NULL;
}


void ThreadsManager::ScheduleThreads() {
    
    for (unsigned long i = 0; i < _threadsNum; i++) {
        
        pthread_create(&_threads[i], NULL, Manage, (void *)i);
    }
    
    for (int i = 0; i < _threadsNum; i++) {
        
        pthread_join(_threads[i], NULL);
    }
    }
