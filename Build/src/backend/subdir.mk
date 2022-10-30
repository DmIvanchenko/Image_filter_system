################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/CropFilter.cpp \
../src/backend/ExposureFilter.cpp \
../src/backend/FilterBase.cpp \
../src/backend/GaussianBlurFilter.cpp \
../src/backend/GrayscaleFilter.cpp \
../src/backend/ImageResult.cpp \
../src/backend/ImportFilter.cpp \
../src/backend/Node.cpp \
../src/backend/ParamInfo.cpp \
../src/backend/ParamList.cpp \
../src/backend/ParamValue.cpp \
../src/backend/Pipeline.cpp \
../src/backend/RotateFilter.cpp 

CPP_DEPS += \
./src/backend/CropFilter.d \
./src/backend/ExposureFilter.d \
./src/backend/FilterBase.d \
./src/backend/GaussianBlurFilter.d \
./src/backend/GrayscaleFilter.d \
./src/backend/ImageResult.d \
./src/backend/ImportFilter.d \
./src/backend/Node.d \
./src/backend/ParamInfo.d \
./src/backend/ParamList.d \
./src/backend/ParamValue.d \
./src/backend/Pipeline.d \
./src/backend/RotateFilter.d 

OBJS += \
./src/backend/CropFilter.o \
./src/backend/ExposureFilter.o \
./src/backend/FilterBase.o \
./src/backend/GaussianBlurFilter.o \
./src/backend/GrayscaleFilter.o \
./src/backend/ImageResult.o \
./src/backend/ImportFilter.o \
./src/backend/Node.o \
./src/backend/ParamInfo.o \
./src/backend/ParamList.o \
./src/backend/ParamValue.o \
./src/backend/Pipeline.o \
./src/backend/RotateFilter.o 


# Each subdirectory must supply rules for building sources it contributes
src/backend/%.o: ../src/backend/%.cpp src/backend/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 `pkg-config --cflags gtkmm-3.0 vips-cpp` -O0 -g3 -Wall -c -fmessage-length=0 -std=c++17 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-backend

clean-src-2f-backend:
	-$(RM) `find ./src/backend -type f -name *.[do]`

.PHONY: clean-src-2f-backend

