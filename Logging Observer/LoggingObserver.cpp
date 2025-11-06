//
// Created by Malak Sefrioui on 2025-11-03.
//

#include "LoggingObserver.h"
#include <iostream>
#include <set>
#include <string>
using std::cout;

void Subject::addObserver(LogObserver *observer) {
    list.insert(observer);
}

