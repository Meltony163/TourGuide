


#ifndef _RCC_H_
#define _RCC_H_

typedef enum
{
	RCC_SYSCLK_HSE_Crys,
	RCC_SYSCLK_HSE_RC,
	RCC_SYSCLK_HSI,
	RCC_SYSCLK_PLL
}RCC_SysClk_t;

typedef enum
{
	RCC_AHB_not_divided,
	RCC_AHB_div_by_2=8,
	RCC_AHB_div_by_4,
	RCC_AHB_div_by_8,
	RCC_AHB_div_by_16,
	RCC_AHB_div_by_64,
	RCC_AHB_div_by_128,
	RCC_AHB_div_by_256,
	RCC_AHB_div_by_512,
}RCC_AHBPrescaler_t;

typedef enum
{
	RCC_APB_not_divided,
	RCC_APB_divBy_2=4,
	RCC_APB_divBy_4,
	RCC_APB_divBy_8,
	RCC_APB_divBy_16,
}RCC_APBPrescaler_t;

typedef enum
{
	RCC_PLL_inputHSE,
	RCC_PLL_inputHSEDevBy2,
	RCC_PLL_inputHSIDevBy2
}RCC_PLLInputClk_t;


typedef enum
{
	RCC_PLL_inpClkx2,
	RCC_PLL_inpClkx3,
	RCC_PLL_inpClkx4,
	RCC_PLL_inpClkx5,
	RCC_PLL_inpClkx6,
	RCC_PLL_inpClkx7,
	RCC_PLL_inpClkx8,
	RCC_PLL_inpClkx9,
	RCC_PLL_inpClkx10,
	RCC_PLL_inpClkx11,
	RCC_PLL_inpClkx12,
	RCC_PLL_inpClkx13,
	RCC_PLL_inpClkx14,
	RCC_PLL_inpClkx15,
	RCC_PLL_inpClkx16
}PLL_MultFactor_t;


typedef enum
{
	RCC_MCO_SYSCLK,
	RCC_MCO_HSI,
	RCC_MCO_HSE,
	RCC_MCO_PLLDevBy2,
}RCC_MCO_t;

typedef enum
{
	RCC_AHB_BUS,
	RCC_APB1_BUS,
	RCC_APB2_BUS
}RCC_BusProt_t;

/********************/

typedef enum
{
	DMA1,
	DMA2,
	SRAM,
}RCC_AHBPeriph_t;

typedef enum
{
	TIM2,
	TIM3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	TIM12,
	TIM13,
	TIM14,
	/*TODO*/
}RCC_APB1Periph_t;

typedef enum
{
	AFIO,
	GPIOA=2,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	/*TODO*/
}RCC_APB2Periph_t;

typedef struct
{
	RCC_SysClk_t             RCC_SysClkSource;
	RCC_AHBPrescaler_t  RCC_AHBPrescaler;
	RCC_APBPrescaler_t  RCC_APB1Prescaler;
	RCC_APBPrescaler_t  RCC_APB2Prescaler;
	RCC_PLLInputClk_t     RCC_PLLInputClk;
	PLL_MultFactor_t         RCC_MultFactor;

}RCC_Handler_t;


/*****************************************/

ES_t RCC_enuInitSystemClk(RCC_Handler_t *Copy_pstrRCCSettings);

ES_t RCC_enuAHBPeriphClkCtrl(RCC_AHBPeriph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi);

ES_t RCC_enuAPB1PeriphClkCtrl(RCC_APB1Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi);

ES_t RCC_enuAPB2PeriphClkCtrl(RCC_APB2Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi);

ES_t RCC_enuGetSysClkType(RCC_SysClk_t *Copy_penuSysClk);

ES_t RCC_enuGetSysClkValue(u32 *Copy_pu32SysClkValue);


#endif
