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
 *  @file hardware.c
 *
 *  @brief init routines to setup clocks, interrupts, also destructor functions.
 *  does not include USB stuff. EEPROM read/write functions.
 *
 */
#include "common.h"
#include "hardware.h"

void gpioWriteBit(u32 bank, u8 pin, u8 val) {
    val = !val; // "set" bits are lower than "reset" bits
    SET_REG(GPIO_BSRR(bank), (1U << pin) << (16 * val));
}

bool readButtonState() {
    /* Todo, implement read */
    if (GET_REG(GPIO_IDR(BUTTON_BANK)) & (0x01 << BUTTON_PIN)) {
		return FALSE;
    }
	else {
		return TRUE;
	}
}

void strobePin(u32 bank, u8 pin, u32 rate) {
    u32 c;
	
	gpioWriteBit(bank, pin, 0);
    for (c = rate; c > 0; c --) {
        asm volatile("nop");
    }
	
    gpioWriteBit(bank, pin, 1);
    for (c = rate; c > 0; c --) {
        asm volatile("nop");
    }
}

void resetRCC(void) {
    SET_REG(RCC_CR, GET_REG(RCC_CR)     | 0x00000001);
    SET_REG(RCC_CFGR, GET_REG(RCC_CFGR) & 0xF8FF0000);
    SET_REG(RCC_CR, GET_REG(RCC_CR)     & 0xFEF6FFFF);
    SET_REG(RCC_CR, GET_REG(RCC_CR)     & 0xFFFBFFFF);
    SET_REG(RCC_CFGR, GET_REG(RCC_CFGR) & 0xFF80FFFF);
    SET_REG(RCC_CIR, 0x00000000);  // Выключение всех RCC прерываний
}

void setupCLK(void) {
    /* Включение HSE */
    SET_REG(RCC_CR, GET_REG(RCC_CR) | 0x00010001);
    while ((GET_REG(RCC_CR) & 0x00020000) == 0); // Ждем выполнения
    /* Включение буфера FLASH памяти */
    SET_REG(FLASH_ACR, 0x00000012);
    /* Основной кварц на 8 MHz */
    SET_REG(RCC_CFGR, GET_REG(RCC_CFGR) | 0x001D0400); // PLL=72Mhz(x9), APB1=36Mhz, AHB=72Mhz
    SET_REG(RCC_CR, GET_REG(RCC_CR)     | 0x01000000); // Включение PLL
    /* Установка SYSCLK как PLL */
    SET_REG(RCC_CFGR, GET_REG(RCC_CFGR) | 0x00000002);
    while ((GET_REG(RCC_CFGR) & 0x00000008) == 0); // Ждем выполнения
	/* Подключение групп выводов GPIO A B C */
    pRCC->APB2ENR |= 0b11100;
    pRCC->APB1ENR |= RCC_APB1ENR_USB_CLK;
}

void setupBTN(void) {
	/* Подтяжка резистором к питанию должна быть внешней! */
    SET_REG(GPIO_CR(BUTTON_BANK, BUTTON_PIN), (GET_REG(GPIO_CR(BUTTON_BANK, BUTTON_PIN)) & crMask(BUTTON_PIN)) | CR_INPUT << CR_SHITF(BUTTON_PIN));
}

void setupLED(void) {
    SET_REG(GPIO_CR(LED_BANK, LED_PIN), (GET_REG(GPIO_CR(LED_BANK, LED_PIN)) & crMask(LED_PIN)) | CR_OUTPUT_PP << CR_SHITF(LED_PIN));
	gpioWriteBit(LED_BANK, LED_PIN, 1); // Светодиод выключен
}

void setupFLASH() {
    /* Настройка HSI осциллятора */
    if ((pRCC->CR & 0x01) == 0x00) {
        u32 rwmVal = pRCC->CR;
        rwmVal |= 0x01;
        pRCC->CR = rwmVal;
    }
    /* Ждем выполнения */
    while ((pRCC->CR & 0x02) == 0x00) {}
}

bool checkUserCode(u32 usrAddr) {
    u32 sp = *(vu32 *) usrAddr;
	
    if ((sp & 0x2FFE0000) == 0x20000000) {
        return TRUE;
    }
	else {
        return FALSE;
    }
}

void setMspAndJump(u32 usrAddr) {
    /* Dedicated function with no call to any function (appart the last call)
       This way, there is no manipulation of the stack here, ensuring that GGC
       didn't insert any pop from the SP after having set the MSP */
    typedef void (*funcPtr)(void);
    u32 jumpAddr = *(vu32 *)(usrAddr + 0x04); // Reset ptr in vector table
    funcPtr usrMain = (funcPtr) jumpAddr;
    SET_REG(SCB_VTOR, (vu32) (usrAddr));
    asm volatile("msr msp, %0"::"g"(*(volatile u32 *)usrAddr));
    usrMain(); // Go!
}

void jumpToUserCode(u32 usrAddr) {
    /* Tear down all the dfu related setup
       Disable usb interrupts, clear them, turn off usb, set the disc pin
       todo pick exactly what we want to do here, now its just a conservative */
    flashLock();
    usbDsbISR();
    nvicDisableInterrupts();
    resetRCC(); // Без регистров ядра
    setMspAndJump(usrAddr);
}

