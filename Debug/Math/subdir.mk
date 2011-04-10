################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Math/Base64Functions.cpp \
../Math/Ellipse.cpp \
../Math/Math.cpp \
../Math/Polygon.cpp \
../Math/Quadrilateral.cpp \
../Math/Rectangle.cpp \
../Math/Vector.cpp 

OBJS += \
./Math/Base64Functions.o \
./Math/Ellipse.o \
./Math/Math.o \
./Math/Polygon.o \
./Math/Quadrilateral.o \
./Math/Rectangle.o \
./Math/Vector.o 

CPP_DEPS += \
./Math/Base64Functions.d \
./Math/Ellipse.d \
./Math/Math.d \
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


