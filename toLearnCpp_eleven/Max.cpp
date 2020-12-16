#include <iostream>
#include <algorithm>

#if 0
struct _Iter_less_iter
{
    template<typename _Iterator1, typename _Iterator2>
    bool operator()(_Iterator1 it1, _Iterator2 it2)const
    {
        return *it1 < *it2;
    }
};

inline _Iter_less_iter __iter_less_iter()
{
    return _Iter_less_iter();
}

template<typename _ForwardIterator, typename _Compare>
_ForwardIterator __max_element(_ForwardIterator __first, _ForwardIterator __last,
                               _Compare _comp)
{
    if(__first == __last)
        return __first;
    _ForwardIterator ret = __first;
    while(++__first != __last)
    {
        if(_comp(ret, __first))
            ret = __first;
    }
    return ret;
}

template<typename _ForwardIterator>
inline _ForwardIterator
max_element(_ForwardIterator __first,
            _ForwardIterator __last)
{
    return __max_element(__first, __last, __iter_less_iter());
}

template<typename _Tp>
inline _Tp max(std::initializer_list<_Tp> _l)
{
    return *max_element(_l.begin(), _l.end());
}
#endif

int maximum(int n)
{
    return n;
}

template<typename... Args>
int maximum(int n, Args... args)
{
    return std::max(n, maximum(args...));
}

int main()
{
    std::cout << maximum(1, 9, 7, 22, 43) << std::endl;
}

