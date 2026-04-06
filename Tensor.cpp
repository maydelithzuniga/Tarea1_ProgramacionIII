#include "Tensor.h"
#include <stdexcept>
#include <random>
#include "TensorTransform.h"
#include <vector>
using namespace std;
Tensor::Tensor(const vector<size_t>& shape_, const vector<double>& values)
{
    is_view=false;
    if (shape_.empty() or shape_.size() > 3)
    {
        throw invalid_argument("El tensor debe tener entre 1 y 3 dimensiones");
    }
    shape = shape_;
    total_size = 1;
    for (size_t i = 0; i < shape.size(); i++)
    {
        total_size = total_size * shape[i];
    }
    if (values.size() != total_size)
    {
        throw invalid_argument("La cantidad de values no coincide con el producto de las dimensiones");
    }
    data = new double[total_size];
    for (size_t i = 0; i < total_size; i++)
    {
        data[i] = values[i];
    }
}

Tensor Tensor::zeros(const vector<size_t>& shape)
{
    if (shape.empty())
    {
        throw invalid_argument("Ingresa el tamano de tu tensor");
    }
    size_t total = 1;
    for (size_t i = 0; i < shape.size(); i++)
    {
        total *= shape[i];
    }
    vector<double> values(total, 0.0);
    return Tensor(shape, values);
}
Tensor Tensor::ones(const vector<size_t>& shape)
{
    if (shape.empty())
    {
        throw invalid_argument("Ingresa el tamano de tu tensor");
    }
    size_t total = 1;
    for (size_t i = 0; i < shape.size(); i++)
    {
        total *= shape[i];
    }
    vector<double> values(total, 1.0);
    return Tensor(shape, values);
}
Tensor Tensor::random(const vector<size_t>& shape, double min, double max)
{
    if (shape.empty())
    {
        throw invalid_argument("Ingresa el tamano de tu tensor");
    }
    size_t total = 1;
    for (size_t i = 0; i < shape.size(); i++)
    {
        total *= shape[i];
    }
    vector<double> values(total);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);
    for (size_t i = 0; i < total; i++)
    {
        values[i] = dis(gen);
    }
    return Tensor(shape, values);
}
Tensor Tensor::arange(double start, double end)
{
    if (start==0 and end==0)
    {
        throw invalid_argument("Ingresa un rango verdadero");
    }
    vector<double> values;
    for (double i = start; i < end; i++)
    {
        values.push_back(i);
    }
    vector<size_t> shape = { values.size() };
    return Tensor(shape, values);
}
Tensor::Tensor(const Tensor& other)
{
    shape = other.shape;
    total_size = other.total_size;
    is_view = false;
    data = new double[total_size];
    for (size_t i = 0; i < total_size; i++)
    {
        data[i] = other.data[i];
    }
}
Tensor::Tensor(Tensor&& other) noexcept
{
    shape = other.shape;
    total_size = other.total_size;
    data = other.data;
    is_view = other.is_view;
    other.data = nullptr;
    other.total_size = 0;
    other.shape.clear();
    other.is_view = false;
}
Tensor& Tensor::operator=(const Tensor& other)
{
    if (this == &other)
    {
        return *this;
    }
    if (!is_view)
    {
        delete[] data;
    }
    shape = other.shape;
    total_size = other.total_size;
    is_view = false;
    data = new double[total_size];
    for (size_t i = 0; i < total_size; i++)
    {
        data[i] = other.data[i];
    }
    return *this;
}
Tensor& Tensor::operator=(Tensor&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    if (!is_view)
    {
        delete[] data;
    }
    shape = other.shape;
    total_size = other.total_size;
    data = other.data;
    is_view = other.is_view;
    other.data = nullptr;
    other.total_size = 0;
    other.shape.clear();
    return *this;
}
Tensor Tensor::apply(const TensorTransform& transform) const
{
    return transform.apply(*this);
}
Tensor Tensor::operator+(const Tensor& other) const
{
    if (shape == other.shape) {
        vector<double> values(total_size);
        for (size_t i = 0; i < total_size; i++) {
            values[i] = data[i] + other.data[i];
        }
        return Tensor(shape, values);
    }

    if (shape.size() == 2 &&
        other.shape.size() == 2 &&
        other.shape[0] == 1 &&
        shape[1] == other.shape[1]) {
        vector<double> values(total_size);
        for (size_t i = 0; i < shape[0]; i++) {
            for (size_t j = 0; j < shape[1]; j++) {
                values[i * shape[1] + j] =
                    data[i * shape[1] + j] +
                    other.data[j];
            }
        }
        return Tensor(shape, values);
        }
    throw invalid_argument("Dimensiones incompatibles");
}

