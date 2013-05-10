################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Agrupador.c \
../EditorMapa.c \
../GUI.c \
../LightMap.c \
../estruturas.c \
../fonte.c \
../load.c \
../log.c \
../main.c \
../mapa.c \
../opengl.c \
../png.c \
../util.c 

OBJS += \
./Agrupador.o \
./EditorMapa.o \
./GUI.o \
./LightMap.o \
./estruturas.o \
./fonte.o \
./load.o \
./log.o \
./main.o \
./mapa.o \
./opengl.o \
./png.o \
./util.o 

C_DEPS += \
./Agrupador.d \
./EditorMapa.d \
./GUI.d \
./LightMap.d \
./estruturas.d \
./fonte.d \
./load.d \
./log.d \
./main.d \
./mapa.d \
./opengl.d \
./png.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


