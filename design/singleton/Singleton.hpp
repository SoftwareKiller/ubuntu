#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

#include <mutex>
#include <iostream>

using namespace std;

template <typename T>
class Singleton{
public:
    static T& Instance() {
        //static std::once_flag of;
        //std::call_once(of, [&]{ m_instance = new T;});
        return m_instance;
    }

    /*static void Release() {
        if(m_instance){
            delete m_instance;
            m_instance = nullptr;
        }
    }*/

private:
    Singleton();
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton operator=(const Singleton&) = delete;
private:
    //static T* m_instance;
    static T m_instance;
};

template <typename T>
T Singleton<T>::m_instance;
//T* Singleton<T>::m_instance = nullptr;

#endif
