################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Triggers/ExplodingTrigger.cpp \
../Triggers/LoadLevelTrigger.cpp \
../Triggers/Trigger.cpp 

OBJS += \
./Triggers/ExplodingTrigger.o \
./Triggers/LoadLevelTrigger.o \
./Triggers/Trigger.o 

CPP_DEPS += \
./Triggers/ExplodingTrigger.d \
./Triggers/LoadLevelTrigger.d \
./Triggers/Trigger.d 


# Each subdirectory must supply rules for building sources it contributes
Triggers/%.o: ../Triggers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


