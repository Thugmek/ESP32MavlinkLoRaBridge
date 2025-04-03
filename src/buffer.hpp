#include <cstdint>

template <typename T>
class CircularBuffer {
    private:
        const uint16_t size;
        T* buffer;
        uint16_t write_i;
        uint16_t read_i;
    public:
        CircularBuffer(uint16_t size);
        bool isEmpty();
        bool isFull();
        uint16_t length();
        void push(T data);
        T pop();
};