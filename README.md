# Tensor++

## Descripción

Este proyecto implementa una librería de tensores en C++ denominada **Tensor++**, inspirada en herramientas como NumPy y PyTorch. Su objetivo es permitir la creación, manipulación y transformación de tensores de hasta tres dimensiones mediante el uso de memoria dinámica contigua.

La implementación soporta operaciones algebraicas, transformaciones polimórficas y un flujo de procesamiento que simula el comportamiento de una red neuronal.

---

## Representación del tensor

Cada tensor está compuesto por:

* `shape`: vector que define las dimensiones del tensor
* `total_size`: número total de elementos
* `data`: arreglo dinámico contiguo (`double*`)
* `is_view`: indicador para evitar liberación incorrecta de memoria en vistas

---

## Funcionalidades implementadas

### 1. Constructor principal

```cpp
Tensor(const std::vector<size_t>& shape_, const std::vector<double>& values);
```

* Permite crear tensores de hasta 3 dimensiones
* Valida que la cantidad de valores coincida con el producto de las dimensiones

---

### 2. Métodos de creación

* `Tensor::zeros(shape)`
* `Tensor::ones(shape)`
* `Tensor::random(shape, min, max)`
* `Tensor::arange(start, end)`

Estos métodos facilitan la creación de tensores sin gestionar manualmente la memoria.

---

### 3. Gestión de memoria

Se implementan correctamente:

* Constructor de copia (deep copy)
* Constructor de movimiento
* Asignación por copia
* Asignación por movimiento
* Destructor

Esto asegura un manejo adecuado de memoria dinámica.

---

### 4. Transformaciones (Polimorfismo)

Se define una interfaz abstracta:

```cpp
class TensorTransform {
public:
    virtual Tensor apply(const Tensor& t) const = 0;
};
```

Implementaciones:

* **ReLU**: `y = max(0, x)`
* **Sigmoid**: `y = 1 / (1 + e^{-x})`

Uso:

```cpp
Tensor B = A.apply(relu);
Tensor C = A.apply(sigmoid);
```

---

### 5. Sobrecarga de operadores

Se implementan:

* `+` suma de tensores
* `-` resta de tensores
* `*` multiplicación elemento a elemento
* `*` multiplicación por escalar

Incluye soporte para suma con bias en dimensiones compatibles.

---

### 6. Modificación de dimensiones

#### view

Permite reinterpretar la forma del tensor sin copiar datos.

```cpp
Tensor B = A.view({3,4});
```

#### unsqueeze

Agrega una dimensión de tamaño 1 en una posición específica.

```cpp
Tensor C = A.unsqueeze(0);
```

---

### 7. Concatenación

```cpp
Tensor::concat({A, B}, dimension);
```

* Une múltiples tensores
* Funciona en 1D, 2D y 3D
* Valida compatibilidad dimensional
* Crea un nuevo tensor con memoria propia

---

### 8. Funciones amigas

#### dot

Calcula el producto punto entre tensores de igual dimensión.

#### matmul

Realiza multiplicación matricial entre tensores 2D compatibles.

---

### 9. Aplicación: Red neuronal

Se implementa un flujo completo:

1. Entrada: `1000 x 20 x 20`
2. Reinterpretación: `1000 x 400`
3. Multiplicación con pesos
4. Suma de bias
5. Activación ReLU
6. Nueva multiplicación
7. Nueva suma de bias
8. Activación Sigmoid

Esto demuestra la integración de todas las funcionalidades desarrolladas.

---

## Estructura del proyecto

```
Tensor++
├── main.cpp
├── Tensor.h
├── Tensor.cpp
├── TensorTransform.h
├── ReLU.h / ReLU.cpp
├── Sigmoid.h / Sigmoid.cpp
└── README.md
```

---

## Decisiones de diseño

* Uso de memoria contigua (`double*`) para eficiencia
* Representación flexible mediante `shape`
* Reutilización de memoria en `view` y `unsqueeze`
* Uso de polimorfismo para transformaciones

---

## Requisitos cumplidos

El proyecto incluye:

* Implementación completa de la clase Tensor
* Métodos estáticos de creación
* Gestión de memoria
* Transformaciones polimórficas
* Sobrecarga de operadores
* Modificación de dimensiones
* Concatenación
* Funciones amigas (`dot`, `matmul`)
* Aplicación en red neuronal

---

## Autores

* Maydelith Laura Zúñiga Cabrera
* Joaquín Mathias Alejandro Llallire Meza

---



