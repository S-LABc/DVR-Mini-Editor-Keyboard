/* 0 Чтобы клавиша не делала ничего */
void toolNone() {
  asm("nop");
}
/* 1 Отменить (Undo) */
void toolUndo() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_Z);
  Keyboard.release(LOWERCASE_Z);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 2 Прикрепление (Snapping) */
void toolSnapping() {
  Keyboard.press(LOWERCASE_N);
  Keyboard.release(LOWERCASE_N);
}
/* 3 Режим окна просмотра кинотеатр (Cinema Viewer) */
void toolCinemaViewer() {
  Keyboard.press(LOWERCASE_P);
  Keyboard.release(LOWERCASE_P);
}
/* 4 Вставить (Insert) */
void toolInsert() {
  Keyboard.press(KEY_F9);
  Keyboard.release(KEY_F9);
}
/* 5 Добавить в конец временной шкалы (Append to End of Timeline)*/
void toolAppendToEndOfTimeline() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_F12);
  Keyboard.release(KEY_F12);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 6 Перезаписать со сдвигом (Ripple Overwrite) */
void toolRippleOverwrite() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_F10);
  Keyboard.release(KEY_F10);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 7 Заполнить (Fit to Fill) */
void toolFitToFill() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_F11);
  Keyboard.release(KEY_F11);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 8 Разместить сверху (Place on Top) */
void toolPlaceOnTop() {
  Keyboard.press(KEY_F12);
  Keyboard.release(KEY_F12);
}
/* 9 Заменить (Replace) */
void toolReplace() {
  Keyboard.press(KEY_F11);
  Keyboard.release(KEY_F11);
}
/* 10 Отметить вход (Mark In) */
void toolMarkIn() {
  Keyboard.press(LOWERCASE_I);
  Keyboard.release(LOWERCASE_I);
}
/* 11 Добавить маркер (Add Marker) */
void toolAddMarker() {
  Keyboard.press(LOWERCASE_M);
  Keyboard.release(LOWERCASE_M);
}
/* 12 Отметить выход (Mark Out) */
void toolMarkOut() {
  Keyboard.press(LOWERCASE_O);
  Keyboard.release(LOWERCASE_O);
}
/* 13 Изменить размер в точке входа (Resize In) */
void toolResizeIn() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_B);
  Keyboard.release(LOWERCASE_B);
  Keyboard.release(KEY_LEFT_SHIFT);
  knobSubMode(NUDGE);
}
/* 14 Изменить размер в точке выхода (Resize Out) */
void toolResizeOut() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_N);
  Keyboard.release(LOWERCASE_N);
  Keyboard.release(KEY_LEFT_SHIFT);
  knobSubMode(NUDGE);
}
/* 15 Совместить (Roll) */
void toolRoll() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_G);
  Keyboard.release(LOWERCASE_G);
  Keyboard.release(KEY_LEFT_SHIFT);
  knobSubMode(NUDGE);
}
/* 16 Переместить (Move) */
void toolMove() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_X);
  Keyboard.release(LOWERCASE_X);
  Keyboard.release(KEY_LEFT_SHIFT);
  knobSubMode(NUDGE);
}
/* 17 Сместить (Slide) */
void toolSlide() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_Y);
  Keyboard.release(LOWERCASE_Y);
  Keyboard.release(KEY_LEFT_SHIFT);
  knobSubMode(NUDGE);
}
/* 18 Прокрутить скольжением (Slip) */
void toolSlip() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_U);
  Keyboard.release(LOWERCASE_U);
  Keyboard.release(KEY_LEFT_SHIFT);
  knobSubMode(NUDGE);
}
/* 19 Окно просмотра источника/временной шкалы (Source/Timeline Viewer) */
void toolSourceTimelineViewer() {
  Keyboard.press(LOWERCASE_Q);
  Keyboard.release(LOWERCASE_Q);
}
/* 20 Настройки проекта (Project Settings) */
void toolProjectSettings() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_NINE);
  Keyboard.release(NUMBER_NINE);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 21 Исходный клип/исходная кассета (Source Clip/Tape) */
void toolSourceClipTape() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_Q);
  Keyboard.release(LOWERCASE_Q);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 22 Проигрывание колесом с разной скоростью (Shuttle) */
