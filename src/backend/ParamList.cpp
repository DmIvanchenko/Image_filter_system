/*
 * ParamList.cpp
 *
 *  Created on: 2022-05-07
 *      Author: linukon
 */

#include "ParamList.h"

namespace backend {
using namespace std;

ParamList::ParamList(
        std::vector<std::pair<ParamInfo, ParamValue>> _params) {
    for (std::pair<ParamInfo, ParamValue> I : params) {
        if (I.first.type != I.second.type) {
            throw; // ArgumentException (debug?)
        }
    }
    params = _params;
}

ParamList::~ParamList() {
}

std::vector<std::pair<ParamInfo, ParamValue>> ParamList::get_list() {
    return params;
}

ParamValue ParamList::get_value(int at) {
    if (at < 0 || (size_t)at >= params.size()) {
        throw; // ArgumentException (debug?)
    }
    return params[at].second;
}

void ParamList::set_value(int at, ParamValue v) {
    if (at < 0 || (size_t)at >= params.size()
            || v.type != params[at].first.type) {
        throw; // ArgumentException (debug?)
    }
    params[at].second = v;
}

} /* namespace backend */
