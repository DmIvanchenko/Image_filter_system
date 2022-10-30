/*
 * ImportFilter.cpp
 *
 *  Created on: 2022-05-05
 *      Author: ImageIt
 */

#include "ImportFilter.h"

namespace backend {
using namespace vips;
using namespace std;

ImportFilter::ImportFilter() {

}

ImportFilter::~ImportFilter() {
}

const char *ImportFilter::get_name() {
    return "Import";
}

std::shared_ptr<vips::VImage> ImportFilter::process(
        std::optional<std::shared_ptr<vips::VImage>> input_opt) {
    if (input_opt) {
        throw; // ArgumentException
    }
    auto val = params.get_value(0).value;
    if (!holds_alternative<string>(val)) {
        throw; // ApplicationException
    }
    string inpath = get<string>(val);

    VImage result = VImage::new_from_file(inpath.c_str(),
            VImage::option()->set("access",
                    VIPS_ACCESS_SEQUENTIAL));
    auto result_ptr = make_shared<VImage>(result);
    validated = true;
    return result_ptr;
}

ParamValue ImportFilter::get_param_value(int id) {
    return params.get_value(id);
}

void ImportFilter::set_param_value(int id,
        ParamValue val) {
    validated = false;
    return params.set_value(id, val);
}

std::vector<std::pair<ParamInfo, ParamValue>> ImportFilter::get_param_list() {
    return params.get_list();
}

void ImportFilter::invalidate() {
    validated = false;
}

bool ImportFilter::is_validated() {
    return validated;
}

} /* namespace backend */