void toolWheelShuttle() {
  ledMode(LED_SHUTTLE);
  toolStop();
  knob.playback_speed = NEUTRAL;
  knob.selected_mode = SHUTTLE;
  knob.previous_selected_mode = SHUTTLE;
}
/* 23 Покадровое перемещение колесом (Jog) */
void toolWheelJog() {
  ledMode(LED_JOG);
  toolStop();
  knob.selected_mode = JOG;
  knob.previous_selected_mode = JOG;
}
/* 24 Покадровое, посекундное перемещение колесом (Scroll) */
void toolWheelScroll() {
  ledMode(LED_SCROLL);
  toolStop();
  knob.selected_mode = SCROLL;
  knob.previous_selected_mode = SCROLL;
}
/* 25 Пауза/Начать воспроизведение (Pause/Start Playback) */
void toolPauseStartPlayback() {
  Keyboard.press(SPACE);
  Keyboard.release(SPACE);
  knob.playback_speed = NEUTRAL; // Для алгоритмов колеса
}
/* 26 Воспроизвести назад (Play Revers) */
void toolPlayRevers() {
  Keyboard.press(LOWERCASE_J);
  Keyboard.release(LOWERCASE_J);
}
/* 27 Воспроизвести вперед (Play Forward) */
void toolPlayForward() {
  Keyboard.press(LOWERCASE_L);
  Keyboard.release(LOWERCASE_L);
}
/* 28 Перейти ко входу (Go to In) */
void toolGoToIn() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_I);
  Keyboard.release(LOWERCASE_I);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 29 Перейти к выходу (Go to Out) */
void toolGoToOut() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_O);
  Keyboard.release(LOWERCASE_O);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 30 Сдвинуть от начала до курсора воспроизведения (Riple Start to Playhead) */
void toolRipleStartToPlayhead() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(OPENING_BRACKET);
  Keyboard.release(OPENING_BRACKET);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 31 Сдвинуть от конца до курсора воспроизведения (Riple End to Playhead) */
void toolRipleEndToPlayhead() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(CLOSING_BRACKET);
  Keyboard.release(CLOSING_BRACKET);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 32 Предыдущий клип/точка монтажа (Previous Clip/Edit) */
void toolPreviousClipEdit() {
  Keyboard.press(KEY_UP_ARROW);
  Keyboard.release(KEY_UP_ARROW);
}
/* 33 Следующий клип/точка монтажа (Next Clip/Edit) */
void toolNextClipEdit() {
  Keyboard.press(KEY_DOWN_ARROW);
  Keyboard.release(KEY_DOWN_ARROW);
}
/* 34 Перемотать назад (Fast Reverse) */
void toolFastReverse() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_J);
  Keyboard.release(LOWERCASE_J);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 35 Перемотать вперед (Fast Forward) */
void toolFastForward() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_L);
  Keyboard.release(LOWERCASE_L);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 36 На один кадр назад (Frame Reverse) */
void toolFrameReverse() {
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.release(KEY_LEFT_ARROW);
}
/* 37 На один кадр вперед (Frame Forward) */
void toolFrameForward() {
  Keyboard.press(KEY_RIGHT_ARROW);
  Keyboard.release(KEY_RIGHT_ARROW);
}
/* 38 На кадр влево (One Frame Left) */
void toolOneFrameLeft() {
  Keyboard.press(COMMA);
  Keyboard.release(COMMA);
}
/* 39 На кадр вправо (One Frame Right) */
void toolOneFrameRight() {
  Keyboard.press(PERIOD);
  Keyboard.release(PERIOD);
}
/* 40 Перейти к началу временной шкалы (Timeline Start) */
void toolTimelineStart() {
  Keyboard.press(KEY_HOME);
  Keyboard.release(KEY_HOME);
}
/* 41 Перейти к концу временной шкалы (Timeline End) */
void toolTimelineEnd() {
  Keyboard.press(KEY_END);
  Keyboard.release(KEY_END);
}
/* 42 Несколько кадров влево (Multiframe Left) */
void toolMultiframeLeft() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(COMMA);
  Keyboard.release(COMMA);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 43 Несколько кадров вправо (Multiframe Right) */
