/*
 * RotateFilter.cpp
 *
 *  Created on: 18 трав. 2022 р.
 *      Author: linukon
 */

#include "RotateFilter.h"

namespace backend {
using namespace std;
using namespace vips;

RotateFilter::RotateFilter() {
}

RotateFilter::~RotateFilter() {
}

const char* RotateFilter::get_name() {
    return "Rotate";
}

std::shared_ptr<vips::VImage> RotateFilter::process(
        std::optional<std::shared_ptr<vips::VImage>> input_opt) {
    const VipsAngle VANGLE[] =
            { VIPS_ANGLE_D0, VIPS_ANGLE_D90,
                    VIPS_ANGLE_D180, VIPS_ANGLE_D270 };
    if (input_opt) {
        auto param = params.get_value(0).value;
        if (!holds_alternative<int>(param)) {
            throw; // ApplicationException
        }
        int val = get<int>(param);
        VImage &input = *((*input_opt).get());
        auto result = make_shared<VImage>(
                input.rot(VANGLE[val]));
        validated = true;
        return result;
    }
    throw; // ArgumentException
}

ParamValue RotateFilter::get_param_value(int id) {
    return params.get_value(id);
}

void RotateFilter::set_param_value(int id, ParamValue val) {
    validated = false;
    return params.set_value(id, val);
}

std::vector<std::pair<ParamInfo, ParamValue>> RotateFilter::get_param_list() {
    return params.get_list();
}

void RotateFilter::invalidate() {
    validated = false;
}

bool RotateFilter::is_validated() {
    return validated;
}
} /* namespace backend */
