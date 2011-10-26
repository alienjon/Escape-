################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Math/CollisionArea.cpp \
../Math/Math.cpp \
../Math/Point.cpp \
../Math/Polygon.cpp \
../Math/Quadrilateral.cpp \
../Math/Rectangle.cpp \
../Math/Vector.cpp 

OBJS += \
./Math/CollisionArea.o \
./Math/Math.o \
./Math/Point.o \
./Math/Polygon.o \
./Math/Quadrilateral.o \
./Math/Rectangle.o \
./Math/Vector.o 

CPP_DEPS += \
./Math/CollisionArea.d \
./Math/Math.d \
./Math/Point.d \
./Math/Polygon.d \
./Math/Quadrilateral.d \
./Math/Rectangle.d \
./Math/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
Math/%.o: ../Math/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


