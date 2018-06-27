/**
 *                             _ooOoo_
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  =  /O
 *                         ____/`---'\____
 *                       .'  \|       |/  `.
 *                      /  \\|||  :  |||//  \
 *                     /  _||||| -:- |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     |  _|  ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. /
 *                   ___`. .'  /--.--  `. . ___
 *                ."" '<  `.___\_<|>_/___.'  >'"".
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /
 *          ======`-.____`-.________/___.-`____.-'======
 *                             `=---='
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *   >  Buddha bless:        ThreadPool.h      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Mon 25 Jun 2018 10:25:15 AM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <pthread.h>
#include <list>
#include <iostream>
#include <mutex>
#include <condition_variable>

//#include "Thread.h"
#include "Data.h"

void* thread_main(void* arg)
{  
    std::unique_lock<std::mutex> LOCK(MUTEX);
    while(!READY)
    {
        printf("thread %ld waiting\n", pthread_self());
        COND.wait(LOCK);
    }
    printf("thread %ld signaling\n", pthread_self());
    /* execute thread func below*/
    
    return NULL;
}
typedef void* (*CallbackFunc)(void*);
//class ThreadPool;

class Thread 
{
public:
    Thread(){}
    ~Thread(){}

    unsigned long* tid() { return &tid_; }
  //  void setPool(ThreadPool* pool){ pool_ = pool; }
    void assignCallBack(CallbackFunc cb){ cb_ = cb; }
    CallbackFunc getCallBack() { return cb_; }
protected:
    pthread_t tid_;
    long tcount_; 
    CallbackFunc cb_;
  //  ThreadPool* pool_;
};

class ThreadPool
{
//friend class Thread;
public:
    ThreadPool(){}
    ~ThreadPool(){}

     
    void thread_make(int count){
        for(auto i = 0; i < count; i++)
        {
            Thread t;
           // t.setPool(this);
           
            t.assignCallBack(thread_main);
            pthread_create(t.tid(), NULL, t.getCallBack(), (void*)&count); 
            tids_.push_back(*t.tid()); 
        }
    }

    bool ready(){ 
        if(tids_.size() > 0)
            return true;
        else 
            return false;
    }

    void start(){
        READY = true;
        //std::unique_lock<std::mutex> LOCK(MUTEX);
        COND.notify_all(); 
    }

    void stop(){
        for(auto tid : tids_)
            pthread_join(tid, NULL);
    }

protected:
    std::list<pthread_t> tids_;
};
#endif
