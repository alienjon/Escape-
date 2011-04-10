################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Guichan/actionevent.cpp \
../Guichan/basiccontainer.cpp \
../Guichan/cliprectangle.cpp \
../Guichan/color.cpp \
../Guichan/defaultfont.cpp \
../Guichan/event.cpp \
../Guichan/exception.cpp \
../Guichan/focushandler.cpp \
../Guichan/font.cpp \
../Guichan/genericinput.cpp \
../Guichan/graphics.cpp \
../Guichan/gui.cpp \
../Guichan/guichan.cpp \
../Guichan/image.cpp \
../Guichan/imagefont.cpp \
../Guichan/inputevent.cpp \
../Guichan/key.cpp \
../Guichan/keyevent.cpp \
../Guichan/keyinput.cpp \
../Guichan/mouseevent.cpp \
../Guichan/mouseinput.cpp \
../Guichan/rectangle.cpp \
../Guichan/selectionevent.cpp \
../Guichan/widget.cpp 

OBJS += \
./Guichan/actionevent.o \
./Guichan/basiccontainer.o \
./Guichan/cliprectangle.o \
./Guichan/color.o \
./Guichan/defaultfont.o \
./Guichan/event.o \
./Guichan/exception.o \
./Guichan/focushandler.o \
./Guichan/font.o \
./Guichan/genericinput.o \
./Guichan/graphics.o \
./Guichan/gui.o \
./Guichan/guichan.o \
./Guichan/image.o \
./Guichan/imagefont.o \
./Guichan/inputevent.o \
./Guichan/key.o \
./Guichan/keyevent.o \
./Guichan/keyinput.o \
./Guichan/mouseevent.o \
./Guichan/mouseinput.o \
./Guichan/rectangle.o \
./Guichan/selectionevent.o \
./Guichan/widget.o 

CPP_DEPS += \
./Guichan/actionevent.d \
./Guichan/basiccontainer.d \
./Guichan/cliprectangle.d \
./Guichan/color.d \
./Guichan/defaultfont.d \
./Guichan/event.d \
./Guichan/exception.d \
./Guichan/focushandler.d \
./Guichan/font.d \
./Guichan/genericinput.d \
./Guichan/graphics.d \
./Guichan/gui.d \
./Guichan/guichan.d \
./Guichan/image.d \
./Guichan/imagefont.d \
./Guichan/inputevent.d \
./Guichan/key.d \
./Guichan/keyevent.d \
./Guichan/keyinput.d \
./Guichan/mouseevent.d \
./Guichan/mouseinput.d \
./Guichan/rectangle.d \
./Guichan/selectionevent.d \
./Guichan/widget.d 


# Each subdirectory must supply rules for building sources it contributes
Guichan/%.o: ../Guichan/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


