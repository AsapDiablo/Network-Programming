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
 *   >  Buddha bless:        TimerTest.cc      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Wed 27 Jun 2018 09:03:02 AM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#include <boost/test/test_tools.hpp>
#include <string>
#include <iostream>

#include <Timer.h>
#include "TimerTest.h"

void TimerTestCases::testRun()
{
    Timer t;
    BOOST_CHECK(t.fd() > 0);

}
