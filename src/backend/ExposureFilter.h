/*
 * ExposureFilter.h
 *
 *  Created on: 2022-05-05
 *      Author: ImageIt
 */

#ifndef EXPOSUREFILTER_H_
#define EXPOSUREFILTER_H_

#include "FilterBase.h"
#include "ParamList.h"

namespace backend {

class ExposureFilter: public FilterBase {
public:
    ExposureFilter();
    virtual ~ExposureFilter();

    // -- implementation of FilterBase -- {
    const char *get_name();
    std::shared_ptr<vips::VImage> process(
            std::optional<std::shared_ptr<vips::VImage>> input_opt);
    ParamValue get_param_value(int id);
    void set_param_value(int id, ParamValue val);
    std::vector<std::pair<ParamInfo, ParamValue>> get_param_list();
    void invalidate();
    bool is_validated();
    // -- }

private:
    ParamList params { { std::make_pair(
            ParamInfo::double_range("Brightness", -2, 2),
            ParamValue::double_range(0)), std::make_pair(
            ParamInfo::double_range("Contrast", -2, 2),
            ParamValue::double_range(0)) } };
    bool validated = false;
};

} /* namespace backend */

#endif /* EXPOSUREFILTER_H_ */
