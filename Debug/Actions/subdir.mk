################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Actions/DebugAction.cpp \
../Actions/DisplayMessageAction.cpp \
../Actions/DisplaySpriteAction.cpp \
../Actions/FastSearchAction.cpp \
../Actions/MoveToAction.cpp \
../Actions/MultipleActionsAction.cpp \
../Actions/PauseAction.cpp \
../Actions/PlayMusicAction.cpp \
../Actions/PlaySoundAction.cpp \
../Actions/SetSpeedAction.cpp \
../Actions/SetWanderAction.cpp \
../Actions/SetWidgetVisibilityAction.cpp \
../Actions/WanderAction.cpp 

OBJS += \
./Actions/DebugAction.o \
./Actions/DisplayMessageAction.o \
./Actions/DisplaySpriteAction.o \
./Actions/FastSearchAction.o \
./Actions/MoveToAction.o \
./Actions/MultipleActionsAction.o \
./Actions/PauseAction.o \
./Actions/PlayMusicAction.o \
./Actions/PlaySoundAction.o \
./Actions/SetSpeedAction.o \
./Actions/SetWanderAction.o \
./Actions/SetWidgetVisibilityAction.o \
./Actions/WanderAction.o 

CPP_DEPS += \
./Actions/DebugAction.d \
./Actions/DisplayMessageAction.d \
./Actions/DisplaySpriteAction.d \
./Actions/FastSearchAction.d \
./Actions/MoveToAction.d \
./Actions/MultipleActionsAction.d \
./Actions/PauseAction.d \
./Actions/PlayMusicAction.d \
./Actions/PlaySoundAction.d \
./Actions/SetSpeedAction.d \
./Actions/SetWanderAction.d \
./Actions/SetWidgetVisibilityAction.d \
./Actions/WanderAction.d 


# Each subdirectory must supply rules for building sources it contributes
Actions/%.o: ../Actions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\msys\1.0\home\alienjon\SFML\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


