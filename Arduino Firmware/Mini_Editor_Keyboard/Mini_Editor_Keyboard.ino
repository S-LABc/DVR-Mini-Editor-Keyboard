/**
 * Mini Editor Keyboard
 * 
 * ########## В А Ж Н О ##########
 * 
 ** Ядро для поддержки плат STM32 от rogerclarkmelbourne https://github.com/rogerclarkmelbourne/Arduino_STM32
 ** Для его работы нужно:
 *** Установить "Arduino SAM boards (Cortex-M3)" через менеджер плат
 *** Скопировать содержимое скаченного архива в папку "hardware" по пути C:\Users\[Имя пользователя]\Documents\Arduino
 *** Если папки "hardware" нет, ее нужно создать самостоятельно
 ** Для прошивки из среды Arduino IDE добавить в файл C:\Users\[Имя пользователя]\Documents\Arduino\hardware\Arduino_STM32\STM32F1\boards.txt
 ** Содержимое файла "Add Arduino boards.txt" из папки Support
 * 
 * Настройки платы: (БЕЗ DFU ЗАГРУЗЧИКА)
 * Board            Mini Editor Keyboard (ST-Link)
 * Используется для проверки, не поддерживается программой для назначения инструментов
 * 
 * Настройки платы: (С DFU ЗАГРУЗЧИКОМ)
 * Board            Mini Editor Keyboard (DFU)
 * Финальный вариант, поддерживается программой для назначения инструментов
 * Зажать Ctrl+Alt+S, перейти в папку со скетчем, там будет готовы бинарный файл прошивки
 * 
 ** В скетче используются встроенные в ядро билиотеки: EEPROM.h, USBComposite.h, libmaple/iwdg.h
 * 
 ** Связь со мной:
 ** YouTube https://www.youtube.com/channel/UCbkE52YKRphgkvQtdwzQbZQ
 ** Telegram https://www.t.me/slabyt
 ** Telegram Channel https://www.t.me/t_slab
 ** GitHub https://github.com/S-LABc
 * 
 ** ARDUINO v1.8.19
 ** Copyright (C) 2022. v1.1 / Скляр Роман S-LAB
*/

#include "MiniEditorKeyboard.h"

void setup() {
  iwdg_init(IWDG_PRE_256, 1250); // Настройка строжевого таймера (~8 секунд)
  enableDebugPorts(); // Отключает JTAG, иначе не работает PB3
  settingWheel();
  settingLED();
  settingUSB();
  settingTools();
}

void loop() {
  mainMEK();
}
