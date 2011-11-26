################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Engine/AudioManager.cpp \
../Engine/Colors.cpp \
../Engine/Engine.cpp \
../Engine/FontManager.cpp \
../Engine/GUI.cpp \
../Engine/Logger.cpp \
../Engine/Timer.cpp \
../Engine/VideoManager.cpp 

OBJS += \
./Engine/AudioManager.o \
./Engine/Colors.o \
./Engine/Engine.o \
./Engine/FontManager.o \
./Engine/GUI.o \
./Engine/Logger.o \
./Engine/Timer.o \
./Engine/VideoManager.o 

CPP_DEPS += \
./Engine/AudioManager.d \
./Engine/Colors.d \
./Engine/Engine.d \
./Engine/FontManager.d \
./Engine/GUI.d \
./Engine/Logger.d \
./Engine/Timer.d \
./Engine/VideoManager.d 


# Each subdirectory must supply rules for building sources it contributes
Engine/%.o: ../Engine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\msys\1.0\home\alienjon\SFML\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


