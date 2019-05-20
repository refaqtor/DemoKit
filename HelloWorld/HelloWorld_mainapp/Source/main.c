/********************************************************************************
 *    ___             _   _     _			
 *   / _ \ _ __   ___| |_| |__ (_)_ __ __  __
 *  | | | | '_ \ / _ \ __| '_ \| | '_ \\ \/ /
 *  | |_| | | | |  __/ |_| | | | | | | |>  < 
 *   \___/|_| |_|\___|\__|_| |_|_|_| |_/_/\_\
 *
 ********************************************************************************
 *
 * Copyright (c) 2019 Onethinx BV <info@onethinx.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ********************************************************************************/
#include "OnethinxCore01.h"
#include "DemoKit01.h"
#include "LoRaWAN_keys.h"
#include "cy_pdl.h"
#include "cycfg.h"
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
	.TX.Confirmed = 		true,
	.TX.DataRate = 			DR_0,
	.TX.Power = 			PWR_MAX,
	.TX.FPort = 			1,
};

/*******************************************************************************
* Function Name: main()
********************************************************************************
* Summary:
*  Sends a "Hello World" message using LoRaWAN.
*  Uses only LED to signal status to the user.
* Details:
*  Go to ../OnethinxCore/LoRaWAN_keys.h and fill in the fields of the TTN_OTAAkeys structure
*  Read the quickstart guide on how to create keys.
*******************************************************************************/

/* OnethinxCore uses the following structures and variables, which should be defined globally */
coreStatus_t status;
errorStatus_t errorStatus;
uint8_t RXbuffer[64];
uint8_t TXbuffer[64];

int main(void)
  {
	uint8_t j=0;

	/* initialize hardware configuration */
	init_cycfg_all();

	/* a delay is necessary to prevent spurious joins in the debug procedure */
	CyDelay(1000);

	/* enable global interrupts */
	__enable_irq();

	/* Blue LED ON */
	LED_B_SET(LED_ON);

	/* initialize radio with parameters in coreConfig, delay necessary for debugger to work */
	status = LoRaWAN_Init(&coreConfig);

	/* send join using parameters in coreConfig, blocks until either success or MAXtries */
	status = LoRaWAN_Join(true);

	/* check for successful join */
	if (!status.mac.isJoined){
		while(1) {
			LED_B_INV;
			CyDelay(100);
		}
	} else {
		LED_B_SET(LED_OFF);
		/*delay before first message will be sent */
		CyDelay(1000);
	}

	/* main loop */
	for(;;)
	{
		LED_B_SET(LED_ON);

		/* compose a message to send */
        j=0;
        TXbuffer[j++] = 0x48; /* H */
		TXbuffer[j++] = 0x45; /* E */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x4f; /* O */
		TXbuffer[j++] = 0x20; /*   */
		TXbuffer[j++] = 0x57; /* W */
		TXbuffer[j++] = 0x4f; /* O */
		TXbuffer[j++] = 0x52; /* R */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x44; /* D */
        status = LoRaWAN_Send((uint8_t *) TXbuffer, j, true);
        /* check for errors */
		errorStatus = LoRaWAN_GetError();
		if( errorStatus.errorValue != errorStatus_NoError ){
			/* errors encountered */
        	for(int i=0; i<10; i++){
				LED_B_INV;
				CyDelay(100);
        	}
		}

		LED_B_SET(LED_OFF);

		/* wait before sending next message */
		CyDelay( 10000 );
	}
}


/* [] END OF FILE */
