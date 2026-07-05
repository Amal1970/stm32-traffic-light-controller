#ifndef MAIN_H_
#define MAIN_H_

// systick configuration
#define SYS_CLK_HZ 16000000U
#define TICK_HZ 1000U

#define SYST_CSR (*((volatile uint32_t *)0xE000E010U))
#define SYST_RVR (*((volatile uint32_t *)0xE000E014U))
#define SYST_CVR (*((volatile uint32_t *)0xE000E018U))

// prototypes 
void systick_init(uint32_t ticks);


#endif