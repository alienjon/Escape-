################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/Creature.cpp \
../Entities/Entity.cpp \
../Entities/FlipScreen.cpp \
../Entities/ImageEntity.cpp \
../Entities/KeyEntity.cpp \
../Entities/Pickup.cpp \
../Entities/Player.cpp \
../Entities/Portal.cpp \
../Entities/SpeedChange.cpp \
../Entities/Teleporter.cpp \
../Entities/TimeChange.cpp \
../Entities/ZoomScreen.cpp 

OBJS += \
./Entities/Creature.o \
./Entities/Entity.o \
./Entities/FlipScreen.o \
./Entities/ImageEntity.o \
./Entities/KeyEntity.o \
./Entities/Pickup.o \
./Entities/Player.o \
./Entities/Portal.o \
./Entities/SpeedChange.o \
./Entities/Teleporter.o \
./Entities/TimeChange.o \
./Entities/ZoomScreen.o 

CPP_DEPS += \
./Entities/Creature.d \
./Entities/Entity.d \
./Entities/FlipScreen.d \
./Entities/ImageEntity.d \
./Entities/KeyEntity.d \
./Entities/Pickup.d \
./Entities/Player.d \
./Entities/Portal.d \
./Entities/SpeedChange.d \
./Entities/Teleporter.d \
./Entities/TimeChange.d \
./Entities/ZoomScreen.d 


# Each subdirectory must supply rules for building sources it contributes
Entities/%.o: ../Entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\msys\1.0\home\alienjon\SFML\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


