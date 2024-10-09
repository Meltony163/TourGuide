


#include "../common_lib/imp_data_types.h"
#include "../common_lib/error_state.h"
#include "../common_lib/bit_math.h"

#include "rcc.h"
#include "rcc_reg.h"
#include "rcc_prv.h"

ES_t RCC_enuInitSystemClk(RCC_Handler_t *Copy_pstrRCCSettings)
{
	ES_t Local_enuErrorState = ES_NOT_OK;


	if(Copy_pstrRCCSettings != NULL)
	{
		u32 Local_u32CFGRTemp = 0;
		u32 Local_u32CRTemp = 0;

		/*set the buses pre-scaler*/
		Local_u32CFGRTemp |= ( Copy_pstrRCCSettings->RCC_AHBPrescaler  << 4  ); //AHB pre-scaler
		Local_u32CFGRTemp |= ( Copy_pstrRCCSettings->RCC_APB1Prescaler << 8  ); //APB1 pre-scaler
		Local_u32CFGRTemp |= ( Copy_pstrRCCSettings->RCC_APB2Prescaler << 11 ); //APB2 pre-scaler

		/*set the clock sources ON*/
		if(Copy_pstrRCCSettings->RCC_SysClkSource == RCC_SYSCLK_HSI)
		{
			Local_u32CRTemp = RCC_HSI_ON_MASK; //HSI ON
			RCC->CR = Local_u32CRTemp;

			Local_u32CFGRTemp |= 0x0;  //select HSI
			RCC->CFGR = Local_u32CFGRTemp;

			Local_enuErrorState = ES_OK;
		}
		else if(Copy_pstrRCCSettings->RCC_SysClkSource == RCC_SYSCLK_HSE_Crys)
		{
			Local_u32CRTemp = RCC_HSE_CRYSTAL_ON_MASK; //HSE ON
			RCC->CR = Local_u32CRTemp;

			Local_u32CFGRTemp |= 0x1;                  //select HSE
			RCC->CFGR = Local_u32CFGRTemp;

			Local_enuErrorState = ES_OK;
		}
		else if(Copy_pstrRCCSettings->RCC_SysClkSource == RCC_SYSCLK_HSE_RC)
		{
			Local_u32CRTemp = RCC_HSE_RC_ON_MASK; //HSE ON
			RCC->CR = Local_u32CRTemp;

			Local_u32CFGRTemp |= 0x1;             //select HSE
			RCC->CFGR = Local_u32CFGRTemp;

			Local_enuErrorState = ES_OK;
		}
		else if(Copy_pstrRCCSettings->RCC_SysClkSource == RCC_SYSCLK_PLL)
		{

			/*select the PLL multiplication factor*/

			/*
			 * PLL must be disabled, so we can enable the HSI until set the PLL configurations
			 * then we can enable and select the PLL as a system clock source
			 *
			 */

			Local_u32CRTemp = RCC_HSI_ON_MASK; //HSI ON
			RCC->CR = Local_u32CRTemp;

			Local_u32CFGRTemp |= 0x0;  //select HSI
			RCC->CFGR = Local_u32CFGRTemp;


			Local_u32CFGRTemp &= ~( 0x1111 << 18 );
			Local_u32CFGRTemp |= ( Copy_pstrRCCSettings->RCC_MultFactor << 18 );



			/*select the PLL input clock*/
			if(Copy_pstrRCCSettings->RCC_PLLInputClk == RCC_PLL_inputHSE)
			{
				SET_BIT(Local_u32CRTemp,RCC_CR_HSEON);                 //Enable HSE for PLL
				CLR_BIT(Local_u32CRTemp,RCC_CR_HSION);                 //HSI OFF

				SET_BIT(Local_u32CFGRTemp,RCC_CFGR_PLLSRC);            //select HSE for PLL
				CLR_BIT(Local_u32CFGRTemp,RCC_CFGR_PLLXTPRE );         //HSE not divided for PLL
			}
			else if(Copy_pstrRCCSettings->RCC_PLLInputClk == RCC_PLL_inputHSEDevBy2)
			{
				SET_BIT(Local_u32CRTemp,RCC_CR_HSEON);                 //Enable HSE for PLL
				CLR_BIT(Local_u32CRTemp,RCC_CR_HSION);                 //HSI OFF

				SET_BIT(Local_u32CFGRTemp,RCC_CFGR_PLLSRC);            //select HSE for PLL
				SET_BIT(Local_u32CFGRTemp,RCC_CFGR_PLLXTPRE );         //HSE divided for PLL
			}
			else if(Copy_pstrRCCSettings->RCC_PLLInputClk == RCC_PLL_inputHSIDevBy2)
			{
				CLR_BIT(Local_u32CFGRTemp,RCC_CFGR_PLLSRC);            //select HSI for PLL
				CLR_BIT(Local_u32CFGRTemp,RCC_CFGR_PLLXTPRE );         //HSE not divided for PLL
			}
			else
			{
				return Local_enuErrorState;
			}

			RCC->CFGR = Local_u32CFGRTemp;               //Set the configurations
			RCC->CR   = Local_u32CRTemp;

			SET_BIT(Local_u32CRTemp,RCC_CR_PLLON);       //PLL ON
			Local_u32CFGRTemp |= 0x2 ;                   //select PLL as system clock source

			RCC->CFGR = Local_u32CFGRTemp;               //Set the configurations
			RCC->CR   = Local_u32CRTemp;

			Local_enuErrorState = ES_OK;
		}

	}
	else
	{
		Local_enuErrorState = ES_NULL_PTR;
	}

	return Local_enuErrorState;
}


