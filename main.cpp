#include <iostream>
//#include "myhashmap.h"
#include "md5.h"
#include "myhashmap.cpp"

using namespace std;

class Test{
public:
    Test(const char *a, int b) {
        this->b = b;
        this->a = new char[sizeof (a)];
        strcpy(this->a, a);
        cout << "test created" << endl;
    }
    ~Test(){
        if (a!=nullptr)
            delete [] a;
        cout << "test deleted" << endl;
    }
    int b;
    char *a = nullptr;
};

struct MyHash {
    char value[33];
};
ostream & operator << (ostream &out, const MyHash &c)
{
    out << c.value;
    return out;
}

MyHash fun(const Test *element) {
    MyHash hash;
    string s1 = to_string(element->b);
    string s2 = string(element->a);
    string s = s1+s2;
    string md5Hash = md5(s);
    strcpy(hash.value,md5Hash.substr(0,32).c_str());
    return hash;
}
int comp(const MyHash *l, const MyHash *r){
    return strcmp(l->value, r->value);
}

struct MyHash1 {
    size_t value;
};
ostream & operator << (ostream &out, const MyHash1 &c)
{
    out << c.value;
    return out;
}

MyHash1 fun1(const Test *element) {
    MyHash1 hash;
    hash.value = strlen(element->a);
    return hash;
}
int comp1(const MyHash1 *l, const MyHash1 *r){
    return static_cast<int>(l->value - r->value);
}

int main()
{
    MyHashMap<Test, MyHash> *myHashMap = new MyHashMap<Test, MyHash>(&fun, &comp);
//    MyHashMap<Test, MyHash1> *myHashMap = new MyHashMap<Test, MyHash1>(&fun1, &comp1);
    Test a(static_cast<char const*>("dbcas"), 5);
    Test b(static_cast<char const*>("abc"), 3);
    Test c(static_cast<char const*>("abcdaawd"), 40);
    Test d(static_cast<char const*>("abac"), 4);
    Test e(static_cast<char const*>("abadawdawc"), 41);
    Test f(static_cast<char const*>("abcdw"), 5);
    myHashMap->append(&a);
    myHashMap->append(&b);
    myHashMap->append(&c);
    myHashMap->append(&d);
    myHashMap->append(&e);

    Test *found = &f;

    if (myHashMap->find(found))
        cout << found->a << " found" << endl;
    else
        cout << found->a << " not found" << endl;

    found = &d;

    if (myHashMap->find(found))
        cout << found->a << " found" << endl;
    else
        cout << found->a << " not found" << endl;

    myHashMap->printAll();
    cout << "------" << endl;
    myHashMap->remove(&a);
    myHashMap->printAll();
    cout << "------" << endl;
    myHashMap->remove(&b);
    myHashMap->printAll();
    cout << "------" << endl;
    myHashMap->remove(&c);
    myHashMap->printAll();
    cout << "------" << endl;
    myHashMap->remove(&d);
    myHashMap->printAll();
    cout << "------" << endl;
    myHashMap->remove(&e);
    myHashMap->printAll();
    cout << "------" << endl;
    delete myHashMap;

    return 0;
}
