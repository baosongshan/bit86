#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

template<class Type>
class SeqList
{
public:
	SeqList(int sz = 8);
	~SeqList();
public:
	bool full()const;
public:
	void push_back(const Type &x);
private:
	const int SEQLIST_DEFAULT_SIZE = 8; 
private:
	Type *base;
	size_t capacity;
	size_t size;
};

template<class Type>
SeqList<Type>::SeqList(int sz)
{
	capacity = sz > SEQLIST_DEFAULT_SIZE ? sz : SEQLIST_DEFAULT_SIZE;
	base = new Type[SEQLIST_DEFAULT_SIZE];
	assert(base != NULL);
	size = 0;
}

template<class Type>
SeqList<Type>::~SeqList()
{
	delete[]base;
	base = nullptr;
	capacity = size = 0;
}
