#include <iostream>
#include "MyVector.h"

int main()
{
    MyVector<int> vi; // вектор для int
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    vi.push_back(4);
    vi.push_back(5);
    vi.push_back(6);
    vi.push_back(7);
    vi.push_back(8);

    vi.pop_back();
    vi.pop_back();

    // vi.clear();

    vi.insert(1, 99);
    vi.erase(1);

    // Integer
    std::cout
        << "---------Integer-------------" << std::endl;
    for (int i = 0; i < vi.getSize(); ++i)
        std::cout << vi[i] << " ";

    std::cout << std::endl;
    std::cout << "Integer Size arr: " << vi.getSize() << std::endl;
    std::cout << "Integer capacity: " << vi.getCapacity() << std::endl;
    std::cout << "isEmpty         : " << vi.empty() << std::endl;

    MyVector<double> vd; // вектор для double
    vd.push_back(3.14);
    vd.push_back(2.71);

    // Double
    std::cout << "----------Double------------" << std::endl;
    for (int i = 0; i < vd.getSize(); ++i)
        std::cout << vd[i] << ", ";

    std::cout << std::endl;
    std::cout << "Double Size arr: " << vd.getSize() << std::endl;
    std::cout << "Double capacity: " << vd.getCapacity() << std::endl;

    MyVector<std::string> vs; // вектор для строк
    vs.push_back("Hello");
    vs.push_back("World");
    vs.push_back("this");
    vs.push_back("is");
    vs.push_back("string");

    // String
    std::cout << "----------String------------" << std::endl;
    for (int i = 0; i < vs.getSize(); ++i)
        std::cout << vs[i] << ", ";

    std::cout << std::endl;
    std::cout << "String Size arr: " << vs.getSize() << std::endl;
    std::cout << "String capacity: " << vs.getCapacity() << std::endl;

    /*
      INFORMATION:
      reserve() вызывается не напрямую пользователем, а внутри метода push_back()
      Пользователь вызывает vec.push_back(value)
      push_back() видит, что size == capacity (память закончилась)
      Вектор увеличивает свою ёмкость (capacity), обычно удваивая её, чтобы обеспечить быстрые вставки в будущем
      Цель reserve() — минимизировать дорогие операции. Перераспределение и копирование памяти — это медленные операции.

      =================================================================================================================

      Метод insert у std::vector вставляет элементы в указанное место
      Все элементы, начиная с позиции pos, сдвигаются вправо.
      В указанную позицию помещается новый элемент.
      Если места не хватает vector увеличит capacity.
      Возвращает итератор на вставленный элемент.
    */

    return 0;
}