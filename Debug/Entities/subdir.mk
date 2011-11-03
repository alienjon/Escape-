################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/Creature.cpp \
../Entities/Entity.cpp \
../Entities/KeyEntity.cpp \
../Entities/Pickup.cpp \
../Entities/Player.cpp \
../Entities/Portal.cpp 

OBJS += \
./Entities/Creature.o \
./Entities/Entity.o \
./Entities/KeyEntity.o \
./Entities/Pickup.o \
./Entities/Player.o \
./Entities/Portal.o 

CPP_DEPS += \
./Entities/Creature.d \
./Entities/Entity.d \
./Entities/KeyEntity.d \
./Entities/Pickup.d \
./Entities/Player.d \
./Entities/Portal.d 


# Each subdirectory must supply rules for building sources it contributes
Entities/%.o: ../Entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


