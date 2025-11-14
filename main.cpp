#include <iostream>

template <typename T>
class MyVector
{
private:
    T *data;      // Указатель на массив
    int size;     // сколько реально элементов мы положили.
    int capacity; // сколько памяти выделено

public:
    // Конструктор
    MyVector()
    {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    // Деструктор
    ~MyVector()
    {
        delete[] data;
        // чтобы освободить память, выделенную new[]
        // delete для одного объекта
        // delete[] для массива объектов
    }

    // Добавление элемента
    void push_back(const T &value)
    {
        // capacity всегда >= size. Когда массив заполнен, мы удваиваем capacity, чтобы потом добавлять элементы без частых копирований.
        if (size == capacity)
        {
            // 2. Рассчитываем новую емкость
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;

            // 3. Вызываем reserve() для выделения новой памяти и копирования данных
            reserve(newCapacity);
        }

        data[size] = value;
        ++size;
    }

    void reserve(int newCapacity)
    {
        if (newCapacity <= capacity)
            return;

        T *newData = new T[newCapacity];

        for (int i = 0; i < size; ++i)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void pop_back()
    {
        // Размер size уменьшается на 1.
        // Ёмкость capacity не изменяется.
        // Сам элемент просто уничтожается (вызов его деструктора).
        if (size == 0)
            return;

        --size;          // уменьшаем размер
        data[size].~T(); // вызываем деструктор последнего элемента
    }

    bool empty()
    {
        return (size == 0) ? true : false;
    }

    void clear()
    {
        // Устанавливает size = 0
        // Ёмкость capacity не изменяется.
        // Вызываем деструктор
        for (int i = 0; i < size; ++i)
        {
            data[i].~T();
        }

        size = 0;
    }

    // Получение элемента по индексу
    T &operator[](int index)
    {
        return data[index];
    }

    // Текущее количество элементов
    int getSize()
    {
        return size;
    }

    int getCapacity()
    {
        return capacity;
    }
};

int main()
{
    MyVector<int> vi; // вектор для int
    vi.push_back(10);
    vi.push_back(20);
    vi.push_back(30);
    vi.push_back(40);
    vi.push_back(50);
    vi.push_back(6);
    vi.push_back(7);
    vi.push_back(8);

    vi.pop_back();
    vi.pop_back();

    // vi.clear();

    // Integer
    std::cout << "---------Integer-------------" << std::endl;
    for (int i = 0; i < vi.getSize(); ++i)
        std::cout << vi[i] << " ";

    std::cout << std::endl;
    std::cout << "Integer Size arr: " << vi.getSize() << std::endl;
    std::cout << "Integer capacity: " << vi.getCapacity() << std::endl;
    std::cout << "isEmpty         : " << vi.empty() << std::endl;

    /*
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
    */

    /*
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
     */

    /*
      INFORMATION:
      reserve() вызывается не напрямую пользователем, а внутри метода push_back()
      Пользователь вызывает vec.push_back(value)
      push_back() видит, что size == capacity (память закончилась)
      Вектор увеличивает свою ёмкость (capacity), обычно удваивая её, чтобы обеспечить быстрые вставки в будущем
      Цель reserve() — минимизировать дорогие операции. Перераспределение и копирование памяти — это медленные операции.
    */

    return 0;
}