#pragma once 
#include <iostream>
#include <cmath>
using namespace std;
class linkString
{
	friend linkString operator+(const linkString& s1, const linkString& s2);
	friend bool operator==(const linkString& s1, const linkString& s2);
	friend bool operator>(const linkString& s1, const linkString& s2);
	friend bool operator>=(const linkString& s1, const linkString& s2);
	friend bool operator<(const linkString& s1, const linkString& s2);
	friend bool operator<=(const linkString& s1, const linkString& s2);
	friend bool operator!=(const linkString& s1, const linkString& s2);
	friend ostream& operator<<(ostream& os, const linkString& s2);

	struct node
	{
		int size;
		char* data;
		node* next;
		node(int s = 1, node * n = nullptr)
		{
			size = s;
			data = new char[s];
			next = n;
		}
	};

	node* head;
	int len;
	int nodeSize;
	void clear();
	void findPos(int start, int& pos, node*& p) const;
	void split(node* p, int pos);
	void merge(node* p);

public:
	linkString(const char* s = "");
	linkString(const linkString& other);
	~linkString();
	int length() const;
	linkString& operator=(const linkString& other);
	linkString subStr(int start, int num) const;
	void insert(int start, const linkString& s);
	void remove(int start, int num);
};

/**
 * 构造函数
 */
linkString::linkString(const char* s)
{
	node* p;
	for (len = 0; s[len] != '\0'; ++len);
		nodeSize = sqrt(len);
	p = head = new node(1);
	while (*s)
	{
		p = p->next = new node(nodeSize);
		for (int i = 0; i < nodeSize && *s; ++s, ++i) {
			p->data[i] = s[0];
		}
				
	}
}

/**
 * 复制构造函数
 */
linkString::linkString(const linkString& other)
{
	node* p, * otherp = other.head->next;

	p = head = new node(1);
	len = other.len;
	nodeSize = other.nodeSize;
	while (otherp)
	{
		p = p->next = new node(nodeSize);
		for (int i=0; i< otherp->size; ++i)
			p->data[i] = otherp->data[i];
		otherp = otherp->next;
	}
}

/**
 * clear 函数 清除所有的值
 */
void linkString::clear()
{
	node* p = head->next;
	node* nextp;
	while (p)
	{
		nextp = p->next;
		delete p;
		p = nextp;
	}
}

/**
 * 析构函数
 */
linkString::~linkString()
{
	clear();
	delete head;
}

/**
 * length 函数 获得字符串的长度
 */
int linkString::length() const
{
	return len;
}

/**
 * 复制构造函数
 */
linkString& linkString::operator=(const linkString& other)
{
	node* p = head->next;
	node* otherp = other.head->next;
	if (this == &other)
		return *this;
	clear();
	len = other.len;
	nodeSize = other.nodeSize;
	while (otherp)
	{
		p = p->next = new node(nodeSize);
		for (int i = 0; i < otherp->size; ++i) {
			p->data[i] = otherp->data[i];
			cout << p->data[i] << endl;
		}
		otherp = otherp->next;
	}
	return *this;
}

/**
 * findPos 函数 查找起始位置
 */
void linkString::findPos(int start, int& pos, node*& p) const
{
	int count = 0;
	p = head->next;
	while (count <= start)
	{
		if (count + p->size < start)
		{
			count += p->size;
			p = p->next;
		}
		else
		{
			pos = start - count;
			return;
		}
	}
}

/**
 * subStr 函数 取子串
 */

linkString linkString::subStr(int start, int num) const
{
	linkString tmp;
	int count = 0, pos;
	node* p, * tp = tmp.head;
	if (start < 0 || start > len)
		return tmp;
	num = (start + num) > len ? len - start : num;
	tmp.len = num;
	tmp.nodeSize = sqrt(num);
	findPos(start, pos, p);

	for (int i = 0; i < tmp.len;)
	{
		tp = tp->next = new node(tmp.nodeSize);
		for (int j=0; j < tmp.nodeSize && i < tmp.len; ++i, ++j)
		{
			if (pos == p->size)
			{
				p = p->next;
				pos = 0;
			}
			tp->data[j] = p->data[pos++];
		}
	}
	return tmp;
}

/**
 * split 函数 分裂结点
 */
void linkString::split(node* p, int pos)
{
	p->next = new node(nodeSize, p->next);
	int i;
	for (i = pos; i < p->size; ++i)
		p->next->data[i - pos] = p->data[pos];
	p->next->size = i - pos;
	p->size = pos;
}

/**
 * merge 函数 合并结点
 */
