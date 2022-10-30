/*
 * ParamList.h
 *
 *  Created on: 2022-05-07
 *      Author: linukon
 *
 *  ParamList: a wrapper unifying ParamInfo and ParamValue
 *
 */

#ifndef PARAMLIST_H_
#define PARAMLIST_H_

#include <vector>
#include "ParamInfo.h"
#include "ParamValue.h"

namespace backend {

class ParamList {
public:
    ParamList(
            std::vector<std::pair<ParamInfo, ParamValue>> _params);
    virtual ~ParamList();
    std::vector<std::pair<ParamInfo, ParamValue>> get_list();
    ParamValue get_value(int at);
    void set_value(int at, ParamValue v);
private:
    std::vector<std::pair<ParamInfo, ParamValue>> params;

};

} /* namespace backend */

#endif /* PARAMLIST_H_ */
