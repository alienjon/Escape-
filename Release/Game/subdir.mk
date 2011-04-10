################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game/Direction.cpp \
../Game/EnvironmentData.cpp \
../Game/GUI.cpp \
../Game/Game.cpp \
../Game/GameData.cpp \
../Game/Input.cpp \
../Game/Keywords.cpp \
../Game/TileData.cpp \
../Game/TileType.cpp \
../Game/Tileset.cpp 

OBJS += \
./Game/Direction.o \
./Game/EnvironmentData.o \
./Game/GUI.o \
./Game/Game.o \
./Game/GameData.o \
./Game/Input.o \
./Game/Keywords.o \
./Game/TileData.o \
./Game/TileType.o \
./Game/Tileset.o 

CPP_DEPS += \
./Game/Direction.d \
./Game/EnvironmentData.d \
./Game/GUI.d \
./Game/Game.d \
./Game/GameData.d \
./Game/Input.d \
./Game/Keywords.d \
./Game/TileData.d \
./Game/TileType.d \
./Game/Tileset.d 


# Each subdirectory must supply rules for building sources it contributes
Game/%.o: ../Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


