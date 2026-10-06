//Защита от повторного включения
#ifndef I2C1_H
#define I2C1_H

#include <stdint.h>

//Инициализация
void I2C1_Init(void);

//Сигнал СТАРТ
void I2C1_Start(void);

//Сигнал СТОП
void I2C1_Stop(void);

//Передача адреса устройства
void I2C1_SendAddress(uint8_t address, uint8_t direction);

//Запись одного байта данных
void I2C1_Write(uint8_t data);

//Чтение одного байта данных
void I2C1_Read(uint8_t address);

#endif
