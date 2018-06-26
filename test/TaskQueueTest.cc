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
 *   >  Buddha bless:        TaskQueueTest.cc      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Thu 31 May 2018 03:11:19 PM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#include <boost/test/test_tools.hpp>
#include <string>
#include <iostream>
	  
#include <TaskQueue.h>
#include "TaskQueueTest.h"
#include "Task.h"

void TaskQueueTestCases::testPushPop()
{
    TaskQueue queue;
    Task t1, t2, t3;

    BOOST_CHECK(queue.empty());
    queue.push(t1);
    BOOST_CHECK(!queue.empty());
    BOOST_CHECK(queue.size() == 1);
    //BOOST_CHECK(true);  
    
    Task* task = queue.pop();
    BOOST_CHECK(task == &t1);
    BOOST_CHECK(queue.size() == 0);
    BOOST_CHECK(queue.empty());

    queue.push(t2);
    queue.push(t3);
    BOOST_CHECK(queue.size() == 2);
    BOOST_CHECK(!queue.empty());

    task = queue.pop();
    BOOST_CHECK(task == &t2);
    BOOST_CHECK(queue.size() == 1);
    
    
    task = queue.pop();
    BOOST_CHECK(task == &t3);
    BOOST_CHECK(queue.size() == 0);
    BOOST_CHECK(queue.empty());

    task = queue.pop();
    BOOST_CHECK(task == NULL);
}
