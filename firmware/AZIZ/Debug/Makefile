################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../buttons.c \
../encoder.c \
../led_driver.c \
../led_pattern.c \
../main.c \
../mode_leds.c \
../timer.c \
../TWI_master.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
buttons.o \
encoder.o \
led_driver.o \
led_pattern.o \
main.o \
mode_leds.o \
timer.o \
TWI_master.o


OBJS_AS_ARGS +=  \
buttons.o \
encoder.o \
led_driver.o \
led_pattern.o \
main.o \
mode_leds.o \
timer.o \
TWI_master.o


C_DEPS +=  \
buttons.d \
encoder.d \
led_driver.d \
led_pattern.d \
main.d \
mode_leds.d \
timer.d \
TWI_master.d


C_DEPS_AS_ARGS +=  \
buttons.d \
encoder.d \
led_driver.d \
led_pattern.d \
main.d \
mode_leds.d \
timer.d \
TWI_master.d


OUTPUT_FILE_PATH +=AZIZ.elf

OUTPUT_FILE_PATH_AS_ARGS +=AZIZ.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler

















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 
	$(QUOTE)D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=attiny1634 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 
	$(QUOTE)D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="AZIZ.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=attiny1634 
	@echo Finished building target: $@
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "AZIZ.elf" "AZIZ.hex"
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "AZIZ.elf" "AZIZ.eep" || exit 0
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "AZIZ.elf" > "AZIZ.lss"
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "AZIZ.elf" "AZIZ.srec"
	"D:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.876\avr8-gnu-toolchain\bin\avr-size.exe" "AZIZ.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "AZIZ.elf" "AZIZ.a" "AZIZ.hex" "AZIZ.lss" "AZIZ.eep" "AZIZ.map" "AZIZ.srec"
	