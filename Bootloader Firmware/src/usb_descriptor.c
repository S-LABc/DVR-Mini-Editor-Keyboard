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
 *  @file usb_descriptor.c
 *
 *  @brief aka application descriptor; big static struct and callbacks for sending
 *  the descriptor.
 *
 */

#include "usb_descriptor.h"

u8 u8_usbDeviceDescriptorDFU[DFU_DEVICE_DESC_LEN] = {
    DFU_DEVICE_DESC_LEN, // bLength: 18 байт
    0x01, // bDescriptorType
    0x00, // bcdUSB: Версия USB (1.00)
    0x01,
    0x00, // bDeviceClass
    0x00, // bDeviceSubClass
    0x00, // bDeviceProtocol
    0x40, // bMaxPacketSize0: 64 байта
    VEND_ID0, // idVendor
    VEND_ID1,
    PROD_ID0, // idProduct
    PROD_ID1,
    0x01, // bcdDevice
    0x02,
    0x01, // iManufacturer: Индекс строки Производителя
    0x02, // iProduct: Индекс строки названия Продукта
    0x03, // iSerialNumber: Индекс строки Серийного Номера
    0x01  // bNumConfigurations
};
ONE_DESCRIPTOR usbDeviceDescriptorDFU = {
    u8_usbDeviceDescriptorDFU,
    DFU_DEVICE_DESC_LEN
};

/*** Функциональный дескриптор DFU ***/
u8 u8_usbFunctionalDescriptor[USB_FUNC_DESC_LEN] = {
    USB_FUNC_DESC_LEN, // blength: 9 байт
    0x21, // Функциональный дескриптор DFU
    0x03, // bmAttributes, bitCanDnload | bitCanUpload
    0xFF, // DetachTimeOut: 255 мс
    0x00,
    (TRANSFER_SIZE & 0x00FF),
    (TRANSFER_SIZE & 0xFF00) >> 8, // TransferSize
    0x10, // bcdDFUVersion: Версия DFU (1.1)
    0x01
};
ONE_DESCRIPTOR usbFunctionalDescriptor = {
    u8_usbFunctionalDescriptor,
    USB_FUNC_DESC_LEN
};

u8 u8_usbConfigDescriptorDFU[DFU_CONFIG_DESC_LEN] = {
    0x09, // bLength: Размер дескриптора конфигурации (9)
    0x02, // bDescriptorType: Тип дескриптора
    DFU_CONFIG_DESC_LEN, // wTotalLength: Полная длинна дескриптора (36)
    0x00,
    0x01, // bNumInterfaces: Кол-во интерфейсов (1)
    0x01, // bConfigurationValue
    0x00, // iConfiguration
    0x80, // bmAttributes
    0x32, // MaxPower: 100 мА

    /*** Дескриптор DFU. intf = 0 Alt = 0 ***/
    0x09, // bLength: Размер дескриптора интерфейса (9)
    0x04, // bDescriptorType
    0x00, // bInterfaceNumber: Номер интерфейса (0)
    0x00, // bAlternateSetting: Номер канала Alternate (0)
    0x00, // bNumEndpoints
    0xFE, // bInterfaceClass: Класс DFU
    0x01, // bInterfaceSubClass
    0x02, // nInterfaceProtocol: 0x02 пока в dfu_mode
    0x04, // iInterface

    /*** Дескриптор DFU. intf = 0 Alt = 1 ***/
    0x09, // bLength: Размер дескриптора интерфейса (9)
    0x04, // bDescriptorType
    0x00, // bInterfaceNumber: Номер интерфейса (0)
    0x01, // bAlternateSetting: Номер канала Alternate (1)
    0x00, // bNumEndpoints
    0xFE, // bInterfaceClass: Класс DFU
    0x01, // bInterfaceSubClass
    0x02, // nInterfaceProtocol: 0x02 пока в dfu_mode
    0x05, // iInterface

    /*** Функциональный дескриптор DFU ***/
    USB_FUNC_DESC_LEN, // bLength: 9 байт
    0x21, // Функциональный дескриптор DFU
    0x03, // bmAttributes, bitCanDnload | bitCanUpload
    0xFF, // DetachTimeOut: 255 мс
    0x00,
    (TRANSFER_SIZE & 0x00FF),
    (TRANSFER_SIZE & 0xFF00) >> 8, // TransferSize
    0x10, // bcdDFUVersion: Версия DFU (1.1)
    0x01
};

ONE_DESCRIPTOR usbConfigDescriptorDFU = {
    u8_usbConfigDescriptorDFU,
    DFU_CONFIG_DESC_LEN
};

u8 u8_usbStringLangId[USB_STR_LANG_ID_LEN] = {
    USB_STR_LANG_ID_LEN,
    0x03,
    0x09,
    0x04 // LangID: U.S. English (0x0409)
};

u8 u8_usbStringVendor[USB_VENDOR_STR_LEN] = {
    USB_VENDOR_STR_LEN,
    0x03,
	USB_VENDOR_MSG_STR
};

u8 u8_usbStringProduct[USB_PRODUCT_STR_LEN] = {
    USB_PRODUCT_STR_LEN,
    0x03,
	USB_PRODUCT_MSG_STR
};

u8 u8_usbStringSerial[USB_SERIAL_STR_LEN] = {
    USB_SERIAL_STR_LEN,
    0x03,
    USB_SERIAL_MSG_STR
};

u8 u8_usbStringAlt0[ALT0_STR_LEN] = {
    ALT0_STR_LEN,
    0x03,
    ALT0_MSG_STR
};

u8 u8_usbStringAlt1[ALT1_STR_LEN] = {
    ALT1_STR_LEN,
    0x03,
    ALT1_MSG_STR
};

u8 u8_usbStringInterface = NULL;

ONE_DESCRIPTOR usbStringDescriptor[STR_DESC_LEN] = {
    { (u8 *)u8_usbStringLangId,  USB_STR_LANG_ID_LEN },
    { (u8 *)u8_usbStringVendor,  USB_VENDOR_STR_LEN },
    { (u8 *)u8_usbStringProduct, USB_PRODUCT_STR_LEN },
    { (u8 *)u8_usbStringSerial,  USB_SERIAL_STR_LEN },
	{ (u8 *)u8_usbStringAlt0,    ALT0_STR_LEN },
    { (u8 *)u8_usbStringAlt1,    ALT1_STR_LEN }
};