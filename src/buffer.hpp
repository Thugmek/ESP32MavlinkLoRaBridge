#include <cstdint>

class CircularBuffer {
    private:
        const uint16_t size;
        uint8_t* buffer;
        uint16_t write_i;
        uint16_t read_i;
    public:
        CircularBuffer(uint16_t size);
        bool isEmpty();
        bool isFull();
        uint16_t length();
        void push(uint8_t data);
        uint8_t pop();
};