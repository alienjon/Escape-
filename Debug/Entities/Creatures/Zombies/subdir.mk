################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/Creatures/Zombies/GreenZombie.cpp \
../Entities/Creatures/Zombies/PinkZombie.cpp \
../Entities/Creatures/Zombies/RedZombie.cpp \
../Entities/Creatures/Zombies/Zombie.cpp 

OBJS += \
./Entities/Creatures/Zombies/GreenZombie.o \
./Entities/Creatures/Zombies/PinkZombie.o \
./Entities/Creatures/Zombies/RedZombie.o \
./Entities/Creatures/Zombies/Zombie.o 

CPP_DEPS += \
./Entities/Creatures/Zombies/GreenZombie.d \
./Entities/Creatures/Zombies/PinkZombie.d \
./Entities/Creatures/Zombies/RedZombie.d \
./Entities/Creatures/Zombies/Zombie.d 


# Each subdirectory must supply rules for building sources it contributes
Entities/Creatures/Zombies/%.o: ../Entities/Creatures/Zombies/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