void toolMultiframeRight() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(PERIOD);
  Keyboard.release(PERIOD);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 44 На одну секунду назад (Second Reverse) */
void toolSecondReverse() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.release(KEY_LEFT_ARROW);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 45 На одну секунду вперед (Second Forward) */
void toolSecondForward() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RIGHT_ARROW);
  Keyboard.release(KEY_RIGHT_ARROW);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 46 Изменить скорость клипа (Change Clip Speed) */
void toolChangeClipSpeed() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  Keyboard.press(LOWERCASE_R);
  Keyboard.release(LOWERCASE_R);
}
/* 47 Изменить длительность клипа (Change Clip Duration) */
void toolChangeClipDuration() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_D);
  Keyboard.release(LOWERCASE_D);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 48 Показать/скрыть редактор кривых (Show Curve Editor) */
void toolShowCurveEditor() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_C);
  Keyboard.release(LOWERCASE_C);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 49 Показать/скрыть редактор ключевых кадров (Show Keyframe Editor) */
void toolShowKeyframeEditor() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_C);
  Keyboard.release(LOWERCASE_C);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 50 Выбрать ближайшую точку редактирования видео (Select Nearest Video Edit Point) */
void toolSelectNearestVideoEditPoint() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(LOWERCASE_E);
  Keyboard.release(LOWERCASE_E);
  Keyboard.release(KEY_LEFT_ALT);
  knobSubMode(NUDGE);
}
/* 51 Выбрать ближайшую точку редактирования аудио (Select Nearest Audio Edit Point) */
void toolSelectNearestAudioEditPoint() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_E);
  Keyboard.release(LOWERCASE_E);
  Keyboard.release(KEY_LEFT_SHIFT);
  knobSubMode(NUDGE);
}
/* 52 Уменьшить уровень громкости клипа на 1дБ (Decrease Audio Level 1dB) */
void toolDecreaseAudioLevel1dB() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(HYPHEN);
  Keyboard.release(HYPHEN);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_ALT);
}
/* 53 Увеличить уровень громкости клипа на 1дБ (Increase Audio Level 1dB) */
void toolIncreaseAudioLevel1dB() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(EQUALS);
  Keyboard.release(EQUALS);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_ALT);
}
/* 54 Отметить клип по входу и выходу (Mark Clip) */
void toolMarkClip() {
  Keyboard.press(LOWERCASE_X);
  Keyboard.release(LOWERCASE_X);
}
/* 55 Стереть точку входа (Clear In) */
void toolClearIn() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(LOWERCASE_I);
  Keyboard.release(LOWERCASE_I);
  Keyboard.release(KEY_LEFT_ALT);
}
/* 56 Стереть точку выхода (Clear Out) */
void toolClearOut() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(LOWERCASE_O);
  Keyboard.release(LOWERCASE_O);
  Keyboard.release(KEY_LEFT_ALT);
}
/* 57 Стереть точки входа и выхода (Clear In and Out) */
void toolClearInAndOut() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(LOWERCASE_X);
  Keyboard.release(LOWERCASE_X);
  Keyboard.release(KEY_LEFT_ALT);
}
/* 58 Добавить переход (Add Transition) */
void toolAddTransition() {
  toolSelectNearestEditPoint(); // Выбрать склейку
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_T);
  Keyboard.release(LOWERCASE_T);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 59 Добавить переход только на видео (Add Video Only Transition) */
void toolAddVideoOnlyTransition() {
  toolSelectNearestEditPoint(); // Выбрать склейку
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(LOWERCASE_T);
  Keyboard.release(LOWERCASE_T);
  Keyboard.release(KEY_LEFT_ALT);
}
/* 60 Добавить переход только на аудио (Add Audio Only Transition) */
void toolAddAudioOnlyTransition() {
  toolSelectNearestEditPoint(); // Выбрать склейку
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_T);
  Keyboard.release(LOWERCASE_T);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 61 Выбрать ближайший клип/промежуток (Select Nearest Clip/Gap) */
void toolSelectNearestClipGap() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_V);
  Keyboard.release(LOWERCASE_V);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 62 Выбрать ближайшую точку редактирования (Select Nearest Edit Point) */
