#include <stdint.h>

/* Define region offset alias */
#define PERIPH_BASE             (0x40000000)

/* Peripheral memory map */
#define APB1PERIPH_BASE      	(PERIPH_BASE)
#define APB2PERIPH_BASE      	(PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE      	(PERIPH_BASE + 0x00020000)

/* Define APB2 peripherals */
#define USART1_BASE				(APB2PERIPH_BASE + 0x1000)
#define TIM2_BASE				(PERIPH_BASE     + 0x0000)

/* Define AHB1 peripherals */
#define GPIOA_BASE				(AHB1PERIPH_BASE + 0x0000) 
#define GPIOB_BASE 				(AHB1PERIPH_BASE + 0x0400)
#define CRC_BASE              	(AHB1PERIPH_BASE + 0x3000)
#define RCC_BASE				(AHB1PERIPH_BASE + 0x3800)

/* Define RCC offset configuration bits */
#define RCC_AHB1ENR				(0x00000034)
#define RCC_APB1RSTR 			(0x00000020)
#define RCC_APB1ENR				(0x00000040)
#define RCC_APB2ENR				(0x00000044)

/* Define GPIO offset configuration bits */
#define GPIO_MODER				(0x00000000)
#define GPIO_SPEEDR				(0x00000008)
#define GPIO_PUPDR				(0x0000000C)
#define GPIO_IDR				(0x00000010)
#define GPIO_ODR				(0x00000014)
#define GPIO_BSRR				(0x00000018)

/* Define TIM2 offset configuration */
#define TIM2_CR1				(0x00000000)
#define TIM2_CR2				(0x00000004)
#define TIM2_DIER				(0x0000000C)
#define TIM2_SMRC				(0x00000008)
#define TIM2_SR					(0x00000010)
#define TIM2_EGR				(0x00000014)
#define TIM2_PSC				(0x00000028)
#define TIM2_CNT				(0x00000024)
#define TIM2_ARR				(0x0000002C)

/* Define USART registers */
#define USART_SR				(0x00000000)
#define USART_DR				(0x00000004)
#define USART_BRR				(0x00000008)
#define USART_CR1				(0x0000000C)
#define USART_CR2				(0x00000010)

/* Define SysTick */
#define SYST_CSR  				(0xE000E010)
#define SYST_RVR  				(0xE000E014)
#define	SYST_CSR_CLKSOURCE	    (2)
#define	SYST_CSR_TICKINT	    (1)
#define	SYST_CSR_ENABLE		    (0)

#define	AFIO_EXTICR1			(0x40010008)
#define	EXTI_IMR				(0x40010400)
#define	EXTI_FTSR				(0x4001040C)
#define	EXTI_PR					(0x40010414)
#define	NVIC_ISER0				(0xE000E100)
#define	NVIC_IPR				(0xE000E400)
#define NVIC_ICPR0				(0xE000E280)

/* Stack pointer */
extern char _estack;

/* Prototypes */
int main();
void tim2_int();
void SysTick();

/* Interruption vector table */
uint32_t (* const vector_table[]) __attribute__ ((section(".text.vector_table"))) = {
	(uint32_t*)(&_estack),	// End stack
	(uint32_t*)(main),		// Reset
	0,						// NMI
	0,						// Hard fault
	0,						// Memory management fault
	0,						// Bus fault
	0,						// Usage fault
	0, 0, 0, 0,				// Reserved 
	0,						// SVCall
	0,						// Debug monitor
	0,						// Reserved
	0,						// PendSV
	0,						// SysTick
	0,						// Window Watchdog interrupt
	0,						// PVD through EXTI Line detection interrupt
	0,						// Tamper interrupt
	0,						// RTC global interrupt
	0,						// Flash global interrupt
	0,						// RCC global interrupt
	0,						// EXTI Line0 interrupt
	0,						// EXTI Line1 interrupt
	0,						// EXTI Line2 interrupt
	0,						// EXTI Line3 interrupt
	0,						// EXTI Line4 interrupt
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	0,						// 
	(uint32_t*)tim2_int,	// 
};

/* Memory section description for the GPIO PORTA */
volatile uint32_t *const PORTA     = (volatile uint32_t *) (GPIOA_BASE);
volatile uint32_t *const PORTARCC  = (volatile uint32_t *) (RCC_BASE + RCC_AHB1ENR);
volatile uint32_t *const PADIR     = (volatile uint32_t *) (GPIOA_BASE + GPIO_MODER);
volatile uint32_t *const PASPEEDR  = (volatile uint32_t *) (GPIOA_BASE + GPIO_SPEEDR);
volatile uint32_t *const PAPUPDR   = (volatile uint32_t *) (GPIOA_BASE + GPIO_PUPDR);
volatile uint32_t *const PAIDR	   = (volatile uint32_t *) (GPIOA_BASE + GPIO_IDR);
volatile uint32_t *const PAODR     = (volatile uint32_t *) (GPIOA_BASE + GPIO_ODR);
volatile uint32_t *const PABSRR    = (volatile uint32_t *) (GPIOA_BASE + GPIO_BSRR);

