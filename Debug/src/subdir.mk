################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Interface.cpp \
../src/Sudoku.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/Interface.d \
./src/Sudoku.d \
./src/main.d 

OBJS += \
./src/Interface.o \
./src/Sudoku.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Interface.d ./src/Interface.o ./src/Sudoku.d ./src/Sudoku.o ./src/main.d ./src/main.o

.PHONY: clean-src

