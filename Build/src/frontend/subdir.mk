# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/frontend/frontend.cpp 

CPP_DEPS += \
./src/frontend/frontend.d 

OBJS += \
./src/frontend/frontend.o 


# Each subdirectory must supply rules for building sources it contributes
src/frontend/%.o: ../src/frontend/%.cpp src/frontend/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 `pkg-config --cflags gtkmm-3.0 vips-cpp` -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-frontend

clean-src-2f-frontend:
	-$(RM) `find ./src/frontend -type f -name *.[do]`

.PHONY: clean-src-2f-frontend

