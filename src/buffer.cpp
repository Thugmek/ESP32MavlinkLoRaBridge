#include "buffer.hpp"
#include <iostream>

template <typename T>
CircularBuffer<T>::CircularBuffer(uint16_t size):
    size(size), read_i(0), write_i(0), buffer(new T[size])
{
    std::cout << "Size of Circular Buffer is " << size << "\n";
}

template <typename T>
bool CircularBuffer<T>::isEmpty()
{
    return read_i == write_i;
}

template <typename T>
bool CircularBuffer<T>::isFull()
{
    if (write_i == size-1)
        return read_i == 0;
    else
        return read_i == write_i + 1;
}

template <typename T>
uint16_t CircularBuffer<T>::length(){
    if(write_i >= read_i){
        return write_i - read_i;
    }else{
        return write_i - read_i + size;
    }
}

template <typename T>
void CircularBuffer<T>::push(T data)
{
    if(isFull()) return;
    buffer[write_i] = data;
    write_i++;
    if(write_i == size) write_i = 0;
}

template <typename T>
T CircularBuffer<T>::pop()
{
    if(isEmpty()) return 0;
    T data = buffer[read_i];
    read_i++;
    if(read_i == size) read_i = 0;
    return data;
}

// Buffer data types definition
template class CircularBuffer<uint8_t>;