/* Memory section description for the USART1 */
volatile uint32_t *const U1SR      = (volatile uint32_t *) (USART1_BASE + USART_SR);
volatile uint32_t *const U1DR      = (volatile uint32_t *) (USART1_BASE + USART_DR);
volatile uint32_t *const U1BRR     = (volatile uint32_t *) (USART1_BASE + USART_BRR);
volatile uint32_t *const U1CR1     = (volatile uint32_t *) (USART1_BASE + USART_CR1);
volatile uint32_t *const U1CR2     = (volatile uint32_t *) (USART1_BASE + USART_CR2);
volatile uint32_t *const U1EN      = (volatile uint32_t *) (RCC_BASE + RCC_APB2ENR);

/* Timer section description */
volatile uint32_t *const TIMR2CR1  = (volatile uint32_t *) (TIM2_BASE + TIM2_CR1);
volatile uint32_t *const TIMR2CR2  = (volatile uint32_t *) (TIM2_BASE + TIM2_CR2);
volatile uint32_t *const TIMR2DIER = (volatile uint32_t *) (TIM2_BASE + TIM2_DIER);
volatile uint32_t *const TIMR2SR   = (volatile uint32_t *) (TIM2_BASE + TIM2_SR);
volatile uint32_t *const TIMR2CNT  = (volatile uint32_t *) (TIM2_BASE + TIM2_CNT);
volatile uint32_t *const TIMR2PSC  = (volatile uint32_t *) (TIM2_BASE + TIM2_PSC);
volatile uint32_t *const TIMR2ARR  = (volatile uint32_t *) (TIM2_BASE + TIM2_ARR);
volatile uint32_t *const TIMR2RCC  = (volatile uint32_t *) (RCC_BASE + RCC_APB1RSTR);
volatile uint32_t *const TIMR2EN   = (volatile uint32_t *) (RCC_BASE + RCC_APB1ENR);
volatile uint32_t *const TIMR2SMRC = (volatile uint32_t *) (TIM2_BASE + TIM2_SMRC);

/* SysTick */
volatile uint32_t* const CSR 	   = (volatile uint32_t *) (SYST_CSR);
volatile uint32_t* const RVR 	   = (volatile uint32_t *) (SYST_RVR);

volatile uint32_t* const ISER0 	   = (volatile uint32_t *) (NVIC_ISER0);
volatile uint8_t*  const IPR 	   = (volatile uint8_t  *) (NVIC_IPR);
volatile uint32_t *const ICPR0	   = (volatile uint32_t *) (NVIC_ICPR0);

volatile uint32_t* const EXTICR1   = (volatile uint32_t *) (AFIO_EXTICR1);
volatile uint32_t* const IMR 	   = (volatile uint32_t *) (EXTI_IMR);
volatile uint32_t* const FTSR 	   = (volatile uint32_t *) (EXTI_FTSR);
volatile uint32_t* const PR 	   = (volatile uint32_t *) (EXTI_PR);

/* Define pin macros for ease references */
#define PORTA_A0				(0x00)
#define PORTA_A1				(0x02)
#define PORTA_A2				(0x04)
#define PORTA_BIT0				(0x00)
#define PORTA_BIT1				(0x01)
#define GPIOA_RCC				(0x00)
#define USART1_RXNE				(0x05)
#define USART1_TXE				(0x07)
#define USART1_UE				(0x0D)
#define USART1_RE				(0x02)
#define USART1_TE				(0x03)

#define delay_ms(X) \
	asm volatile ( \
			"mov r1, %[counter]\n\t"   \
			"loop:\n\t" 			  \
			"	subs r1, r1, 1\n\t"   \
			"	bne loop" 			  \
			: 						  \
			: [counter] "r"(X * 4000) \
			: "r1" 					  \
	)

uint8_t SEM_TIMER = 0;
char SEM_STATUS = 'S';

void GPIO_config(void) {
	/* Set the GPIO clock for the PORTA */
	(*PORTARCC) |= (1 << GPIOA_RCC) | (1 << 0x00) | (1 << 0x0E);
	/* Set bit A0 of PORTA as general purpose output mode */
	(*PADIR)    &= (0b01 << PORTA_A0);
	/* Define A0 clock frequency (0b01 = medium speed) */
	(*PASPEEDR) &= (0b01 << PORTA_A0);
}

