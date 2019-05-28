#include "serializer.h"

void serialize(trackingContainer_t *packet, unsigned char *returnString)
{
    // Create these every time the 
    
    // Data containers, 6 2byte, 6 4byte (minus null character)
    unsigned char ethRawChar[6] = {0};
    unsigned char h2RawChar[6] = {0};
    unsigned char tvocChar[6] = {0};
    unsigned char co2Char[6] = {0};
    unsigned char coRelChar[6] = {0};
    unsigned char noxRelChar[6] = {0};
    unsigned char pm2p5Char[11] = {0};
    unsigned char pm10Char[11] = {0};
    unsigned char latitudeValChar[11] = {0};
    unsigned char latitudeScaleChar[11] = {0};
    unsigned char longitudeValChar[11] = {0};
    unsigned char longitudeScaleChar[11] = {0};

    // The char array to copy 'out' from
    unsigned char constructBuffer[244] = {0}; // Fill with null characters

    // 'Key' names for JSON
    // Braces are to emulate the JSON format for clarity
    // {
    unsigned char gasReadings[6] = "\"GASR\"";
        // : {
    unsigned char ethKey[6] = "\"ETRV\"";       // ,
    unsigned char h2Key[6] = "\"H2RV\"";        // , 
    unsigned char tvocKey[6] = "\"TVOC\"";      // ,
    unsigned char co2Key[6] = "\"CO2V\"";       // ,
    unsigned char coKey[6] = "\"CORV\"";        // ,
    unsigned char noxKey[6] = "\"NORV\"";       // ,
        // },

    unsigned char pm[6] = "\"PMRS\"";
        // : {
    unsigned char pm2p5Key[6] = "\"PM25\"";     // ,
    unsigned char pm10Key[6] = "\"PM10\"";      // ,
        // }, 

    unsigned char positionKey[6] = "\"POSN\"";
        // : {
    unsigned char latValKey[6] = "\"LATV\"";    // ,
    unsigned char latScaleKey[6] = "\"LATS\"";  // ,
    unsigned char longValKey[6] = "\"LNGV\"";   // ,
    unsigned char longScaleKey[6] = "\"LNGS\""; // ,
        // }
    // }

    // 15 colons in the string, each for the Key:Value pair
    // Don't need to worry about quotations marks, as no string values
    // 14 commas to separate the  key:value pairs- we want legal JSON
    // 30 bytes (?) total for the delimiters

    // Maximum number of bytes to be put into the string
    // (hard-coded, poor form I know but since this isn't going to
    // be extended then I think it's fine)

    // Convert the uints into char
    // Note that the ARM processor in the nRF52 is little endian

    // 16 bit conversions
    sprintf(ethRawChar, "%d", packet->ethRaw);
    sprintf(h2RawChar, "%d", packet->h2Raw);
    sprintf(tvocChar, "%d", packet->tvoc);
    sprintf(co2Char, "%d", packet->co2);
    sprintf(coRelChar, "%d", packet->coRelative);
    sprintf(noxRelChar, "%d", packet->noxRelative);

    // 32 bit float conversions
    // (\/ -> these are wrong)
    sprintf(pm2p5Char, "%d", packet->pm2p5);
    sprintf(pm10Char, "%d", packet->pm10);
    sprintf(latitudeValChar, "%d", packet->latitudeValue);
    sprintf(latitudeScaleChar, "%d", packet->latitudeScale);
    sprintf(longitudeValChar, "%d", packet->longitudeValue);
    sprintf(longitudeScaleChar, "%d", packet->longitudeScale);

    /*
    

    // 32 bit float conversions
    pm2p5Char[0] = (packet->pm2p5 & 0xFFu);
    pm2p5Char[1] = ((packet->pm2p5 >> 8u) & 0xFFu);
    pm2p5Char[2] = ((packet->pm2p5 >> 16u) & 0xFFu);
    pm2p5Char[3] = ((packet->pm2p5 >> 24u) & 0xFFu);

    pm10Char[0] = (packet->pm10 & 0xFFu);
    pm10Char[1] = ((packet->pm10 >> 8u) & 0xFFu);
    pm10Char[2] = ((packet->pm10 >> 16u) & 0xFFu);
    pm10Char[3] = ((packet->pm10 >> 24u) & 0xFFu);

    latitudeValChar[0] = (packet->latitudeValue & 0xFFu);
    latitudeValChar[1] = ((packet->latitudeValue >> 8u) & 0xFFu);
    latitudeValChar[2] = ((packet->latitudeValue >> 16u) & 0xFFu);
    latitudeValChar[3] = ((packet->latitudeValue >> 24u) & 0xFFu);

    latitudeScaleChar[0] = (packet->latitudeScale & 0xFFu);
    latitudeScaleChar[1] = ((packet->latitudeScale >> 8u) & 0xFFu);
    latitudeScaleChar[2] = ((packet->latitudeScale >> 16u) & 0xFFu);
    latitudeScaleChar[3] = ((packet->latitudeScale >> 24u) & 0xFFu);

    longitudeValChar[0] = (packet->longitudeValue & 0xFFu);
    longitudeValChar[1] = ((packet->longitudeValue >> 8u) & 0xFFu);
    longitudeValChar[2] = ((packet->longitudeValue >> 16u) & 0xFFu);
    longitudeValChar[3] = ((packet->longitudeValue >> 24u) & 0xFFu);

    longitudeScaleChar[0] = (packet->longitudeScale & 0xFFu);
    longitudeScaleChar[1] = ((packet->longitudeScale >> 8u) & 0xFFu);
    longitudeScaleChar[2] = ((packet->longitudeScale >> 16u) & 0xFFu);
    longitudeScaleChar[3] = ((packet->longitudeScale >> 24u) & 0xFFu);
    */
     
    // This needs to be accounted for with the GATT_MAX_MTU_SIZE

    // not sure there is an any lighter way to do this
    // Gas readings
    strncpy(constructBuffer, "{", 1);
    strncat(constructBuffer, gasReadings, 6);
    strncat(constructBuffer, ":{", 2);
    strncat(constructBuffer, ethKey, 6);
    strncat(constructBuffer, ":", 1);
    strncat(constructBuffer, ethRawChar, 5);
    strncat(constructBuffer, ",", 1);
    strncat(constructBuffer, h2Key, 6);
    strncat(constructBuffer, ":", 1);
    strncat(constructBuffer, h2RawChar, 5);
    strncat(constructBuffer, ",", 1);
    strncat(constructBuffer, tvocKey, 6);
    strncat(constructBuffer, ":", 1);
    strncat(constructBuffer, tvocChar, 5);
    strncat(constructBuffer, ",", 1);
    strncat(constructBuffer, co2Key, 6);
    strncat(constructBuffer, ":", 1);
    strncat(constructBuffer, co2Char, 5);
    strncat(constructBuffer, ",", 1);
    strncat(constructBuffer, coKey, 6);
    strncat(constructBuffer, ":", 1);
    strncat(constructBuffer, coRelChar, 5);
    strncat(constructBuffer, ",", 1);
    strncat(constructBuffer, noxKey, 6);
    strncat(constructBuffer, ":", 1);
    strncat(constructBuffer, noxRelChar, 5);
    strncat(constructBuffer, "},", 2);

    // PM readings
    strncat(constructBuffer, pm, 6);
    strncat(constructBuffer, ":{", 2);
    strncat(constructBuffer, pm2p5Key, 6);
    strncat(constructBuffer, ":", 2);
    strncat(constructBuffer, pm2p5Char, 10);
    strncat(constructBuffer, ",", 2);
    strncat(constructBuffer, pm10Key, 6);
    strncat(constructBuffer, ":", 2);
    strncat(constructBuffer, pm10Char, 10);
    strncat(constructBuffer, "},", 2);

    // Coordinates
    strncat(constructBuffer, positionKey, 6);
    strncat(constructBuffer, ":{", 2);
    strncat(constructBuffer, latValKey, 6);
    strncat(constructBuffer, ":", 2);
    strncat(constructBuffer, latitudeValChar, 10);
    strncat(constructBuffer, ",", 2);
    strncat(constructBuffer, latScaleKey, 6);
    strncat(constructBuffer, ":", 2);
    strncat(constructBuffer, latitudeScaleChar, 10);
    strncat(constructBuffer, ",", 2);
    strncat(constructBuffer, longValKey, 6);
    strncat(constructBuffer, ":", 2);
    strncat(constructBuffer, longitudeValChar, 10);
    strncat(constructBuffer, ",", 2);
    strncat(constructBuffer, longScaleKey, 6);
    strncat(constructBuffer, ":", 2);
    strncat(constructBuffer, longitudeScaleChar, 10);
    strncat(constructBuffer, "}}", 2); // Null char should already be at the end of the string

    // 'Return' the string
    memcpy(returnString, constructBuffer, sizeof(constructBuffer));

}