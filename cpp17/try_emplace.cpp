#include <map>
#include <iostream>
#include <memory>

using namespace std;

class Object
{
public:
    Object(int64_t ullID)
    {
        m_ullObjId = ullID;
        cout << "Object ID:" << m_ullObjId << endl;
    }

    ~Object()
    {
        cout << "Destructor" << endl;
    }
private:
    int64_t m_ullObjId;
};

map<int64_t, unique_ptr<Object>> m_Mgr;

void AddObj(int64_t ullId)
{
    auto [iter,inserted] = m_Mgr.try_emplace(ullId, nullptr);
    if(inserted)
    {
        auto spObj = make_unique<Object>(ullId);
        iter->second = move(spObj);
    }
}

int main()
{
    AddObj(20210901);
    AddObj(20210902);
    AddObj(20210902);
}

