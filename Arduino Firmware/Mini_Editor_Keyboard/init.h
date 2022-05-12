#pragma once

/* Для отслеживания проблем USB */
bool connection_lost = false;
/* Для использования с millis() */
uint32_t last_time = 0;
/* Загруженные номера инструментов */
uint16_t tool_number[KEYS_COUNT];
/* Номера инструментов при чистом запуске */
uint16_t default_tools[KEYS_COUNT] = {
  TOOL_UNDO,
  TOOL_SNAPPING,
  TOOL_CINEMA_VIEWER,
  TOOL_INSERT,
  TOOL_APPEND_TO_END_OF_TIMELINE,
  TOOL_RIPPLE_OVERWRITE,
  TOOL_FIT_TO_FILL,
  TOOL_PLACE_ON_TOP,
  TOOL_REPLACE,
  TOOL_MARK_IN,
  TOOL_ADD_MARKER,
  TOOL_MARK_OUT,
  TOOL_RESIZE_IN,
  TOOL_RESIZE_OUT,
  TOOL_ROLL,
  TOOL_MOVE,
  TOOL_SLIDE,
  TOOL_SLIP,
  TOOL_SOURCE_TIMELINE_VIEWER,
  TOOL_PROJECT_SETTINGS,
  TOOL_SOURCE_CLIP_TAPE,
  TOOL_WHEEL_SHUTTLE,
  TOOL_WHEEL_JOG,
  TOOL_WHEEL_SCROLL,
  TOOL_PAUSE_START_PLAYBACK
};
/* Номера цветов колпачков клавиш при чистом запуске */
uint16_t default_colors[KEYS_COUNT] = {
  COLOR_RED,
  COLOR_RED,
  COLOR_RED,
  COLOR_BLACK,
  COLOR_BLACK,
  COLOR_BLACK,
  COLOR_BLACK,
  COLOR_BLACK,
  COLOR_BLACK,
  COLOR_WHITE,
  COLOR_WHITE,
  COLOR_WHITE,
  COLOR_GREEN,
  COLOR_GREEN,
  COLOR_GREEN,
  COLOR_GREEN,
  COLOR_GREEN,
  COLOR_GREEN,
  COLOR_WHITE,
  COLOR_WHITE,
  COLOR_WHITE,
  COLOR_BLUE,
  COLOR_BLUE,
  COLOR_BLUE,
  COLOR_SILVER
};
/* Для алгоритмов колеса */
struct Knob {
  int8_t playback_speed          = NEUTRAL;
  uint8_t selected_mode          = 0;
  uint8_t previous_selected_mode = 0;
} knob;
/* Для энкодера */
struct RotaryEncoder {
  volatile byte state = 0x00;
  volatile byte previous_state = 0x00;
  volatile bool reset = false;
  volatile bool flag = false;
  volatile bool turn_left = false;
  volatile bool turn_right = false;
} encoder;
/* Объект HID, Keyboard */
USBHID HID;
HIDKeyboard Keyboard(HID);
/* Объекты клавиш */
Switch Key1(KEY_1);
Switch Key2(KEY_2);
Switch Key3(KEY_3);
Switch Key4(KEY_4);
Switch Key5(KEY_5);
Switch Key6(KEY_6);
Switch Key7(KEY_7);
Switch Key8(KEY_8);
Switch Key9(KEY_9);
Switch Key10(KEY_10);
Switch Key11(KEY_11);
Switch Key12(KEY_12);
Switch Key13(KEY_13);
Switch Key14(KEY_14);
Switch Key15(KEY_15);
Switch Key16(KEY_16);
Switch Key17(KEY_17);
Switch Key18(KEY_18);
Switch Key19(KEY_19);
Switch Key20(KEY_20);
Switch Key21(KEY_21);
Switch Key22(KEY_22);
Switch Key23(KEY_23);
Switch Key24(KEY_24);
Switch Key25(KEY_25); // Кнопка внутри энкодера
