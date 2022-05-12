/* Поведение ручки поиска в режиме SHUTTLE */
void actionShuttle (bool dir_) {
  if (dir_) { /* ЛЕВО */
    if (knob.playback_speed > MINIMUM && knob.playback_speed <= NEUTRAL) { // Стоим или движемся влево
        toolPlayRevers();
        knob.playback_speed --;
      }
      else if (knob.playback_speed > NEUTRAL && knob.playback_speed <= MAXIMUM) { // Двигались вправо, сменили навправление
        if (knob.playback_speed > NEUTRAL + 1) { // Не стоим на нейтрали
          toolPlaySlow();
        }
        else if (knob.playback_speed == NEUTRAL + 1) {
          toolStop();
        }
        knob.playback_speed --;
      }
      else if (knob.playback_speed == MAXIMUM + 1) { // Дошли до конца вправо и сменили направление
        toolPlayRevers();
        knob.playback_speed = NEUTRAL - 1;
      }
      else if (knob.playback_speed == MINIMUM) { // Дошли до конца влево, остановились
        toolStop();
        toolGoToIn();
        knob.playback_speed --; // Для избежания зацикливания
      }
  }
  else { /* ПРАВО */
    if (knob.playback_speed < MAXIMUM && knob.playback_speed >= NEUTRAL) { // Стоим или движемся вправо
      toolPlayForward();
      knob.playback_speed ++;
    }
    else if (knob.playback_speed < NEUTRAL && knob.playback_speed >= MINIMUM) { // Двигались влево, сменили навправление
      if (knob.playback_speed < NEUTRAL - 1) { // Не стоим на нейтрали
        toolPlaySlow();
      }
      else if (knob.playback_speed == NEUTRAL - 1) {
        toolStop();
      }
      knob.playback_speed ++;
    }
    else if (knob.playback_speed == MINIMUM - 1) { // Дошли до конца влево и сменили напрвление
      toolPlayForward();
      knob.playback_speed = NEUTRAL + 1;
    }
    else if (knob.playback_speed == MAXIMUM) { // Дошли до конца вправо, остановились
      toolStop();
      toolGoToOut();
      knob.playback_speed ++; // Для избежания зацикливания
    }
  }
}
/* Поведение ручки поиска в режиме JOG */
void actionJog (bool dir_) {
  dir_ ? toolFrameReverse() : toolFrameForward();
}
/* Поведение ручки поиска в режиме SCROLL */
void actionScroll (bool dir_) {
  uint16_t delta_time = millis() - last_time;
  if (dir_) { /* ЛЕВО */
    (delta_time < SCROLL_INTERVAL) ? toolSecondReverse() : toolFrameReverse();
  }
  else { /* ПРАВО */
    (delta_time < SCROLL_INTERVAL) ? toolSecondForward() : toolFrameForward();
  }
  last_time = millis();
}
/* Поведение ручки поиска в дополнительном режиме точной подгонки */
void actionNudge (bool dir_) {
  dir_ ? toolOneFrameLeft() : toolOneFrameRight();
}
/* Поведение ручки поиска в дополнительном режиме управления громкостью */
void actionAudio (bool dir_) {
  dir_ ? toolDecreaseAudioLevel1dB() : toolIncreaseAudioLevel1dB();
}
/* Поведение ручки поиска в дополнительном режиме смены клипов местами */
void actionSwap (bool dir_) {
  dir_ ? toolSwapClipsTowardsLeft() : toolSwapClipsTowardsRight();
}
