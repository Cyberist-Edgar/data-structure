#include<iostream>
#include "seqStack.h"
using namespace std;

int main(){
    seqStack<int> stack;
    stack.push(2);
    cout<<stack.isEmpty();
    cout<<stack.top();
    cout<<stack.pop();
    return 0;
}