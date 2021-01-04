# Xilinx_DPU_Baremetal
The baremetal application for Xilinx DPU. 

## Prerequisites
* Ultra96 V2 platform
* PYNQ 2.4
* Vivado 2018.2
* DPU version: dpu_eu_v3_2_0 (ip folder)

## DPU register 
According to the DPU specification and the analysis of the DPU driver, I found several important registers related to the operation of the DPU. 
| Function | Offset Address | Active Value | IDLE Value |
| :-----:  | :----:  | :----: | :----: |
| Start DPU | 0x220  | 0x0000_0001  | 0x0000_0000 |
| Instruction address on DRAM | 0x20C | -- | -- |
| Weight/Bias address on DRAM | 0x224 | -- | -- |
| Input data  address on DRAM | 0x22C | -- | -- |
| Interrupt (Finish signal)   | 0x608 | 0x0000_0001 | 0x0000_0000 |

## Hack DPU step
In this case, I will leverage the mobilenetv2 model as example to show how to obtain the input data, instruction, weight/bias parameters of mobilenetV2 model and deploy it in baremental application.
1. First, you need the Ultra96 V2 platform with PYNQ 2.4 image that support DPU-PYNQ, more details about this configuration can be found in this [link](https://github.com/Xilinx/DPU-PYNQ)

1. Read the input to binary file in PYNQ on Ultra96 V2 platform

1. Read the instruction to binary file in PYNQ on Ultra96 V2 platform

1. Read the Weight/Bias to binary file in PYNQ on Ultra96 V2 platform

1. Write the instruction binary file to DRAM via Xilinx SDK 2018.2

1. Write the weight/bias binary file to DRAM via Xilinx SDK 2018.2

1. Write the register of DPU

1. Read the interrupt register of DPU to check whether the task is completed
