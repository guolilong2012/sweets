#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Test {
public:
    Test() {}; //c++ OK
    ~Test() {};

public:
    enum { //used in class
        ONE = 1,
    };

    struct A { //used in class
        A() { printf("Hello A\n"); };
        ~A() {};
    };

    void PirntOneA(void) { printf("ONE = <%d>\n", ONE); struct A a; };
};

struct B {
    B() { printf("Hello B\n"); }; //default public
    ~B() {};
};

int main(void)
{
    cout << "Hello World" << endl;

    //string
    string strMyString = "Hello World";
    printf("strMyString = <%s>\n" \
           "strMyString.size() = <%d>\n" \
           "strMyString.length() = <%d>\n" \
           "strMyString[6] = <%c>\n" \
           "strMyString.at(0) = <%c>\n", \
           strMyString.c_str(), \
           strMyString.size(), \
           strMyString.length(), \
           strMyString[6], \
           strMyString.at(0) \
           );

    //vector
    typedef std::vector<int> INT_ARRAY;
    INT_ARRAY intArray;
    intArray.push_back(1);
    intArray.push_back(2);
    for (INT_ARRAY::size_type i = 0; i<intArray.size(); i++)
    {
        printf("intArray[%d] = <%d>\n", i, intArray[i]);
    }
    for (INT_ARRAY::iterator iter = intArray.begin(); iter != intArray.end(); iter++)
    {
        printf("iter = <%d>\n",  *iter);
    }

    //map
    typedef map<string, string> MAP_ARRAY;
    MAP_ARRAY mapArray;
    mapArray["Hello"] = "World";
    MAP_ARRAY::const_iterator iter = mapArray.find("Hello");
    if (iter != mapArray.end())
    {
        printf("mapArray[\"Hello\"] = <%s>\n", (*iter).second.c_str());
    }

    //struct
    Test test;
    //printf("ONE = <%d>\n", ONE); //error
    //struct A a; //error
    test.PirntOneA();

    struct B b;
    B c; //c++ OK

    return 0;
}
