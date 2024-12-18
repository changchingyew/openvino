// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "shape_inference_cpu.hpp"
#include "shape_inference.hpp"

namespace ov {
namespace intel_cpu {

/**
 * @brief This class wraps core specific shape inference class to implement CPU plugin specific interface.
 */
class NgraphShapeInfer : public IShapeInfer {
public:
    /**
     * @brief Wraps IStaticShapeInfer into IShapeInfer interface. Will use port mask defined in IStaticShapeInfer.
     *
     * @param shape_infer Instance of IStaticShapeInfer.
     */
    NgraphShapeInfer(std::shared_ptr<IStaticShapeInfer> shape_infer);

    /**
     * @brief Wraps IStaticShapeInfer into IShapeInfer interface. Will use port mask defined by user
     *
     * @param shape_infer Instance of IStaticShapeInfer.
     * @param port_mask   Port mask define.
     */
    NgraphShapeInfer(std::shared_ptr<IStaticShapeInfer> shape_infer, IShapeInfer::port_mask_t port_mask);

    Result infer(
        const std::vector<std::reference_wrapper<const VectorDims>>& input_shapes,
        const std::unordered_map<size_t, MemoryPtr>& data_dependency) override;

    // infer may generate padding as by-product, these APIs is designed to retrieve them back
    const ov::CoordinateDiff& get_pads_begin() override {
        return m_shape_infer->get_pads_begin();
    }
    const ov::CoordinateDiff& get_pads_end() override {
        return m_shape_infer->get_pads_end();
    }
    port_mask_t get_port_mask() const override {
        return m_port_mask;
    }

private:
    std::shared_ptr<IStaticShapeInfer> m_shape_infer;
    IShapeInfer::port_mask_t m_port_mask;
};

} // namespace intel_cpu
} // namespace ov
