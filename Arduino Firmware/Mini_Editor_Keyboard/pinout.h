#pragma once

/* Выводы клавиш, светодиодов, энкодера, подключения/отключения USB */
// ПЕЧАТНАЯ ПЛАТА
/*enum MEKPins {
  USB_DISC = PB2,
  PHASE_A = PB1,
  PHASE_B = PB0,
  LED_1  = PB10,
  LED_2  = PB12,
  LED_3  = PB14,
  KEY_1  = PB4,
  KEY_2  = PB3,
  KEY_3  = PA15,
  KEY_4  = PB7,
  KEY_5  = PB6,
  KEY_6  = PB5,
  KEY_7  = PC13,
  KEY_8  = PB9,
  KEY_9  = PB8,
  KEY_10 = PA0,
  KEY_11 = PC15,
  KEY_12 = PC14,
  KEY_13 = PA3,
  KEY_14 = PA2,
  KEY_15 = PA1,
  KEY_16 = PA4,
  KEY_17 = PA5,
  KEY_18 = PA6,
  KEY_19 = PA10,
  KEY_20 = PA9,
  KEY_21 = PA8,
  KEY_22 = PB15,
  KEY_23 = PB13,
  KEY_24 = PB11,
  KEY_25 = PA7, // Кнопка внутри энкодера
};
*/
// МАКЕТ
enum BreadboardPins {
  USB_DISC = PB2,
  PHASE_A = PA1,
  PHASE_B = PA0,
  LED_1  = PA4,
  LED_2  = PA3,
  LED_3  = PA2,
  KEY_1  = PB12,
  KEY_2  = PB11,
  KEY_3  = PB10,
  KEY_4  = PB15,
  KEY_5  = PB14,
  KEY_6  = PB13,
  KEY_7  = PA8,
  KEY_8  = PA9,
  KEY_9  = PA10,
  KEY_10 = PA15,
  KEY_11 = PB3,
  KEY_12 = PC13,
  KEY_13 = PB4,
  KEY_14 = PB5,
  KEY_15 = PB7,
  KEY_16 = PB6,
  KEY_17 = PB8,
  KEY_18 = PB9,
  KEY_19 = PB0,
  KEY_20 = PB1,
  KEY_21 = PC15,
  KEY_22 = PC14,
  KEY_23 = PA6,
  KEY_24 = PA5,
  KEY_25 = PA7, // Кнопка внутри энкодера
};
