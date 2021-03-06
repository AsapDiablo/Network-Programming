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
#include <functional>
//#include "ThreadPool.h"
#include "Data.h"

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

#endif
