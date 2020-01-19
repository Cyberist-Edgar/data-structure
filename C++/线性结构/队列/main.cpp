#include<iostream>
#include"circleLinkQueue.h"

using namespace std;

int main(){
    linkQueue<int> queue;
    queue.enQueue(1);
    queue.enQueue(2);
    cout<<queue.isEmpty();
    cout<<queue.getHead();
    cout<<queue.deQueue();
    return 0;
}