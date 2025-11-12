#include <iostream>

template <typename T>
class MyVector
{
private:
    T *data;    // Указатель на массив
    int size;   // сколько реально элементов мы положили.
    int volume; // сколько памяти выделено

public:
    // Конструктор
    MyVector()
    {
        data = nullptr;
        size = 0;
        volume = 0;
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
        // volume всегда >= size. Когда массив заполнен, мы удваиваем volume, чтобы потом добавлять элементы без частых копирований.
        if (size >= volume)
        {
            // нужно больше памяти
            int newVolume = (volume == 0) ? 1 : volume * 2;
            T *newData = new T[newVolume];

            // копируем старые данные
            for (int i = 0; i < size; ++i)
                newData[i] = data[i];

            delete[] data; // освобождаем старую память
            data = newData;
            volume = newVolume;
        }

        data[size] = value;
        ++size;
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

    int getVolume()
    {
        return volume;
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

    MyVector<double> vd; // вектор для double
    vd.push_back(3.14);
    vd.push_back(2.71);

    MyVector<std::string> vs; // вектор для строк
    vs.push_back("Hello");
    vs.push_back("World");
    vs.push_back("this");
    vs.push_back("is");
    vs.push_back("string");

    // Integer
    std::cout << "---------Integer-------------" << std::endl;
    for (int i = 0; i < vi.getSize(); ++i)
        std::cout << vi[i] << ", ";

    std::cout << std::endl;
    std::cout << "Integer Size arr: " << vi.getSize() << std::endl;
    std::cout << "Integer volume: " << vi.getVolume() << std::endl;

    // Double
    std::cout << "----------Double------------" << std::endl;
    for (int i = 0; i < vd.getSize(); ++i)
        std::cout << vd[i] << ", ";

    std::cout << std::endl;
    std::cout << "Double Size arr: " << vd.getSize() << std::endl;
    std::cout << "Double volume: " << vd.getVolume() << std::endl;

    // String
    std::cout << "----------String------------" << std::endl;
    for (int i = 0; i < vs.getSize(); ++i)
        std::cout << vs[i] << ", ";

    std::cout << std::endl;
    std::cout << "String Size arr: " << vs.getSize() << std::endl;
    std::cout << "String volume: " << vs.getVolume() << std::endl;

    return 0;
}