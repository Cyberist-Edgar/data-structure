#include<iostream>
#include"double.h"
using namespace std;

int main(){

    dLinkList<int> list;
    list.insert(0,2);
    list.traverse();
    cout<<list.search(1);
    cout<<list.visit(0);
    cout<<list.length();
    return 0;
}