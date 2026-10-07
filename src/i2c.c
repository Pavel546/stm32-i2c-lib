//Подключение заголовочных файлов
#include "registers.h"
#include "i2c.h"

void I2C1_Init(uint32_t APB1_clock_mhz){

	//Включаем тактирование GPIO_B и I2C1
	RCC_AHB1ENR |= (1 << 1); 
	RCC_APB1ENR |= (1 << 21); 

	//Настройка ножек
	//Установка альтернативного режима на ножках PB6(SCL) и PB7(SDA)
	GPIOB_MODER &= ~(15 << 12);
	GPIOB_MODER |= (10 << 12);

	//установка типа вывода в положение Open-Drain
	GPIOB_OTYPER &= ~(3 << 6);
	GPIOB_OTYPER |= (3 << 6);

	//Установка скорости работы пинов
	GPIOB_OSPEEDR &= ~(15 << 12);
	GPIOB_OSPEEDR |= (10 << 12);

	//подключение внутренней подтяжки
	GPIOB_PUPDR &= ~(15 << 12);
	GPIOB_PUPDR |= (5 << 12);

	//Установка функции AF4 (0100)
	GPIOB_AFRL &= ~(255 << 24);
	GPIOB_AFRL |= (68 << 24);

	//Программный сброс переферии
	I2C1_CR1 |= (1 << 15);
	I2C1_CR1 &= ~(1 << 15);

	//Задание частоты тактирования шины
	I2C1_CR2 &= ~(63 << 0);
	I2C1_CR2 |= (APB1_clock_mhz << 0);

	//Настройка скорости шины
	I2C1_CCR = (5*APB1_clock_mhz)/2;

	//Настройка времени нарастания
	I2C1_TRISE = APB1_clock_mhz+1;

	//Включение модуля
	I2C1_CR1 |= (1 << 0);
}

void I2C1_Start(void){

	I2C1_CR1 |= (1 << 8);
	while(!(I2C1_SR1 & (1 << 0)));

}

void I2C1_Stop(void){

	I2C1_CR1 |= (1 << 9);

}

void I2C1_SendAddress(uint8_t address, uint8_t direction){

	address <<= 1;
	address |= direction;
	I2C1_DR = address;
	while(!(I2C1_SR1 & (1 << 1)));
	(void) I2C1_SR1;
	(void) I2C1_SR2;

}
