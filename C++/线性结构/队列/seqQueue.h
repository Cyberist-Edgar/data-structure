template<class elemType>
class queue{
    public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType&x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead()const = 0;
    virtual ~queue(){}
};


template <class elemType>
class seqQueue : public queue<elemType>
{
private:
    elemType *elem;
    int maxSize;
    int front, rear;
    void doubleSpace();

public:
    seqQueue(int initSize = 10);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() const;
};

/**
 * 构造函数
 */
template <class elemType>
seqQueue<elemType>::seqQueue(int initSize)
{
    elem = new elemType[initSize];
    maxSize = initSize;
    front = rear = 0;
}

/**
 * 析构函数
 */
template <class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete[] elem;
}

/**
 * isEmpty 函数 判断队列是否为空
 */
template <class elemType>
bool seqQueue<elemType>::isEmpty() const
{
    return front == rear;
}

/**
 * deQueue 函数 出队
 */
template <class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

/**
 * getHead 函数 获取头元素
 */
template <class elemType>
elemType seqQueue<elemType>::getHead() const
{
    return elem[(front + 1) % maxSize];
}

/**
 * enQueue 函数 入队
 */
template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if ((rear + 1) % maxSize == front)
        doubleSpace();
    else
        rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

/**
 * doubleSpace 函数 扩展空间
 */
template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[maxSize * 2];
    for (int i = 1; i <= maxSize; i++)
        elem[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete tmp;
}