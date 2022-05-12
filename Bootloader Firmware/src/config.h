/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *****************************************************************************/

/**
 *  @file config.h
 *
 *  @brief Настройки основных параметров загрузчика.
 *
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "common.h"

/* Интервал мигания светоиода (0.5 сек). Опорная частота 8MHz */
#define BLINK_RATE 4000000L

/* ВАЖНО! Прочитайте внимательно перед внесением изменений!

* В этом документе (RM0008) описаны все имена и назначения регистров:
	http://www.st.com/web/en/resource/technical/document/reference_manual/CD00171190.pdf

* Для корректной работы загрузчика нужны два вывода микроконтроллера: 
	1. Светодиод состояния загрузчика  (GPIOA 4)
	2. Кнопка управления загрузчиком   (GPIOA 7)

* BANK указывает на группу выводов, PIN указывает на контакт в группе:
	например GPIOB 2 в среде Arduino IDE будет PB2

* Кнопки считается нажатой при наличии низкого уровня на выводе микроконтроллера.
	для кнопки обязательна внешняя подтяжка резистором (4.7 - 10 КОм) к питанию.
* Светодиод светит при низком значении на выводе микроконтроллера.

*/

/* Вывод включения USB */
#define USB_DISC_BANK	GPIOA
#define USB_DISC_PIN	12
	
/* Вывод кнопки */
#define BUTTON_BANK		GPIOA
#define BUTTON_PIN		7

/* Вывод светодиода */
#define LED_BANK		GPIOA
#define LED_PIN			4

/* Начальный адрес памяти прошивки FLASH */
#define USER_ADDR_FIRMWARE  ((u32)0x08002000)
/* Размер памяти прошивки FLASH (120832 Байт) */
#define USER_FIRMWARE_SIZE ((u32)0x1D800)

/* Начальный адрес памяти прошивки EEPROM */
#define USER_ADDR_EEPROM ((u32)0x0801F800)
/* Размер памяти прошивки EEPROM (2048 Байт) */
#define USER_EEPROM_SIZE ((u32)0x800)

/* Размер передаваемых данных в DFU (2048 Байт) */
#define TRANSFER_SIZE 0x800

/* Для изменения этих строк нужно использовать usb_description_strings_util.html */
#define USB_VENDOR_STR_LEN 0xC
#define USB_VENDOR_MSG_STR 'S',0,'-',0,'L',0,'A',0,'B',0

#define USB_PRODUCT_STR_LEN 0x2A
#define USB_PRODUCT_MSG_STR 'M',0,'i',0,'n',0,'i',0,' ',0,'E',0,'d',0,'i',0,'t',0,'o',0,'r',0,' ',0,'K',0,'e',0,'y',0,'b',0,'o',0,'a',0,'r',0,'d',0

#define USB_SERIAL_STR_LEN 0x6
#define USB_SERIAL_MSG_STR '0',0,'1',0

#define ALT0_STR_LEN 0x58
#define ALT0_MSG_STR 'M',0,'i',0,'n',0,'i',0,' ',0,'E',0,'d',0,'i',0,'t',0,'o',0,'r',0,' ',0,'K',0,'e',0,'y',0,'b',0,'o',0,'a',0,'r',0,'d',0,' ',0,'|',0,' ',0,'F',0,'L',0,'A',0,'S',0,'H',0,' ',0,' ',0,'0',0,'x',0,'8',0,'0',0,'0',0,'2',0,'0',0,'0',0,'0',0,' ',0,'R',0,'/',0,'W',0

#define ALT1_STR_LEN 0x58
#define ALT1_MSG_STR 'M',0,'i',0,'n',0,'i',0,' ',0,'E',0,'d',0,'i',0,'t',0,'o',0,'r',0,' ',0,'K',0,'e',0,'y',0,'b',0,'o',0,'a',0,'r',0,'d',0,' ',0,'|',0,' ',0,'E',0,'E',0,'P',0,'R',0,'O',0,'M',0,' ',0,'0',0,'x',0,'8',0,'0',0,'1',0,'F',0,'8',0,'0',0,'0',0,' ',0,'R',0,'/',0,'W',0

#endif
