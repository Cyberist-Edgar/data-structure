#include "linkString.h"
#include "seqString.h"
#include <iostream>
using namespace std;

int main()
{

    seqString s("123456");
    cout << s.length() << endl;
    cout << s<<endl;
    seqString s1 = s.subStr(0, 2);
    cout<<s1<<endl;
    // int flag = (s2>s);
    // cout<<endl;
    // cout<<flag;
    return 0;
}