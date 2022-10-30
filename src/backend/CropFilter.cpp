/*
 * CropFilter.cpp
 *
 *  Created on: 18 трав. 2022 р.
 *      Author: linukon
 */

#include "CropFilter.h"

namespace backend {
using namespace std;
using namespace vips;

CropFilter::CropFilter() {
}

CropFilter::~CropFilter() {
}

const char* CropFilter::get_name() {
    return "Crop";
}

std::shared_ptr<vips::VImage> CropFilter::process(
        std::optional<std::shared_ptr<vips::VImage>> input_opt) {
    if (input_opt) {
        double dparam[4];
        for (int i = 0; i < 4; i++) {
            auto val = params.get_value(i).value;
            if (!holds_alternative<double>(val)) {
                throw; // ApplicationException
            }
            dparam[i] = get<double>(val);
        }
        VImage &input = *((*input_opt).get());
        int w = input.width();
        int h = input.height();
        int ix = dparam[0] * w;
        int iy = dparam[1] * h;
        int iw = dparam[2] * w;
        int ih = dparam[3] * h;
        auto result = make_shared<VImage>(input.crop(ix, iy, iw, ih));
        validated = true;
        return result;
    }
    throw; // ArgumentException
}

ParamValue CropFilter::get_param_value(int id) {
    return params.get_value(id);
}

void CropFilter::set_param_value(int id, ParamValue val) {
    validated = false;
    return params.set_value(id, val);
}

std::vector<std::pair<ParamInfo, ParamValue>> CropFilter::get_param_list() {
    return params.get_list();
}

void CropFilter::invalidate() {
    validated = false;
}

bool CropFilter::is_validated() {
    return validated;
}
} /* namespace backend */
