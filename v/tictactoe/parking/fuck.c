#include <MKL25Z4.H>

#define BIT0 (1U << 0)
#define BIT1 (1U << 1)
#define BIT2 (1U << 2)
#define BIT3 (1U << 3)
#define BIT4 (1U << 4)
#define BIT5 (1U << 5)
#define BIT6 (1U << 6)
#define BIT7 (1U << 7)
#define BIT8 (1U << 8)
#define BIT9 (1U << 9)
#define BIT10 (1U << 10)
#define BIT11 (1U << 11)
#define BIT12 (1U << 12)
#define BIT13 (1U << 13)
#define BIT14 (1U << 14)
#define BIT15 (1U << 15)
#define BIT16 (1U << 16)
#define BIT17 (1U << 17)
#define BIT18 (1U << 18)
#define BIT19 (1U << 19)
#define BIT20 (1U << 20)
#define BIT21 (1U << 21)
#define BIT22 (1U << 22)
#define BIT23 (1U << 23)
#define BIT24 (1U << 24)
#define BIT25 (1U << 25)
#define BIT26 (1U << 26)
#define BIT27 (1U << 27)
#define BIT28 (1U << 28)
#define BIT29 (1U << 29)
#define BIT30 (1U << 30)
#define BIT31 (1U << 31)

#include <math.h>

#define PI 3.1415926535897

#define N_sine 256

uint16_t sinewave[N_sine], i = 0;

float A_sine = 0.6;

void Delay100us(void) {

  uint16_t i;

  for (i = 0; i < 350; i++) {
  }
}

void Sine_Init(void) {

  uint16_t i;

  for (i = 0; i < N_sine; i++)
    sinewave[i] = 2047 + ((4096 * A_sine / 3.3) * sinf(2 * PI * i / N_sine));
}

void DAC_Init(void) {

  SIM->SCGC6 |= BIT31;

  DAC0->C1 = 0;

  DAC0->C0 = BIT5 + BIT7;
}

void System_Init(void) {

  DAC_Init();
  Sine_Init();
}

int main(void) {

  System_Init();

  while (1) {

    DAC0->DAT[0].DATL = sinewave[i] & 0xFF;

    DAC0->DAT[0].DATH = (sinewave[i] >> 8) & 0x0F;

    i++;

    if (i >= N_sine)
      i = 0;

    Delay100us();
  }
}

void delay(int n) {
  int i;
  for (i = 0; i < n; i++)
    ;
}

int main2(void) {
  SIM->SCGC5 |= 0x0400;    // enable clock to Port B
  PORTB->PCR[18] = 0x0100; // make pin PTB18 as GPIO
  FPTB->PDOR = 0x40000;    // switch Red/Green LED off
  FPTB->PDDR = 0x40000;    // enable PTB18/19 as Output
  while (1) {
    FPTB->PCOR = 0x40000; // make the pin output low
    delay(5000000);
    FPTB->PSOR = 0x40000; // make the pin output high
    delay(5000000);
  }
}
