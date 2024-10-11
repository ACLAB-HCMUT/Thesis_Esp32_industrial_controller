/**
 * @file dht20_Temp.h
 * @author 
 * @brief DHT20 module interface
 * @version 0.1
 * @date 
 *
 * @copyright 
 *
 */

#ifndef DHT20_TEMP_H
#define DHT20_TEMP_H

typedef struct
{
	float temp;
    float humm;

} DHT20_Data;

void DHT20_init(void);
void DHT20_deinit(void);

void DHT20_turnOn(void);
void DHT20_turnOff(void);
DHT20_Data DHT20_get();
bool DHT20_isError();
void DHT20_test();


#endif // DHT20_TEMP_H
