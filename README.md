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
Creación de tensores:
zeros: Crea un tensor con las dimenciones brindadas, lleno de ceros
ones: Crea un tensor con las dimenciones brindadas, lleno de unos
random: Crea un tensor con las dimenciones brindadas, con números random entre el min y máx brindado
arange:  crea un tensor unidimensional con valores secuenciales desde start hasta end
(no inclusivo).
Diversos Constructores:
Constructor de Copia: Copia profunda (deep copy) de los datos.
• Asignador de Copia (operator=): Libera la memoria actual antes de copiar
los nuevos datos, manejando la auto-asignación.
• Constructor de Movimiento (move constructor): Transfiere la propiedad
del puntero de datos del objeto origen al nuevo objeto, dejando al origen en un estado
válido pero nulo.
• Asignador de Movimiento (move operator=): Libera los recursos actuales y
tomar posesión de los del objeto temporal.
Operaciones:
Suma (+)
Resta (-)
Multiplicación elemento a elemento (*)
Multiplicación por escalar
Operaciones avanzadas:
view (reinterpretación sin copia)
unsqueeze: permite agregar una dimensión de tamano 1 en una posición específica
del tensor, sin modificar los datos subyacentes.
concat: Permite unir múltiples tensores a lo largo de una dimensión
específica, creando un nuevo tensor con memoria propia.
dot: calcula el producto punto entre dos tensores de igual dimensión
matmul: realizar la multiplicación matricial entre tensores bidimensionales compatibles.
Transformaciones:
ReLU:Aplica la siguiente función al tensor: y = max(0, x)
Sigmoid:Aplica la siguiente función al tensor:  y = 1/(1+e−x)
🧠 Red neuronal

El programa incluye una simulación de red neuronal con el siguiente flujo:

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
La suma soporta broadcasting básico para bias ({1, N})
👨‍💻 Autor
Joaquin Llallire
Maydelith Zuñiga
