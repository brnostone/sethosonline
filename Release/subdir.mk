################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GUI.c \
../animais.c \
../ataca.c \
../balao.c \
../caracteristicas.c \
../chat.c \
../colisao.c \
../comandos.c \
../crypto.c \
../equipamentos.c \
../estruturas.c \
../fechas.c \
../fonte.c \
../guiitens.c \
../interacao.c \
../lightmap.c \
../load.c \
../log.c \
../magicas.c \
../main.c \
../mapas.c \
../menus.c \
../menusjogo.c \
../modoconstrucao.c \
../monstros.c \
../msgs.c \
../npcs.c \
../online.c \
../opengl.c \
../particulas.c \
../pathfinding.c \
../personagem.c \
../pesca.c \
../tela_carregar.c \
../tela_jogo.c \
../tela_modoConstrucao.c \
../telas.c \
../util.c 

OBJS += \
./GUI.o \
./animais.o \
./ataca.o \
./balao.o \
./caracteristicas.o \
./chat.o \
./colisao.o \
./comandos.o \
./crypto.o \
./equipamentos.o \
./estruturas.o \
./fechas.o \
./fonte.o \
./guiitens.o \
./interacao.o \
./lightmap.o \
./load.o \
./log.o \
./magicas.o \
./main.o \
./mapas.o \
./menus.o \
./menusjogo.o \
./modoconstrucao.o \
./monstros.o \
./msgs.o \
./npcs.o \
./online.o \
./opengl.o \
./particulas.o \
./pathfinding.o \
./personagem.o \
./pesca.o \
./tela_carregar.o \
./tela_jogo.o \
./tela_modoConstrucao.o \
./telas.o \
./util.o 

C_DEPS += \
./GUI.d \
./animais.d \
./ataca.d \
./balao.d \
./caracteristicas.d \
./chat.d \
./colisao.d \
./comandos.d \
./crypto.d \
./equipamentos.d \
./estruturas.d \
./fechas.d \
./fonte.d \
./guiitens.d \
./interacao.d \
./lightmap.d \
./load.d \
./log.d \
./magicas.d \
./main.d \
./mapas.d \
./menus.d \
./menusjogo.d \
./modoconstrucao.d \
./monstros.d \
./msgs.d \
./npcs.d \
./online.d \
./opengl.d \
./particulas.d \
./pathfinding.d \
./personagem.d \
./pesca.d \
./tela_carregar.d \
./tela_jogo.d \
./tela_modoConstrucao.d \
./telas.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


