#include <iostream>
#include <algorithm>

void print(std::initializer_list<int> vals)
{
    for(auto it = vals.begin(); it != vals.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    print({1, 3, 9, 2, 5, 4, 6});
    std::cout << std::max({1, 9, 2, 4, 99, 87, 43}) << std::endl;
    return 0;
}

