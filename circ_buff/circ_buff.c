#include "circ_buff.h"

#define CB_LENGTH 20u


void circular_buffer_push(circularBuffer_t *cb, char *data)
{
    strcpy(cb->data[cb->writePosition], data);

    cb->writePosition++;
    cb->writePosition &= (CB_LENGTH - 1); // wraparound
} 

void circular_buffer_pop(circularBuffer_t *cb, char *data)
{
    strcpy(data, cb->data[cb->readPosition]);

    cb->readPosition++;
    cb->readPosition &= (CB_LENGTH - 1); // wraparound
}