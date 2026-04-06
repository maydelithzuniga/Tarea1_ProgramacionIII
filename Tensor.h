#include <vector>
#include <cstddef>

#ifndef TAREA1_TENSOR_H
#define TAREA1_TENSOR_H
using namespace std;

class TensorTransform;
class ReLU;
class Sigmoid;
class Tensor
{
    private:
    vector<size_t> shape;
    size_t total_size;
    double* data;
    bool is_view;

    public:
    Tensor(const std::vector<size_t>& shape_, const std::vector<double>& values);

    static Tensor zeros(const std::vector<size_t>& shape);
    static Tensor ones(const std::vector<size_t>& shape);
    static Tensor random(const std::vector<size_t>& shape, double min, double max);
    static Tensor arange(double start, double end);

    Tensor(const Tensor& other);
    Tensor(Tensor&& other) noexcept;
    Tensor(vector<size_t> _shape, double *data_,size_t _total_size): shape(_shape), data(data_), total_size(_total_size), is_view(true){};
    Tensor& operator=(const Tensor& other);
    Tensor& operator=(Tensor&& other) noexcept;

    Tensor apply(const TensorTransform& transform) const;
    friend class ReLU;
    friend class Sigmoid;
    friend Tensor dot ( const Tensor & a , const Tensor & b ) ;
    friend Tensor matmul ( const Tensor & a , const Tensor & b ) ;

    Tensor operator+(const Tensor& other) const;
    Tensor operator-(const Tensor& other) const;
    Tensor operator*(const Tensor& other) const;
    Tensor operator*(double scalar) const;

    Tensor view (const vector<size_t> &shape_) const;
    Tensor unsqueeze(size_t posicion) const;
    static Tensor concat (const vector<Tensor> & tensores,size_t dimension) ;

    ~Tensor();
};



#endif //TAREA1_TENSOR_H