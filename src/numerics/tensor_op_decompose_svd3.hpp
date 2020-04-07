/** ExaTN::Numerics: Tensor operation: Decomposes a tensor into three tensor factors via SVD
REVISION: 2020/04/07

Copyright (C) 2018-2020 Dmitry I. Lyakh (Liakh)
Copyright (C) 2018-2020 Oak Ridge National Laboratory (UT-Battelle) **/

/** Rationale:
 (a) Decomposes a tensor into three tensor factors via SVD, for example:
     D(a,b,c,d,e) = L(c,i,e,j) * S(i,j) * R(d,j,a,b,i)
**/

#ifndef EXATN_NUMERICS_TENSOR_OP_DECOMPOSE_SVD3_HPP_
#define EXATN_NUMERICS_TENSOR_OP_DECOMPOSE_SVD3_HPP_

#include "tensor_basic.hpp"
#include "tensor_operation.hpp"

namespace exatn{

namespace numerics{

class TensorOpDecomposeSVD3: public TensorOperation{
public:

 TensorOpDecomposeSVD3();

 TensorOpDecomposeSVD3(const TensorOpDecomposeSVD3 &) = default;
 TensorOpDecomposeSVD3 & operator=(const TensorOpDecomposeSVD3 &) = default;
 TensorOpDecomposeSVD3(TensorOpDecomposeSVD3 &&) noexcept = default;
 TensorOpDecomposeSVD3 & operator=(TensorOpDecomposeSVD3 &&) noexcept = default;
 virtual ~TensorOpDecomposeSVD3() = default;

 /** Returns TRUE iff the tensor operation is fully set. **/
 virtual bool isSet() const override;

 /** Accepts tensor node executor which will execute this tensor operation. **/
 virtual int accept(runtime::TensorNodeExecutor & node_executor,
                    runtime::TensorOpExecHandle * exec_handle) override;

 /** Create a new polymorphic instance of this subclass. **/
 static std::unique_ptr<TensorOperation> createNew();

private:

};

} //namespace numerics

} //namespace exatn

#endif //EXATN_NUMERICS_TENSOR_OP_DECOMPOSE_SVD3_HPP_