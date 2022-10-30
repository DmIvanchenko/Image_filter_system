/*
 * ParamValue.cpp
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 */

#include "ParamValue.h"

namespace backend {

ParamValue::~ParamValue() {
}

ParamValue ParamValue::double_range(double range) {
    ParamValue v;
    v.type = ParamType::DOUBLE_RANGE;
    v.value = range;
    return v;
}

ParamValue ParamValue::int_range(int value) {
    ParamValue v;
    v.type = ParamType::INT_RANGE;
    v.value = value;
    return v;
}

ParamValue ParamValue::file_path(std::string path) {
    ParamValue v;
    v.type = ParamType::FILE_PATH;
    v.value = path;
    return v;
}

} /* namespace backend */
