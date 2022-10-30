/*
 * ImportFilter.h
 *
 *  Created on: 2022-05-05
 *      Author: ImageIt
 */

#ifndef IMPORTFILTER_H_
#define IMPORTFILTER_H_

#include "FilterBase.h"
#include "ParamList.h"

namespace backend {

class ImportFilter: public FilterBase {
public:
    ImportFilter();
    virtual ~ImportFilter();

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
    // Source: Dice by Dimitrios Psychogios (CC-BY-SA 4.0)
    // https://www.gimp.org/tutorials/Digital_Black_and_White_Conversion/dmitrios-dice.jpg
    const char *INPATH = "res/dmitrios-dice.jpg";
    ParamList params { { { ParamInfo::file_path("Path"),
            ParamValue::file_path(INPATH) } } };
    bool validated = false;
};

} /* namespace backend */

#endif /* IMPORTFILTER_H_ */
