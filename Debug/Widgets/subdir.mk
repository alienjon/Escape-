################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Widgets/FPSDisplayWidget.cpp \
../Widgets/GameOptionsWidget.cpp \
../Widgets/GameOverWidget.cpp \
../Widgets/GameScreenMenuBar.cpp \
../Widgets/LevelCompleteWidget.cpp \
../Widgets/MenuButton.cpp \
../Widgets/MessageDisplayWidget.cpp \
../Widgets/MiniMap.cpp \
../Widgets/SpriteWidget.cpp \
../Widgets/TimerWidget.cpp 

OBJS += \
./Widgets/FPSDisplayWidget.o \
./Widgets/GameOptionsWidget.o \
./Widgets/GameOverWidget.o \
./Widgets/GameScreenMenuBar.o \
./Widgets/LevelCompleteWidget.o \
./Widgets/MenuButton.o \
./Widgets/MessageDisplayWidget.o \
./Widgets/MiniMap.o \
./Widgets/SpriteWidget.o \
./Widgets/TimerWidget.o 

CPP_DEPS += \
./Widgets/FPSDisplayWidget.d \
./Widgets/GameOptionsWidget.d \
./Widgets/GameOverWidget.d \
./Widgets/GameScreenMenuBar.d \
./Widgets/LevelCompleteWidget.d \
./Widgets/MenuButton.d \
./Widgets/MessageDisplayWidget.d \
./Widgets/MiniMap.d \
./Widgets/SpriteWidget.d \
./Widgets/TimerWidget.d 


# Each subdirectory must supply rules for building sources it contributes
Widgets/%.o: ../Widgets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


