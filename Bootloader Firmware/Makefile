# Makefile skeleton adapted from Peter Harrison's - www.micromouse.com

# Ядро микроконтроллера
MCUCORE = cortex-m3
# toolchain (using code sourcery now)
TCHAIN 	 = arm-none-eabi
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork
# Оновные пути
BUILDDIR = build
SRCDIR   = src
DEPDIR   = dep
STLIB 	 = $(SRCDIR)/stm32_lib
STUSB   = $(SRCDIR)/usb_lib
# Имя промежуточного и финального файлов без расширения
TARGET      = $(BUILDDIR)/raw_boot
OUTFILENAME = bootloader_mini_editor_keyboard

# ----- Флаги -----
# Компилятор
CFLAGS  = -Os
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wall -Wimplicit
CFLAGS += -Wcast-align
CFLAGS += -Wpointer-arith -Wswitch
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
CFLAGS += -Wa,-adhlns=$(BUILDDIR)/$(subst $(suffix $<),.lst,$<)
CFLAGS += $(patsubst %,-I%,./$(STLIB) ./$(STUSB))
# Ассемблер
ASFLAGS = -Wa,-adhlns=$(BUILDDIR)/$(<:.s=.lst)#,--g
# Компановшщик
LDFLAGS = -nostartfiles -Wl,-Map=$(TARGET).map,--cref,--gc-sections -lc -lgcc -T$(STLIB)/c_only_md_high_density.ld
# Объединение флагов
ALLCFLAGS  = -g -mcpu=$(MCUCORE) $(THUMB_IW) -I. $(CFLAGS) -MD -MP -MF $(DEPDIR)/$(@F).d
ALLASFLAGS = -g -mcpu=$(MCUCORE) $(THUMB_IW) -I. -x assembler-with-cpp $(ASFLAGS)
# Дополнительные
MKDIR   = mkdir -p
CC      = $(TCHAIN)-gcc
OBJCOPY = $(TCHAIN)-objcopy
SIZE    = $(TCHAIN)-size
NM      = $(TCHAIN)-nm
REMOVE  = rm -f
COPY    = cp

# ----- Пути к файлам -----
# Управление файлами
ASRC = $(STLIB)/c_only_startup.s $(STLIB)/cortexm3_macro.s
# Исходники библиотеки USB
USBSRCS = $(patsubst %, $(STUSB)/%, usb_regs.c usb_int.c usb_init.c usb_core.c usb_mem.c)
# Исходники загрузчика
SRC = $(patsubst %, $(SRCDIR)/%, usb.c usb_descriptor.c main.c hardware.c dfu.c) $(USBSRCS)
# Объекты
COBJ = $(patsubst %, $(BUILDDIR)/%, $(SRC:.c=.o))
AOBJ = $(patsubst %, $(BUILDDIR)/%, $(ASRC:.s=.o))
# Списки
LST = $(patsubst %, $(BUILDDIR)/%, $(ASRC:.s=.lst) $(SRC:.c=.lst))

# ----- Текст сообщений -----
# EN
MSG_BEGIN       = -------- begin --------
MSG_ERRORS_NONE = Errors: none
MSG_END         = -------- end --------
MSG_COMP        = --- The firmware file is located in the main folder ---
MSG_FLASH 		= Creating load file for Flash:
MSG_LINKING     = Linking:
MSG_COMPILING   = Compiling C:
MSG_ASSEMBLING  = Assembling:
MSG_CLEANING    = Cleaning project:
MSG_CLN_BIN     = - Binary -
MSG_CLN_ELF     = - Link -
MSG_CLN_MAP     = - Map -
MSG_CLN_COBJ    = - Compile -
MSG_CLN_AOBJ    = - Assemble -
MSG_CLN_LST     = - List -
MSG_CLN_DEP     = - Dependency -

# ----- Главная задача -----
mini_editor_keyboard: begin clean gccversion build end
# Создание основных путей
begin:
	$(MKDIR) $(BUILDDIR)/$(STLIB)
	$(MKDIR) $(BUILDDIR)/$(STUSB)
	@echo
	@echo $(MSG_BEGIN)
	@echo $(COBJ)
	@echo $(AOBJ)
# Удаление всех старых файлов
clean:
	@echo
	@echo $(MSG_CLEANING)
	@echo $(MSG_CLN_BIN)
	$(REMOVE) $(OUTFILENAME).bin
	@echo $(MSG_CLN_ELF)
	$(REMOVE) $(TARGET).elf
	@echo $(MSG_CLN_MAP)
	$(REMOVE) $(TARGET).map
	@echo $(MSG_CLN_COBJ)
	$(REMOVE) $(COBJ)
	@echo $(MSG_CLN_AOBJ)
	$(REMOVE) $(AOBJ)
	@echo $(MSG_CLN_LST)
	$(REMOVE) $(LST)
	@echo $(MSG_CLN_DEP)
	$(REMOVE) $(DEPDIR)/*
# Вверсия toolchain
gccversion:
	@echo
	@$(CC) --version
# Имя с расширением файла прошивки
build: $(OUTFILENAME).bin
# Сообщение окончания процесса
end:
	@echo
	@echo $(MSG_ERRORS_NONE)
	@echo $(MSG_END)
	@echo
	@echo $(MSG_COMP)
	@echo
# Содание файла прошивки .bin из файла .elf
%.bin: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O binary $< $@
# Линковщик: Содание файла .elf из файлов объектов
.SECONDARY: $(TARGET).elf
.PRECIOUS: $(COBJ) $(AOBJ)
%.elf:  $(COBJ) $(AOBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(THUMB) $(ALLCFLAGS) $(AOBJ) $(COBJ) --output $@ $(LDFLAGS)
# Компилятор. Создание файлов объектов из исходников Си. ARM/Thumb
$(COBJ) : $(BUILDDIR)/%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(THUMB) $(ALLCFLAGS) $< -o $@
# Ассемблер. Создание файлов объектов из исходников Ассемблера. ARM/Thumb
$(AOBJ) : $(BUILDDIR)/%.o : %.s
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(THUMB) $(ALLASFLAGS) $< -o $@
# Подключение файлов с зависимостями
-include $(shell mkdir $(DEPDIR) 2>/dev/null) $(wildcard $(DEPDIR)/*)
# Перечисление ложных целей
.PHONY: begin clean gccversion build end elf bin