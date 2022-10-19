#pragma once

// we already have a doubly-linked list implementation in the standard library
#include <list>

namespace qjs {
using std::list;

auto foo() {
  list<int> a = list<int>();

  //  // list_add
  //  a.push_front(1);
  //  // list_add_tail
  //  a.push_back(2);
  //  // list_del
  //  a.remove(1);
  //  // list_empty
  //  a.clear();
  //  // list_for_each
  //  // std::for_each(a.begin(), a.end(), [](int i) {
  //  //   do something
  //  // });
  //  // list_for_each_prev
  //  // std::for_each(a.end(), a.begin(), [](int i) {
  //  //   do something
  //  // });
}
}  // namespace qjs