void linkString::merge(node* p)
{
	node* nextp = p->next;
	if (p->size + nextp->size <= nodeSize)
	{
		for (int pos = 0; pos < nextp->size; ++pos, ++p->size)
			p->data[p->size] = nextp->data[pos];
		p->next = nextp->next;
		delete nextp;
	}
}

/**
 * insert 函数，插入字符串
 */
void linkString::insert(int start, const linkString& s)
{
	node* p, * nextp, * tmp;
	int pos;
	if (start < 0 || start > len)
		return;
	findPos(start, pos, p);
	split(p, pos);
	nextp = p->next;
	tmp = s.head->next;
	while (tmp)
	{
		for (pos = 0; pos < tmp->size; ++pos)
		{
			if (p->size == nodeSize)
				p = p->next = new node(nodeSize);
			p->data[p->size] = tmp->data[pos];
			++p->size;
		}
		tmp = tmp->next;
	}
	len += s.len;
	p->next = nextp;
	merge(p);
}

/**
 * remove 函数 删除字符串
 */
void linkString::remove(int start, int num)
{
	if (start < 0 || start > len)
		return;
	node* startp;
	int pos;
	findPos(start, pos, startp);
	split(startp, pos);
	if (start + num >= len)
	{
		num = len - start;
		len = start;
	}
	else
		len -= num;
	while (true)
	{
		node* nextp = startp->next;
		if (num > nextp->size)
		{
			num -= nextp->size;
			startp->next = nextp->next;
			delete nextp;
		}
		else
		{
			split(nextp, num);
			startp->next = nextp->next;
			delete nextp;
			break;
		}
	}
	merge(startp);
}

/**
 * 重载加号运算符
 */
linkString operator+(const linkString& s1, const linkString& s2)
{
	char* tmp = new char[s1.len + s2.len + 1];
	linkString::node* p;
	int count = 0;

	for (p = s1.head->next; p != nullptr; p = p->next)
		for (int i = 0; i < p->size; ++i)
			tmp[count++] = p->data[i];
	for (p = s2.head->next; p != nullptr; p = p->next)
		for (int i = 0; i < p->size; i++)
			tmp[count++] = p->data[i];
	tmp[count] = '\0';
	linkString returnValue(tmp);
	delete tmp;
	return returnValue;
}

/**
 * 重载== 运算符
 */
bool operator==(const linkString& s1, const linkString& s2)
{
	linkString::node* p1 = s1.head->next;
	linkString::node* p2 = s2.head->next;

	int pos1 = 0, pos2 = 0;

	if (s1.len != s2.len)
		return false;
	while (p1 && p2)
	{
		if (p1->data[pos1] != p2->data[pos2])
			return false;
		if (++pos1 == p1->size)
		{
			p1 = p1->next;
			pos1 = 0;
		}
		if (++pos2 == p2->size)
		{
			p2 = p2->next;
			pos2 = 0;
		}
	}
	return true;
}

/**
 * 重载运算符 !=
 */
bool operator!=(const linkString& s1, const linkString& s2)
{
	return !(s1 == s2);
}

/**
 * 重载运算符 >
 */
bool operator>(const linkString& s1, const linkString& s2)
{
	linkString::node* p1 = s1.head->next;
	linkString::node* p2 = s2.head->next;
	int pos1 = 0, pos2 = 0;
	while (p1)
	{
		if (p2 == nullptr)
			return true;
		if (p1->data[pos1] > p2->data[pos2])
			return true;
		if (p1->data[pos1] > p2->data[pos2])
			return false;
		if (++pos1 == p1->size)
		{
			p1 = p1->next;
			pos1 = 0;
		}
		if (++pos2 == p2->size)
		{
			p2 = p2->next;
			pos2 = 0;
		}
	}
	return false;
}

/**
 * 重载运算符 >=
 */
bool operator>=(const linkString& s1, const linkString& s2)
{
	return (s1 == s2 || s1 > s2);
}

/**
 * 重载运算符 <
 */

bool operator<(const linkString& s1, const linkString& s2)
{
	return !(s1 >= s2);
}

/**
 * 重载运算符 <=
 */
bool operator<=(const linkString& s1, const linkString& s2)
{
	return !(s1 > s2);
}

/**
 * 重载运算符 <<
 */
ostream& operator<<(ostream& os, const linkString& s)
{
	linkString::node* p = s.head->next;
	int pos;
	while (p)
	{
		for (pos = 0; pos < p->size; pos++)
		{
			os << p->data[pos];
		}
		p = p->next;
	}
	return os;
}
