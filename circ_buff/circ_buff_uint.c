#include "circ_buff_uint.h"

#define CB_LENGTH 8u


void uint_circular_buffer_push(uintCircularBuffer_t *cb, uint16_t in)
{
    cb->data[cb->writePosition] = in;

    cb->writePosition++;
    //cb->writePosition &= (CB_LENGTH - 1); // wraparound
} 

void uint_circular_buffer_pop(uintCircularBuffer_t *cb, uint16_t *out)
{
    *out = cb->data[cb->readPosition];

    cb->readPosition++;
    //cb->readPosition &= (CB_LENGTH - 1); // wraparound
}