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

#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "stm32f10x_type.h"
#include "cortexm3_macro.h"
#include "common.h"

/* Макросы регистров и переферии */
#define RCC   ((u32)0x40021000)
#define FLASH ((u32)0x40022000)
#define GPIOA ((u32)0x40010800)
#define GPIOB ((u32)0x40010C00)

#define RCC_CR      RCC
#define RCC_CFGR    (RCC + 0x04)
#define RCC_CIR     (RCC + 0x08)

#define FLASH_ACR     (FLASH + 0x00)
#define FLASH_KEYR    (FLASH + 0x04)
#define FLASH_SR      (FLASH + 0x0C)
#define FLASH_CR      (FLASH + 0x10)
#define FLASH_AR      (FLASH + 0x14)

#define FLASH_KEY1     0x45670123
#define FLASH_KEY2     0xCDEF89AB
#define FLASH_SR_BSY   0x01
#define FLASH_CR_PER   0x02
#define FLASH_CR_PG    0x01
#define FLASH_CR_START 0x40

#define GPIO_IDR(port)  (port+0x08)
#define GPIO_BSRR(port) (port+0x10)
#define GPIO_CR(port,pin) (port + (0x04*(pin>7)))

#define CR_OUTPUT_PP        0x01
#define CR_INPUT            0x04

#define SCS_BASE   ((u32)0xE000E000)
#define NVIC_BASE  (SCS_BASE + 0x0100)
#define SCB_BASE   (SCS_BASE + 0x0D00)

#define SCS      0xE000E000
#define NVIC     (SCS+0x100)
#define SCB      (SCS+0xD00)
#define STK      (SCS+0x10)

#define SCB_VTOR (SCB+0x08)
#define STK_CTRL (STK+0x00)

/* Тактирование USB */
#define RCC_APB1ENR_USB_CLK   0x00800000

/* Тактирование регистров резервного копирования */
#define RCC_APB1ENR_PWR_CLK   0x10000000
#define RCC_APB1ENR_BKP_CLK   0x08000000

#define USB_LP_IRQ  ((u8)0x14)

/* AIRCR  */
#define AIRCR_RESET         0x05FA0000
#define AIRCR_RESET_REQ     (AIRCR_RESET | (u32)0x04);

/* More bit twiddling to set Control register bits */
#define CR_SHITF(pin) ((pin - 8*(pin>7))<<2)

#define SET_REG(addr,val) do { *(vu32*)(addr)=val; } while(0)
#define GET_REG(addr)     (*(vu32*)(addr))

/* todo: there must be some major misunderstanding in how we access
   regs. The direct access approach (GET_REG) causes the usb init to
   fail upon trying to activate RCC_APB1 |= 0x00800000. However, using
   the struct approach from ST, it works fine...temporarily switching
   to that approach */
typedef struct {
    vu32 CR;
    vu32 CFGR;
    vu32 CIR;
    vu32 APB2RSTR;
    vu32 APB1RSTR;
    vu32 AHBENR;
    vu32 APB2ENR;
    vu32 APB1ENR;
    vu32 BDCR;
    vu32 CSR;
} RCC_RegStruct;
#define pRCC ((RCC_RegStruct *) RCC)

typedef struct {
    vu32 ISER[2];
    u32  RESERVED0[30];
    vu32 ICER[2];
    u32  RSERVED1[30];
    vu32 ISPR[2];
    u32  RESERVED2[30];
    vu32 ICPR[2];
    u32  RESERVED3[30];
    vu32 IABR[2];
    u32  RESERVED4[62];
    vu32 IPR[15];
} NVIC_TypeDef;

typedef struct {
    u8 NVIC_IRQChannel;
    u8 NVIC_IRQChannelPreemptionPriority;
    u8 NVIC_IRQChannelSubPriority;
    bool NVIC_IRQChannelCmd; // Для включания должно быть TRUE
} NVIC_InitTypeDef;

typedef struct {
    vuc32 CPUID;
    vu32 ICSR;
    vu32 VTOR;
    vu32 AIRCR;
    vu32 SCR;
    vu32 CCR;
    vu32 SHPR[3];
    vu32 SHCSR;
    vu32 CFSR;
    vu32 HFSR;
    vu32 DFSR;
    vu32 MMFAR;
    vu32 BFAR;
    vu32 AFSR;
} SCB_TypeDef;

void gpioWriteBit(u32 bank, u8 pin, u8 val);
unsigned int crMask(int pin);

bool readButtonState();
void strobePin(u32 bank, u8 pin, u32 rate);

void systemHardReset(void);
void resetRCC(void);
void setupCLK(void);
void setupBTN(void);
void setupLED(void);
void setupFLASH(void);
bool checkUserCode(u32 usrAddr);
void jumpToUserCode(u32 usrAddr);

bool flashWriteWord(u32 addr, u32 word);
bool flashErasePage(u32 addr);
void flashLock(void);
void flashUnlock(void);
void nvicInit(NVIC_InitTypeDef *);
void nvicDisableInterrupts(void);

int getFlashEnd(void);
int getFlashPageSize(void);

#endif
