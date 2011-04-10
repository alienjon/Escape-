################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Interfaces/ActionInterface.cpp \
../Interfaces/EnvironmentInterface.cpp \
../Interfaces/EventInterface.cpp \
../Interfaces/GameInterfaceInterface.cpp 

OBJS += \
./Interfaces/ActionInterface.o \
./Interfaces/EnvironmentInterface.o \
./Interfaces/EventInterface.o \
./Interfaces/GameInterfaceInterface.o 

CPP_DEPS += \
./Interfaces/ActionInterface.d \
./Interfaces/EnvironmentInterface.d \
./Interfaces/EventInterface.d \
./Interfaces/GameInterfaceInterface.d 


# Each subdirectory must supply rules for building sources it contributes
Interfaces/%.o: ../Interfaces/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


