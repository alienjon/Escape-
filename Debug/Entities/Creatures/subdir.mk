################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/Creatures/Creature.cpp \
../Entities/Creatures/Enemy.cpp \
../Entities/Creatures/Player.cpp 

OBJS += \
./Entities/Creatures/Creature.o \
./Entities/Creatures/Enemy.o \
./Entities/Creatures/Player.o 

CPP_DEPS += \
./Entities/Creatures/Creature.d \
./Entities/Creatures/Enemy.d \
./Entities/Creatures/Player.d 


# Each subdirectory must supply rules for building sources it contributes
Entities/Creatures/%.o: ../Entities/Creatures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


