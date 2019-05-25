// Circular Buffer for the nRF52 UART
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint16_t data[256];
    uint8_t readPosition;
    uint8_t writePosition;

} uintCircularBuffer_t;

// Insert new data, overwriting the old in the circular manner
void uint_circular_buffer_push(uintCircularBuffer_t *cb, uint16_t data);

// Retrieve the data, returning an error code
void uint_circular_buffer_pop(uintCircularBuffer_t *cb, uint16_t *data);