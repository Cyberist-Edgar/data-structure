#include<iostream>
using namespace std;

//抽象类
template <class elemType>
class list
{
public:
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual void insert(int i, const elemType &x) = 0;
    virtual void remove(int i) = 0;
    virtual int search(const elemType &x) const = 0;
    virtual elemType visit(int i) const = 0;
    virtual void traverse() const = 0;
    virtual ~list(){};
};

//抽象实现
template <class elemType>
class seqList : public list<elemType>
{
private:
    elemType *data;
    int currentLength;
    int maxSize;
    void doubleSpace();

public:
    seqList(int initSize = 10);
    ~seqList();
    void clear();
    int length() const;
    void insert(int i, const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;
    void erase(int i);
};

/**
 *析构函数
 */
template <class elemType>
seqList<elemType>::~seqList()
{
    delete[] data;
}

/**
 * clear 函数，清除所有的元素，实际上只需要将length置0就好
 * 因为之后再进行操作仍然会覆盖掉之前的数据，并且之前的数据
 * 已经不可以获取了
 */

template <class elemType>
void seqList<elemType>::clear()
{
    currentLength = 0;
}

/**
 * length 函数 返回线性表的长度
 */
template <class elemType>
int seqList<elemType>::length() const
{
    return currentLength;
}

/**
 * visit 函数 访问指定位置的元素值
 */
template <class elemType>
elemType seqList<elemType>::visit(int i) const
{
    return data[i];
}

/**
 * traverse 函数 输出线性表中的元素
 */

template <class elemType>
void seqList<elemType>::traverse() const
{
    cout << endl;
    for (int i = 0; i < currentLength; i++)
    {
        cout << data[i];
        cout << " ";
    }
}

/**
 * 构造函数 申请空间 初始化变量
 */
template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

/**
 * search 函数 搜索列表中的值，如果存在输出相对应的序号
 */
template <class elemType>
int seqList<elemType>::search(const elemType &x) const
{
    int i;
    for (i = 0; i < currentLength && data[i] != x; ++i)
        ;
    if (i == currentLength)
        return -1;
    else
        return i;
}

/**
 * doubleSpace 函数 动态扩展空间
 */
template <class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];
    for (int i = 0; i < currentLength; ++i)
        data[i] = tmp[i];
    delete[] tmp;
}

/**
 * insert 函数 向某个特定的位置插入值
 */
template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x)
{
    if (currentLength == maxSize)
        doubleSpace();
    for (int j = currentLength; j > i; j--)
        data[j] = data[j - 1];
    data[i] = x;
    ++currentLength;
}

/**
 * remove 函数 删除线性表中某个位置的数
 */
template <class elemType>
void seqList<elemType>::remove(int i)
{
    if (i > currentLength)
    {
        cout << "无此序号的元素";
        return ;
    }
    else
        for (int j = i; j < currentLength; j++)
            data[j] = data[j + 1];
    --currentLength;
}

/**
 * erase 函数 删除数组中的特定的序号对应元素值的所有元素
 */

template <class elemType>
void seqList<elemType>::erase(int i)
{
    elemType tmp = data[i];
    int cnt = 0;
    for (int j = 0; j < currentLength; j++)
        if (data[j] == tmp)
            ++cnt;
        else
            data[j - cnt] = data[j];
    currentLength -= cnt;
}
