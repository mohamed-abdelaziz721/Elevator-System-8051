# write the files without extension
FILES := app Timer0 Led PushButton Common SevenSegment
mainFile := app
SiLabsPath = C:/SiLabs


space := $(null) #
comma := ,
SRCS := $(foreach file,$(FILES),$(file).c)
OBJSList := $(foreach file, $(FILES), $(file).OBJ)
OBJS := $(subst $(space), $(comma),$(strip $(OBJSList)))
CC      := $(SiLabsPath)/MCU/IDEfiles/C51/BIN/C51.exe
OH 		:= $(SiLabsPath)/MCU/IDEfiles/C51/BIN/oh51.exe
ld 		:= $(SiLabsPath)/MCU/IDEfiles/C51/BIN/bl51.exe
	
default: link
	$(OH) $(mainFile).ABS
	make clean

clear:
	rm -f *.OBJ *.LST *.M51 *.ABS *.hex

link:
	$(foreach var,$(SRCS), $(CC) $(var) DB OE BR;)
	$(ld) $(OBJS) TO $(mainFile).ABS

clean:
	rm -f *.OBJ *.LST *.M51 *.ABS