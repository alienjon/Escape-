################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Guichan/opengl/oglftfont.cpp \
../Guichan/opengl/opengl.cpp \
../Guichan/opengl/openglgraphics.cpp \
../Guichan/opengl/openglimage.cpp 

OBJS += \
./Guichan/opengl/oglftfont.o \
./Guichan/opengl/opengl.o \
./Guichan/opengl/openglgraphics.o \
./Guichan/opengl/openglimage.o 

CPP_DEPS += \
./Guichan/opengl/oglftfont.d \
./Guichan/opengl/opengl.d \
./Guichan/opengl/openglgraphics.d \
./Guichan/opengl/openglimage.d 


# Each subdirectory must supply rules for building sources it contributes
Guichan/opengl/%.o: ../Guichan/opengl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


