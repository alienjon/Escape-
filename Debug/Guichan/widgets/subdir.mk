################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Guichan/widgets/adjustingcontainer.cpp \
../Guichan/widgets/button.cpp \
../Guichan/widgets/checkbox.cpp \
../Guichan/widgets/container.cpp \
../Guichan/widgets/dropdown.cpp \
../Guichan/widgets/icon.cpp \
../Guichan/widgets/imagebutton.cpp \
../Guichan/widgets/label.cpp \
../Guichan/widgets/listbox.cpp \
../Guichan/widgets/radiobutton.cpp \
../Guichan/widgets/scrollarea.cpp \
../Guichan/widgets/slider.cpp \
../Guichan/widgets/tab.cpp \
../Guichan/widgets/tabbedarea.cpp \
../Guichan/widgets/textbox.cpp \
../Guichan/widgets/textfield.cpp \
../Guichan/widgets/window.cpp 

OBJS += \
./Guichan/widgets/adjustingcontainer.o \
./Guichan/widgets/button.o \
./Guichan/widgets/checkbox.o \
./Guichan/widgets/container.o \
./Guichan/widgets/dropdown.o \
./Guichan/widgets/icon.o \
./Guichan/widgets/imagebutton.o \
./Guichan/widgets/label.o \
./Guichan/widgets/listbox.o \
./Guichan/widgets/radiobutton.o \
./Guichan/widgets/scrollarea.o \
./Guichan/widgets/slider.o \
./Guichan/widgets/tab.o \
./Guichan/widgets/tabbedarea.o \
./Guichan/widgets/textbox.o \
./Guichan/widgets/textfield.o \
./Guichan/widgets/window.o 

CPP_DEPS += \
./Guichan/widgets/adjustingcontainer.d \
./Guichan/widgets/button.d \
./Guichan/widgets/checkbox.d \
./Guichan/widgets/container.d \
./Guichan/widgets/dropdown.d \
./Guichan/widgets/icon.d \
./Guichan/widgets/imagebutton.d \
./Guichan/widgets/label.d \
./Guichan/widgets/listbox.d \
./Guichan/widgets/radiobutton.d \
./Guichan/widgets/scrollarea.d \
./Guichan/widgets/slider.d \
./Guichan/widgets/tab.d \
./Guichan/widgets/tabbedarea.d \
./Guichan/widgets/textbox.d \
./Guichan/widgets/textfield.d \
./Guichan/widgets/window.d 


# Each subdirectory must supply rules for building sources it contributes
Guichan/widgets/%.o: ../Guichan/widgets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


