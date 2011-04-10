################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/Non-Creatures/Flashlight.cpp \
../Entities/Non-Creatures/Item.cpp \
../Entities/Non-Creatures/Letter.cpp \
../Entities/Non-Creatures/NonDisplayingEntity.cpp \
../Entities/Non-Creatures/Object.cpp \
../Entities/Non-Creatures/Tile.cpp 

OBJS += \
./Entities/Non-Creatures/Flashlight.o \
./Entities/Non-Creatures/Item.o \
./Entities/Non-Creatures/Letter.o \
./Entities/Non-Creatures/NonDisplayingEntity.o \
./Entities/Non-Creatures/Object.o \
./Entities/Non-Creatures/Tile.o 

CPP_DEPS += \
./Entities/Non-Creatures/Flashlight.d \
./Entities/Non-Creatures/Item.d \
./Entities/Non-Creatures/Letter.d \
./Entities/Non-Creatures/NonDisplayingEntity.d \
./Entities/Non-Creatures/Object.d \
./Entities/Non-Creatures/Tile.d 


# Each subdirectory must supply rules for building sources it contributes
Entities/Non-Creatures/%.o: ../Entities/Non-Creatures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


