

#ifndef _RCC_REG_H_
#define _RCC_REG_H_


#define RCC_BASE_ADDR                   0x40021000U

/*RCC registers definitions*/
typedef struct
{
	__vo u32 CR;                /* RCC clock control register                  ,, register offset is [0x00]  */
	__vo u32 CFGR;              /* RCC clock configuration register            ,, register offset is [0x04]  */
	__vo u32 CIR;               /* RCC clock interrupt register                ,, register offset is [0x08]  */
	__vo u32 APB2RSTR;          /* APB2 peripheral reset register			   ,, register offset is [0x0C]  */
	__vo u32 APB1RSTR;			/* APB1 peripheral reset register              ,, register offset is [0x10]  */
	__vo u32 AHBENR;			/* AHB peripheral clock enable register        ,, register offset is [0x14]  */
	__vo u32 APB2ENR;			/* APB2 peripheral clock enable register       ,, register offset is [0x10]  */
	__vo u32 APB1ENR;			/* APB1 peripheral clock enable register       ,, register offset is [0x14]  */
	__vo u32 BDCR;				/* Backup domain control register              ,, register offset is [0x18]  */
	__vo u32 CSR;				/* Control/status register                     ,, register offset is [0x1C]  */

}RCC_RegDef_t;

/*Pointer to RCC registers*/
#define RCC         ((RCC_RegDef_t*)RCC_BASE_ADDR)


#define RCC_CR_HSION  		    0
#define RCC_CR_HSITRIM_0        3
#define RCC_CR_HSITRIM_1        4
#define RCC_CR_HSITRIM_2        5
#define RCC_CR_HSITRIM_3        6
#define RCC_CR_HSITRIM_4        7
#define RCC_CR_HSEON  		    16
#define RCC_CR_HSEBYP           18
#define RCC_CR_PLLON  	    	24

#define RCC_CFGR_PLLSRC     16
#define RCC_CFGR_PLLXTPRE   17
#define RCC_CFGR_SW         0


#define RCC_CLK_MASK			3

/*HSI ON mask (RCC_CR)*/
#define     RCC_HSI_ON_MASK    	            0x00000081
/*HSI Crystal ON mask (RCC_CR)*/
#define     RCC_HSE_CRYSTAL_ON_MASK       	0x00050000
/*HSE RC ON mask (RCC_CR)*/
#define     RCC_HSE_RC_ON_MASK              0x00010000

#endif
