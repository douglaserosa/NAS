// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

void foo(int x) 
{
  printf("foo: %d\n", x);
}

void bar(int x)
{
  int i;
  for(i = 0; i < x; i++) {
    printf("bar: %d\n", i);
  }
}

int main() 
{
  std::thread threads[20];
  int i;

  for(i = 0; i < 20; i++) {
    threads[i] = std::thread(foo,i);
  }

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  for(i = 0; i < 20; i++) {
    threads[i].join();
  }

  std::cout << "foo and bar completed.\n";

  return 0;
}