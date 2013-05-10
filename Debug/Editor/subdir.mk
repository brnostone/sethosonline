################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Editor/Agrupador.c \
../Editor/EditorMapa.c \
../Editor/GUI.c \
../Editor/LightMap.c \
../Editor/estruturas.c \
../Editor/fonte.c \
../Editor/load.c \
../Editor/log.c \
../Editor/main.c \
../Editor/mapa.c \
../Editor/opengl.c \
../Editor/png.c \
../Editor/util.c 

OBJS += \
./Editor/Agrupador.o \
./Editor/EditorMapa.o \
./Editor/GUI.o \
./Editor/LightMap.o \
./Editor/estruturas.o \
./Editor/fonte.o \
./Editor/load.o \
./Editor/log.o \
./Editor/main.o \
./Editor/mapa.o \
./Editor/opengl.o \
./Editor/png.o \
./Editor/util.o 

C_DEPS += \
./Editor/Agrupador.d \
./Editor/EditorMapa.d \
./Editor/GUI.d \
./Editor/LightMap.d \
./Editor/estruturas.d \
./Editor/fonte.d \
./Editor/load.d \
./Editor/log.d \
./Editor/main.d \
./Editor/mapa.d \
./Editor/opengl.d \
./Editor/png.d \
./Editor/util.d 


# Each subdirectory must supply rules for building sources it contributes
Editor/%.o: ../Editor/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


