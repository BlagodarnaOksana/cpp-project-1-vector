#include <cassert>
#include <iostream>
#include "MyVector.h"

void test_push_back()
{
  MyVector<int> v;
  v.push_back(10);
  v.push_back(20);

  assert(v.getSize() == 2);
  assert(v[0] == 10);
  assert(v[1] == 20);

  std::cout << "test_push_back OK\n";
}

void test_insert()
{
  MyVector<int> v;
  v.push_back(1);
  v.push_back(3);
  v.insert(1, 2); // вставляем перед индексом 1

  assert(v.getSize() == 3);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 3);

  std::cout << "test_insert OK\n";
}

void test_erase()
{
  MyVector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);

  v.erase(1); // удаляем 20

  assert(v.getSize() == 2);
  assert(v[0] == 10);
  assert(v[1] == 30);

  std::cout << "test_erase OK\n";
}

void test_pop_back()
{
  MyVector<int> v;
  v.push_back(5);
  v.push_back(7);

  v.pop_back();

  assert(v.getSize() == 1);
  assert(v[0] == 5);

  v.pop_back();
  assert(v.getSize() == 0);

  std::cout << "test_pop_back OK\n";
}

void test_clear()
{
  MyVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  v.clear();

  assert(v.getSize() == 0);
  assert(v.getCapacity() >= 3); // capacity не уменьшается

  std::cout << "test_clear OK\n";
}

void test_reserve()
{
  MyVector<int> v;
  v.reserve(10);

  assert(v.getCapacity() == 10);
  assert(v.getSize() == 0);

  v.push_back(1);
  v.push_back(2);

  assert(v.getSize() == 2);

  std::cout << "test_reserve OK\n";
}

void test_operator_index()
{
  MyVector<int> v;
  v.push_back(42);

  assert(v[0] == 42);

  v[0] = 100;
  assert(v[0] == 100);

  std::cout << "test_operator_index OK\n";
}

int main()
{
  test_push_back();
  test_insert();
  test_erase();
  test_pop_back();
  test_clear();
  test_reserve();
  test_operator_index();

  std::cout << "\nAll tests passed!\n";
  return 0;

  /*
    INFORMATION:
    assert — это проверка условия во время выполнения программы.
    Проверяет инварианты (то, что должно быть обязательно верно).
  */
}
