# Tarea1_ProgramacionIII
📌 Descripción
Este proyecto implementa una clase Tensor en C++ que permite trabajar con tensores de hasta 3 dimensiones. Incluye operaciones básicas, transformaciones y una simulación simple de una red neuronal.

⚙️ Requisitos
Compilador C++ compatible con C++11 o superior (g++, clang++)
CMake (opcional si usas CLion)

🛠️ Compilación
🔹 Opción 1: Usando g++

Desde la carpeta del proyecto:

g++ main.cpp Tensor.cpp -o programa
🔹 Opción 2: Usando CMake (CLion)
Abrir el proyecto en CLion
Ejecutar el botón Run
El ejecutable se generará automáticamente
▶️ Ejecución
🔹 En terminal (g++)
./programa
🔹 En Windows
programa.exe
🚀 Funcionalidades implementadas
Creación de tensores
zeros: crea un tensor con las dimensiones brindadas, lleno de ceros
ones: crea un tensor con las dimensiones brindadas, lleno de unos
random: crea un tensor con valores aleatorios entre un mínimo y máximo
arange: crea un tensor unidimensional con valores secuenciales desde start hasta end (no inclusivo)
Constructores
Constructor de copia: copia profunda (deep copy)
Asignador de copia (operator=): libera memoria antes de copiar
Constructor de movimiento: transfiere la propiedad del puntero
Asignador de movimiento: toma posesión de recursos del objeto temporal
Operaciones
Suma (+)
Resta (-)
Multiplicación elemento a elemento (*)
Multiplicación por escalar
Operaciones avanzadas
view: reinterpretación sin copia
unsqueeze: agrega una dimensión de tamaño 1
concat: une múltiples tensores en una dimensión
dot: producto punto
matmul: multiplicación matricial
Transformaciones
ReLU: y = max(0, x)
Sigmoid: y = 1 / (1 + e^{-x})
🧠 Red neuronal

El programa incluye una simulación con el siguiente flujo:

Entrada: 1000 × 20 × 20
Transformación a 1000 × 400
Multiplicación por pesos 400 × 100
Suma de bias 1 × 100 (con broadcasting)
Activación ReLU
Multiplicación por pesos 100 × 10
Suma de bias 1 × 10
Activación Sigmoid
⚠️ Notas importantes
Los tensores tipo view comparten memoria (no copian datos)
Se usa is_view para evitar liberar memoria dos veces
La suma soporta broadcasting básico para bias {1, N}
👨‍💻 Autor
Joaquin Llallire
Maydelith Zuñiga
