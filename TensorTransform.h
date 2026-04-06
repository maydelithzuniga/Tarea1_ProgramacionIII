#ifndef TAREA1_TENSORTRANSFORM_H
#define TAREA1_TENSORTRANSFORM_H
#include "Tensor.h"


class TensorTransform {
public :
virtual Tensor apply ( const Tensor & t ) const = 0;
    virtual ~ TensorTransform () = default ;
};


#endif //TAREA1_TENSORTRANSFORM_H