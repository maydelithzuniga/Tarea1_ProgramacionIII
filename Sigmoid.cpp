#include "Sigmoid.h"
#include <vector>
#include <cstddef>
#include <cmath>

using namespace std;
Tensor Sigmoid::apply(const Tensor& t) const
{
    vector<double> values(t.total_size);
    for (size_t i = 0; i < t.total_size; i++)
    {
        values[i] = 1.0 / (1.0 + exp(-t.data[i]));
    }
    return Tensor(t.shape, values);
}