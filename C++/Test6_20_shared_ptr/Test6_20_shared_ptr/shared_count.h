#pragma once

#include"sysutil.h"
#include"sp_counted_base.h"
#include"sp_counted_impl.h"

class shared_count
{
public:
	shared_count(): pi_(0) 
    {
    }
	template<class Y>
	shared_count(Y *p) : pi_(new sp_counted_impl<Y>(p))
	{
#ifdef DISPLAY
		cout<<"Create SHARED_COUNT"<<endl;
#endif
	}
	shared_count(const shared_count &r):pi_(r.pi_)
	{
		if(pi_ != 0)
			pi_->add_ref_copy();
	}
	~shared_count()
	{
#ifdef DISPLAY
		cout<<"Free SHARED_COUNT"<<endl;
#endif
		if(pi_ != 0)
			pi_->release();
	}
public:
	long use_count()const
	{
		return pi_->use_count();
	}
	void swap(shared_count & r)
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }
private:
	sp_counted_base *pi_;
};