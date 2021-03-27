#pragma once

template<class _Ty> 
_Ty  *_My_Allocate(size_t _N, _Ty *)
{
	if (_N < 0)
		_N = 0;
	return ((_Ty *)operator new(_N * sizeof (_Ty)));
}

template<class _T1, class _T2> 
void _My_Construct(_T1  *_P, const _T2& _V)
{
	new((void *)_P) _T1(_V); //��λnew  String(_V);
}

template<class _Ty> 
void _Destroy(_Ty *_P)
{
	_P->~_Ty(); //�൱�ڵ�����������
}

//�ռ�������
template<class _Ty>
class my_allocator
{
public:
	//����ռ�
	_Ty* allocate(size_t _N, const void *)
	{
		return (_My_Allocate(_N, (_Ty*)0));
	}
	//�����ֽڿռ�
	char *_Charalloc(size_t _N)
	{
		return (_My_Allocate(_N,(char *)0));
	}
	//�ͷſռ�
	void deallocate(void *_P, size_t)
	{
		operator delete(_P);
	}
	//�������
	void construct(_Ty * _P, const _Ty& _V)
	{
		_My_Construct(_P, _V);
	}
	//��������
	void destroy(_Ty *_P)
	{
		_Destroy(_P);
	}
};