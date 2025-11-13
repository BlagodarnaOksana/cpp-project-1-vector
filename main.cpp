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
        if (size >= capacity)
        {
            // нужно больше памяти
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T *newData = new T[newCapacity];

            // копируем старые данные
            for (int i = 0; i < size; ++i)
                newData[i] = data[i];

            delete[] data; // освобождаем старую память
            data = newData;
            capacity = newCapacity;
        }

        data[size] = value;
        ++size;
    }

    void pop_back()
    {
        // Размер контейнера (size()) уменьшается на 1.
        // Ёмкость (capacity()) не изменяется.
        // Сам элемент просто уничтожается (вызов его деструктора).
        if (size == 0)
            return;

        --size;          // уменьшаем размер
        data[size].~T(); // вызываем деструктор последнего элемента
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

    // Integer
    std::cout << "---------Integer-------------" << std::endl;
    for (int i = 0; i < vi.getSize(); ++i)
        std::cout << vi[i] << " ";

    std::cout << std::endl;
    std::cout << "Integer Size arr: " << vi.getSize() << std::endl;
    std::cout << "Integer capacity: " << vi.getCapacity() << std::endl;

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
    return 0;
}