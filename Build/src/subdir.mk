# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/imageit.cpp 

CPP_DEPS += \
./src/imageit.d 

OBJS += \
./src/imageit.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 `pkg-config --cflags gtkmm-3.0 vips-cpp` -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/imageit.d ./src/imageit.o

.PHONY: clean-src

