/*
 * GrayscaleFilter.h
 *
 *  Created on: 2022-05-05
 *      Author: ImageIt
 */

#ifndef GRAYSCALEFILTER_H_
#define GRAYSCALEFILTER_H_

#include "FilterBase.h"
#include "ParamList.h"

namespace backend {

class GrayscaleFilter: public FilterBase {
public:
    GrayscaleFilter();
    virtual ~GrayscaleFilter();

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
            ParamInfo::double_range("Red", 0, 1),
            ParamValue::double_range(1)), std::make_pair(
            ParamInfo::double_range("Green", 0, 1),
            ParamValue::double_range(1)), std::make_pair(
            ParamInfo::double_range("Blue", 0, 1),
            ParamValue::double_range(1)) } };
    bool validated = false;
};

} /* namespace backend */

#endif /* GRAYSCALEFILTER_H_ */
