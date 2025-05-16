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
