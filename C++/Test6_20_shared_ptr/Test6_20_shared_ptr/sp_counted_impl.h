#pragma once

#include"sysutil.h"
#include"sp_counted_base.h"

template<class X>
class sp_counted_impl : public sp_counted_base
{
public:
	sp_counted_impl(X *px) : px_(px)
	{
#ifdef DISPLAY
		cout<<"Create SP_COUNTED_IMPL"<<endl;
#endif
	}
	~sp_counted_impl()
	{
#ifdef DISPLAY
		cout<<"Free SP_COUNTED_IMPL"<<endl;
#endif
	}
public:
	void dispose()
	{
		delete px_;
	}
private:
	X *px_;
};