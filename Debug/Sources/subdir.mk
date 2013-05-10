################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/GUI.c \
../Sources/animais.c \
../Sources/balao.c \
../Sources/caracteristicas.c \
../Sources/chat.c \
../Sources/colisao.c \
../Sources/comandos.c \
../Sources/equipamentos.c \
../Sources/estruturas.c \
../Sources/fonte.c \
../Sources/interacao.c \
../Sources/lightmap.c \
../Sources/load.c \
../Sources/log.c \
../Sources/magiceflechas.c \
../Sources/main.c \
../Sources/mapas.c \
../Sources/menus.c \
../Sources/menusjogo.c \
../Sources/modoconstrucao.c \
../Sources/monstros.c \
../Sources/msgs.c \
../Sources/npcs.c \
../Sources/online.c \
../Sources/opengl.c \
../Sources/particulas.c \
../Sources/pathfinding.c \
../Sources/personagem.c \
../Sources/pesca.c \
../Sources/tela_carregar.c \
../Sources/tela_jogo.c \
../Sources/tela_modoConstrucao.c \
../Sources/telas.c \
../Sources/temp.c 

OBJS += \
./Sources/GUI.o \
./Sources/animais.o \
./Sources/balao.o \
./Sources/caracteristicas.o \
./Sources/chat.o \
./Sources/colisao.o \
./Sources/comandos.o \
./Sources/equipamentos.o \
./Sources/estruturas.o \
./Sources/fonte.o \
./Sources/interacao.o \
./Sources/lightmap.o \
./Sources/load.o \
./Sources/log.o \
./Sources/magiceflechas.o \
./Sources/main.o \
./Sources/mapas.o \
./Sources/menus.o \
./Sources/menusjogo.o \
./Sources/modoconstrucao.o \
./Sources/monstros.o \
./Sources/msgs.o \
./Sources/npcs.o \
./Sources/online.o \
./Sources/opengl.o \
./Sources/particulas.o \
./Sources/pathfinding.o \
./Sources/personagem.o \
./Sources/pesca.o \
./Sources/tela_carregar.o \
./Sources/tela_jogo.o \
./Sources/tela_modoConstrucao.o \
./Sources/telas.o \
./Sources/temp.o 

C_DEPS += \
./Sources/GUI.d \
./Sources/animais.d \
./Sources/balao.d \
./Sources/caracteristicas.d \
./Sources/chat.d \
./Sources/colisao.d \
./Sources/comandos.d \
./Sources/equipamentos.d \
./Sources/estruturas.d \
./Sources/fonte.d \
./Sources/interacao.d \
./Sources/lightmap.d \
./Sources/load.d \
./Sources/log.d \
./Sources/magiceflechas.d \
./Sources/main.d \
./Sources/mapas.d \
./Sources/menus.d \
./Sources/menusjogo.d \
./Sources/modoconstrucao.d \
./Sources/monstros.d \
./Sources/msgs.d \
./Sources/npcs.d \
./Sources/online.d \
./Sources/opengl.d \
./Sources/particulas.d \
./Sources/pathfinding.d \
./Sources/personagem.d \
./Sources/pesca.d \
./Sources/tela_carregar.d \
./Sources/tela_jogo.d \
./Sources/tela_modoConstrucao.d \
./Sources/telas.d \
./Sources/temp.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


