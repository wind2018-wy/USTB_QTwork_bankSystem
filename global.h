#ifndef GLOBAL_H
#define GLOBAL_H

#endif // GLOBAL_H
#include "account.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include<fstream>
#include<filesystem>
#include<QString>
using namespace std;
struct deleter {
    template <class T> void operator () (T* p) { delete p; }
};
Date tdate(2008, 11, 1);//起始日期
vector<Account*> accounts;//创建账户数组，元素个数为0
