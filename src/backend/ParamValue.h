/*
 * ParamValue.h
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 */

#ifndef PARAMVALUE_H_
#define PARAMVALUE_H_
#include <string>
#include <variant>
#include "ParamInfo.h"

namespace backend {

class ParamValue {
public:

    virtual ~ParamValue();
    ParamType type;
    std::variant<std::string, double, int> value;

    static ParamValue double_range(double range);
    static ParamValue int_range(int value);
    static ParamValue file_path(std::string path);

private:
};

} /* namespace backend */

#endif /* PARAMVALUE_H_ */
