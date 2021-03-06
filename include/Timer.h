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
 *   >  Buddha bless:        Timer.h      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Wed 27 Jun 2018 08:56:24 AM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#ifndef _TIMER_H
#define _TIMER_H
#include <sys/timerfd.h>
#include <sys/time.h>
#include <stdio.h>
#include <set>

#include "BasicFile.h"
//#include "ThreadPool.h"

typedef void* (*CallbackFunc)(void*);

class Timer : public BasicFile
{
protected:
	struct Item
	{
		timespec time;
		CallbackFunc func;
		void *param;

		Item(timespec &t, CallbackFunc f, void *p) : func(f), param(p)
		{ time.tv_sec = t.tv_sec; time.tv_nsec = t.tv_nsec;	}
	};

	struct Comp
	{
		bool operator()(Item const &i1, Item const &i2)
		{
			return i1.time.tv_sec == i2.time.tv_sec ?
					i1.time.tv_nsec < i2.time.tv_nsec :
					i1.time.tv_sec < i2.time.tv_sec;
		}
	};

	std::multiset<Item, Comp> queue_;

public:
	typedef std::multiset<Item, Comp>::iterator Handle;

	Timer()
	{ create(); }
	~Timer()
	{ close(fd_); }

	size_t size()
	{ return queue_.size(); }

	Handle add(timespec &tv, CallbackFunc f, void *p)
	{
		timespec tvc;
		clock_gettime(CLOCK_MONOTONIC, &tvc);
		tvc.tv_sec += tv.tv_sec;
		tvc.tv_nsec += tv.tv_nsec;

		Item item(tvc, f, p);
		Handle h = queue_.insert(item);
		if (h == queue_.begin())
		{
			itimerspec t1;
			t1.it_interval = {0, 0};
			t1.it_value = {h->time.tv_sec, h->time.tv_nsec};
			if (timerfd_settime(fd_,
					TFD_TIMER_ABSTIME, &t1, NULL) != 0)
				//throw EXCEPTION();
                perror("error");
		}
		return h;
	}

	void remove(Handle h)
	{
		itimerspec t1;
		if (h == queue_.begin())
		{
			if (queue_.size() == 1) {
				queue_.erase(h);
				t1.it_interval = {0, 0};
				t1.it_value = {0, 0};
				timerfd_settime(fd_, TFD_TIMER_ABSTIME, &t1, NULL);
			} else {
				queue_.erase(h);
				h = queue_.begin();
				t1.it_interval = {0, 0};
				t1.it_value = {h->time.tv_sec, h->time.tv_nsec};
				timerfd_settime(fd_, TFD_TIMER_ABSTIME, &t1, NULL);
			}
			return;
		}
		else
			queue_.erase(h);
	}

	bool first(timespec &tv, CallbackFunc &f, void *&p)
	{
		if (queue_.size() > 0) {
			Handle h = queue_.begin();
			tv.tv_sec = h->time.tv_sec;
			tv.tv_nsec = h->time.tv_nsec;
			f = h->func;
			p = h->param;
			return true;
		} else
			return false;
	}

	void create()
	{
		fd_ = timerfd_create(CLOCK_MONOTONIC, 0);
		if (fd_ == -1)
	        perror("create error");
    }

	static void* callback(void *p)
	{
		Timer *This = (Timer*)p;
		Handle h = This->queue_.begin();
		CallbackFunc f = h->func;
		void *param = h->param;
		This->queue_.erase(h);
		return f(param);
	}

    
};
#endif
