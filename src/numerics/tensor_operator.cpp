/** ExaTN::Numerics: Tensor operator
REVISION: 2019/12/06

Copyright (C) 2018-2019 Dmitry I. Lyakh (Liakh)
Copyright (C) 2018-2019 Oak Ridge National Laboratory (UT-Battelle) **/

#include "tensor_operator.hpp"

namespace exatn{

namespace numerics{

bool TensorOperator::appendComponent(std::shared_ptr<TensorNetwork> network, //in: tensor network (or single tensor as a tensor network)
     const std::vector<std::pair<unsigned int, unsigned int>> & ket_pairing, //in: ket pairing: Global tensor mode id <-- Output tensor leg
     const std::vector<std::pair<unsigned int, unsigned int>> & bra_pairing, //in: bra pairing: Global tensor mode id <-- Output tensor leg
     const std::complex<double> coefficient)                                 //in: expansion coefficient
{
 assert(network);
 auto output_tensor = network->getTensor(0);
 const auto output_tensor_rank = output_tensor->getRank();
 assert(ket_pairing.size() + bra_pairing.size() == output_tensor_rank);
 components_.emplace_back(OperatorComponent{network,ket_pairing,bra_pairing,coefficient});
 return true;
}


bool TensorOperator::appendComponent(std::shared_ptr<Tensor> tensor,         //in: tensor
     const std::vector<std::pair<unsigned int, unsigned int>> & ket_pairing, //in: ket pairing: Global tensor mode id <-- Tensor leg
     const std::vector<std::pair<unsigned int, unsigned int>> & bra_pairing, //in: bra pairing: Global tensor mode id <-- Tensor leg
     const std::complex<double> coefficient)                                 //in: expansion coefficient
{
 assert(tensor);
 bool appended = false;
 const auto tensor_rank = tensor->getRank();
 auto output_tensor = std::make_shared<Tensor>(*tensor);
 output_tensor->rename("_"+(tensor->getName())+"_");
 std::vector<TensorLeg> legs(tensor_rank,TensorLeg{0,0});
 for(unsigned int i = 0; i < tensor_rank; ++i) legs[i] = TensorLeg{1,i};
 auto network = makeSharedTensorNetwork(tensor->getName(),output_tensor,legs);
 for(unsigned int i = 0; i < tensor_rank; ++i) legs[i] = TensorLeg{0,i};
 appended = network->placeTensor(1,tensor,legs);
 if(appended){
  appended = network->finalize();
  if(appended){
   appended = appendComponent(network,ket_pairing,bra_pairing,coefficient);
  }else{
   std::cout << "#ERROR(exatn::numerics::TensorOperator::appendComponent): Unable to finalize the intermediate tensor network!"
             << std::endl;
  }
 }else{
  std::cout << "#ERROR(exatn::numerics::TensorOperator::appendComponent): Unable to build a tensor network from the given tensor!"
            << std::endl;
 }
 return appended;
}


void TensorOperator::conjugate()
{
 for(auto & component: components_){
  component.network->conjugate();
  component.ket_legs.swap(component.bra_legs);
  component.coefficient = std::conj(component.coefficient);
 }
 return;
}


void TensorOperator::printIt() const
{
 std::cout << "TensorNetworkOperator(" << this->getName()
           << ")[rank = " << this->getRank()
           << ", size = " << this->getNumComponents() << "]{" << std::endl;
 std::size_t i = 0;
 for(const auto & component: components_){
  std::cout << "Component " << i++ << ": " << component.coefficient << std::endl;
  std::cout << "Ket legs { ";
  for(const auto & leg: component.ket_legs) std::cout << "{" << leg.second << "->" << leg.first << "}";
  std::cout << " }" << std::endl;
  std::cout << "Bra legs { ";
  for(const auto & leg: component.bra_legs) std::cout << "{" << leg.second << "->" << leg.first << "}";
  std::cout << " }" << std::endl;
  component.network->printIt();
 }
 std::cout << "}" << std::endl;
 return;
}

} //namespace numerics

} //namespace exatn
