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
   
 * InterfaceDataTypes.h
 * Created on: 24 февр. 2023 г.
 ********************************************************************************/

#ifndef INTERFACEDATATYPES_H_
#define INTERFACEDATATYPES_H_


/*	состояние порта как аппаратного модуля МК
*	используется для определения, можно ли работать на низком уровне
*	при многочисленных ошибках или таймауте порт считается неисправным
*/
typedef enum Port_Status {//состояние порта используется внутри функций
	PORT_FREE,		//свободно можно работать
	PORT_BUSY,		//занято
	PORT_DONE,    //операция завершена успешно
	PORT_ERROR,		//возникли ошибки, повторить последний запрос
	PORT_TIMEOUT,	//таймаут, устройство не отвечает
	PORT_WTF		//произошла НЕХОРОШАЯ МАГИЯ, полный перезапуск с нуля
} Port_Status_t;

/* состояние процесса обмена данными с устройством как с отдельным элементом сети
 * 	применяется для отображения состояния процесса работы с устройством для главного кода
 */
typedef enum Device_status {//состояние устройства на шине
	INIT,			//устройство не настроено
	OK,				//устройство настроено опрос выполняется без ошибок
	BadValue,	//опрос данных завершился с ошибкой
	FAULTH		//ошибки при опросе устройства, потеря связи и тд
} Device_status_t;


#endif /* INTERFACEDATATYPES_H_ */
