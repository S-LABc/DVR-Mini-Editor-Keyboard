@echo off
win\utils\dfu-util-0.9-win64\dfu-util -d 1EAF:0003 -a 0 -D bin\firmware.bin
pause