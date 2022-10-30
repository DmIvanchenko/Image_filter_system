/*
 * Node.cpp
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 */

#include "Node.h"

namespace backend {
using namespace std;

Node::Node(std::shared_ptr<FilterBase> in_filter) {
    this->filter = in_filter;
    this->result = nullopt;
    this->prev = nullopt;
    this->next = nullopt;
}

Node::~Node() {
}

} /* namespace backend */
