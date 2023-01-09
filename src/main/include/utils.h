#pragma once

template<class T>
int arraySize(T t[]) {
    if (sizeof[t] == 0) return 0;
    else return sizeof(t) / sizeof(t[0]);
}