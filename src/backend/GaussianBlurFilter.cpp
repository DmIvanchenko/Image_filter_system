/*
 * GaussianBlurFilter.cpp
 *
 *  Created on: 2022-05-05
 *      Author: linukon
 */

#include "GaussianBlurFilter.h"

namespace backend {
using namespace std;
using namespace vips;

GaussianBlurFilter::GaussianBlurFilter() {
}

GaussianBlurFilter::~GaussianBlurFilter() {
}

const char *GaussianBlurFilter::get_name() {
    return "Gaussian Blur";
}

std::shared_ptr<vips::VImage> GaussianBlurFilter::process(
        std::optional<std::shared_ptr<vips::VImage>> input_opt) {
    if (input_opt) {
        auto val = params.get_value(0).value;
        if (!holds_alternative<double>(val)) {
            throw; // ApplicationException
        }
        double sigma = get<double>(val);
        VImage &input = *((*input_opt).get());
        auto result = std::make_shared<VImage>(
                input.gaussblur(sigma));
        validated = true;
        return result;
    }
    throw; // ArgumentException
}

ParamValue GaussianBlurFilter::get_param_value(int id) {
    return params.get_value(id);
}

void GaussianBlurFilter::set_param_value(int id,
        ParamValue val) {
    validated = false;
    return params.set_value(id, val);
}

std::vector<std::pair<ParamInfo, ParamValue>> GaussianBlurFilter::get_param_list() {
    return params.get_list();
}

void GaussianBlurFilter::invalidate() {
    validated = false;
}

bool GaussianBlurFilter::is_validated() {
    return validated;
}

} /* namespace backend */
