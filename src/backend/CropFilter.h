/*
 * CropFilter.h
 *
 *  Created on: 18 трав. 2022 р.
 *      Author: ImageIt
 */

#ifndef CROPFILTER_H_
#define CROPFILTER_H_

#include "FilterBase.h"
#include "ParamList.h"

namespace backend {

class CropFilter: public FilterBase {
public:
    CropFilter();
    virtual ~CropFilter();

    // -- implementation of FilterBase -- {
    const char* get_name();
    std::shared_ptr<vips::VImage> process(
            std::optional<std::shared_ptr<vips::VImage>> input_opt);
    ParamValue get_param_value(int id);
    void set_param_value(int id, ParamValue val);
    std::vector<std::pair<ParamInfo, ParamValue>> get_param_list();
    void invalidate();
    bool is_validated();
    // -- }

private:
    // At the time of writing, the image measures are relative.
    // (0;0) denotes the top-left corner of the window.
    // (1;1) denotes the bottom-right corner.
    // When evaluating the filter, X and Y are multiplied by image width
    //   and image height respectively.
    ParamList params { { std::make_pair(
            ParamInfo::double_range("Left X", 0, 1),
            ParamValue::double_range(0)), std::make_pair(
            ParamInfo::double_range("Left Y", 0, 1),
            ParamValue::double_range(0)), std::make_pair(
            ParamInfo::double_range("Width", 0, 1),
            ParamValue::double_range(1)), std::make_pair(
            ParamInfo::double_range("Height", 0, 1),
            ParamValue::double_range(1)) }, };
    bool validated = false;
};

} /* namespace backend */

#endif /* CROPFILTER_H_ */
