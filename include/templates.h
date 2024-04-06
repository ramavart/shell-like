#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>

using namespace std;

inline void print() { cout << endl; }

template <typename T1, typename... Types>
inline void print(T1 arg1, Types... args) {
  cout << arg1 << " ";
  print(args...);
}

#endif // TEMPLATES_H
