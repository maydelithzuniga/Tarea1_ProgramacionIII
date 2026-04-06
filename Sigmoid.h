#ifndef TAREA1_SIGMOID_H
#define TAREA1_SIGMOID_H
#include "TensorTransform.h"

class Sigmoid : public TensorTransform
{
public:
    Tensor apply(const Tensor& t) const override;
};


#endif //TAREA1_SIGMOID_H