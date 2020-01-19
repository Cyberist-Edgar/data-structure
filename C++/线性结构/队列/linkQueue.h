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
    node *front, *rear;

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
    front = rear = nullptr;
}

/**
 * 析构函数
 */
template <class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp;
    while (front != nullptr)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

/**
 * isEmpty 函数 判断是否为空
 */
template <class elemType>
bool linkQueue<elemType>::isEmpty() const
{
    return front == nullptr;
}

/**
 * getHead 函数 获取头元素
 */
template <class elemType>
elemType linkQueue<elemType>::getHead() const
{
    return front->data;
}

/**
 * enQueue 函数 进队
 */
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear == nullptr)
        front = rear = new node(x);
    else
        rear = rear->next = new node(x);
}

/**
 * deQueue 函数 出队
 */
template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType value = front->data;
    front = front->next;
    if (front == nullptr)
        rear = nullptr;
    delete tmp;
    return value;
}
