/*
 * ParamInfo.cpp
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 *
 */

#include "ParamInfo.h"

namespace backend {

ParamInfo::~ParamInfo() {
}

ParamInfo ParamInfo::double_range(std::string name,
        double range_from, double range_to) {
    ParamInfo p;
    p.name = name;
    p.type = ParamType::DOUBLE_RANGE;
    p.range_from = range_from;
    p.range_to = range_to;
    return p;
}

ParamInfo ParamInfo::int_range(std::string name,
        int irange_from, int irange_to) {
    ParamInfo p;
    p.name = name;
    p.type = ParamType::INT_RANGE;
    p.irange_from = irange_from;
    p.irange_to = irange_to;
    return p;
}

ParamInfo ParamInfo::file_path(std::string name) {
    ParamInfo p;
    p.name = name;
    p.type = ParamType::FILE_PATH;
    return p;
}

} /* namespace backend */
