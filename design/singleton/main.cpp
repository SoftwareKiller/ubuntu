#include <iostream>
#include <thread>
#include <string>
#include "Singleton.hpp"

using namespace std;

class Init {
public:
    void set(string& s) {
        str_ = s;
        cout << str_ << endl;
    }
    string str_;
};

void print() {
    cout << "call once" << endl;
}

int main() {
    string s{"hello"};
    //Singleton<Init>::Instance()->set(s);
    //once_flag oc;
    //call_once(oc, print);
    Singleton<Init>::Instance().set(s);
;}