ES_t RCC_enuAHBPeriphClkCtrl(RCC_AHBPeriph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi)
{
	ES_t Local_enuErrorState =ES_NOT_OK;

	if(Copy_u8EnOrDi == ENABLE)
	{
		SET_BIT(RCC->AHBENR,Copy_enuPerphNum);
		Local_enuErrorState =ES_OK;
	}
	else if(Copy_u8EnOrDi == DISABLE)
	{
		CLR_BIT(RCC->AHBENR,Copy_enuPerphNum);
		Local_enuErrorState =ES_OK;
	}

	return Local_enuErrorState;
}


ES_t RCC_enuAPB1PeriphClkCtrl(RCC_APB1Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi)
{
	ES_t Local_enuErrorState =ES_NOT_OK;

	if(Copy_u8EnOrDi == ENABLE)
	{
		SET_BIT(RCC->APB1ENR,Copy_enuPerphNum);
		Local_enuErrorState =ES_OK;
	}
	else if(Copy_u8EnOrDi == DISABLE)
	{
		CLR_BIT(RCC->APB1ENR,Copy_enuPerphNum);
		Local_enuErrorState =ES_OK;
	}

	return Local_enuErrorState;
}


ES_t RCC_enuAPB2PeriphClkCtrl(RCC_APB2Periph_t Copy_enuPerphNum, u8 Copy_u8EnOrDi)
{
	ES_t Local_enuErrorState =ES_NOT_OK;

	if(Copy_u8EnOrDi == ENABLE)
	{
		SET_BIT(RCC->APB2ENR,Copy_enuPerphNum);
		Local_enuErrorState =ES_OK;
	}
	else if(Copy_u8EnOrDi == DISABLE)
	{
		CLR_BIT(RCC->APB2ENR,Copy_enuPerphNum);
		Local_enuErrorState =ES_OK;
	}

	return Local_enuErrorState;
}

