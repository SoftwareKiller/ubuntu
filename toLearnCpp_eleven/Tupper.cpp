#include <iostream>
#include <string>
#include <bitset>
#include <tuple>

using namespace std;

#if 0
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
#endif

template<typename...Values>
class Tuple;
template<> class Tuple<>{};

template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...>
{
    typedef Tuple<Tail...> inherited;
public:
    Tuple(){}
    Tuple(Head v, Tail... vtail)
        :m_head(v), inherited(vtail...) //这里的inherited循环创建initialization list,调用父类的构造
    {}
    Head head()
    {
        return m_head;
    }
    inherited& tail()
    {
        return *this;
    }
protected:
    Head m_head;
};

int main()
{
    Tuple<int, double, string> tp(8, 9.6, "Template is cool");
    cout << tp.head() << endl;
    cout << tp.tail().head() << endl;
    cout << tp.tail().tail().head() << endl;
}

