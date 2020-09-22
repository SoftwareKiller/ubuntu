//#include "BTree.h"
#include "BPTree.h"
#include <iostream>

template<typename T, size_t N = 3>
struct m{
    T x = 1;
    int s = N;
};

int main() {
    using namespace std;
    //BTreeNode<int, 3> node;
    //m<int, 10> p;
    //cout << p.x << " " << p.s << endl;
    /*BTree<int, int> bt;
    bt.Insert(53);
    bt.Insert(75);
	bt.Insert(139);
	bt.Insert(49);
	bt.Insert(145);
	bt.Insert(36);
	bt.Insert(101);
	bt.InOrder();*/

    BTree<int, int, 16> bt;
	int a[] = { 53, 49, 75, 139, 145, 36, 101 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		bt.Insert(std::make_pair(a[i], i));
	}
	bt.InOrder();
}

