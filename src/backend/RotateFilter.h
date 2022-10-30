/*
 * RotateFilter.h
 *
 *  Created on: 18 трав. 2022 р.
 *      Author: linukon
 */

#ifndef ROTATEFILTER_H_
#define ROTATEFILTER_H_

#include "FilterBase.h"
#include "ParamList.h"

namespace backend {

class RotateFilter: public FilterBase {
public:
    RotateFilter();
    virtual ~RotateFilter();

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
    // The phase value is the actual phase value divided by pi/2
    //   e. g. if the rotation angle is -90 degrees (3pi/2),
    //   then the rotation angle is 3.
    ParamList params { { std::make_pair(
            ParamInfo::int_range("Phase", 0, 3),
            ParamValue::int_range(0)) } };
    bool validated = false;
};

} /* namespace backend */

#endif /* ROTATEFILTER_H_ */
