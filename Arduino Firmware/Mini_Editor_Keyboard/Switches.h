/**
 * Алгоритм отсюда https://alexgyver.ru/gyverbutton/
 * Использовать библиотеку не стал, её функционал слишком избыточен
 * Всё написано в .h, объём кода очень маленький, нет смысла использовать .cpp
 */
#pragma once

/* Класс переключателя */
class Switch {
  public:
    Switch(uint8_t pin);
    bool press();
    bool release();
  private:
    uint8_t _pin = 0;
    bool _flag   = false;
};
/* Конструктор класса */
Switch::Switch(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP); // Если подтяжка внешняя, заменить INPUT_PULLUP на INPUT
}
/* Нажатие */
bool Switch::press() {
  if (!_flag && digitalRead(_pin) == LOW) {
    _flag = true;
    return true;
  }
  else {
    return false;
  }
}
/* Отпускание */
bool Switch::release() {
  if (_flag && digitalRead(_pin) == HIGH) {
    _flag = false;
    return true;
  }
  else {
    return false;
  }
}
