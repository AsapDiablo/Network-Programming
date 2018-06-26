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
 *   >  Buddha bless:        TaskQueue.h      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Thu 31 May 2018 02:42:48 PM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include <list>
#include <mutex>
#include "Task.h"

class TaskQueue 
{
protected:
    //这里如果只给出一个队列链表的头指针，而且Task中
    //包含前驱和后继指针，每次插入任务的时候只需要修改
    //指针(因为插入前用户肯定已经把Task内容包装好),
    //这样就可以省去如果是用list或vector时的插入对象而
    //分配或删除的内存空间
    std::list<Task*> queue_;
    std::mutex mutex_;
public:
    bool empty(){ return queue_.empty(); }
    size_t size(){ return queue_.size(); }
    void push(Task &task)
    {
        mutex_.lock();
        queue_.push_back(&task);
        mutex_.unlock();
    } 

    Task* pop()
    {
        mutex_.lock();
        if (queue_.empty()) {
            //访问过了queue_的指针后解锁
            //
            mutex_.unlock();
            return NULL; 
        }else {
            Task* task = queue_.front();
            queue_.pop_front();
            mutex_.unlock();
            return task;
        }
    }
};

#endif
