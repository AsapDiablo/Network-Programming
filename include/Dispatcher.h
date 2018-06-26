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
 *   >  Buddha bless:        Dispatcher.h      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Thu 07 Jun 2018 02:40:23 PM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#ifndef _DISPATCHER_H
#define _DISPATCHER_H

#include <sys/epoll.h>
#include <errno.h>
#include <fcntl.h>
#include "TaskQueue.h"
#include "Task.h"

class Dispatcher 
{
public:
    Dispatcher(TaskQueue* q):
    epoll_(-1),
    read_pipe_(-1),
    write_pipe_(-1),
    queue_(q){   
        create();
    }
    ~Dispatcher(){ close(); }
    int create(){
        epoll_ = epoll_create(1);
        int fd[2];
        int ret = pipe2(fd, O_NONBLOCK);
        if(ret == -1) return errno;
        read_pipe_ = fd[0];
        write_pipe_ = fd[1];

        struct epoll_event event = {EPOLLIN|EPOLLET, {&read_pipe_}};
        ret = epoll_ctl(epoll_, EPOLL_CTL_ADD, read_pipe_, &event);
        return epoll_ == -1 ? errno:0;
    }   
    void close()
    { 
        if(epoll_ != -1)
        {
            ::close(epoll_);
            epoll_ = -1; 
        }

        ::close(read_pipe_);
        read_pipe_ = -1;
        ::close(write_pipe_);
        write_pipe_ = -1;
    }

    int getFd() const { return epoll_; }
    int control(int fd, int op, struct epoll_event &event){
        int ret = epoll_ctl(epoll_, op, fd, &event);
        return ret == -1 ? errno : 0;
    }

    int interrupt()
    {
        int *buf = &read_pipe_;
        int ret = write(write_pipe_, buf, sizeof(buf));
        return ret;
    }
    
    void wait()
    {
        static const size_t EventsNum = 128;
        struct epoll_event events[EventsNum];
        
        while(1)
        {
            int ret = epoll_wait(epoll_, events, EventsNum, -1); 
            if( ret == -1 && errno == EINTR) continue;


            for(int i = 0 ; i < ret; i++)
            {
                Task* task = reinterpret_cast<Task*>(events[i].data.ptr);
                if( task == NULL ) 
                    continue;
                else if( task == reinterpret_cast<Task*>(&read_pipe_) )
                    return;
                else 
                   // queue_->push(*task);
                    printf("enqueue\n");
            }
            
        }

    }
protected:
    int epoll_;  //the descriptor of epoll
    int read_pipe_;
    int write_pipe_;
    TaskQueue* queue_;
};

#endif
