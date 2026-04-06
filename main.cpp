#include <iostream>
#include "Tensor.h"
#include "ReLU.h"
#include "Sigmoid.h"

using namespace std;
 Tensor dot ( const Tensor & a , const Tensor & b ) {
     if (a.shape!=b.shape) {
         throw invalid_argument("Las dimenciones no son iguales");
     }
     double suma=0;
     for (int i=0;i<a.total_size;i++) {
         suma+=a.data[i]*b.data[i];
     }
     return Tensor({1},{suma});
 }
Tensor matmul ( const Tensor & a , const Tensor & b ) {
     if (a.shape.size() != 2 || b.shape.size() != 2) {
         throw invalid_argument("Ambos tensores deben ser 2D");
     }

     if (a.shape[1] != b.shape[0]) {
         throw invalid_argument("Las dimensiones no son compatibles para matmul");
     }
     vector<size_t> shape_({a.shape[0],b.shape[1]});
     vector <double> valores_((a.shape[0]*b.shape[1]));
     double suma=0;
     for (int i=0;i<a.shape[0];i++) {
         for (int j=0;j<b.shape[1];j++) {
             for (int k=0;k<a.shape[1];k++) {
                 suma+=a.data[k + i*a.shape[1]]*b.data[j + k*b.shape[1]];
             }
             valores_[j + i*b.shape[1]]=suma;
             suma=0.0;
         }
     }
     return Tensor(shape_,valores_);
 };
int main()
{
    Tensor A({2, 2}, {1, 2, 3, 4});
    Tensor B({2, 2}, {5, 6, 7, 8});
    Tensor C = A + B;
    Tensor D = A - B;
    Tensor E = A * B;
    Tensor F = A * 2.0;
    Tensor G = Tensor::zeros({2, 3});
    Tensor H = Tensor::ones({2, 3});
    Tensor I = Tensor::random({2, 2}, 0.0, 1.0);
    Tensor J = Tensor::arange(0, 6);
    ReLU relu;
    Sigmoid sig;
    Tensor K = A.apply(relu);
    Tensor L = A.apply(sig);
    Tensor X = Tensor::random({1000, 20,20},1.0,5.0);
    Tensor X_resize = X.view({1000,400});
    Tensor Y = Tensor::random({400,100},10.0,20.0);
    Tensor Multiplicado= matmul(X_resize,Y);
    Tensor Z = Tensor::ones({1,100});
    Tensor sumado=Multiplicado +Z ;
    ReLU relu2;
    Tensor aplicacion_ReLU = sumado.apply(relu2);
    Tensor segundo_multiplicado=matmul(aplicacion_ReLU,Tensor::random({100, 10},1.0,6.0));
    Tensor segundo_sumado=segundo_multiplicado+Tensor::random({1, 10},1.0,3.0);
    Sigmoid sig2;
    Tensor aplicacion_sigmoid = segundo_sumado.apply(sig2);

    return 0;
}