/*
 * Pipeline.h
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 *
 *  Definitions:
 *    The head node is the node from which the pipeline begins working.
 *    The tail node is the the last used node.
 *
 *  Normally, there is an only one pipeline for an editing context.
 *  Sharing the nodes between several pipelines is an undefined behaviour.
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <memory>
#include <set>
#include <vector>
#include <string>
#include "Node.h"

namespace backend {
class Pipeline {
public:
    Pipeline();
    virtual ~Pipeline();
    std::vector<std::shared_ptr<FilterBase>> get_filter_list();
    void append_node(std::shared_ptr<Node> node);
    void pop_head_node();
    void pop_tail_node();
    bool is_empty();
    std::optional<std::shared_ptr<FilterBase>> get_filter_by_name(
            const char *name);
    std::optional<int> get_node_index_by_name(
            const char *name);
    std::shared_ptr<ImageResult> evaluate();
    int get_total_steps();
    bool evaluate_step();
    void export_result(std::string path);
    void remove_node_at(int idx);
private:
    std::optional<std::shared_ptr<Node>> head;
    std::optional<std::shared_ptr<Node>> tail;
    std::optional<std::shared_ptr<Node>> step;
    std::optional<ImageResult> cache_opt = std::nullopt;
    static std::shared_ptr<vips::VImage> load_from_cache(
            ImageResult cache);

};

} /* namespace backend */

#endif /* PIPELINE_H_ */
