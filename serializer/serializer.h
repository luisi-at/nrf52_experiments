// Lightweight JSON-type serializer for the BLE data transfer

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct 
{
    uint16_t ethRaw;
    uint16_t h2Raw;
    uint16_t tvoc;
    uint16_t co2;
    uint16_t coRelative;
    uint16_t noxRelative;
    uint32_t pm2p5; // avoids any floating point issues
    uint32_t pm10;
    uint32_t latitudeValue;
    uint32_t latitudeScale; // apply scale in the host
    uint32_t longitudeValue;
    uint32_t longitudeScale; 

} trackingContainer_t;

void serialize(trackingContainer_t *packet, unsigned char *returnString);