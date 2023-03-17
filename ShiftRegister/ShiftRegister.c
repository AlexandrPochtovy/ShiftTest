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
   
 * ShiftRegister.c
 * Created on: Mar 17, 2023
 ********************************************************************************/

#include "ShiftRegister.h"



__STATIC_INLINE void ShiftIn_InputStore(ShiftIn_t *shift) {
	LL_GPIO_ResetOutputPin(shift->inputPort, shift->inputPin);
}

__STATIC_INLINE void ShiftIn_InputFree(ShiftIn_t *shift) {
	LL_GPIO_SetOutputPin(shift->inputPort, shift->inputPin);
}

__STATIC_INLINE void ShiftOut_OutputDisable(ShiftOut_t *shift) {
	LL_GPIO_ResetOutputPin(shift->outputPort, shift->outputPin);
}

__STATIC_INLINE void ShiftOut_OutputEnable(ShiftOut_t *shift) {
	LL_GPIO_SetOutputPin(shift->outputPort, shift->outputPin);
}


void ShiftIn_Start(ShiftIn_t *_shift) {
	ShiftIn_InputStore(_shift);
	_shift->status = PORT_BUSY;
	_shift->ind = 0;
	_shift->SPIbus->CR2 |= SPI_CR2_RXNEIE;
	ShiftIn_InputFree(_shift);
	LL_SPI_Enable(_shift->SPIbus); //enable SPI
}

void ShiftIn_IRQ_RO_CallBack(ShiftIn_t *_shift) {
	volatile uint16_t SPI_SR = _shift->SPIbus->SR;
	if (SPI_SR & SPI_SR_RXNE) {
		if (_shift->len > 1) {
			_shift->data[_shift->ind++] = (uint8_t)_shift->SPIbus->DR;
			--_shift->len;
			if (_shift->len == 1) {
				LL_SPI_Disable(_shift->SPIbus);
			}
		}
		else {
			//_shift->SPIbus->CR2 &= ~SPI_CR2_RXNEIE; //interrupt off
			_shift->data[_shift->ind] = (uint8_t)_shift->SPIbus->DR;
			//LL_SPI_Disable(_shift->SPIbus);
			_shift->status = PORT_DONE;
		}
	}
}

void ShiftOut_Start(ShiftOut_t *_shift) {
	//ShiftOut_OutputEnable(_shift);
	_shift->status = PORT_BUSY;
	_shift->ind = 0;
	_shift->SPIbus->CR2 |= SPI_CR2_TXEIE;
	LL_SPI_Enable(_shift->SPIbus); //enable SPI
}

void ShiftOut_IRQ_TO_CallBack(ShiftOut_t *_shift) {
	volatile uint16_t SPI_SR = _shift->SPIbus->SR;
	if (SPI_SR & SPI_SR_TXE) {
 		if (_shift->len > 0) {
 			_shift->SPIbus->DR = _shift->data[_shift->ind++];
			--_shift->len;
		}
		else {
			_shift->SPIbus->CR2 &= ~SPI_CR2_TXEIE;
			LL_SPI_Disable(_shift->SPIbus);
			_shift->status = PORT_DONE;
		}
	}
}

