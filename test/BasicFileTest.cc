////
// @file BasicFileTest.cc
// @brief
// implement the test cases of BasicFile
//
// @author niexw
// @email xiaowen.nie.cn@gmail.com
//
#include <boost/test/test_tools.hpp>
#include <string>
#include <iostream>

#include <BasicFile.h>
#include "BasicFileTest.h"

void BasicFileTestCases::testFd()
{
	int fd = 5;
	BasicFile file(fd);
	BOOST_CHECK(file.fd() == 5);
}

