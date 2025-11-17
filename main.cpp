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

    void insert(int index, const T &value)
    {
        if (index < 0 || index > size)
            return;

        // Если нет места — увеличиваем capacity
        if (size == capacity)
        {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            reserve(newCapacity);
        }

        // Сдвигаем элементы вправо, начиная с конца
        // Идём с конца чтобы не перезаписать данные
        for (int i = size; i > index; --i)
        {
            data[i] = data[i - 1];
        }

        // Вставляем новый элемент
        data[index] = value;

        ++size;
    }

    void erase(int index)
    {
        if (index < 0 || index >= size)
            return;

        // Вызываем деструктор удаляемого элемента
        data[index].~T();

        // Сдвигаем все элементы после index на одну позицию влево
        for (int i = index; i < size - 1; ++i)
        {
            data[i] = data[i + 1];
        }

        --size;
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

      =================================================================================================================

      Метод insert у std::vector вставляет элементы в середину вектора
      Все элементы, начиная с позиции pos, сдвигаются вправо.
      В указанную позицию помещается новый элемент.
      Если места не хватает vector увеличит capacity.
      Возвращает итератор на вставленный элемент.
    */

    return 0;
}