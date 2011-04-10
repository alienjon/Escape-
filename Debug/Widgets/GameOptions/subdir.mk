################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Widgets/GameOptions/GameSettingsWidget.cpp \
../Widgets/GameOptions/MessageWidget.cpp \
../Widgets/GameOptions/MessagesWidget.cpp \
../Widgets/GameOptions/TaskWidget.cpp \
../Widgets/GameOptions/TasksContainerWidget.cpp \
../Widgets/GameOptions/TasksWidget.cpp 

OBJS += \
./Widgets/GameOptions/GameSettingsWidget.o \
./Widgets/GameOptions/MessageWidget.o \
./Widgets/GameOptions/MessagesWidget.o \
./Widgets/GameOptions/TaskWidget.o \
./Widgets/GameOptions/TasksContainerWidget.o \
./Widgets/GameOptions/TasksWidget.o 

CPP_DEPS += \
./Widgets/GameOptions/GameSettingsWidget.d \
./Widgets/GameOptions/MessageWidget.d \
./Widgets/GameOptions/MessagesWidget.d \
./Widgets/GameOptions/TaskWidget.d \
./Widgets/GameOptions/TasksContainerWidget.d \
./Widgets/GameOptions/TasksWidget.d 


# Each subdirectory must supply rules for building sources it contributes
Widgets/GameOptions/%.o: ../Widgets/GameOptions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


