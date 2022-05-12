/* Подключение к хосту или отключение от хоста +  настройка вывода */
void conUSB (uint8_t state_) {
  switch (state_) {
    case CONNECT:
      digitalWrite(USB_DISC, HIGH);
    break;
    case DISCONNECT:
      digitalWrite(USB_DISC, LOW);
    break;
    case SETUP:
      pinMode(USB_DISC, OUTPUT);
      digitalWrite(USB_DISC, LOW);
    break;
  }
}
/* Настройка светодиодов при старте */
void settingLED (void) {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  ledMode(LEDs_OFF);
}
/* Настройка энкодера на внешнее прерывание по EXTI0 и EXTI1 (PA0 и PA1) */
void settingWheel (void) {
  pinMode(PHASE_A, INPUT_PULLUP); // Если подтяжка внешняя, заменить INPUT_PULLUP на INPUT
  pinMode(PHASE_B, INPUT_PULLUP); // Если подтяжка внешняя, заменить INPUT_PULLUP на INPUT
  attachInterrupt(digitalPinToInterrupt(PHASE_A), isWheel, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PHASE_B), isWheel, CHANGE);
}
/* Настройка USB */
void settingUSB (void) {
  conUSB(SETUP);
  USBComposite.setManufacturerString(USB_MANUFACTURER);
  USBComposite.setProductString(USB_PRODUCT);
  USBComposite.setSerialString(USB_SERIAL);
  conUSB(CONNECT);
  HID.begin(HID_KEYBOARD);
  while (!USBComposite) { // Ждем успешного соединения
    strobeLED(LED_2, 1, 100);
    iwdg_feed(); // Сброс сторожевого таймера. Чтобы не было перезагрузки при долгой инициализации
  }
}
/* Записывает базовый набор инструментов в EEPROM при ЧИСТОМ ЗАПУСКЕ */
void writeDefaultTools (void) {
  for (uint8_t i = ADDR_TOOLS_START; i <= ADDR_TOOLS_END; i ++) {
    EEPROM.update(i, default_tools[i]);
  }
}
/* Записывает набор цветов колпачков клавиш в EEPROM при ЧИСТОМ ЗАПУСКЕ */
void writeDefaultColors (void) {
  for (uint8_t i = ADDR_COLORS_START; i <= ADDR_COLORS_END; i ++) {
    EEPROM.update(i, default_colors[i]);
  }
}
/**
 * Если по адресу EEP_ADDR_CHECK нет значния EEP_KEY_EMPTY
 * до подкючения кабеля USB, то считаем, что была ЧИСТАЯ УСТАНОВКА
 */
void settingTools (void) {
  EEPROM.PageBase0 = EEP_PAGE_BEGIN;
  EEPROM.PageSize  = EEP_PAGE_SIZE;
  uint16_t check_value = EEPROM.read(EEP_ADDR_CHECK);
  if (check_value != EEP_KEY_EMPTY) {
    EEPROM.format();
    writeDefaultTools();
    writeDefaultColors();
    EEPROM.update(EEP_ADDR_CHECK, EEP_KEY_EMPTY);
    nvic_sys_reset(); // Перезагрузка. Функция из libmaple
  }
  else {
    for (uint8_t i = ADDR_TOOLS_START; i <= ADDR_TOOLS_END; i ++) {
      tool_number[i] = EEPROM.read(i);
    }
    setDefaultWheelTool();
  }
}
/* Управление светодиодами */
void ledMode (uint8_t led_) {
  switch (led_) {
    case LED_SHUTTLE:
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
    break;
    case LED_JOG:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
    break;
    case LED_SCROLL:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);
    break;
    case LEDs_OFF:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
    break;
  }
}
/* Управление дополнительным режимом ручки поиска */
void knobSubMode (uint8_t mode_) {
  switch (mode_) {
    case NUDGE:
      knob.previous_selected_mode = knob.selected_mode;
      knob.selected_mode = NUDGE;
    break;
    case AUDIO:
      knob.previous_selected_mode = knob.selected_mode;
      knob.selected_mode = AUDIO;
    break;
    case SWAP:
      knob.previous_selected_mode = knob.selected_mode;
      knob.selected_mode = SWAP;
    break;
    case SUB_MODE_OFF:
      toolDeselectAll();
      knob.selected_mode = knob.previous_selected_mode;
    break;
  }
}
/**
 * Обработка прерываний от энкодера для определения направления вращения.
 * Пример взят отсюда https://alexgyver.ru/encoder/
 */