void toolSelectNearestEditPoint() {
  Keyboard.press(LOWERCASE_V);
  Keyboard.release(LOWERCASE_V);
}
/* 63 Управление проектами (Project Manager) */
void toolProjectManager() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_ONE);
  Keyboard.release(NUMBER_ONE);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 64 Переключить на вкладку Media (Switch to Page Media) */
void toolSwitchToPageMedia() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_TWO);
  Keyboard.release(NUMBER_TWO);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 65 Переключить на вкладку Cut (Switch to Page Cut) */
void toolSwitchToPageCut() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_THREE);
  Keyboard.release(NUMBER_THREE);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 66 Переключить на вкладку Edit (Switch to Page Edit) */
void toolSwitchToPageEdit() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_FOUR);
  Keyboard.release(NUMBER_FOUR);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 67 Переключить на вкладку Fusion (Switch to Page Fusion) */
void toolSwitchToPageFusion() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_FIVE);
  Keyboard.release(NUMBER_FIVE);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 68 Переключить на вкладку Color (Switch to Page Color) */
void toolSwitchToPageColor() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_SIX);
  Keyboard.release(NUMBER_SIX);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 69 Переключить на вкладку Fairlight (Switch to Page Fairlight) */
void toolSwitchToPageFairlight() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_SEVEN);
  Keyboard.release(NUMBER_SEVEN);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 70 Переключить на вкладку Deliver (Switch to Page Deliver) */
void toolSwitchToPageDeliver() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(NUMBER_EIGHT);
  Keyboard.release(NUMBER_EIGHT);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 71 Вырезать на ракурс 1 (Cut to Angle 1) */
void toolCutToAngle1() {
  Keyboard.press(NUMBER_ONE);
  Keyboard.release(NUMBER_ONE);
}
/* 72 Вырезать на ракурс 2 (Cut to Angle 2) */
void toolCutToAngle2() {
  Keyboard.press(NUMBER_TWO);
  Keyboard.release(NUMBER_TWO);
}
/* 73 Вырезать на ракурс 3 (Cut to Angle 3) */
void toolCutToAngle3() {
  Keyboard.press(NUMBER_THREE);
  Keyboard.release(NUMBER_THREE);
}
/* 74 Вырезать на ракурс 4 (Cut to Angle 4) */
void toolCutToAngle4() {
  Keyboard.press(NUMBER_FOUR);
  Keyboard.release(NUMBER_FOUR);
}
/* 75 Вырезать на ракурс 5 (Cut to Angle 5) */
void toolCutToAngle5() {
  Keyboard.press(NUMBER_FIVE);
  Keyboard.release(NUMBER_FIVE);
}
/* 76 Вырезать на ракурс 6 (Cut to Angle 6) */
void toolCutToAngle6() {
  Keyboard.press(NUMBER_SIX);
  Keyboard.release(NUMBER_SIX);
}
/* 77 Вырезать на ракурс 7 (Cut to Angle 7) */
void toolCutToAngle7() {
  Keyboard.press(NUMBER_SEVEN);
  Keyboard.release(NUMBER_SEVEN);
}
/* 78 Вырезать на ракурс 8 (Cut to Angle 8) */
void toolCutToAngle8() {
  Keyboard.press(NUMBER_EIGHT);
  Keyboard.release(NUMBER_EIGHT);
}
/* 79 Вырезать на ракурс 9 (Cut to Angle 9) */
void toolCutToAngle9() {
  Keyboard.press(NUMBER_NINE);
  Keyboard.release(NUMBER_NINE);
}
/* 80 Сохранить проект (Save Project) */
void toolSaveProject() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_S);
  Keyboard.release(LOWERCASE_S);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 81 Сохранить проект как (Save Project As) */
void toolSaveProjectAs() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_S);
  Keyboard.release(LOWERCASE_S);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 82 Поменять местами клипы влево (Swap Clips Towards Left) */
void toolSwapClipsTowardsLeft() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(COMMA);
  Keyboard.release(COMMA);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 83 Поменять местами клипы вправо (Swap Clips Towards Right) */
