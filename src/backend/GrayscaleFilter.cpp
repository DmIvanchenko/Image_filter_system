/*
 * GrayscaleFilter.cpp
 *
 *  Created on: 2022-05-05
 *      Author: ImageIt
 */

#include "GrayscaleFilter.h"

namespace backend {
using namespace vips;
using namespace std;

GrayscaleFilter::GrayscaleFilter() {
}

GrayscaleFilter::~GrayscaleFilter() {
}

const char *GrayscaleFilter::get_name() {
    return "Grayscale";
}

std::shared_ptr<vips::VImage> GrayscaleFilter::process(
        std::optional<std::shared_ptr<vips::VImage>> input_opt) {
    if (input_opt) {
        const int BANDS = 3;
        double band[BANDS]; // band strength values
        for (int i = 0; i < BANDS; i++) {
            if (!holds_alternative<double>(
                    params.get_value(i).value)) {
                throw; // ApplicationException
            }
            band[i] = get<double>(params.get_value(i).value);
        }

        double band_sum = band[0] + band[1] + band[2];
        if (band_sum == 0) {
            throw; // ArgumentException
        }
        VImage &input = *((*input_opt).get());
        VImage result = (input[0] * (band[0] / band_sum))
                + (input[1] * (band[1] / band_sum))
                + (input[2] * (band[2] / band_sum)) / 3;
        auto result_ptr = make_shared<VImage>(result);
        validated = true;
        return result_ptr;
    }
    throw; // ArgumentException
}

ParamValue GrayscaleFilter::get_param_value(int id) {
    return params.get_value(id);
}

void GrayscaleFilter::set_param_value(int id,
        ParamValue val) {
    validated = false;
    return params.set_value(id, val);
}

std::vector<std::pair<ParamInfo, ParamValue>> GrayscaleFilter::get_param_list() {
    return params.get_list();
}

void GrayscaleFilter::invalidate() {
    validated = false;
}

bool GrayscaleFilter::is_validated() {
    return validated;
}

} /* namespace backend */
