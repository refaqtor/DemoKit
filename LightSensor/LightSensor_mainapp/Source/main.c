/* ==========================================================
 *    ___             _   _     _
 *   / _ \ _ __   ___| |_| |__ (_)_ __ __  __
 *  | | | | '_ \ / _ \ __| '_ \| | '_ \\ \/ /
 *  | |_| | | | |  __/ |_| | | | | | | |>  <
 *   \___/|_| |_|\___|\__|_| |_|_|_| |_/_/\_\
 *
 * Copyright Onethinx, 2018
 * All Rights Reserved
 *
 * UNPUBLISHED, LICENSED SOFTWARE.
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Onethinx BV
 *
 * ==========================================================
*/
#include "OnethinxCore01.h"
#include "DemoKit01.h"
#include "LoRaWAN_keys.h"
#include "cy_pdl.h"
#include "cycfg.h"
#include "stdio.h"

/* 
 Include this file if using CapSense: #include "cycfg_capsense.h"
 Include this file if using SMIF/QSPI: #include "cycfg_qspi_memslot.h"
 Include this file if using USB device: #include "cycfg_usbdev.h"
*/

/* Go to ../OnethinxCore/LoRaWAN_keys.h and fill in the fields of the TTN_OTAAkeys structure */
coreConfiguration_t	coreConfig = {
	.Join.KeysPtr = 		&TTN_OTAAkeys,
	.Join.DataRate =		DR_0,
	.Join.Power =			PWR_MAX,
	.Join.MAXTries = 		10,
	.TX.Confirmed = 		false,
	.TX.DataRate = 			DR_0,
	.TX.Power = 			PWR_MAX,
	.TX.FPort = 			1,
};

/*******************************************************************************
* Function Name: main()
********************************************************************************
* Summary:
*   Uses ADC and light sensor input (pin 10_3) to generate a value that gets sent with LoRaWAN.
*   Additionally, displays the value on UART using pin 10_0 and pin 10_1.
*   Please make sure that the jumpers are set correctly.
*
* Details:
*	The setup of hardware resources (UART, ADC, AREF, PINs) is done in *_config/design.modus.
*	This example gives a lot more information about the LoRaWAN connection than the "hello world" example.
*
*******************************************************************************/

/* OnethinxCore uses the following structures and variables, which should be defined globally */
coreStatus_t status;
errorStatus_t errorStatus;
char RXbuffer[64];
char TXbuffer[64];
char buffer[64];
cy_stc_scb_uart_context_t uartContext;


/* Populate uart configuration structure */
const cy_stc_scb_uart_config_t uartConfig =
{
    .uartMode                   = CY_SCB_UART_STANDARD,
    .enableMutliProcessorMode   = false,
    .smartCardRetryOnNack       = false,
    .irdaInvertRx               = false,
    .irdaEnableLowPowerReceiver = false,
    .oversample                 = 12UL,
    .enableMsbFirst             = false,
    .dataWidth                  = 8UL,
    .parity                     = CY_SCB_UART_PARITY_NONE,
    .stopBits                   = CY_SCB_UART_STOP_BITS_1,
    .enableInputFilter          = false,
    .breakWidth                 = 11UL,
    .dropOnFrameError           = false,
    .dropOnParityError          = false,
    .receiverAddress            = 0UL,
    .receiverAddressMask        = 0UL,
    .acceptAddrInFifo           = false,
    .enableCts                  = false,
    .ctsPolarity                = CY_SCB_UART_ACTIVE_LOW,
    .rtsRxFifoLevel             = 0UL,
    .rtsPolarity                = CY_SCB_UART_ACTIVE_LOW,
    .rxFifoTriggerLevel  = 0UL,
    .rxFifoIntEnableMask = 0UL,
    .txFifoTriggerLevel  = 0UL,
    .txFifoIntEnableMask = 0UL,
};

