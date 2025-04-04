#include <MKL25Z4.H>
#include <stdio.h>
#include "user.h"

volatile char buffer[20]; // 用于存储 sprintf 输出的字符串

// 定时器中断服务程序
void TPM0_IRQHandler(void) {
    if (TPM0->SC & TPM_SC_TOF_MASK) { // 检查溢出标志
        TPM0->SC &= ~TPM_SC_TOF_MASK; // 清除溢出标志
        sprintf(buffer, "hello\n");  // 使用 sprintf 输出字符串
    }
}

// 定时器初始化函数
void timer_init() {
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; // 启用 TPM0 时钟
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // 选择 MCGFLLCLK 作为时钟源（48 MHz）

    TPM0->SC = 0;                      // 先关闭 TPM0
    TPM0->MOD = 4800000 - 1;           // 设置周期为 4800000 个时钟周期 -> 10 Hz (48 MHz / 4800000 = 10 Hz)
    TPM0->SC |= TPM_SC_PS(0);          // 设置分频为 1（无分频）
    TPM0->SC |= TPM_SC_CMOD(1);        // 启用 TPM 模块并使用时钟源
    TPM0->SC |= TPM_SC_TOIE_MASK;      // 启用溢出中断

    NVIC_EnableIRQ(TPM0_IRQn);         // 启用 NVIC 对应的 TPM0 中断
}

int main() {
    timer_init(); // 初始化定时器
    while (1) {
        // 主程序可以执行其他任务，"hello\n" 将每 0.1 秒通过中断输出
    }
}
