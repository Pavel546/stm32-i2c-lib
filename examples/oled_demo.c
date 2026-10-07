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

	delay(500000);
	//Инициализация I2C1
	I2C1_Init(16);

	//Конфигурация дисплея
	OLED_SendCommand(0xAE); // Выключить дисплей (Display OFF)
	OLED_SendCommand(0x20); // Выбор режима адресации памяти
	OLED_SendCommand(0x00); // Горизонтальная адресация (память как один массив)
	OLED_SendCommand(0xA8); // Настройка коэффициента мультиплексирования (высота)
	OLED_SendCommand(0x1F); // Высота матрицы: 32 строки (0x1F = 31)
	OLED_SendCommand(0xD3); // Настройка вертикального смещения (Display Offset)
	OLED_SendCommand(0x00); // Смещение отсутствует
	OLED_SendCommand(0x40); // Установка стартовой строки развертки памяти в 0
	OLED_SendCommand(0x8D); // Управление встроенным умножителем напряжения (Charge Pump)
	OLED_SendCommand(0x14); // Включить умножитель (иначе OLED-панель не засветится)
	OLED_SendCommand(0xA1); // Развертка по горизонтали (отражение влево/вправо)
	OLED_SendCommand(0xC8); // Развертка по вертикали (отражение вверх/вниз)
	OLED_SendCommand(0xDA); // Конфигурация аппаратных выводов сетки (COM Pins)
	OLED_SendCommand(0x02); // Оптимальный режим для разрешения 128x32
	OLED_SendCommand(0x81); // Настройка яркости (Яркость/Контраст)
	OLED_SendCommand(0x7F); // Значение яркости (среднее положение)
	OLED_SendCommand(0xD5); // Настройка частоты генератора дисплея
	OLED_SendCommand(0x80); // Стандартное заводское значение делителя
	OLED_SendCommand(0xD9); // Фазы циклов предзаряда матрицы
	OLED_SendCommand(0xF1); // Рекомендуемые тайминги для стабильной картинки
	OLED_SendCommand(0xDB); // Уровень напряжения удержания пикселей (VCOMH)
	OLED_SendCommand(0x40); // Стандартный порог стабильности
	OLED_SendCommand(0xA4); // Включение режима вывода данных из памяти RAM
	OLED_SendCommand(0xA6); // Режим отображения: прямой (не инверсный)
	OLED_SendCommand(0xAF); // Включить дисплей (Display ON)


	while(1){

		// Подготовка геометрии перед полной заливкой
		OLED_SendCommand(0x21); // Задать диапазон колонок
		OLED_SendCommand(0x00); // Старт: 0
		OLED_SendCommand(0x7F); // Конец: 127
		OLED_SendCommand(0x22); // Задать диапазон страниц (полос)
		OLED_SendCommand(0x00); // Старт: 0
		OLED_SendCommand(0x03); // Конец: 3 (всего 4 страницы для 32 пикселей)

		//Заливка экрана
		for(int i = 0; i < 512; i++){
			OLED_SendData(0xFF);
		}

		//Задержка
		delay(1000000);

		// Подготовка геометрии перед полной очисткой
		OLED_SendCommand(0x21); // Задать диапазон колонок
		OLED_SendCommand(0x00); // Старт: 0
		OLED_SendCommand(0x7F); // Конец: 127
		OLED_SendCommand(0x22); // Задать диапазон страниц
		OLED_SendCommand(0x00); // Старт: 0
		OLED_SendCommand(0x03); // Конец: 3
        
		//Очистка экрана
		for(int i = 0; i < 512; i++){
			OLED_SendData(0x00);
		}

		//Задержка
		delay(1000000);

	}

}
