################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PlotInfo/AddEntityNode.cpp \
../PlotInfo/ConversationNode.cpp \
../PlotInfo/CreatureConfigNode.cpp \
../PlotInfo/DebugNode.cpp \
../PlotInfo/EndGameNode.cpp \
../PlotInfo/EnvironmentNode.cpp \
../PlotInfo/GoToNode.cpp \
../PlotInfo/HoldInputNode.cpp \
../PlotInfo/MessageNode.cpp \
../PlotInfo/MusicNode.cpp \
../PlotInfo/PauseGameNode.cpp \
../PlotInfo/PauseNode.cpp \
../PlotInfo/PlotEvent.cpp \
../PlotInfo/PlotNode.cpp \
../PlotInfo/RemoveEntityNode.cpp \
../PlotInfo/SoundNode.cpp \
../PlotInfo/TaskNode.cpp \
../PlotInfo/WalkToNode.cpp 

OBJS += \
./PlotInfo/AddEntityNode.o \
./PlotInfo/ConversationNode.o \
./PlotInfo/CreatureConfigNode.o \
./PlotInfo/DebugNode.o \
./PlotInfo/EndGameNode.o \
./PlotInfo/EnvironmentNode.o \
./PlotInfo/GoToNode.o \
./PlotInfo/HoldInputNode.o \
./PlotInfo/MessageNode.o \
./PlotInfo/MusicNode.o \
./PlotInfo/PauseGameNode.o \
./PlotInfo/PauseNode.o \
./PlotInfo/PlotEvent.o \
./PlotInfo/PlotNode.o \
./PlotInfo/RemoveEntityNode.o \
./PlotInfo/SoundNode.o \
./PlotInfo/TaskNode.o \
./PlotInfo/WalkToNode.o 

CPP_DEPS += \
./PlotInfo/AddEntityNode.d \
./PlotInfo/ConversationNode.d \
./PlotInfo/CreatureConfigNode.d \
./PlotInfo/DebugNode.d \
./PlotInfo/EndGameNode.d \
./PlotInfo/EnvironmentNode.d \
./PlotInfo/GoToNode.d \
./PlotInfo/HoldInputNode.d \
./PlotInfo/MessageNode.d \
./PlotInfo/MusicNode.d \
./PlotInfo/PauseGameNode.d \
./PlotInfo/PauseNode.d \
./PlotInfo/PlotEvent.d \
./PlotInfo/PlotNode.d \
./PlotInfo/RemoveEntityNode.d \
./PlotInfo/SoundNode.d \
./PlotInfo/TaskNode.d \
./PlotInfo/WalkToNode.d 


# Each subdirectory must supply rules for building sources it contributes
PlotInfo/%.o: ../PlotInfo/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


