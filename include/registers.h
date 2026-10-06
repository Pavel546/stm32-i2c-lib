#include <stdint.h>

//Базовые регистры переферии
#define RCC_BASE 0x40023800
#define GPIOB_BASE 0x40020400
#define I2C1_BASE 0x40005400


//Адреса подачи питания на шины переферии
#define AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define APB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x40))

//Адреса управления GPIOB
#define GPIOB_MODER (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER (*(volatile uint32_t*)(GPIOB_BASE + 0x04))
#define GPIOB_OSPEEDR (*(volatile uint32_t*)(GPIOB_BASE + 0x08))
#define GPIOB_PUPDR (*(volatile uint32_t*)(GPIOB_BASE + 0x0C))
#define GPIOB_AFRL (*(volatile uint32_t*)(GPIOB_BASE + 0x20))

//Адреса для управления I2C1
#define I2C1_CR1 (*(volatile uint32_t*)(I2C1_BASE + 0x00))
#define I2C1_CR2 (*(volatile uint32_t*)(I2C1_BASE + 0x04))
#define I2C1_DR (*(volatile uint32_t*)(I2C1_BASE + 0x10))
#define I2C1_SR1 (*(volatile uint32_t*)(I2C1_BASE + 0x14))
#define I2C1_SR2 (*(volatile uint32_t*)(I2C1_BASE + 0x18))
#define I2C1_CCR (*(volatile uint32_t*)(I2C1_BASE + 0x1C))
#define I2C1_TRISE (*(volatile uint32_t*)(I2C1_BASE +0x20))

