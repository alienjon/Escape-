################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Widgets/FPSDisplayWidget.cpp \
../Widgets/GUIMessageWidget.cpp \
../Widgets/GameOptionsListModel.cpp \
../Widgets/GameOptionsWidget.cpp \
../Widgets/GameOverWidget.cpp \
../Widgets/HealthBarContainer.cpp \
../Widgets/HealthWidget.cpp \
../Widgets/LetterGUIWidget.cpp \
../Widgets/MenuButton.cpp \
../Widgets/MessageDisplayWidget.cpp \
../Widgets/SpriteWidget.cpp 

OBJS += \
./Widgets/FPSDisplayWidget.o \
./Widgets/GUIMessageWidget.o \
./Widgets/GameOptionsListModel.o \
./Widgets/GameOptionsWidget.o \
./Widgets/GameOverWidget.o \
./Widgets/HealthBarContainer.o \
./Widgets/HealthWidget.o \
./Widgets/LetterGUIWidget.o \
./Widgets/MenuButton.o \
./Widgets/MessageDisplayWidget.o \
./Widgets/SpriteWidget.o 

CPP_DEPS += \
./Widgets/FPSDisplayWidget.d \
./Widgets/GUIMessageWidget.d \
./Widgets/GameOptionsListModel.d \
./Widgets/GameOptionsWidget.d \
./Widgets/GameOverWidget.d \
./Widgets/HealthBarContainer.d \
./Widgets/HealthWidget.d \
./Widgets/LetterGUIWidget.d \
./Widgets/MenuButton.d \
./Widgets/MessageDisplayWidget.d \
./Widgets/SpriteWidget.d 


# Each subdirectory must supply rules for building sources it contributes
Widgets/%.o: ../Widgets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


