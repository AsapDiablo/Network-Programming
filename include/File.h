////
// @file File.h
// @brief
// declare the class File
//
// @author niexw
// @email xiaowen.nie.cn@gmail.com
//
#ifndef _FILE_H_
#define _FILE_H_

#include <errno.h>
#include <BasicFile.h>

class File : public BasicFile
{
  public:
	int open(const char *path, int flags)
	{
		this->fd_ = ::open(path, flags);
		if (this->fd_ == -1)
			return errno;
	}
	int open(const ::std::string path, int flags)
	{
		return open(path.c_str(), flags);
	}
};

#endif // _FILE_H_

