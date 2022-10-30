/*
 * Node.h
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 *
 *  The Node structure encapsulates the inner workings of a filter.
 *  The Node structure is also the type of the linked list
 *    implemented by the Pipeline.
 *  The node has a strictly one filter.
 *  The type of the filter cannot be changed.
 */

#ifndef NODE_H_
#define NODE_H_

#include <optional>
#include "FilterBase.h"
#include "ImageResult.h"

namespace backend {

class Node {
public:
    Node(std::shared_ptr<FilterBase> in_filter);
    virtual ~Node();
    std::shared_ptr<FilterBase> filter;
    std::optional<ImageResult> result;
    std::optional<std::shared_ptr<Node>> next;
    std::optional<std::shared_ptr<Node>> prev;
};

} /* namespace backend */

#endif /* NODE_H_ */
