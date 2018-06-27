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
 *   >  Buddha bless:        ThreadPoolTest.cc      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Mon 25 Jun 2018 10:40:22 AM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#include <boost/test/test_tools.hpp>
#include <string>
#include <iostream>

#include <ThreadPool.h>
#include "ThreadPoolTest.h"

void ThreadPoolTestCases::testInit()
{
    ThreadPool pool;
    pool.thread_make(4);
    sleep(1);
    pool.start();
    pool.stop();
    BOOST_CHECK(pool.ready());
}


