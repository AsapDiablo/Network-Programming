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
 *   >  Buddha bless:        Thread.h      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Mon 25 Jun 2018 10:20:24 AM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#ifndef _THREAD_H
#define _THREAD_H
#include <pthread.h>
#include "ThreadPool.h"
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

class ThreadPool;

class Thread 
{
public:
    Thread(){}
    ~Thread(){}

    unsigned long* tid() { return &tid_; }
    void setPool(ThreadPool* pool){ pool_ = pool; }
protected:
    pthread_t tid_;
    long tcount_; 
    ThreadPool* pool_;
};

#endif
