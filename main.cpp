#include <iostream>

class MyVector
{
private:
    int *data;  // Указатель на массив
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
    void push_back(int value)
    {
        // volume всегда >= size. Когда массив заполнен, мы удваиваем volume, чтобы потом добавлять элементы без частых копирований.
        if (size >= volume)
        {
            // нужно больше памяти
            int newVolume = (volume == 0) ? 1 : volume * 2;
            int *newData = new int[newVolume];

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
    int operator[](int index) const
    {
        return data[index];
    }

    // Текущее количество элементов
    int getSize() const
    {
        return size;
    }

    int getVolume() const
    {
        return volume;
    }
};

int main()
{
    MyVector v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    // v.push_back(9);
    // v.push_back(10);

    for (int i = 0; i < v.getSize(); ++i)
        std::cout << v[i] << ", ";

    std::cout << std::endl;
    std::cout << "Size arr: " << v.getSize() << std::endl;
    std::cout << "volume: " << v.getVolume() << std::endl;

    return 0;
}