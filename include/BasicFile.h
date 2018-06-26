////
// @file BasicFile.h
// @brief
// declare the class BasicFile
//
// @author niexw
// @email xiaowen.nie.cn@gmail.com
//
#ifndef _BASICFILE_H_
#define _BASICFILE_H_

class BasicFile
{
  private:
	int fd_;

  public:
	BasicFile() : fd_(-1) {}
	explicit BasicFile(int fd) : fd_(fd) {}
	~BasicFile() { close_(); }

	int fd() { return fd_; }
	void detach(int &fd)
	{
		fd = fd_;
		fd_ = -1;
	}

#if 0
	int stat()
	{}
	int chown()
	{}
	int chmod()
	{}
#endif	
	
  private:
	void close_()	
	{
		if (fd_ != -1) {
			::close(fd_);
			fd_ = -1;
		}
	}
};

#endif // _BASICFILE_H_
