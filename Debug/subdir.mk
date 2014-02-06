################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../camera.cpp \
../main.cpp \
../opengl.cpp \
../vector3d.cpp 

OBJS += \
./camera.o \
./main.o \
./opengl.o \
./vector3d.o 

CPP_DEPS += \
./camera.d \
./main.d \
./opengl.d \
./vector3d.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/bullet -I/usr/include/boost -I/usr/include/ois -I/usr/local/include/OGRE -I/usr/local/include/OGRE/Overlay -I/usr/local/include/OGRE/Terrain -O0 -g3 -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


