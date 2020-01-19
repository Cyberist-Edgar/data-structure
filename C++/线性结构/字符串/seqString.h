#pragma once
#include <iostream>
using namespace std;
class seqString
{
    friend seqString operator+(const seqString &s1, const seqString &s2);
    friend bool operator==(const seqString &s1, const seqString &s2);
    friend bool operator!=(const seqString &s1, const seqString &s2);
    friend bool operator>(const seqString &s1, const seqString &s2);
    friend bool operator>=(const seqString &s1, const seqString &s2);
    friend bool operator<=(const seqString &s1, const seqString &s2);
    friend bool operator<(const seqString &s1, const seqString &s2);
    friend ostream &operator<<(ostream &os, const seqString &s);
    char *data;
    int len;

public:
    seqString(const char *s = "");
    seqString(const seqString &other);
    ~seqString();
    int length() const;
    seqString &operator=(const seqString &other);
    seqString subStr(int start, int num) const;
    void insert(int start, const seqString &s);
    void remove(int start, int num);
};

/**
 * 构造函数
 */
seqString::seqString(const char *s)
{
    for (len = 0; s[len] != '\0'; ++len)
        ;
    data = new char[len + 1];
    for (len = 0; s[len] != '\0'; ++len)
        data[len] = s[len];
    data[len] = '\0';
}

/**
 * 复制构造函数
 */
seqString::seqString(const seqString &other)
{
    data = new char[other.len + 1];
    for (len = 0; len <= other.len; ++len)
        data[len] = other.data[len];
}

/**
 * 析构函数
 */
seqString::~seqString()
{
    delete data;
}

/**
 * length 函数 获取字符串的长度
 */
int seqString::length() const
{
    return len;
}

/**
 * 赋值重载
 */
seqString &seqString::operator=(const seqString &other)
{
    if (this == &other)
        return *this;
    delete data;
    data = new char[other.len + 1];
    for (len = 0; len <= other.len; len++)
        data[len] = other.data[len];
    return *this;
}

/**
 * subStr 函数 取子串
 */
seqString seqString::subStr(int start, int num) const
{
    if (start >= len - 1 || start < 0)
        return "";
    seqString tmp;
    tmp.len = (start + num > len) ? len - start : num;
    delete tmp.data;
    tmp.data = new char[tmp.len + 1];
    for (int i = 0; i < tmp.len; i++)
        tmp.data[i] = data[start + i];
    tmp.data[tmp.len] = '\0';
    return tmp;
}

/**
 * insert 函数 插入字符串
 */
void seqString::insert(int start, const seqString &s)
{
    char *tmp = data;
    int i;
    if (start > len || start < 0)
        return;
    len += s.len;
    data = new char[len + 1];
    for (i = 0; i < start; i++)
        data[i] = tmp[i];
    for (i = 0; i < s.len; ++i)
        data[i + start] = s.data[i];
    for (i = start; tmp[i] != '\0'; ++i)
        data[i + s.len] = tmp[i];
    data[i + s.len] = '\0';
    delete tmp;
}

/**
 * remove 函数 删除字子符串
 */
void seqString::remove(int start, int num)
{
    if (start < 0 || start > len)
        return;
    if (start + num >= len)
    {
        data[start] = '\0';
        len = start;
    }
    else
    {
        for (len = start; data[len + num] != '\0'; ++len)
            data[len] = data[len + num];
        data[len] = '\0';
    }
}

/**
 * 加号重载
 */
seqString operator+(const seqString &s1, const seqString &s2)
{
    seqString tmp;
    int i;
    tmp.len = s1.len + s2.len;
    delete tmp.data;
    tmp.data = new char[tmp.len + 1];
    for (i = 0; i < s1.len; i++)
        tmp.data[i] = s1.data[i];
    for (i = 0; i < s2.len; i++)
        tmp.data[i + s1.len] = s2.data[i];
    tmp.data[s1.len + s2.len] = '\0';
    return tmp;
}

/**
 * 重载等号
 */
bool operator==(const seqString &s1, const seqString &s2)
{
    if (s1.len != s2.len)
        return false;
    for (int i = 0; i < s1.len; ++i)
        if (s1.data[i] != s2.data[i])
            return false;
    return true;
}

/**
 * 重载不等号
 */
bool operator!=(const seqString &s1, const seqString &s2)
{
    return !(s1 == s2);
}

/**
 * 重载大于号
 */
bool operator>(const seqString &s1, const seqString &s2)
{
    for (int i = 0; i < s1.len; i++)
    
        if (s1.data[i] > s2.data[i])
            return true;
        else if (s1.data[i] < s2.data[i])
            return false;
        return false;
    
}


/**
 * 重载大于等于号
 */
bool operator>=(const seqString&s1, const seqString&s2){
    return(s1==s2||s1>s2);
}

/**
 * 重载小于号
 */
bool operator<(const seqString&s1, const seqString&s2){
    return !(s1>=s2);
}


/**
 * 重载小于等于号
 */
bool operator<=(const seqString&s1, const seqString&s2){
    return !(s1>s2);
}


/**
 * 重载输出
 */
ostream &operator<<(ostream&os, const seqString&s){
    os<<s.data;
    return os;
}