int main(void)
 {

	int32 adc_result = 0x10101010;
	uint8_t j=0;

	/* initialize hardware configuration */
	init_cycfg_all();

	/* a delay is necessary to prevent spurious joins in the debug procedure */
	CyDelay(1000);

    /* Set up internal routing, pins, and clock-to-peripheral connections */
	init_cycfg_peripherals();
	/* Turn on AREF, then initialize SAR-ADC */
	Cy_SAR_DeInit(ADC_HW, true );
	Cy_SysAnalog_Enable();
    Cy_SAR_Init(ADC_HW, &ADC_config);

	/* enable global interrupts. */
	__enable_irq();

	LED_B_SET(LED_ON);

	/* display welcome string on UART, pins 10_0 and 10_1 */
	Cy_SCB_UART_Init( UART_HW, &UART_config, &uartContext);
	Cy_SCB_UART_Enable( UART_HW );
	Cy_SCB_UART_PutString(UART_HW, "\r-------------------------------------" );
	Cy_SCB_UART_PutString(UART_HW, "\r--  Light Sensor readout example   --" );
	Cy_SCB_UART_PutString(UART_HW, "\r-------------------------------------" );

	/* initialize radio with parameters in coreConfig */
	status = LoRaWAN_Init(&coreConfig);

	/* display the LoRaWAN stack version */
	sprintf( buffer, "\r\rOnethinx LoRaWAN stack version: 0x%x", (int) status.system.version );
	Cy_SCB_UART_PutString(UART_HW, buffer );

	/* send join using parameters in coreConfig, blocks until either success or MAXtries */
	status = LoRaWAN_Join(true);

	/* check for successful join */
	if (!status.mac.isJoined){
		Cy_SCB_UART_PutString(UART_HW, "\r\rDEVICE NOT JOINED" );
		while(1) {
			LED_B_INV;
			CyDelay(1000);
		 }
	} else {
		LED_B_SET(LED_OFF);
		sprintf( buffer, "\r\rDevice joined network, device address: 0x%x", (int) status.mac.devAddr );
		Cy_SCB_UART_PutString(UART_HW, buffer );
		/*delay before first message will be sent */
		CyDelay(1000);
	}

	/* Turn on the SAR hardware. */
	Cy_SAR_Enable(ADC_HW);

	/* Set PIN_BUTTON (when configured as output, it supplies the light sensors' voltage) */
	Cy_GPIO_Pin_FastInit( PIN_BUTTON_PORT, PIN_BUTTON_PIN, CY_GPIO_DM_HIGHZ, 1UL, PIN_BUTTON_HSIOM );

	/* main loop */
	for(;;)
	{
		LED_B_SET(LED_ON);
		Cy_SCB_UART_PutString(UART_HW, "\r-------------" );

		/* Set PIN_BUTTON to strong drive, high output */
		Cy_GPIO_Pin_FastInit( PIN_BUTTON_PORT, PIN_BUTTON_PIN, CY_GPIO_DM_STRONG, 1UL, PIN_BUTTON_HSIOM );
		CyDelay( 10 );

		/* read ADC channel 0 as 32bit unsigned integer*/
		Cy_SAR_StartConvert(ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT  );
		Cy_SAR_IsEndConversion(ADC_HW, CY_SAR_WAIT_FOR_RESULT);
		adc_result = Cy_SAR_GetResult32(ADC_HW, 0);

		/* set PIN_BUTTON to high impedance state */
		Cy_GPIO_Pin_FastInit( PIN_BUTTON_PORT, PIN_BUTTON_PIN, CY_GPIO_DM_HIGHZ, 1UL, PIN_BUTTON_HSIOM );

		/* compose a message to send. the maximum value of the ADC is 32752 (7FF0), so the last 16 bytes carry all info */
        j=0;
        TXbuffer[j++] = adc_result >> 8  & 0xFF;
        TXbuffer[j++] = adc_result       & 0xFF;

        /* output to UART */
        sprintf( buffer, "\rADC_result: %d", (int)adc_result );
        Cy_SCB_UART_PutString(UART_HW, buffer );
        Cy_SCB_UART_PutString(UART_HW, "\rTXbuffer: " );
        for( int i=0; i<j; i++ ){
			sprintf( buffer, "\r  byte %d, %02x", i, (int)TXbuffer[i] );
			Cy_SCB_UART_PutString(UART_HW, buffer );
		}

        /* send with LoRaWAN */
        status = LoRaWAN_Send((uint8_t *) TXbuffer, j, true);

        /* check for errors */
        errorStatus = LoRaWAN_GetError();
        if( errorStatus.errorValue != errorStatus_NoError ){
        	/* errors encountered, list the 4 categories. See OnethinxCore01.h for the enumeration */
        	sprintf( buffer, "\rParameter error: 0x%x", (errorStatus.errorValue >> 24) && 0xFF );
        	Cy_SCB_UART_PutString(UART_HW, buffer );
        	sprintf( buffer, "\rRadio Error:     0x%x", (errorStatus.errorValue >> 12) && 0xFF );
        	Cy_SCB_UART_PutString(UART_HW, buffer );
        	sprintf( buffer, "\rMAC Error:       0x%x", (errorStatus.errorValue >> 8) && 0xFF );
        	Cy_SCB_UART_PutString(UART_HW, buffer );
        	sprintf( buffer, "\rSystem Error:    0x%x",  errorStatus.errorValue && 0xFF );
        	Cy_SCB_UART_PutString(UART_HW, buffer );
        }

        /* check for downlink messages */
    	if (status.mac.messageReceived) {
    		Cy_SCB_UART_PutString(UART_HW, "\rReceived a downlink message: " );
    		LoRaWAN_GetRXdata((uint8_t *) RXbuffer, status.mac.bytesToRead);
    		Cy_SCB_UART_PutString(UART_HW, "\rRXbuffer: " );
			for( int i=0; i<status.mac.bytesToRead; i++ ){
				sprintf( buffer, "\r  byte %d, %02x", i, (int)RXbuffer[i] );
				Cy_SCB_UART_PutString(UART_HW, buffer );
			}
    	}

		LED_B_SET(LED_OFF);

		/* wait for next */
		CyDelay( 10000 );
	}
}



/* [] END OF FILE */
