/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "xil_printf.h"
#include "xdebug.h"
#include "xil_exception.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xscugic.h"
#include "sleep.h"
#include "xil_cache.h"
#include "xil_exception.h"
#include "xil_mmu.h"
#include "xparameters_ps.h"
#include "xscugic_hw.h"
#include "xscugic.h"
#include "inttypes.h"

#define IO_WRITE32(addr, val)		*((volatile unsigned int *)(addr)) = val
#define IO_READ32(addr)				*((volatile unsigned int *)(addr))


int main()
{
    print("Hello World\n\r");
    IO_WRITE32(XPAR_DPU_EU_0_BASEADDR+0x220, 0x00000000);
    IO_WRITE32(XPAR_DPU_EU_0_BASEADDR+0x004, 0x00000000);
    usleep(10);
    IO_WRITE32(XPAR_DPU_EU_0_BASEADDR+0x004, 0xFFFFFFFF);

    IO_WRITE32(XPAR_DPU_EU_0_BASEADDR+0x20C, 0x00038280);  //inst
    IO_WRITE32(XPAR_DPU_EU_0_BASEADDR+0x224, 0x38300000);  //weight
    IO_WRITE32(XPAR_DPU_EU_0_BASEADDR+0x22C, 0x38700000);  //input and output
    usleep(10);
    IO_WRITE32(XPAR_DPU_EU_0_BASEADDR+0x220, 0x00000001);

    int message;
    while(1){
    	message = IO_READ32(XPAR_DPU_EU_0_BASEADDR+0x608);
    	printf("---interrupt=%d--",message);
    	if(message == 1) {
    		break;
    	}
    }
    Xil_DCacheFlushRange((u32)(0x38700500), 1000);
    print("----int result-------\n\r");
    int8_t result[1000];
    memcpy((void *)result, (void *)(0x38700500), 1000);
    print("\n\r----float result-------\n\r");
    int u;
    for (u = 0; u < 1000; u++) {
    	printf("%f", result[u]*(0.25));
    }
    print("Hello World----\n\r");
    return 0;
}
