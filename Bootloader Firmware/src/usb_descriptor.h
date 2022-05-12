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

#ifndef __USB_DESC_H
#define __USB_DESC_H

#include "common.h"
#include "usb_lib.h"
#include "usb.h"

/* Количество каналов Alternate */
#define NUM_ALT_SETTINGS 2

/* Размер в байтах дескриптора устройства DFU */
#define DFU_DEVICE_DESC_LEN 0x12
/* Размер в байтах функционального дескриптора */
#define USB_FUNC_DESC_LEN 0x09
/* Размер в байтах идентификатора языка */
#define USB_STR_LANG_ID_LEN 0x04
/* Размер в байтах дескриптора конфигурации DFU */
#define DFU_CONFIG_DESC_LEN 0x24
/* Размер в байтах строкового дескриптора */
#define STR_DESC_LEN 0x06

/* Страший и младший байты для VID и PID */
#define VEND_ID0 0xAF
#define VEND_ID1 0x1E
#define PROD_ID0 0x03
#define PROD_ID1 0x00

extern ONE_DESCRIPTOR  usbDeviceDescriptorDFU;
extern ONE_DESCRIPTOR  usbConfigDescriptorDFU;
extern ONE_DESCRIPTOR  usbStringDescriptor[STR_DESC_LEN];
extern ONE_DESCRIPTOR  usbFunctionalDescriptor;

#endif
