################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/ghaas/Downloads/sloeber/arduinoPlugin/libraries/Stepper/1.1.2/src/Stepper.cpp 

LINK_OBJ += \
./libraries/Stepper/src/Stepper.cpp.o 

CPP_DEPS += \
./libraries/Stepper/src/Stepper.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Stepper/src/Stepper.cpp.o: /home/ghaas/Downloads/sloeber/arduinoPlugin/libraries/Stepper/1.1.2/src/Stepper.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/ghaas/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/ghaas/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/home/ghaas/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/eightanaloginputs" -I"/home/ghaas/Downloads/sloeber/arduinoPlugin/libraries/Stepper/1.1.2" -I"/home/ghaas/Downloads/sloeber/arduinoPlugin/libraries/Stepper/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


