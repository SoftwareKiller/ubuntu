#include <iostream>
#include <string>
#include <bitset>
#include <tuple>

using namespace std;

template<int IDX, int MAX, typename...Args>
struct PRINT_TUPLE{
    static void Print(ostream& os, const tuple<Args...>& t)
    {
        os << get<IDX>(t) << (IDX+1 == MAX ? "" : ",");
        PRINT_TUPLE<IDX+1, MAX, Args...>::Print(os, t);
    }
};

template<int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...>{
    static void Print(ostream& os, const tuple<Args...>& t)
    {}
};

template<typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t)
{
    os << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::Print(os, t);
    return os << "]" << endl;
}

int main()
{
    cout << make_tuple(7.5, string("hello"), bitset<16>(377), 42);
}

