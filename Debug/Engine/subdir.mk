################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Engine/Colors.cpp \
../Engine/Cursor.cpp \
../Engine/Logger.cpp \
../Engine/Renderer.cpp \
../Engine/Sprite.cpp \
../Engine/Surface.cpp \
../Engine/Timer.cpp \
../Engine/Viewport.cpp 

OBJS += \
./Engine/Colors.o \
./Engine/Cursor.o \
./Engine/Logger.o \
./Engine/Renderer.o \
./Engine/Sprite.o \
./Engine/Surface.o \
./Engine/Timer.o \
./Engine/Viewport.o 

CPP_DEPS += \
./Engine/Colors.d \
./Engine/Cursor.d \
./Engine/Logger.d \
./Engine/Renderer.d \
./Engine/Sprite.d \
./Engine/Surface.d \
./Engine/Timer.d \
./Engine/Viewport.d 


# Each subdirectory must supply rules for building sources it contributes
Engine/%.o: ../Engine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


