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