################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game/CollisionArea.cpp \
../Game/Game.cpp \
../Game/Keywords.cpp \
../Game/Level.cpp \
../Game/Map.cpp \
../Game/Math.cpp \
../Game/Tileset.cpp \
../Game/TilesetManager.cpp 

OBJS += \
./Game/CollisionArea.o \
./Game/Game.o \
./Game/Keywords.o \
./Game/Level.o \
./Game/Map.o \
./Game/Math.o \
./Game/Tileset.o \
./Game/TilesetManager.o 

CPP_DEPS += \
./Game/CollisionArea.d \
./Game/Game.d \
./Game/Keywords.d \
./Game/Level.d \
./Game/Map.d \
./Game/Math.d \
./Game/Tileset.d \
./Game/TilesetManager.d 


# Each subdirectory must supply rules for building sources it contributes
Game/%.o: ../Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\MinGW\msys\1.0\home\alienjon\SFML\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


