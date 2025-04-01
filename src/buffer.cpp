#include "buffer.hpp"
#include <iostream>

CircularBuffer::CircularBuffer(uint16_t size):
    size(size), read_i(0), write_i(0), buffer(new uint8_t[size])
{
    std::cout << "Size of Circular Buffer is " << size << "\n";
}

bool CircularBuffer::isEmpty()
{
    return read_i == write_i;
}

bool CircularBuffer::isFull()
{
    if (write_i == size-1)
        return read_i == 0;
    else
        return read_i == write_i + 1;
}

void CircularBuffer::push(uint8_t data)
{
    buffer[write_i] = data;
    write_i++;
    if(write_i == size) write_i = 0;
}

uint8_t CircularBuffer::pop()
{
    uint8_t data = buffer[read_i];
    read_i++;
    if(read_i == size) read_i = 0;
    return data;
}