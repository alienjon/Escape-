################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Screens/MenuScreenWidgets/LoadGame/LoadGameListModel.cpp 

OBJS += \
./Screens/MenuScreenWidgets/LoadGame/LoadGameListModel.o 

CPP_DEPS += \
./Screens/MenuScreenWidgets/LoadGame/LoadGameListModel.d 


# Each subdirectory must supply rules for building sources it contributes
Screens/MenuScreenWidgets/LoadGame/%.o: ../Screens/MenuScreenWidgets/LoadGame/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


