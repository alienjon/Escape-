################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MapInfo/Map.cpp \
../MapInfo/MapData.cpp \
../MapInfo/MapRule.cpp 

OBJS += \
./MapInfo/Map.o \
./MapInfo/MapData.o \
./MapInfo/MapRule.o 

CPP_DEPS += \
./MapInfo/Map.d \
./MapInfo/MapData.d \
./MapInfo/MapRule.d 


# Each subdirectory must supply rules for building sources it contributes
MapInfo/%.o: ../MapInfo/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


