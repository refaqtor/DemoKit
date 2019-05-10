/*******************************************************************************
* File Name: cycfg_peripherals.h
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

#if !defined(CYCFG_PERIPHERALS_H)
#define CYCFG_PERIPHERALS_H

#include "cycfg_notices.h"
#include "cy_sysanalog.h"
#include "cy_sar.h"
#include "cy_sysclk.h"
#include "cy_scb_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define ADC_HW SAR
#define ADC_IRQ pass_interrupt_sar_IRQn
#define ADC_CTRL (CY_SAR_VREF_PWR_100 | CY_SAR_VREF_SEL_VDDA | CY_SAR_BYPASS_CAP_ENABLE | CY_SAR_NEG_SEL_VREF | CY_SAR_CTRL_NEGVREF_HW | CY_SAR_CTRL_COMP_DLY_12 | CY_SAR_COMP_PWR_100 | CY_SAR_DEEPSLEEP_SARMUX_OFF | CY_SAR_SARSEQ_SWITCH_ENABLE)
#define ADC_SAMPLE (SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk | CY_SAR_RIGHT_ALIGN | CY_SAR_DIFFERENTIAL_SIGNED | CY_SAR_SINGLE_ENDED_UNSIGNED | CY_SAR_AVG_CNT_256 | CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM | CY_SAR_TRIGGER_MODE_FW_ONLY)
#define ADC_CH0_CONFIG (CY_SAR_POS_PORT_ADDR_SARMUX | CY_SAR_CHAN_POS_PIN_ADDR_3 | CY_SAR_CHAN_SINGLE_ENDED | CY_SAR_CHAN_AVG_ENABLE | CY_SAR_CHAN_SAMPLE_TIME_0)
#define ADC_MUX_SWITCH (0u | CY_SAR_MUX_FW_P3_VPLUS)
#define ADC_MUX_SWITCH_HW_CTRL (0u | CY_SAR_MUX_SQ_CTRL_P3)
#define ADC_VREF_MV 3300UL
#define UART_HW SCB1
#define UART_IRQ scb_1_interrupt_IRQn

extern const cy_stc_sysanalog_config_t pass_0_aref_0_config;
extern const cy_stc_sar_config_t ADC_config;
extern const cy_stc_scb_uart_config_t UART_config;

void init_cycfg_peripherals(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PERIPHERALS_H */
