#ifndef TAREA1_RELU_H
#define TAREA1_RELU_H
#include "TensorTransform.h"


class ReLU : public TensorTransform
{
public:
    Tensor apply(const Tensor& t) const override;
};


#endif //TAREA1_RELU_H