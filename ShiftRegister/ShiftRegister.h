/*********************************************************************************
	Original author: alexm

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
 * ShiftRegister.h
 * Created on: Mar 17, 2023
 ********************************************************************************/

#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

#include "main.h"
#include "InterfaceDataTypes.h"

typedef struct ShiftIn {
	SPI_TypeDef *SPIbus;	        	//pointer to HW SPI port
	Port_Status_t status;						//status port
	GPIO_TypeDef *inputPort;				//GPIO port for input latch
	uint32_t inputPin;							//GPIO pin for input latch
	uint8_t *data;		          		//pointer buffer
	uint8_t ind;										//data index
	volatile uint8_t len;			  		//length data
} ShiftIn_t;

typedef struct ShiftOut {
	SPI_TypeDef *SPIbus;	        	//pointer to HW SPI port
	Port_Status_t status;						//status port
	GPIO_TypeDef *outputPort;				//GPIO port for input latch
	uint32_t outputPin;							//GPIO pin for input latch
	uint8_t *data;		          		//pointer buffer
	uint8_t ind;										//data index
	volatile uint8_t len;			  		//length data
} ShiftOut_t;

void ShiftIn_Start(ShiftIn_t *_shift);

void ShiftIn_IRQ_RO_CallBack(ShiftIn_t *_shift);

void ShiftOut_Start(ShiftOut_t *_shift);

void ShiftOut_IRQ_TO_CallBack(ShiftOut_t *_shift);

#endif /* SHIFTREGISTER_H_ */
