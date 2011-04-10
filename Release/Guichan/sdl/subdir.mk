################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Guichan/sdl/sdl.cpp \
../Guichan/sdl/sdlgraphics.cpp \
../Guichan/sdl/sdlimage.cpp \
../Guichan/sdl/sdlimageloader.cpp \
../Guichan/sdl/sdlinput.cpp \
../Guichan/sdl/sdltruetypefont.cpp 

OBJS += \
./Guichan/sdl/sdl.o \
./Guichan/sdl/sdlgraphics.o \
./Guichan/sdl/sdlimage.o \
./Guichan/sdl/sdlimageloader.o \
./Guichan/sdl/sdlinput.o \
./Guichan/sdl/sdltruetypefont.o 

CPP_DEPS += \
./Guichan/sdl/sdl.d \
./Guichan/sdl/sdlgraphics.d \
./Guichan/sdl/sdlimage.d \
./Guichan/sdl/sdlimageloader.d \
./Guichan/sdl/sdlinput.d \
./Guichan/sdl/sdltruetypefont.d 


# Each subdirectory must supply rules for building sources it contributes
Guichan/sdl/%.o: ../Guichan/sdl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