void toolSwapClipsTowardsRight() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(PERIOD);
  Keyboard.release(PERIOD);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 84 Выделить всё (Select All) */
void toolSelectAll() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_A);
  Keyboard.release(LOWERCASE_A);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 85 Отменить выбор всего (Deselect All) */
void toolDeselectAll() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_A);
  Keyboard.release(LOWERCASE_A);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 86 Повторить (Redo) */
void toolRedo() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_Z);
  Keyboard.release(LOWERCASE_Z);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 87 Удалить маркер (Delete Marker) */
void toolDeleteMarker() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(LOWERCASE_M);
  Keyboard.release(LOWERCASE_M);
  Keyboard.release(KEY_LEFT_ALT);
}
/* 88 Удалить со сдвигом (Ripple Delete) */
void toolRippleDelete() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  Keyboard.press(KEY_DELETE);
  Keyboard.release(KEY_DELETE);
}
/* 89 Перезаписать (Overwrite) */
void toolOverwrite() {
  Keyboard.press(KEY_F10);
  Keyboard.release(KEY_F10);
}
/* 90 Разделить клип (Split Clip) */
void toolSplitClip() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(BACKSLASH);
  Keyboard.release(BACKSLASH);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 91 Удалить промежутки (Delete Gaps) */
void toolDeleteGaps() {
  Keyboard.press(LOWERCASE_C);
  Keyboard.release(LOWERCASE_C);
}
/* 92 Остановить воспроизведение (Stop) */
void toolStop() {
  Keyboard.press(LOWERCASE_K);
  Keyboard.release(LOWERCASE_K);
}
/* 93 Медленное воспроизведение (Play Slow) */
void toolPlaySlow() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_K);
  Keyboard.release(LOWERCASE_K);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 94 Копировать (Copy) */
void toolCopy() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_C);
  Keyboard.release(LOWERCASE_C);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 95 Вырезать (Cut) */
void toolCut() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_X);
  Keyboard.release(LOWERCASE_X);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 96 Вставить (Paste) */
void toolPaste() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_V);
  Keyboard.release(LOWERCASE_V);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 97 Включить/выключить клип (Enable Clip) */
void toolEnableClip() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  Keyboard.press(LOWERCASE_D);
  Keyboard.release(LOWERCASE_D);
}
/* 98 Настройки программы (Preferences) */
void toolPreferences() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(COMMA);
  Keyboard.release(COMMA);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 99 Зациклить/отпустить (Loop/Unloop) */
void toolLoopUnloop() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(SLASH);
  Keyboard.release(SLASH);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 100 Стоп-Кадр (Freeze Frame) */
void toolFreezeFrame() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_R);
  Keyboard.release(LOWERCASE_R);
  Keyboard.release(KEY_LEFT_SHIFT);
}
/* 101 Изменить уровень громкости (Change Audio Level) */
void toolChangeAudioLevel() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  knobSubMode(AUDIO);
}
/* 102 Поменять местами клипы (Swap Clips) */
void toolSwapClips() {
  toolSelectNearestClipGap(); // Выделить то, что под плейхэдом
  knobSubMode(SWAP);
}
/* 103 Связь компонентов (Linked Selection) */
void toolLinkedSelection() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(LOWERCASE_L);
  Keyboard.release(LOWERCASE_L);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 104 Настройка клавиатуры (Keyboard Customization) */
void toolKeyboardCustomization() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(LOWERCASE_K);
  Keyboard.release(LOWERCASE_K);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 105 Выйти из программы (Quit DaVinci Resolve) */
void toolQuitDaVinciResolve() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_Q);
  Keyboard.release(LOWERCASE_Q);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 106 Новая временная шкала (New Timeline) */
void toolNewTimeline() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_N);
  Keyboard.release(LOWERCASE_N);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 107 Импортировать медиафайлы (Import Media) */
void toolImportMedia() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(LOWERCASE_I);
  Keyboard.release(LOWERCASE_I);
  Keyboard.release(KEY_LEFT_CTRL);
}
/* 108 Синхроящик (Sync Bin) */
void toolSyncBin() {
  Keyboard.press(LOWERCASE_H);
  Keyboard.release(LOWERCASE_H);
}
