/*
 * Pipeline.cpp
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 */

#include <assert.h>
#include "Pipeline.h"

namespace backend {
using namespace std;
using namespace vips;

Pipeline::Pipeline() {
}

Pipeline::~Pipeline() {
}

bool Pipeline::is_empty() {
    return bool(this->head);
}

std::vector<std::shared_ptr<FilterBase>> Pipeline::get_filter_list() {
    vector<shared_ptr<FilterBase>> v;
    optional<shared_ptr<Node>> node_opt = head;
    while (node_opt) {
        shared_ptr<Node> node = (*node_opt);
        v.push_back(node->filter);
        node_opt = node->next;
    }
    return v;
}

std::optional<int> Pipeline::get_node_index_by_name(
        const char *name) {
    auto filters = get_filter_list();
    for (size_t i = 0; i < filters.size(); i++) {
        if (strcmp(name, filters[i]->get_name()) == 0) {
            return i;
        }
    }
    return nullopt;
}

std::optional<std::shared_ptr<FilterBase>> Pipeline::get_filter_by_name(
        const char *name) {
    auto filters = get_filter_list();
    for (size_t i = 0; i < filters.size(); i++) {
        if (strcmp(name, filters[i]->get_name()) == 0) {
            return filters[i];
        }
    }
    return nullopt;
}

void Pipeline::remove_node_at(int idx) {
    if (idx < 0) {
        throw; // ArgumentException
    }
    optional<shared_ptr<Node>> node_opt = head;
    while (node_opt) {
        shared_ptr<Node> node = (*node_opt);
        if (idx == 0) {
            if (node->prev) {
                (*(node->prev))->next = node->next;
                if (node->next) {
                    (*(node->next))->prev = node->prev;
                    (*(node->next))->filter->invalidate();
                } else {
                    // the node is a tail
                    pop_tail_node();
                }
            } else {
                // the node is a head
                pop_head_node();
            }
            node->prev = nullopt;
            node->next = nullopt;
            return;
        }
        idx--;
        node_opt = node->next;
    }
    throw; // ArgumentException
}

void Pipeline::pop_tail_node() {
    if (!head || !tail) {
        throw;
    }
    if (head == tail) {
        head = tail = nullopt;
    } else {
        tail = (*tail)->prev;
        (*((*tail)->next))->prev = nullopt;
        (*tail)->next = nullopt;
    }
}

void Pipeline::pop_head_node() {
    if (!head || !tail) {
        throw;
    }
    if (head == tail) {
        head = tail = nullopt;
    } else {
        head = (*head)->next;
        (*((*head)->prev))->next = nullopt;
        (*head)->prev = nullopt;
        (*head)->filter->invalidate();
    }
}

void Pipeline::append_node(std::shared_ptr<Node> node) {
    if (!tail) {
        head = tail = node;
    } else {
        (*tail)->next = node;
        node->prev = tail;
    }
    tail = node;
}

int Pipeline::get_total_steps() {
    return this->get_filter_list().size();
}

bool Pipeline::evaluate_step() {
    if (!head) {
        return false;
    }

    shared_ptr<Node> node = (step) ? *step : *head;
    cache_opt = (step) ? cache_opt : nullopt;
    if (node->filter->is_validated()) {
        cache_opt = node->result;
    } else {
        optional<shared_ptr<VImage>> result_ptr_opt = nullopt;
        if (cache_opt) {
            result_ptr_opt = this->load_from_cache(
                    *cache_opt);
        }
        result_ptr_opt = node->filter->process(
                result_ptr_opt);
        ImageResult cache_r;
        cache_r.width = (*result_ptr_opt)->width();
        cache_r.height = (*result_ptr_opt)->height();
        cache_r.band_format = (*result_ptr_opt)->format();
        cache_r.bands = (*result_ptr_opt)->bands();
        std::size_t size;
        char *data_ptr =
                (char*) (*result_ptr_opt)->write_to_memory(
                        &size);
        cache_r.data = shared_ptr<char[]> { data_ptr };
        cache_r.size = size;
        node->result = cache_r;
        cache_opt = node->result;
    }
    step = node->next;

    return bool(step);
}

std::shared_ptr<ImageResult> Pipeline::evaluate() {
    step = nullopt;
    while (evaluate_step()) {
    }
    return make_shared<ImageResult>(*((*tail)->result));
}

void Pipeline::export_result(std::string path) {
    const char *EXT_STR = ".png";
    const size_t EXT_LEN = 4;
    if (path.length() < EXT_LEN
            || path.substr(path.length() - EXT_LEN, EXT_LEN)
                    != EXT_STR) {
        path += EXT_STR;
    }
    if (tail && (*tail)->result) {
        ImageResult &cache = *((*tail)->result);
        shared_ptr<VImage> result = this->load_from_cache(
                cache);
        result->write_to_file(path.c_str());
    } else {
        throw;
    }
}

std::shared_ptr<vips::VImage> Pipeline::load_from_cache(
        ImageResult cache) {
    return make_shared<VImage>(
            vips_image_new_from_memory_copy(
                    cache.data.get(), cache.size,
                    cache.width, cache.height, cache.bands,
                    cache.band_format));
}

} /* namespace backend */
