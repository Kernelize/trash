#include <MKL25Z4.H>
#include "user.h"

void adc_init() {
  SIM->SCGC5 |= BIT10;          // enable portB clock
  PORTB->PCR[3] = 0;            // PTB3.MUX[10 9 8] = 000, analog input

  SIM->SCGC6 |= BIT27;          // enable clock to ADC0
  ADC0->CFG1= BIT6+ BIT4+ BIT2;
  // normal power, clock divided by 4 (ADIV: 10)
  // long sample time,  
  // 12 bit resolution (MODE=01 when SC2.DIFF=0, single ended)
  // ADICLK=00, bus clock
  // TYPE: 5.2MHz(LPC,HSC = 0)
  ADC0->SC2 &= ~0x40; // ADTRG=0 software trigger
}

int read_adc() {
  short int adc_result;
  ADC0->SC1[0] = 8;         // channel 1
  while (!(ADC0->SC1[0] & BIT7)) {} // wait
  adc_result = ADC0->R[0]; //read conversion result and clear COCO flag
  int vi = adc_result * 3.3 / 4096;
  return vi;
}

void system_init() {
  adc_init();
}

int main() {
  system_init();
  while (1) {
    sprintf("%d", read_adc());
  }
  return 0;
}
