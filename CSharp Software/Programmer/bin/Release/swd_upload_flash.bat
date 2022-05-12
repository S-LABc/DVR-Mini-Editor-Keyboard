@echo off
win\utils\stlink\ST-LINK_CLI -c SWD -ME -P bin\flash.bin 0x8000000 -Rst -Run -NoPrompt -Q
pause