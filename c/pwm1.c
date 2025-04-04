#include <MKL25Z4.H>

int main() {
  SIM->SCGC5 |= 0x1000;
  PORTD->PCR[1] = 0x0400;
  SIM->SCGC6 |= 0x01000000;
  SIM->SOPT2 |= 0x01000000;
  TPM0->SC = 0;
  TPM0->MOD = 52428;
  TPM0->CONTROLS[1].CnV = 15729;
  TPM0->SC = 0x08+0x02;
  while(1) {

  }
}