void isWheel (void) {
  encoder.state = gpio_read_bit(PIN_MAP[PHASE_A].gpio_device, PIN_MAP[PHASE_A].gpio_bit) |
    gpio_read_bit(PIN_MAP[PHASE_B].gpio_device, PIN_MAP[PHASE_B].gpio_bit); // Вроде работает быстрее. Функция из libmaple
  if (encoder.state == 0x00) {
    encoder.reset = true;
  }
  if (encoder.reset && encoder.state == 0x03) {
    if (encoder.previous_state == 0x01) {
      encoder.turn_right = !encoder.turn_right;
    }
    if (encoder.previous_state == 0x02) {
      encoder.turn_left = !encoder.turn_left;
    }
    encoder.reset = false;
    encoder.flag = !encoder.flag;
  }
  encoder.previous_state = encoder.state;
}
/* Выбор функции ручки поиска при вращении */
void wheelAction(bool dir_) {
  switch (knob.selected_mode) {
    case NUDGE:
      actionNudge(dir_);
    break;
    case SHUTTLE:
      actionShuttle(dir_);
    break;
    case JOG:
      actionJog(dir_);
    break;
    case SCROLL:
      actionScroll(dir_);
    break;
    case AUDIO:
      actionAudio(dir_);
    break;
    case SWAP:
      actionSwap(dir_);
    break;
    default:
      toolNone();
    break;
  }
}
/*  */
bool findWheelTool (uint16_t tool_) {
  for (uint8_t i = 0; i < (sizeof(tool_number) / sizeof(uint16_t)); i++) {
    if (tool_number[i] == tool_) {
      return true;
    }
  }
  return false;
}
/* Настройка режима колеса при старте. Проверка выполняется по трём клавишам настройки ручки поиска */
void setDefaultWheelTool (void) {
  if (findWheelTool(TOOL_WHEEL_JOG)) { // Выбор по умолчанию JOG
    toolSelection(TOOL_WHEEL_JOG);
  }
  else if (findWheelTool(TOOL_WHEEL_SCROLL)) { // Не сработал JOG, пробуем SCROLL
    toolSelection(TOOL_WHEEL_SCROLL);
  }
  else if (findWheelTool(TOOL_WHEEL_SHUTTLE)) { // Не сработал SCROLL, пробуем SHUTTLE
    toolSelection(TOOL_WHEEL_SHUTTLE);
  }
  else { // В отсутсвии допустимых вариантов, отключаем ручку поиска
    knob.selected_mode = SUB_MODE_OFF;
    toolSelection(TOOL_NONE);
    ledMode(LEDs_OFF);
  }
}
/* Мигалка светодиодом */
void strobeLED (uint8_t pin_, uint8_t count_, uint16_t delay_) {
  for (uint8_t i = 0; i < count_; i ++) {
   if (millis() - last_time > delay_) {
    last_time = millis();
    digitalWrite(pin_, !digitalRead(pin_));
   } 
  }
}
/* Основная функция клавиатуры */
void mainMEK (void) {
  iwdg_feed(); // Сброс сторожевого таймера
  if (!USBComposite.isReady()) { // Когда пропадет содеиние USB, но остается питание
    if (!connection_lost) { // Первая итерация 
      connection_lost = true;
      ledMode(LEDs_OFF);
    }
    strobeLED(LED_2, 1, 100); // Мигаем, ожидая восстановления соединения
  }
  else { // Нормальный режим работы
    if (connection_lost) { // Первая итерация после восстановления соединения
      connection_lost = false;
      toolSelection(knob.selected_mode); // Восстановление режима ручки поиска до потери соединения
    }
    keyEvents();
    wheelEvents();
  }
}
