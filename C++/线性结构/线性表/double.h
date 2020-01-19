#include <iostream>
using namespace std;
template <class T>
class list
{
public:
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual void insert(int i, const T &x) = 0;
    virtual void remove(int i) = 0;
    virtual int search(const T &x) const = 0;
    virtual T visit(int i) const = 0;
    virtual void traverse() const = 0;
    virtual ~list(){};
};

template <class T>
class dLinkList : public list<T>
{
private:
    struct node
    {
        T data;
        node *prev, *next;

        node(const T &x, node *p = NULL, node *n = NULL)
        {
            data = x;
            next = n;
            prev = p;
        }
        node() : next(NULL), prev(NULL) {}
        ~node() {}
    };

    node *head, *tail;
    int currentLength;
    node *move(int i) const
    {
        node *p = head;
        while (i-- >= 0)
            p = p->next;
        return p;
    }

public:
    dLinkList();
    ~dLinkList()
    {
        clear();
        delete head;
        delete tail;
    }

    void clear();
    int length() const;
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
};

/**
 * 构造函数
 */
template <class T>
dLinkList<T>::dLinkList()
{
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}

/**
  *length 函数 返回线性表的长度
  */
template <class T>

int dLinkList<T>::length() const
{
    return currentLength;
}

/**
 * insert 函数 特定位置插入特定的值
 */
template <class T>
void dLinkList<T>::insert(int i, const T &x)
{
    node *pos, *tmp;
    pos = move(i);
    tmp = new node(x, pos->prev, pos);
    pos->prev->next = tmp;
    pos->prev = tmp;
    ++currentLength;
}

/**
 * remove 函数 删除特定位置上的元素
 */
template <class T>
void dLinkList<T>::remove(int i)
{
    node *pos;
    pos = move(i);
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
    --currentLength;
};

/**
 * clear 函数 清除所有的结点
 */
template <class T>
void dLinkList<T>::clear()
{
    node *p = head->next, *q;
    head->next = tail;
    tail->prev = head;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

/**
 * search 函数 寻找给定的值，并返回对应的序号
 */
template <class T>
int dLinkList<T>::search(const T &x) const
{
    node *p = head->next;
    int i;
    for (i = 0; p != tail && p->data != x; i++)
        p = p->next;
    if (p == tail)
        return -1;
    else
        return i;
}

/**
 * visit 函数 获得指定位置的元素
 */
template <class T>
T dLinkList<T>::visit(int i) const
{
    return move(i)->data;
}

/**
 * traverse 函数 历遍所有的元素
 */
template <class T>
void dLinkList<T>::traverse() const
{
    node *p = head->next;
    cout << endl;
    while (p != tail)
    {
        cout << p->data << "  ";
        p = p->next;
    }
    cout << endl;
}
