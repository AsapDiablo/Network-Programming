/**
 * @file suites.h
 * @comment
 * define all test suites here
 *
 * @author niexw
 * @email xiaowen.nie.cn@gmail.com
 */
 
#ifndef _TEST_SUITES_H_
#define _TEST_SUITES_H_

#include "LogTest.h"
#include "ExceptionTest.h"
#include "BasicFileTest.h"
#include "TaskQueueTest.h"
#include "ThreadPoolTest.h"
#include "DispatcherTest.h"
#include "SocketTest.h"

class LogTestSuite : public test_suite
{
  public:
	LogTestSuite() : test_suite("LogTestSuite")
	{
		boost::shared_ptr<LogTestCases> instance(new LogTestCases());
		add(BOOST_CLASS_TEST_CASE(&LogTestCases::testLog, instance));
	}
};

class ExceptionTestSuite : public test_suite
{
  public:
	ExceptionTestSuite() : test_suite("ExceptionTestSuite")
	{
		boost::shared_ptr<ExceptionTestCases> instance(new ExceptionTestCases());
		add(BOOST_CLASS_TEST_CASE(&ExceptionTestCases::testException, instance));
	}
};

class BasicFileTestSuite : public test_suite
{
  public:
	BasicFileTestSuite() : test_suite("BasicFileTestSuite")
	{
		boost::shared_ptr<BasicFileTestCases> instance(new BasicFileTestCases());
		add(BOOST_CLASS_TEST_CASE(&BasicFileTestCases::testFd, instance));
	}
};

class SocketTestSuite : public test_suite 
{
  public:
    SocketTestSuite() : test_suite("SocketTestSuite")
    {
        boost::shared_ptr<SocketTestCases> instance(new SocketTestCases());
        add(BOOST_CLASS_TEST_CASE(&SocketTestCases::test, instance));
    }
};

class TaskQueueTestSuite : public test_suite 
{
  public:
    TaskQueueTestSuite() : test_suite("TaskQueueTestSuite")
    {
        boost::shared_ptr<TaskQueueTestCases> instance(new TaskQueueTestCases());
        add(BOOST_CLASS_TEST_CASE(&TaskQueueTestCases::testPushPop, instance));
    }
};

class DispatcherTestSuite : public test_suite 
{
  public:
    DispatcherTestSuite() : test_suite("DispatcherTestSuite")
    {
        boost::shared_ptr<DispatcherTestCases> instance(new DispatcherTestCases());
        add(BOOST_CLASS_TEST_CASE(&DispatcherTestCases::testConstruct, instance));
        add(BOOST_CLASS_TEST_CASE(&DispatcherTestCases::testInterrupt, instance));
    }
};

class ThreadPoolTestSuite : public test_suite 
{
  public:
    ThreadPoolTestSuite() : test_suite("ThreadPoolTestSuite")
    {
        boost::shared_ptr<ThreadPoolTestCases> instance(new ThreadPoolTestCases());
        add(BOOST_CLASS_TEST_CASE(&ThreadPoolTestCases::testInit, instance));
    }
};
#endif // _TEST_SUITES_H_

