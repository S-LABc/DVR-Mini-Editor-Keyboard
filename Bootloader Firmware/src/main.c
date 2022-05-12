/* *****************************************************************************
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
 * ****************************************************************************/

/**
 *  @file main.c
 *
 *  @brief 
 *  Настройка переферии микроконтроллера.
 *  Инициализация оборудования.
 *  Обработка состояния кнопки.
 *  Переход к основной прошивке.
 *
 */

#include "common.h"
#include "dfu.h"

extern volatile dfuUploadTypes_t userUploadType;

int main() {
	
    resetRCC();
    setupCLK();
    setupBTN();
	setupLED();
    setupUSB();
    setupFLASH();
	
	if (!checkUserCode(USER_ADDR_FIRMWARE) || readButtonState()) {
		while (1) {
			/* Ожидание данных по DFU. Вся работа DFU происходит отдельно.
			   Тут только мигаем светодиодом чтобы показать что мы в загрузчике */
			strobePin(LED_BANK, LED_PIN, BLINK_RATE);
        }
    }
	/* Если при старте не была нажата кнопка и есть прошивка,
	   то переходим к запуску прошивки */
	else {
		jumpToUserCode(USER_ADDR_FIRMWARE);
	}
	
    return 0; // Требование компилятора
}
