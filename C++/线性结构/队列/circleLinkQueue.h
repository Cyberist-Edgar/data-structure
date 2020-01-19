#include <iostream>
using namespace std;

template <class elemType>
class queue
{
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() {}
};

template <class elemType>
class linkQueue : public queue<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *n = nullptr)
        {
            data = x;
            next = n;
        }
        node() : next(nullptr) {}
        ~node() {}
    };

    node *rear;

public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() const;
};

/**
 * 构造函数
 */
template <class elemType>
linkQueue<elemType>::linkQueue()
{
    rear = nullptr;
}

/**
 * 析构函数
 */
template <class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp, *delp;
    if (rear == nullptr)
        return;
    delp = rear->next;
    rear->next = nullptr;
    while (delp != nullptr)
    {
        tmp = delp;
        delp = delp->next;
        delete tmp;
    }
}

/**
 * isEmpty 函数 判断是否为空
 */
template <class elemType>
bool linkQueue<elemType>::isEmpty() const
{
    return rear == nullptr;
}
/**
 * enQueue 函数 进队
 */
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear == nullptr)
    {
        rear = new node(x);
        rear->next = rear;
    }
    else
        rear = rear->next = new node(x, rear->next);
}

/**
 * deQueue 函数 出队
 */
template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = rear->next;
    elemType value = tmp->data;
    if (rear == tmp)
        rear = nullptr;
    else
        rear->next = tmp->next;
    delete tmp;
    return value;
}

/**
 * getHead 函数 获取头元素
 */
template <class elemType>
elemType linkQueue<elemType>::getHead() const
{
    if (rear == nullptr)
    {
        exit(-1);
        return NULL;
    }
    else
        return rear->next->data;
}