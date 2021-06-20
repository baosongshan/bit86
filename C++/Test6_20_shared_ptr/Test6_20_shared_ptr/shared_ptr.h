#pragma once

#include"sysutil.h"
#include"shared_count.h"

template<class Type>
class shared_ptr
{
public:
	typedef shared_ptr<Type> this_type;
public:
	shared_ptr(Type *p):px(p),pn(p)
	{
#ifdef DISPLAY
		cout<<"Create SHARED_PTR"<<endl;
#endif
	}
	shared_ptr(const shared_ptr<Type> &r):px(r.px), pn(r.pn)
	{}

	shared_ptr& operator=( const shared_ptr& r )
    {
        this_type(r).swap(*this);
        return *this;
    }

	~shared_ptr()
	{
#ifdef DISPLAY
		cout<<"Free SHARED_PTR"<<endl;
#endif
	}
public:
	Type& operator*()
	{
		return *px;
	}
	Type* operator->()
	{
		return px;
	}
public:
	long use_count()const
	{
		return pn.use_count();
	}
	void swap(shared_ptr<Type> & other)
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }
private:
	Type        *px;
	shared_count pn; //对象成员
};