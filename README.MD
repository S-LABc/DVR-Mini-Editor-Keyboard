# DVR-Mini-Editor-Keyboard
<p align="center"><img src="/keyboard_front_view.jpg"></p>

* Проект USB клавиатуры для программы видео монтажа DaVinci Resolve. Проект не закончен из-за желания сделать клавиатуру более удобной. Можно [скачать отсюда архив](https://github.com/S-LABc/DVR-Mini-Editor-Keyboard/releases) с программой и всем необходимым для самостоятельного повторения. Работоспособность проверялась на Windows 10 x64

## Содержимое
* В папке Altium Hardware находятся незавершенные файлы схемы, платы нет - не успел сделать
* В папке Arduino Firmware находится исходный код прошивки самой клавиатуры. Ядро для Arduino использовалось [это](https://github.com/rogerclarkmelbourne/Arduino_STM32)
* В папке Bootloader Firmware находится исходный код загрузчика. Он основан на [этом загрузчике](https://github.com/rogerclarkmelbourne/STM32duino-bootloader)
* В папке CSharp Software находится исходный код приложения для смены инструментов. Драйвера и утилиты расположены в *Programmer\bin\Release*