#include <iostream>
#include <stack>

template<typename T>
class Queue{
public:
    Queue() = default;
    ~Queue() = default;
public:
    void push(T val) {
        input.push(val);
    }

    T pop() {
        if(output.empty()) {
            while(!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        T ret = output.top();
        output.pop();
        return ret;
    }

    bool empty() {
        return input.empty() && output.empty();
    }

private:
    std::stack<T> input;
    std::stack<T> output;
};

int main() {
    Queue<int> q;
    q.push(12);
    q.push(13);
    q.push(14);
    q.push(15);
    q.push(16);
    q.push(17);

    while(!q.empty()) {
        std::cout << q.pop() << std::endl;
    }
}

