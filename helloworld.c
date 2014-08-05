/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
// Edited 10/16/13 2:48 PM
/*
 * helloworld.c: simple test application
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "mb_interface.h"

#define INT_ISR				*(volatile int*)(XPAR_XPS_INTC_0_BASEADDR)		//Interupt status
#define INT_IPR				*(volatile int*)(XPAR_XPS_INTC_0_BASEADDR+4)		//Interrupt Pending
#define INT_IER				*(volatile int*)(XPAR_XPS_INTC_0_BASEADDR+8)		//Interrupt Enable
#define INT_IAR				*(volatile int*)(XPAR_XPS_INTC_0_BASEADDR+0x0C)		//Interrupt Acknowledge
#define INT_MER				*(volatile int*)(XPAR_XPS_INTC_0_BASEADDR+0x1c)		//Master Enable
#define port2_data			*(volatile int*)(XPAR_XPS_GPIO_2_BASEADDR)
#define port2_direction		*(volatile int*)(XPAR_XPS_GPIO_2_BASEADDR+4)
#define port2_GIER			*(volatile int*)(XPAR_XPS_GPIO_2_BASEADDR+0x11c)
#define port2_IPISR			*(volatile int*)(XPAR_XPS_GPIO_2_BASEADDR+0x120)
#define port2_IPIER			*(volatile int*)(XPAR_XPS_GPIO_2_BASEADDR+0x128)


void interrupt(void) __attribute__ ((interrupt_handler));
void print(char *str);

char que[17];
char head = 0;

int main()
{
    init_platform();
	INT_IER=0x01;						//next three lines enable interrupts (I don't think order matters)
	INT_MER=0x03;
	microblaze_enable_interrupts();
	port2_direction  = 7;
	port2_IPIER = 1;
	port2_GIER=0x80000000;
	int i;
	int ii;
	char tail = 0;

//---------------------------------------------------------- Event Que

	while(1){

		if(tail!= head){
			xil_printf("%d\r\n", que[tail]);
			tail++;
			port2_IPIER = 0;
			for (i=0;i<50;i++){
				for (ii=0;ii<65000;ii++){

				}
			}
			port2_IPIER=0x1;

		}			#comment added Dr. Hummel

	}

    cleanup_platform();

    return 0;
}

void interrupt(void){
	int temp1;
	//read the IPR register
	temp1=INT_IPR;
	//make necessary changes
	que[head]=port2_data;          	//write to que
	head++;							//increment head
	port2_IPISR=port2_IPISR; //the interrupt bits are set up such that if you write a 1 to it is the only way to manually to change it
	//clear the interrupts that have been handled
	INT_IAR=temp1;
}

