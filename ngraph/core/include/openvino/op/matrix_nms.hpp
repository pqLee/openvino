// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "openvino/op/util/nms_base.hpp"

namespace ov {
namespace op {
namespace v8 {
/// \brief MatrixNms operation
///
class OPENVINO_API MatrixNms : public util::NmsBase {
public:
    OPENVINO_OP("MatrixNms", "opset8", op::util::NmsBase);

    enum class DecayFunction { GAUSSIAN, LINEAR };

    /// \brief Structure that specifies attributes of the operation
    struct Attributes {
        // specifies order of output elements
        SortResultType sort_result_type = SortResultType::NONE;
        // specifies whenever it is necessary to sort selected boxes across batches or
        // not
        bool sort_result_across_batch = false;
        // specifies the output tensor type
        ov::element::Type output_type = ov::element::i64;
        // specifies minimum score to consider box for the processing
        float score_threshold = 0.0f;
        // specifies maximum number of boxes to be selected per class, -1 meaning to
        // keep all boxes
        int nms_top_k = -1;
        // specifies maximum number of boxes to be selected per batch element, -1
        // meaning to keep all boxes
        int keep_top_k = -1;
        // specifies the background class id, -1 meaning to keep all classes
        int background_class = -1;
        // specifies decay function used to decay scores
        DecayFunction decay_function = DecayFunction::LINEAR;
        // specifies gaussian_sigma parameter for gaussian decay_function
        float gaussian_sigma = 2.0f;
        // specifies threshold to filter out boxes with low confidence score after
        // decaying
        float post_threshold = 0.0f;
        // specifies whether boxes are normalized or not
        bool normalized = true;
    };

    MatrixNms();

    /// \brief Constructs a MatrixNms operation
    ///
    /// \param boxes Node producing the box coordinates
    /// \param scores Node producing the box scores
    /// \param attrs Attributes of the operation
    MatrixNms(const Output<Node>& boxes, const Output<Node>& scores, const Attributes& attrs);

    bool visit_attributes(AttributeVisitor& visitor) override;

    std::shared_ptr<Node> clone_with_new_inputs(const OutputVector& new_args) const override;

    /// \brief Returns attributes of the operation MatrixNms
    const Attributes& get_attrs() const {
        return m_attrs;
    }

protected:
    Attributes m_attrs;

    void validate() override;
};
}  // namespace v8
}  // namespace op
OPENVINO_API
std::ostream& operator<<(std::ostream& s, const op::v8::MatrixNms::DecayFunction& type);

template <>
class OPENVINO_API AttributeAdapter<op::v8::MatrixNms::DecayFunction>
    : public EnumAttributeAdapterBase<op::v8::MatrixNms::DecayFunction> {
public:
    AttributeAdapter(op::v8::MatrixNms::DecayFunction& value)
        : EnumAttributeAdapterBase<op::v8::MatrixNms::DecayFunction>(value) {}

    OPENVINO_RTTI("AttributeAdapter<ov::op::v8::MatrixNms::DecayFunction>");
    BWDCMP_RTTI_DECLARATION;
};

}  // namespace ov
