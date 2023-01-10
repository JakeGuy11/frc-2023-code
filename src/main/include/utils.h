#pragma once

template<class T, size_t N>
constexpr size_t arraySize(T (&)[N]) { return N; }

void mPrint(std::string m) {
    std::cout << m << std::endl;
}
