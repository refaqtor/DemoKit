/*******************************************************************************
* File Name: cycfg_peripherals.c
*
* Description:
* Peripheral Hardware Block configuration
* This file was automatically generated and should not be modified.
* 
********************************************************************************
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
********************************************************************************/

#include "cycfg_peripherals.h"

const cy_stc_sysanalog_config_t pass_0_aref_0_config = 
{
	.startup = CY_SYSANALOG_STARTUP_FAST,
	.iztat = CY_SYSANALOG_IZTAT_SOURCE_LOCAL,
	.vref = CY_SYSANALOG_VREF_SOURCE_LOCAL_1_2V,
	.deepSleep = CY_SYSANALOG_DEEPSLEEP_DISABLE,
};
const cy_stc_sar_config_t ADC_config = 
{
	.ctrl = (uint32_t) ADC_CTRL,
	.sampleCtrl = (uint32_t) ADC_SAMPLE,
	.sampleTime01 = (4UL << CY_SAR_SAMPLE_TIME0_SHIFT) | (2UL << CY_SAR_SAMPLE_TIME1_SHIFT),
	.sampleTime23 = (2UL << CY_SAR_SAMPLE_TIME2_SHIFT) | (2UL << CY_SAR_SAMPLE_TIME3_SHIFT),
	.rangeThres = (0UL << CY_SAR_RANGE_HIGH_SHIFT) | (0UL << CY_SAR_RANGE_LOW_SHIFT),
	.rangeCond = CY_SAR_RANGE_COND_BELOW,
	.chanEn = 1UL,
	.chanConfig = {(uint32_t) ADC_CH0_CONFIG, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL},
	.intrMask = (uint32_t) CY_SAR_INTR_EOS_MASK,
	.satIntrMask = 0UL,
	.rangeIntrMask = 0UL,
	.muxSwitch = ADC_MUX_SWITCH,
	.muxSwitchSqCtrl = ADC_MUX_SWITCH_HW_CTRL,
	.configRouting = true,
	.vrefMvValue = ADC_VREF_MV,
};
const cy_stc_scb_uart_config_t UART_config = 
{
	.uartMode = CY_SCB_UART_STANDARD,
	.enableMutliProcessorMode = false,
	.smartCardRetryOnNack = false,
	.irdaInvertRx = false,
	.irdaEnableLowPowerReceiver = false,
	.oversample = 8,
	.enableMsbFirst = false,
	.dataWidth = 8UL,
	.parity = CY_SCB_UART_PARITY_NONE,
	.stopBits = CY_SCB_UART_STOP_BITS_1,
	.enableInputFilter = false,
	.breakWidth = 11UL,
	.dropOnFrameError = false,
	.dropOnParityError = false,
	.receiverAddress = 0x0UL,
	.receiverAddressMask = 0x0UL,
	.acceptAddrInFifo = false,
	.enableCts = false,
	.ctsPolarity = CY_SCB_UART_ACTIVE_LOW,
	.rtsRxFifoLevel = 0UL,
	.rtsPolarity = CY_SCB_UART_ACTIVE_LOW,
	.rxFifoTriggerLevel = 63UL,
	.rxFifoIntEnableMask = 0UL,
	.txFifoTriggerLevel = 63UL,
	.txFifoIntEnableMask = 0UL,
};


void init_cycfg_peripherals(void)
{
	Cy_SysClk_PeriphAssignDivider(PCLK_PASS_CLOCK_SAR, CY_SYSCLK_DIV_8_BIT, 1U);

	Cy_SysClk_PeriphAssignDivider(PCLK_SCB1_CLOCK, CY_SYSCLK_DIV_8_BIT, 2U);
}
