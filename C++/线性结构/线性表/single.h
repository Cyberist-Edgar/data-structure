#pragma once
#include<iostream>
using namespace std;
template <class elemType>
class list
{
public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(int i, const elemType& x) = 0;
	virtual void remove(int i) = 0;
	virtual int search(const elemType& x) const = 0;
	virtual elemType visit(int i) const = 0;
	virtual void traverse() const = 0;
	virtual ~list() {}
};

template <class elemType>
class sLinkList : public list<elemType>
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
	node* head;
	int currentLength;
	node* move(int i) const;

public:
	sLinkList();
	~sLinkList();
	void clear();
	int length() const;
	void insert(int i, const elemType& x);
	void remove(int i);
	int search(const elemType& x) const;
	elemType visit(int i) const;
	void erase(int i);
	void traverse() const;
};

/**
 * move 函数 移动指针到相应的位置
 */
template <class elemType>
typename sLinkList<elemType>::node* sLinkList<elemType>::move(int i) const
{
	node* p = head;
	while (i-- > 0) {
		p = p->next;
	}
	return p;
}

/**
 * 构造函数
 */
template <class elemType>
sLinkList<elemType>::sLinkList()
{
	head = new node;
	currentLength = 0;
}

/**
  *析构函数
  */
template<class elemType>
sLinkList<elemType>::~sLinkList() {
	clear();
	delete head;
}

/**
  *length 函数 返回线性表的长度
  */
template<class elemType>
int sLinkList<elemType>::length()const {
	return currentLength;
}

/**
 * clear 函数 清除所有的结点
 */
template <class elemType>
void sLinkList<elemType>::clear()
{
	node* p = head->next;
	node* q;
	head->next = nullptr;
	while (p != nullptr)
	{
		q = p->next;
		delete p;
		p = q;
	}
	currentLength = 0;
}

/**
 * insert 函数 特定位置插入特定的值
 */
template <class elemType>
void sLinkList<elemType>::insert(int i, const elemType& x)
{
	if (i < 1)
	{
		cout << "输入位置有误";
		return;
	}
	node* p = move(i-1);
	p->next = new node(x, p->next);

	++currentLength;
}

/**
 * remove 函数 删除特定位置上的元素
 */
template <class elemType>
void sLinkList<elemType>::remove(int i)
{
	node* p = move(i - 1);
	node* tmp = p->next;
	p->next = tmp->next;
	delete tmp;
	--currentLength;
}

/**
 * search 函数 寻找给定的值，并返回对应的序号
 */
template <class elemType>
int sLinkList<elemType>::search(const elemType& x) const
{
	node* p = head->next;
	int i = 0;

	while (p != nullptr && p->data != x)
	{
		p = p->next;
		++i;
	}
	if (p = nullptr)
		return -1;
	else
		return i;
}

/**
 * visit 函数 获得指定位置的元素
 */
template <class elemType>
elemType sLinkList<elemType>::visit(int i) const
{
	return move(i)->data;
}

/**
 * traverse 函数 历遍所有的元素
 */
template <class elemType>
void sLinkList<elemType>::traverse() const
{
	node* p = head->next;
	cout << std::endl;
	while (p != nullptr)
	{
		cout << p->data << " ";
		p = p->next;
	}
}

/**
 * erase 函数 删除与指定位置元素值一样的元素
 */
template <class elemType>
void sLinkList<elemType>::erase(int i)
{
	node* pre = move(i - 1);
	node* delp = pre->next;
	elemType tmp = delp->data;
	int cnt = 1;

	pre->next = delp->next;
	delete delp;
	for (pre = head; pre->next != nullptr; pre = pre->next)
	{
		if (pre->next->data == tmp)
		{
			delp = pre->next;
			pre->next = delp->next;
			delete delp;
			++cnt;
		}
	}
	currentLength -= cnt;
}