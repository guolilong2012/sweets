#include <stdio.h>
#include <map>
#include <vector>
#include <string>
using namespace std;

int main(void)
{
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

    typedef map<string, string> MAP_ARRAY;
    MAP_ARRAY mapArray;
    mapArray["Hello"] = "World";
    MAP_ARRAY::const_iterator iter = mapArray.find("Hello");
    if (iter != mapArray.end())
    {
        printf("mapArray[\"Hello\"] = <%s>\n", (*iter).second.c_str());
    }

    return 0;
}
