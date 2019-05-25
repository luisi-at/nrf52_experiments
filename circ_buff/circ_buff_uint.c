#include "circ_buff_uint.h"

#define CB_LENGTH 8u


void uint_circular_buffer_push(uintCircularBuffer_t *cb, uint16_t data)
{
    cb->data[cb->writePosition] = data;

    cb->writePosition++;
    //cb->writePosition &= (CB_LENGTH - 1); // wraparound
} 

void uint_circular_buffer_pop(uintCircularBuffer_t *cb, uint16_t *data)
{
    data = cb->data[cb->readPosition];

    cb->readPosition++;
    //cb->readPosition &= (CB_LENGTH - 1); // wraparound
}