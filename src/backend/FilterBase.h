/*
 * FilterBase.h
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 */

#ifndef FILTERBASE_H_
#define FILTERBASE_H_
#include <optional>
#include <vips/vips8>
#include <vector>
#include <memory>
#include <map>
#include "ParamValue.h"

namespace backend {

class FilterBase {
public:
    FilterBase();
    virtual ~FilterBase();
    virtual const char *get_name() = 0;
    virtual std::shared_ptr<vips::VImage> process(
            std::optional<std::shared_ptr<vips::VImage>> input_opt) = 0;
    virtual ParamValue get_param_value(int id) = 0;
    virtual void set_param_value(int id,
            ParamValue val) = 0;
    virtual std::vector<std::pair<ParamInfo, ParamValue>> get_param_list() = 0;
    virtual void invalidate() = 0;
    virtual bool is_validated() = 0;
};

} /* namespace backend */

#endif /* FILTERBASE_H_ */
