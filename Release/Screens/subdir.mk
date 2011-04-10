################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Screens/GameScreen.cpp \
../Screens/MenuScreen.cpp \
../Screens/SpriteCreditScreen.cpp 

OBJS += \
./Screens/GameScreen.o \
./Screens/MenuScreen.o \
./Screens/SpriteCreditScreen.o 

CPP_DEPS += \
./Screens/GameScreen.d \
./Screens/MenuScreen.d \
./Screens/SpriteCreditScreen.d 


# Each subdirectory must supply rules for building sources it contributes
Screens/%.o: ../Screens/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


