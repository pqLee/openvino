// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <functional>
#include <set>
#include <sstream>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

#include "openvino/pass/pass.hpp"

class HeightMap;

using visualize_tree_ops_map_t =
    std::unordered_map<ov::Node::type_info_t, std::function<void(const ov::Node&, std::ostream& ss)>>;

namespace ov {
namespace pass {
class OPENVINO_API VisualizeTree : public FunctionPass {
public:
    OPENVINO_RTTI("ov::pass::VisualizeTree");

    using node_modifiers_t = std::function<void(const Node& node, std::vector<std::string>& attributes)>;
    VisualizeTree(const std::string& file_name, node_modifiers_t nm = nullptr, bool dot_only = false);
    bool run_on_function(std::shared_ptr<ov::Function>) override;

    void set_ops_to_details(const visualize_tree_ops_map_t& ops_map) {
        m_ops_to_details = ops_map;
    }

protected:
    void add_node_arguments(std::shared_ptr<Node> node,
                            std::unordered_map<Node*, HeightMap>& height_maps,
                            size_t& fake_node_ctr);
    std::string add_attributes(std::shared_ptr<Node> node);
    virtual std::string get_attributes(std::shared_ptr<Node> node);
    virtual std::string get_node_name(std::shared_ptr<Node> node);
    std::string get_constant_value(std::shared_ptr<Node> node, size_t max_elements = 7);

    void render() const;

    std::stringstream m_ss;
    std::string m_name;
    std::set<std::shared_ptr<Node>> m_nodes_with_attributes;
    visualize_tree_ops_map_t m_ops_to_details;
    node_modifiers_t m_node_modifiers = nullptr;
    bool m_dot_only;
    static constexpr int max_jump_distance = 20;
};
}  // namespace pass
}  // namespace ov
