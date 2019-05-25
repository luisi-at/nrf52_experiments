// Circular Buffer for the nRF52 UART
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define CB_LENGTH 20u

typedef struct
{
    char data[CB_LENGTH][256];
    uint8_t readPosition;
    uint8_t writePosition;

} circularBuffer_t;

// Insert new data, overwriting the old in the circular manner
void circular_buffer_push(circularBuffer_t *cb, char *data);

// Retrieve the data, returning an error code
void circular_buffer_pop(circularBuffer_t *cb, char *data);


