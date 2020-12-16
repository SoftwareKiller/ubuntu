#include <iostream>

using namespace std;

#if 0
class CustomerHash{
public:
    size_t operator()(const Customer& c)const {
        return hash_value(c.fname, c.lname, c.no);
    }
};

//first step
template <typename... Types>
inline size_t hash_val(const Types&... args) {
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

//second step
template <typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

//third step
template <typename T>
inline void hash_val(size_t& seed, const T& val)
{
    hash_combine(seed, val);
}

//fourth step
template <typename T>
inline void hash_combine(size_t&seed, const T& val)
{
    seed ^= hash<T>()(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

#endif

void print()
{}

template <typename T, typename...Types>
void print(const T&firstArg, const Types&... args)
{
    cout << sizeof...(args) << endl;  //sizeof...可以计算出pack中有多少参数
    cout << firstArg << endl;
    print(args...);
}

template <typename... Type>
void print(const Type&... args)
{
}

int main()
{
    print(4, 9, "hello C++11");
}

