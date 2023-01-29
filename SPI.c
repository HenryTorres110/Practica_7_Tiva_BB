#include "lib/include.h"

extern void SPI_CONFIGURATION(int spi_module){
    // Tenemos 4 módulos de SPI
    //Four pins are required such as clock, serial data in, serial data out and frame signal.
    SYSCTL -> RCGCSSI = (1 << spi_module);
    SYSCTL -> RCGCGPIO |= (1 << 0);  // Port A

    GPIOA -> AFSEL |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    GPIOA -> PCTL &= ~0x000FFFF00;
    GPIOA -> PCTL |= 0x000222200;
    GPIOA -> DEN |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);

    SSI0 -> CR1 &= ~(1 << 1);
    SSI0 -> CR1 = 0x00000000; // Master Mode
    SSI0 -> CC = 0x0;
    SSI0 -> CPSR = 0x2; //Divisor 2
    SSI0 -> CR0 = (0xB << 0); // 12 bits
    SSI0 -> CR1 |= (1 << 1);
}