//
//  threads_manager.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-07.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

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
    
protected:
    
    ThreadsManager(const int threadsCount) {
        
        _mutexForCount = PTHREAD_MUTEX_INITIALIZER;
        _threads = new pthread_t[threadsCount];
        _threadsCount = threadsCount;
        _threadsNum = threadsCount;
        
        pthread_attr_init(&_attr);
        pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED);
    }
    
public:
    
    static ThreadsManager *sharedInstance;
    static function<void(long)> loopBody;
    
    static ThreadsManager *Instance(const int threadsCount) {
        
        if (!sharedInstance) {
            
            sharedInstance = new ThreadsManager(threadsCount);
        }
        
        return sharedInstance;
    }
    
    
    static void *Manage(void *arg) {
        
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
    
    
    static void *ParallelLoop(void *threadId) {
        
        loopBody((long)threadId);
        
        return NULL;
    }
    
    
    void ScheduleThreads() {
        
        for (unsigned long i = 0; i < _threadsNum; i++) {
            
            pthread_create(&_threads[i], NULL, Manage, (void *)i);
        }
        
        for (int i = 0; i < _threadsNum; i++) {
            
            pthread_join(_threads[i], NULL);
        }
    }
};