Tensor Tensor::operator-(const Tensor& other) const
{
    if (shape != other.shape)
    {
        throw invalid_argument("Dimensiones incompatibles");
    }
    vector<double> values(total_size);
    for (size_t i = 0; i < total_size; i++)
    {
        values[i] = data[i] - other.data[i];
    }
    return Tensor(shape, values);
}
Tensor Tensor::operator*(const Tensor& other) const
{
    if (shape != other.shape)
    {
        throw invalid_argument("Dimensiones incompatibles");
    }
    vector<double> values(total_size);
    for (size_t i = 0; i < total_size; i++)
    {
        values[i] = data[i] * other.data[i];
    }
    return Tensor(shape, values);
}
Tensor Tensor::operator*(double scalar) const
{
    vector<double> values(total_size);
    for (size_t i = 0; i < total_size; i++)
    {
        values[i] = data[i] * scalar;
    }
    return Tensor(shape, values);
}
Tensor Tensor::view(const vector<size_t>& shape_) const
{
    if (shape_.empty())
    {
        throw invalid_argument("Dimensiones vacias");
    }
    if (shape_.size() > 3)
    {
        throw invalid_argument("Maximo 3 dimensiones");
    }
    size_t total_size_nuevo = 1;
    for (size_t i = 0; i < shape_.size(); i++)
    {
        total_size_nuevo *= shape_[i];
    }
    if (total_size_nuevo != total_size)
    {
        throw invalid_argument("La cantidad de elementos no coincide");
    }
    return Tensor(shape_, data, total_size_nuevo);
}
Tensor Tensor::unsqueeze(size_t posicion) const
{
    if (shape.size() >= 3)
    {
        throw invalid_argument("No se puede exceder 3 dimensiones");
    }
    if (posicion > shape.size())
    {
        throw invalid_argument("Posicion invalida");
    }
    vector<size_t> shape_ = shape;
    shape_.insert(shape_.begin() + posicion, 1);
    return Tensor(shape_, data, total_size);
}

Tensor Tensor::concat(const vector<Tensor>& tensores, size_t dimension)
{
    if (tensores.empty()) {
        throw invalid_argument("No hay tensores para concatenar");
    }
    if (dimension >= tensores[0].shape.size()) {
        throw invalid_argument("La dimension no existe");
    }
    for (size_t t = 1; t < tensores.size(); t++) {
        if (tensores[t].shape.size() != tensores[0].shape.size()) {
            throw invalid_argument("No se puede concatenar tensores con distinto numero de dimensiones");
        }
        for (size_t i = 0; i < tensores[0].shape.size(); i++) {
            if (i != dimension && tensores[t].shape[i] != tensores[0].shape[i]) {
                throw invalid_argument("Dimensiones incompatibles para concatenar");
            }
        }
    }
    vector<size_t> tensor_shape = tensores[0].shape;
    tensor_shape[dimension] = 0;
    for (size_t t = 0; t < tensores.size(); t++) {
        tensor_shape[dimension] += tensores[t].shape[dimension];
    }
    size_t total_size_nuevo = 1;
    for (size_t i = 0; i < tensor_shape.size(); i++) {
        total_size_nuevo *= tensor_shape[i];
    }
    vector<double> valores_;
    valores_.reserve(total_size_nuevo);
    if (tensor_shape.size() == 1) {
        for (size_t t = 0; t < tensores.size(); t++) {
            for (size_t i = 0; i < tensores[t].total_size; i++) {
                valores_.push_back(tensores[t].data[i]);
            }
        }
    }
    else if (tensor_shape.size() == 2) {
        if (dimension == 0) {
            for (size_t t = 0; t < tensores.size(); t++) {
                for (size_t i = 0; i < tensores[t].total_size; i++) {
                    valores_.push_back(tensores[t].data[i]);
                }
            }
        }
        else if (dimension == 1) {
            size_t filas = tensores[0].shape[0];
            for (size_t f = 0; f < filas; f++) {
                for (size_t t = 0; t < tensores.size(); t++) {
                    size_t columnas = tensores[t].shape[1];
                    for (size_t c = 0; c < columnas; c++) {
                        valores_.push_back(tensores[t].data[f * columnas + c]);
                    }
                }
            }
        }
        else {
            throw invalid_argument("Dimension invalida para tensor 2D");
        }
    }
    else if (tensor_shape.size() == 3) {
        size_t D = tensores[0].shape[0];
        if (dimension == 0) {
            for (size_t t = 0; t < tensores.size(); t++) {
                for (size_t i = 0; i < tensores[t].total_size; i++) {
                    valores_.push_back(tensores[t].data[i]);
                }
            }
        }
        else if (dimension == 1) {
            size_t C = tensores[0].shape[2];
            for (size_t d = 0; d < D; d++) {
                for (size_t t = 0; t < tensores.size(); t++) {
                    size_t F = tensores[t].shape[1];
                    for (size_t f = 0; f < F; f++) {
                        for (size_t c = 0; c < C; c++) {
                            valores_.push_back(
                                tensores[t].data[d * (F * C) + f * C + c]
                            );
                        }
                    }
                }
            }
        }
        else if (dimension == 2) {
            size_t F = tensores[0].shape[1];
            for (size_t d = 0; d < D; d++) {
                for (size_t f = 0; f < F; f++) {
                    for (size_t t = 0; t < tensores.size(); t++) {
                        size_t C = tensores[t].shape[2];
                        for (size_t c = 0; c < C; c++) {
                            valores_.push_back(
                                tensores[t].data[d * (F * C) + f * C + c]
                            );
                        }
                    }
                }
            }
        }
        else {
            throw invalid_argument("Dimension invalida para tensor 3D");
        }
    }
    else {
        throw invalid_argument("Solo se permiten tensores de hasta 3 dimensiones");
    }
    return Tensor(tensor_shape, valores_);
}
Tensor :: ~Tensor() {
    if (!is_view) {
        delete[] data;
    }
}