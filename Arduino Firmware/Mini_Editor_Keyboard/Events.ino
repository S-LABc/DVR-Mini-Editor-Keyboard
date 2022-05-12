/* Выполнение действия при повороте колеса */
void wheelEvents (void) {
  if (encoder.flag) {
    if (encoder.turn_left) {
      wheelAction(LEFT);
      encoder.turn_left = !encoder.turn_left;
    }
    else if (encoder.turn_right) {
      wheelAction(RIGHT);
      encoder.turn_right = !encoder.turn_right;
    }
    encoder.flag = !encoder.flag;
  }
}
/** 
 * Каждая клавиша имеет два события - isPress и isRelease.
 * Событие release позволяет отключить подрежимы из knobSubMode().
 * Событиям press: назначается инструмент по номеру из tool_number.
 */
void keyEvents (void) {
/***************** KEY_1 PB4(PB12) *****************/
  if (Key1.press()) {
    toolSelection(tool_number[0]);
  }
  if (Key1.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_2 PB3(PB11) *****************/
  if (Key2.press()) {
    toolSelection(tool_number[1]);
  }
  if (Key2.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_3 PA15(PB10) ****************/
  if (Key3.press()) {
    toolSelection(tool_number[2]);
  }
  if (Key3.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_4 PB7(PB15) *****************/
  if (Key4.press()) {
    toolSelection(tool_number[3]);
  }
  if (Key4.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_5 PB6(PB14) *****************/
  if (Key5.press()) { 
    toolSelection(tool_number[4]);
  }
  if (Key5.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_6 PB5(PB13) *****************/
  if (Key6.press()) {
    toolSelection(tool_number[5]);
  }
  if (Key6.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_7 PC13(PA8) *****************/
  if (Key7.press()) {
    toolSelection(tool_number[6]);
  }
  if (Key7.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_8 PB9(PA9) *****************/
  if (Key8.press()) {
    toolSelection(tool_number[7]);
  }
  if (Key8.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_9 PB8(PA10) *****************/
  if (Key9.press()) {
    toolSelection(tool_number[8]);
  }
  if (Key9.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_10 PA0(PA15) ****************/
  if (Key10.press()) {
    toolSelection(tool_number[9]);
  }
  if (Key10.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_11 PC15(PB3) ****************/
  if (Key11.press()) {
    toolSelection(tool_number[10]);
  }
  if (Key11.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/**************** KEY_12 PC14(PC13) ****************/
  if (Key12.press()) {
    toolSelection(tool_number[11]);
  }
  if (Key12.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_13 PA3(PB4) *****************/
  if (Key13.press()) {
    toolSelection(tool_number[12]);
  }
  if (Key13.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_14 PA2(PB5) *****************/
  if (Key14.press()) {
    toolSelection(tool_number[13]);
  }
  if (Key14.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_15 PA1(PB7) *****************/
  if (Key15.press()) {
    toolSelection(tool_number[14]);
  }
  if (Key15.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_16 PA4(PB6 )*****************/
  if (Key16.press()) {
    toolSelection(tool_number[15]);
  }
  if (Key16.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_17 PA5(PB8) *****************/
  if (Key17.press()) {
    toolSelection(tool_number[16]);
  }
  if (Key17.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_18 PA6(PB9) *****************/
  if (Key18.press()) {
    toolSelection(tool_number[17]);
  }
  if (Key18.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_19 PA10(PB0) ****************/
  if (Key19.press()) {
    toolSelection(tool_number[18]);
  }
  if (Key19.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_20 PA9(PB1) *****************/
  if (Key20.press()) {
    toolSelection(tool_number[19]);
  }
  if (Key20.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/**************** KEY_21 PA8(PC15) *****************/
  if (Key21.press()) {
    toolSelection(tool_number[20]);
  }
  if (Key21.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_22 PB15(PA7) ****************/
  if (Key22.press()) {
    toolSelection(tool_number[21]);
  }
  if (Key22.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_23 PB13(PA6) ****************/
  if (Key23.press()) {
    toolSelection(tool_number[22]);
  }
  if (Key23.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_24 PB11(PA5) ****************/
  if (Key24.press()) {
    toolSelection(tool_number[23]);
  }
  if (Key24.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
/***************** KEY_25 PA7(PC14) ****************/
  if (Key25.press()) {
    toolSelection(tool_number[24]);
  }
  if (Key25.release()) {
    knobSubMode(SUB_MODE_OFF);
  }
}
