#pragma once

#include"sysutil.h"

class sp_counted_base
{
public:
	sp_counted_base() : use_count_(1)
	{
#ifdef DISPLAY
		cout<<"Create SP_COUNTED_BASE"<<endl;
#endif
	}
	virtual ~sp_counted_base()
	{
#ifdef DISPLAY
		cout<<"Free SP_COUNTED_BASE"<<endl;
#endif
	}
public:
	virtual void dispose() = 0;
public:
	void add_ref_copy()
	{
		++use_count_;
	}
	void release()
	{
		if(--use_count_ == 0)
		{
			this->dispose();
			delete this;
		}
	}
	long use_count()const
	{
		return use_count_;
	}
private:
	long use_count_;
};