/*
 * GaussianBlurFilter.h
 *
 *  Created on: 2022-05-05
 *      Author: linukon
 */

#ifndef GAUSSIANBLURFILTER_H_
#define GAUSSIANBLURFILTER_H_

#include "FilterBase.h"
#include "ParamList.h"

namespace backend {

class GaussianBlurFilter: public FilterBase {
public:
    GaussianBlurFilter();
    virtual ~GaussianBlurFilter();

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
    ParamList params { {
            { ParamInfo::double_range("Intensity", 0, 3),
                    ParamValue::double_range(1) } } };
    bool validated = false;
};

} /* namespace backend */

#endif /* GAUSSIANBLURFILTER_H_ */
