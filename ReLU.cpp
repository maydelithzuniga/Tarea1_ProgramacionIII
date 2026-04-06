#include <cstddef>
#include <vector>
#include "ReLU.h"
using namespace std;
Tensor ReLU::apply(const Tensor& t) const
{
    vector<double> values(t.total_size);
    for (size_t i = 0; i < t.total_size; i++)
    {
        if (t.data[i] > 0)
            values[i] = t.data[i];
        else
            values[i] = 0;
    }
    return Tensor(t.shape, values);
}