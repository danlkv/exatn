/** ExaTN: Tensor basic types and parameters
REVISION: 2019/03/18

Copyright (C) 2018-2019 Dmitry I. Lyakh (Liakh)
Copyright (C) 2018-2019 Oak Ridge National Laboratory (UT-Battelle) **/

#ifndef TENSOR_BASIC_HPP_
#define TENSOR_BASIC_HPP_

#include <cstdint>

namespace exatn{

using Int4 = int32_t;
using Int8 = int64_t;
using UInt4 = uint32_t;
using UInt8 = uint64_t;

using SpaceId = unsigned int;              //space id type
using SubspaceId = unsigned long long int; //subspace id type
using SymmetryId = int;                    //symmetry id type
using DimExtent = unsigned long long int;  //dimension extent type
using DimOffset = unsigned long long int;  //dimension base offset type

constexpr DimExtent MAX_SPACE_DIM = 0xFFFFFFFFFFFFFFFF; //max dimension of unregistered (anonymous) spaces
constexpr SpaceId SOME_SPACE = 0; //any unregistered (anonymous) space (all registered spaces will have SpaceId > 0)
constexpr SubspaceId FULL_SUBSPACE = 0; //every space has its trivial (full) subspace automatically registered as subspace 0
constexpr SubspaceId UNREG_SUBSPACE = 0xFFFFFFFFFFFFFFFF; //id of any unregistered subspace

enum class LegDirection{
 UNDIRECT, //no direction
 INWARD,   //inward direction
 OUTWARD   //outward direction
};

enum class TensorKind{
 TENSOR,     //base tensor (no numerical implementation)
 TENSOR_SHA, //shared-memory tensor (TAL-SH numerical backend)
 TENSOR_EXA  //distributed-memory tensor (ExaTENSOR numerical backend)
};

} //namespace exatn

#endif //TENSOR_BASIC_HPP_