ES_t RCC_enuGetSysClkType(RCC_SysClk_t *Copy_penuSysClk)
{
	ES_t Local_enuErrorState =ES_OK;

	if(((RCC->CFGR)&RCC_CLK_MASK)==0)
	{
		*Copy_penuSysClk=RCC_SYSCLK_HSI;
	}
	else if(((RCC->CFGR)&RCC_CLK_MASK)==1)
	{
		if((GET_BIT(RCC->CR,RCC_CR_HSEBYP))!=0)
		{
			*Copy_penuSysClk=RCC_SYSCLK_HSE_Crys;
		}
		else
		{
			*Copy_penuSysClk=RCC_SYSCLK_HSE_RC;
		}
	}
	else if(((RCC->CFGR)&RCC_CLK_MASK)==2)
	{
		*Copy_penuSysClk=RCC_SYSCLK_PLL;
	}
	else
	{
		Local_enuErrorState =ES_NOT_OK;
	}
	return Local_enuErrorState;
}

ES_t RCC_enuGetSysClkValue(u32 *Copy_pu32SysClkValue)
{
	ES_t Local_enuErrorState =ES_OK;

	if(((RCC->CFGR)&RCC_CLK_MASK)==0)
	{
		*Copy_pu32SysClkValue=8;
	}
	else if(((RCC->CFGR)&RCC_CLK_MASK)==1)
	{
		*Copy_pu32SysClkValue=RCC_HSE_FREQ;
	}
	else if(((RCC->CFGR)&RCC_CLK_MASK)==2)
	{
		if((GET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC))!=0)
		{
			if((GET_BIT(RCC->CFGR,RCC_CFGR_PLLXTPRE))!=0)
			{
				*Copy_pu32SysClkValue=RCC_HSE_FREQ/2;
			}
			else
			{
				*Copy_pu32SysClkValue=RCC_HSE_FREQ;
			}
		}
		else
		{
			*Copy_pu32SysClkValue=8/2;
		}
		u32 Local_u32PllMul=((RCC->CFGR)&(0x3C0000));
		Local_u32PllMul=(Local_u32PllMul>>18);
		switch(Local_u32PllMul) {
		    case RCC_PLL_inpClkx2:
		        *Copy_pu32SysClkValue *= 2;   // Multiply by 2
		        break;

		    case RCC_PLL_inpClkx3:
		        *Copy_pu32SysClkValue *= 3;   // Multiply by 3
		        break;

		    case RCC_PLL_inpClkx4:
		        *Copy_pu32SysClkValue *= 4;   // Multiply by 4
		        break;

		    case RCC_PLL_inpClkx5:
		        *Copy_pu32SysClkValue *= 5;   // Multiply by 5
		        break;

		    case RCC_PLL_inpClkx6:
		        *Copy_pu32SysClkValue *= 6;   // Multiply by 6
		        break;

		    case RCC_PLL_inpClkx7:
		        *Copy_pu32SysClkValue *= 7;   // Multiply by 7
		        break;

		    case RCC_PLL_inpClkx8:
		        *Copy_pu32SysClkValue *= 8;   // Multiply by 8
		        break;

		    case RCC_PLL_inpClkx9:
		        *Copy_pu32SysClkValue *= 9;   // Multiply by 9
		        break;

		    case RCC_PLL_inpClkx10:
		        *Copy_pu32SysClkValue *= 10;  // Multiply by 10
		        break;

		    case RCC_PLL_inpClkx11:
		        *Copy_pu32SysClkValue *= 11;  // Multiply by 11
		        break;

		    case RCC_PLL_inpClkx12:
		        *Copy_pu32SysClkValue *= 12;  // Multiply by 12
		        break;

		    case RCC_PLL_inpClkx13:
		        *Copy_pu32SysClkValue *= 13;  // Multiply by 13
		        break;

		    case RCC_PLL_inpClkx14:
		        *Copy_pu32SysClkValue *= 14;  // Multiply by 14
		        break;

		    case RCC_PLL_inpClkx15:
		        *Copy_pu32SysClkValue *= 15;  // Multiply by 15
		        break;

		    case RCC_PLL_inpClkx16:
		        *Copy_pu32SysClkValue *= 16;  // Multiply by 16
		        break;

		    default:
		    	Local_enuErrorState =ES_NOT_OK;
		        break;
		}

	}
	else
	{
		Local_enuErrorState =ES_NOT_OK;
	}
	return Local_enuErrorState;
}
