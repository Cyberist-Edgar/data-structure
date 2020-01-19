template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const= 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~stack() {}
};

template <class elemType>
class seqStack : public stack<elemType>
{
private:
    elemType *elem;
    int top_p;
    int maxSize;
    void doubleSpace();

public:
    seqStack(int initSize = 10);
    ~seqStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};

/**
 * 构造函数
 */
template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];
    maxSize = initSize;
    top_p = -1;
}

/**
 * 析构函数
 */
template <class elemType>
seqStack<elemType>::~seqStack()
{
    delete[] elem;
}

/**
 * isEmpty 函数 判断栈是否为空
 */
template <class elemType>
bool seqStack<elemType>::isEmpty() const
{
    return top_p == -1;
}

/**
 * push 函数 进栈
 */
template <class elemType>
void seqStack<elemType>::push(const elemType &x)
{
    if (top_p == maxSize - 1)
        doubleSpace();
    elem[++top_p] = x;
}

/**
 * pop 函数 出栈
 */
template <class elemType>
elemType seqStack<elemType>::pop()
{
    return elem[top_p--];
}

/**
 * top 函数 获得栈顶元素
 */
template <class elemType>
elemType seqStack<elemType>::top() const
{
    return elem[top_p];
}

/**
 * doubleSpace 函数 扩展空间
 */
template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    maxSize *= 2;
    elem = new elemType[maxSize];
    for (int i = 0; i < maxSize / 2; ++i)
        elem[i] = tmp[i];
    delete[] tmp;
}
