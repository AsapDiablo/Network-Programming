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
 *   >  Buddha bless:        DispatcherTest.cc      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Thu 07 Jun 2018 02:53:06 PM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#include <boost/test/test_tools.hpp>
#include <string>
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <Dispatcher.h>
#include <TaskQueue.h>
#include "DispatcherTest.h"

void DispatcherTestCases::testConstruct()
{

    TaskQueue que;
    Dispatcher dispatcher(&que);
    int ret = dispatcher.create();
    BOOST_CHECK(dispatcher.getFd() > 0);

    
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    BOOST_CHECK(fd != -1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.ptr = &fd;
    ret = dispatcher.control(fd, EPOLL_CTL_ADD, event);
    BOOST_CHECK(ret == 0);

    event.events = EPOLLOUT;
    ret = dispatcher.control(fd, EPOLL_CTL_ADD, event);
    BOOST_CHECK(ret == EEXIST);

    ret = dispatcher.control(fd, EPOLL_CTL_MOD, event);
    BOOST_CHECK(ret == 0);
    ret = dispatcher.control(fd, EPOLL_CTL_DEL, event);
    BOOST_CHECK(ret == 0);

    ret = dispatcher.control(fd, EPOLL_CTL_MOD, event);
    BOOST_CHECK(ret == ENOENT);
    std::cout<<"Test done"<<std::endl;
}

void DispatcherTestCases::testInterrupt()
{
    TaskQueue que;
    Dispatcher dispatcher(&que);
    int ret = dispatcher.create();
    BOOST_CHECK(ret == 0);

    ret = dispatcher.interrupt();
    BOOST_CHECK(ret == sizeof(void*));
    dispatcher.wait();
   

}


