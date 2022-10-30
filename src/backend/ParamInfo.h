/*
 * ParamInfo.h - union-like data structure for storing static
 *   (runtime-checked) parameter type.
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 *
 *  USAGE:
 *
 *    // Create a parameter 'foo', a slider range from 3 to 5:
 *    ParamInfo param = ParamInfo::double_range("foo", 3, 5);
 */

#ifndef PARAMINFO_H_
#define PARAMINFO_H_

#include <string>

namespace backend {

enum class ParamType {
    DOUBLE_RANGE, FILE_PATH, INT_RANGE
};

class ParamInfo {
public:
    virtual ~ParamInfo();

    std::string name;
    ParamType type;
    double range_from;
    double range_to;
    int irange_from;
    int irange_to;

    // static constructors:
    static ParamInfo double_range(std::string name,
            double range_from, double range_to);
    static ParamInfo int_range(std::string name,
                int irange_from, int irange_to);
    static ParamInfo file_path(std::string name);

};

} /* namespace backend */

#endif /* PARAMINFO_H_ */
