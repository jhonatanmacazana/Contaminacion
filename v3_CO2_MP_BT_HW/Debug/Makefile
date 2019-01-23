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
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Perif/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../Perif/comps.c \
../Perif/sensors.c \
../Perif/USART_irq.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
Perif/comps.o \
Perif/sensors.o \
Perif/USART_irq.o

OBJS_AS_ARGS +=  \
main.o \
Perif/comps.o \
Perif/sensors.o \
Perif/USART_irq.o

C_DEPS +=  \
main.d \
Perif/comps.d \
Perif/sensors.d \
Perif/USART_irq.d

C_DEPS_AS_ARGS +=  \
main.d \
Perif/comps.d \
Perif/sensors.d \
Perif/USART_irq.d

OUTPUT_FILE_PATH +=v3_CO2_MP_BT_HW.elf

OUTPUT_FILE_PATH_AS_ARGS +=v3_CO2_MP_BT_HW.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.5.1
	$(QUOTE)D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Aplicaciones\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Perif/comps.o: ../Perif/comps.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.5.1
	$(QUOTE)D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Aplicaciones\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Perif/sensors.o: ../Perif/sensors.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.5.1
	$(QUOTE)D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Aplicaciones\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Perif/USART_irq.o: ../Perif/USART_irq.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.5.1
	$(QUOTE)D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Aplicaciones\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.209\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.5.1
	$(QUOTE)D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="v3_CO2_MP_BT_HW.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections  -mmcu=atmega328p   
	@echo Finished building target: $@
	"D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "v3_CO2_MP_BT_HW.elf" "v3_CO2_MP_BT_HW.hex"
	"D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "v3_CO2_MP_BT_HW.elf" "v3_CO2_MP_BT_HW.eep" || exit 0
	"D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-objdump.exe" -h -S "v3_CO2_MP_BT_HW.elf" > "v3_CO2_MP_BT_HW.lss"
	"D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "v3_CO2_MP_BT_HW.elf" "v3_CO2_MP_BT_HW.srec"
	"D:\Aplicaciones\Atmel\AVR Tools\AVR Toolchain\bin\avr-size.exe" "v3_CO2_MP_BT_HW.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "v3_CO2_MP_BT_HW.elf" "v3_CO2_MP_BT_HW.a" "v3_CO2_MP_BT_HW.hex" "v3_CO2_MP_BT_HW.lss" "v3_CO2_MP_BT_HW.eep" "v3_CO2_MP_BT_HW.map" "v3_CO2_MP_BT_HW.srec" "v3_CO2_MP_BT_HW.usersignatures"
	