void USART1_init(void) {
	(*U1EN)  |= (1 << 0x04);
	(*U1CR1) |= (1 << USART1_UE);
	(*U1BRR)  = 0x341;
	(*U1CR1) |= (1 << USART1_RE) | (1 << USART1_TE);
}

void USART1_write(uint8_t data) {
	(*U1DR) = data;
	while(!((*U1SR) & (1 << USART1_TXE)));
}

uint8_t USART1_read() {
	while(!((*U1SR) & (1 << USART1_RXNE)));
	return (*U1DR);
}

void prints(char *buffer) {
	uint32_t i = 0;
	while (buffer[i]) {
		USART1_write(buffer[i++]);
	}
}

void scans(char *buffer) {
	uint32_t i = 0;
	do buffer[i] = USART1_read();
	while (buffer[i++] != '\n');
	buffer[i] = 0;
}

void TIM2_config() {
	/* Counter enabled */
	(*TIMR2EN) |= 0x1 << 0x00;
	/* Prescaler set for 1 sec */
	(*TIMR2PSC) = 1000;
	(*TIMR2ARR) = 1000000;
	/* Timer2 autoload */
	(*TIMR2CR1) |= (1 << 0x07) | (1 << 0x00);
	/* Update interruption enable */
	(*TIMR2DIER) |= (1 << 0x00);
	/* Enable interruption */
	(*ISER0) |= (1 << 28);
	IPR[28] = 0x20;
}

void tim2_int() {
	/* Clear timer6 interrupt status register */
	(*TIMR2SR) &= ~(1 << 0x00);
	(*ICPR0) |= (1 << 28);

	if (SEM_TIMER > 0) {
		SEM_TIMER--;	
	} else if (SEM_TIMER == 0) {
		switch (SEM_STATUS) {
			case 'G':
				SEM_STATUS = 'Y';
				SEM_TIMER = 5;
				break;
			case 'R':
				SEM_STATUS = 'G';
				SEM_TIMER = 15;
				break;
			case 'Y':
				SEM_STATUS = 'R';
				SEM_TIMER = 15;
				break;
		}
		USART1_write(SEM_STATUS);	
		USART1_write('\n');
	}
	if (SEM_STATUS == 'S') {
		USART1_write('S');
		USART1_write('\n');
	} else {
		if (SEM_TIMER >= 10) {
			char arr[3];
			uint8_t i;
			uint8_t tm = SEM_TIMER;
			for(i=0;i<3; i++, tm/=10) 
			{ 
				arr[i] = tm % 10 + '0'; 
			} 
			USART1_write(arr[1]);
			USART1_write(arr[0]);
		} else {
			USART1_write((uint8_t) SEM_TIMER + '0');
		}
		USART1_write('\n');
	}
}

void SysTick_init() {
	(*RVR) = 8000000;
	(*CSR) |= (1 << SYST_CSR_CLKSOURCE) | (1 << SYST_CSR_TICKINT) | (1 << SYST_CSR_ENABLE);
}

int main() {
	char buffer[100];

	GPIO_config();
	TIM2_config();
	USART1_init();

	(*PAODR) = 0x0;

	SEM_STATUS = 'S';
	
	for (;;) {
		scans(buffer);
		switch (buffer[0]) {
			case 'B':
				if (SEM_STATUS == 'G') {
					SEM_STATUS = 'Y';
					SEM_TIMER = 5;
				} else if (SEM_STATUS == 'R') {
					SEM_TIMER = 15;
				}
				USART1_write(SEM_STATUS);	
				USART1_write('\n');
				break;
			case 'R':
				if (SEM_STATUS == 'R' || SEM_STATUS == 'S' || SEM_STATUS == 'G') {
					SEM_TIMER = 15;
				}
				USART1_write(SEM_STATUS);	
				USART1_write('\n');
				break;
			case 'Y':
				if (SEM_STATUS == 'G') {
					SEM_TIMER = 15;
				} else if (SEM_STATUS == 'S' || SEM_STATUS == 'R') {
					SEM_STATUS = 'G';
					SEM_TIMER = 15;
				}
				USART1_write(SEM_STATUS);	
				USART1_write('\n');
				break;
			case 'S':
				SEM_TIMER = 0;
				SEM_STATUS = 'R';
				USART1_write(SEM_STATUS);	
				USART1_write('\n');
				break;
			case 'G':
				if (SEM_STATUS == 'G') {
					SEM_TIMER = 0;
					SEM_STATUS = 'S';
				} else {
					SEM_TIMER = 15;
					SEM_STATUS = 'R';
				}
				USART1_write(SEM_STATUS);	
				USART1_write('\n');
				break;
			default:
				break;
		}
	}
}