void nvicInit(NVIC_InitTypeDef *NVIC_InitStruct) {
    u32 tmppriority = 0x00;
    u32 tmpreg      = 0x00;
    u32 tmpmask     = 0x00;
    u32 tmppre      = 0;
    u32 tmpsub      = 0x0F;
    SCB_TypeDef *rSCB = (SCB_TypeDef *) SCB_BASE;
    NVIC_TypeDef *rNVIC = (NVIC_TypeDef *) NVIC_BASE;
    /* Compute the Corresponding IRQ Priority */
    tmppriority = (0x700 - (rSCB->AIRCR & (u32)0x700)) >> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;
    tmppriority = (u32)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
    tmppriority = ((u32)tmppriority) << ((NVIC_InitStruct->NVIC_IRQChannel & (u8)0x03) * 0x08);
    tmpreg = rNVIC->IPR[(NVIC_InitStruct->NVIC_IRQChannel >> 0x02)];
    tmpmask = (u32)0xFF << ((NVIC_InitStruct->NVIC_IRQChannel & (u8)0x03) * 0x08);
    tmpreg &= ~tmpmask;
    tmppriority &= tmpmask;
    tmpreg |= tmppriority;
    rNVIC->IPR[(NVIC_InitStruct->NVIC_IRQChannel >> 0x02)] = tmpreg;
    /* Enable the Selected IRQ Channels */
    rNVIC->ISER[(NVIC_InitStruct->NVIC_IRQChannel >> 0x05)] =
        (u32)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (u8)0x1F);
}

void nvicDisableInterrupts() {
    NVIC_TypeDef *rNVIC = (NVIC_TypeDef *) NVIC_BASE;
    rNVIC->ICER[0] = 0xFFFFFFFF;
    rNVIC->ICER[1] = 0xFFFFFFFF;
    rNVIC->ICPR[0] = 0xFFFFFFFF;
    rNVIC->ICPR[1] = 0xFFFFFFFF;
    SET_REG(STK_CTRL, 0x04); // Отключение SysTick, который работает отдельно от NVIC
}

void systemHardReset(void) {
    SCB_TypeDef *rSCB = (SCB_TypeDef *) SCB_BASE;
    rSCB->AIRCR = (u32)AIRCR_RESET_REQ; // Перезагрузка
    /* Сюда попасть не должно никогда */
    while (1) {
        asm volatile("nop");
    }
}

bool flashErasePage(u32 pageAddr) {
    u32 rwmVal = GET_REG(FLASH_CR);
    rwmVal = FLASH_CR_PER;
    SET_REG(FLASH_CR, rwmVal);
    while (GET_REG(FLASH_SR) & FLASH_SR_BSY) {}
    SET_REG(FLASH_AR, pageAddr);
    SET_REG(FLASH_CR, FLASH_CR_START | FLASH_CR_PER);
    while (GET_REG(FLASH_SR) & FLASH_SR_BSY) {}
    /* Проверка что страница была очищена */
    rwmVal = 0x00;
    SET_REG(FLASH_CR, rwmVal);
	
    return TRUE;
}

bool flashWriteWord(u32 addr, u32 word) {
    vu16 *flashAddr = (vu16 *)addr;
    vu32 lhWord = (vu32)word & 0x0000FFFF;
    vu32 hhWord = ((vu32)word & 0xFFFF0000) >> 16;
    u32 rwmVal = GET_REG(FLASH_CR);
    SET_REG(FLASH_CR, FLASH_CR_PG);
    /* Apparently we need not write to FLASH_AR and can
	   simply do a native write of a half word */
    while (GET_REG(FLASH_SR) & FLASH_SR_BSY) {}
    *(flashAddr + 0x01) = (vu16)hhWord;
    while (GET_REG(FLASH_SR) & FLASH_SR_BSY) {}
    *(flashAddr) = (vu16)lhWord;
    while (GET_REG(FLASH_SR) & FLASH_SR_BSY) {}
    rwmVal &= 0xFFFFFFFE;
    SET_REG(FLASH_CR, rwmVal);
	
    /* Верификация записанных данных */
    if (*(vu32 *)addr != word) {
        return FALSE;
    }
	
    return TRUE;
}

void flashLock() {
    /* Take down the HSI oscillator? it may be in use elsewhere
	   ensure all FPEC functions disabled and lock the FPEC */
    SET_REG(FLASH_CR, 0x00000080);
}

void flashUnlock() {
    /* Разблокировка памяти */
    SET_REG(FLASH_KEYR, FLASH_KEY1);
    SET_REG(FLASH_KEYR, FLASH_KEY2);
}

/* Used to create the control register masking pattern,
   when setting control register mode */
unsigned int crMask(int pin) {
    unsigned int mask;
    if (pin >= 8) {
        pin -= 8;
    }
    mask = 0x0F << (pin << 2);
    return ~mask;
}

#define FLASH_SIZE_REG 0x1FFFF7E0
int getFlashEnd(void) {
    unsigned short *flashSize = (unsigned short *) (FLASH_SIZE_REG); // Address register
    return ((int)(*flashSize & 0xffff) * 1024) + 0x08000000;
}
