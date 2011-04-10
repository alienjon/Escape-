################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/Alignment.cpp \
../Entities/Entity.cpp \
../Entities/EntityType.cpp 

OBJS += \
./Entities/Alignment.o \
./Entities/Entity.o \
./Entities/EntityType.o 

CPP_DEPS += \
./Entities/Alignment.d \
./Entities/Entity.d \
./Entities/EntityType.d 


# Each subdirectory must supply rules for building sources it contributes
Entities/%.o: ../Entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


