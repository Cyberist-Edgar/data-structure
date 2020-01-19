#include <iostream>
#include "栈的链接实现.h"
#include <cstring>
using namespace std;
bool isReverse(const char *s);
int main()
{
    cout << isReverse("hello");
    return 0;
}

bool isReverse(const char *s)
{
    int i;
    int len = strlen(s);
    linkStack<char> st;
    for (int i = 0; i < len; ++i)
        st.push(s[i]);
    for (i = 0; !st.isEmpty(); ++i)
        if (s[i] != st.pop())
            return false;
    return true;
}