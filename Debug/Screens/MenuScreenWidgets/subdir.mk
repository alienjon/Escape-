################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Screens/MenuScreenWidgets/CreditsMenu.cpp \
../Screens/MenuScreenWidgets/MainMenu.cpp \
../Screens/MenuScreenWidgets/NewGameMenu.cpp \
../Screens/MenuScreenWidgets/OptionsMenu.cpp 

OBJS += \
./Screens/MenuScreenWidgets/CreditsMenu.o \
./Screens/MenuScreenWidgets/MainMenu.o \
./Screens/MenuScreenWidgets/NewGameMenu.o \
./Screens/MenuScreenWidgets/OptionsMenu.o 

CPP_DEPS += \
./Screens/MenuScreenWidgets/CreditsMenu.d \
./Screens/MenuScreenWidgets/MainMenu.d \
./Screens/MenuScreenWidgets/NewGameMenu.d \
./Screens/MenuScreenWidgets/OptionsMenu.d 


# Each subdirectory must supply rules for building sources it contributes
Screens/MenuScreenWidgets/%.o: ../Screens/MenuScreenWidgets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\msys\1.0\home\alienjon\SFML\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


