/**
 * @file main.c
 * @brief Демонстрационный пример использования bare-metal библиотеки I2C1.
 * 
 * Программа выполняет инициализацию интерфейса I2C1 на частоте шины 16 МГц
 * и осуществляет базовую настройку OLED-дисплея 0.91" (контроллер SSD1306, 128x32).
 * В основном цикле производится циклическая заливка экрана белым цветом 
 * и его последующая очистка с задержкой в ~1 секунду.
 */

#include "i2c.h"

#define OLED_ADDR 0x3C

//Функция отправки комманды
void OLED_SendCommand(uint8_t cmd){

	I2C1_Start(); //Старт шины I2C1
	I2C1_SendAddress(OLED_ADDR, 0); //Отправка адреса устройства и установка режима записи
	I2C1_Write(0x00); //Отправка управляющего байта для введения комманд
	I2C1_Write(cmd); //Отправка команды
	I2C1_Stop(); // Стоп

}

//Функция отправки данных
void OLED_SendData(uint8_t data){

	I2C1_Start();
	I2C1_SendAddress(OLED_ADDR, 0);
	I2C1_Write(0x40); // отправка управляющего байта для введения данных
	I2C1_Write(data);
	I2C1_Stop();

}

//Простейшая функция задержки
void delay(volatile uint32_t count) {
	while(count--);
}


void main (void) {

	//Инициализация I2C1
	I2C1_Init(16);

	//Конфигурация дисплея
	OLED_SendCommand(0xAE); // 1. Выключить дисплей (Display OFF)
	OLED_SendCommand(0xA8); // 2. Команда настройки высоты экрана (Multiplex Ratio)
	OLED_SendCommand(0x1F); // 3. Значение высоты: 32 строки (0x1F = 31, отсчет от 0)
	OLED_SendCommand(0xD3); // 4. Команда смещения экрана (Display Offset)
	OLED_SendCommand(0x00); // 5. Значение смещения: 0 (без смещения)
	OLED_SendCommand(0x8D); // 6. Команда управления внутренним питанием (Charge Pump)
	OLED_SendCommand(0x14); // 7. Значение: Включить Charge Pump (иначе OLED не загорится)
	OLED_SendCommand(0xAF); // 8. Включить дисплей (Display ON)

	while(1){

		//Заливка экрана
		for(int i = 0; i < 512; i++){
			OLED_SendData(0xFF);
		}

		//Задержка
		delay(1000000);

		//Очистка экрана
		for(int i = 0; i < 512; i++){
			OLED_SendData(0x00);
		}

		//Задержка
		delay(1000000);

	}

}
