/*
 * ExposureFilter.cpp
 *
 *  Created on: 2022-05-05
 *      Author: ImageIt
 */

#include "ExposureFilter.h"

namespace backend {
using namespace std;
using namespace vips;

ExposureFilter::ExposureFilter() {
}

ExposureFilter::~ExposureFilter() {
}

const char *ExposureFilter::get_name() {
    return "Exposure";
}

std::shared_ptr<vips::VImage> ExposureFilter::process(
        std::optional<std::shared_ptr<vips::VImage>> input_opt) {
    if (input_opt) {
        double dparam[2];
        for (int i = 0; i < 2; i++) {
            auto val = params.get_value(i).value;
            if (!holds_alternative<double>(val)) {
                throw; // ApplicationException
            }
            dparam[i] = get<double>(val);
        }
        VImage &input = *((*input_opt).get());

        // Linear brightness-contrast adjustment:
        // https://www.desmos.com/calculator/rhsfevsr2f
        // See also: CIELAB adjustments
        double contrast = dparam[1];
        double brightness = dparam[0];
        const double EXPO_Q = 256.0; // p = q = 256 for srgb
        double expo_a = exp(contrast);
        double expo_b = EXPO_Q
                * (brightness
                        - ((exp(contrast) - 1.0) / 2.0));
        auto result = make_shared<VImage>(
                input.linear(expo_a, expo_b));
        validated = true;
        return result;
    }
    throw; // ArgumentException
}

ParamValue ExposureFilter::get_param_value(int id) {
    return params.get_value(id);
}

void ExposureFilter::set_param_value(int id,
        ParamValue val) {
    validated = false;
    return params.set_value(id, val);
}

std::vector<std::pair<ParamInfo, ParamValue>> ExposureFilter::get_param_list() {
    return params.get_list();
}

void ExposureFilter::invalidate() {
    validated = false;
}

bool ExposureFilter::is_validated() {
    return validated;
}

} /* namespace backend */
