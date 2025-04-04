#include <MKL25Z4.H>
#include "user.h"

/* initialize UART0 to transmit and receive at 57600 Baud, PA1 and PA2 pads */
void UART0_init (void)
{
    SIM->SCGC4 |= 0x0400;            /* enable clock for UART0 */
    SIM->SOPT2 |= 0x40000000;        /* use MCGFFCLK output for UART Baud rate generator */
    UART0->C2 = 0;                   /* turn off UART0 while changing configurations */
    UART0->BDH = 0x00;
    UART0->BDL = 0x17;               /* 57600 Baud */
    UART0->C4 = 0x0F;                /* Over Sampling Ratio 16 */
    UART0->C1 = 0x00;                /* 8-bit data */
    UART0->C2 |= 0x0C;               /* enable transmit (TE) and receive (RE) */
    SIM->SCGC5 |= 0x0200;            /* enable clock for PORTA */
    PORTA->PCR[2] = 0x0200;          /* make PTA2 UART0_Tx pin */
    PORTA->PCR[1] = 0x0200;          /* make PTA1 UART0_Rx pin */
}


/* UART0 to transmit */
void UART0_Tx (uint8_t data) {
    // wait until Tx data register is empty
    while (!(UART0->S1 & 0x80)) { }
    // Tx data register now empty
    UART0->D = data;
}

uint8_t UART0_Rx (void) {
    // wait until Rx data register is full
    while (!(UART0->S1 & 0x20)) { }
    return UART0->D;
}

int main() {
  UART0_init();
  while (1) {
    sprintf("%d\n", UART0_Rx());
  }
  return 0;
}
