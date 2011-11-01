################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Managers/AudioManager.cpp \
../Managers/FontManager.cpp \
../Managers/TilesetManager.cpp \
../Managers/VideoManager.cpp 

OBJS += \
./Managers/AudioManager.o \
./Managers/FontManager.o \
./Managers/TilesetManager.o \
./Managers/VideoManager.o 

CPP_DEPS += \
./Managers/AudioManager.d \
./Managers/FontManager.d \
./Managers/TilesetManager.d \
./Managers/VideoManager.d 


# Each subdirectory must supply rules for building sources it contributes
Managers/%.o: ../Managers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


