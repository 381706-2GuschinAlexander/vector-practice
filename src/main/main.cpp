#include <list>
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <numeric>
#include <functional>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include "mlib.h"
#include "omp.h"



int main()
{
  cc::RB_tree<int, tp> a;
  a.push(10, tp());
  a.get_value(10);
  std::cout << "Hello world!\n";
  return 0;
}
