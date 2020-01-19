#pragma once
template <class elemType>
class stack
{
public:
	virtual bool isEmpty() const = 0;
	virtual void push(const elemType& x) = 0;
	virtual elemType pop() = 0;
	virtual elemType top() const = 0;
	virtual ~stack() {}
};

template <class elemType>
class linkStack : public stack<elemType>
{
private:
	struct node
	{
		elemType data;
		node* next;
		node(const elemType& x, node* n = nullptr)
		{
			data = x;
			next = n;
		}
		node() : next(nullptr) {}
		~node() {}
	};
	node* top_p;

public:
	linkStack();
	~linkStack();
	bool isEmpty() const;
	void push(const elemType& x);
	elemType pop();
	elemType top() const;
};

/**
 * 构造函数
 */
template <class elemType>
linkStack<elemType>::linkStack() {
	top_p = nullptr;
}

/**
 * 析构函数
 */
template<class elemType>
linkStack<elemType>::~linkStack() {
	node* tmp;
	while (top_p != nullptr) {
		tmp = top_p;
		top_p = top_p->next;
		delete tmp;
	}
}

/**
 * isEmpty 函数 判断是否为空栈
 */
template<class elemType>
bool linkStack<elemType>::isEmpty()const {
	return top_p == nullptr;
}

/**
 * push 函数 元素进栈
 */
template<class elemType>
void linkStack<elemType>::push(const elemType& x) {
	top_p = new node(x, top_p);
}

/**
 * pop 函数 元素出栈
 */
template<class elemType>
elemType linkStack<elemType>::pop() {
	node* tmp = top_p;
	elemType x = tmp->data;
	top_p = top_p->next;
	delete tmp;
	return x;
}

/**
 * top 函数 取栈顶元素
 */
template<class elemType>
elemType linkStack<elemType>::top()const {
	return top_p->data;
}


