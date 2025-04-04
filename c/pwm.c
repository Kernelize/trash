#include <MKL25Z4.H>

// 初始化定时器，用于生成 PWM 波形
void timer_pwm_init() {
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;    // 启用 TPM0 时钟
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    // 选择 MCGFLLCLK 作为时钟源（48 MHz）

    // 配置 TPM0 通道 1 (PTA4 引脚) 为 PWM 输出
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;   // 启用 PORTA 时钟
    PORTA->PCR[4] = PORT_PCR_MUX(3);      // 设置 PTA4 为 TPM0_CH1 功能

    TPM0->SC = 0;                         // 禁止定时器，配置前先清除
    TPM0->MOD = 4800000 - 1;              // 设置周期为 4800000 个时钟周期 -> 10 Hz (48 MHz / 4800000 = 10 Hz)

    // 配置通道 1 的占空比
    TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; // 边沿对齐、高电平有效
    TPM0->CONTROLS[1].CnV = (TPM0->MOD + 1) * 30 / 100;              // 占空比为 30%

    TPM0->SC = TPM_SC_CMOD(1) | TPM_SC_PS(0); // 启用 TPM 模块并设置分频为 1（无分频）
}

int main() {
    timer_pwm_init(); // 初始化定时器生成 PWM 波形
    while (1) {
        // 主程序可以执行其他任务
    }
}

/* 
 * 低有效就是
 * TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
 * MSB = 1：选择边沿对齐模式。
 * ELSB = 1，ELSA = 0：高有效，PWM 信号的高电平表示有效。
 * 高有效
 * TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
*/
