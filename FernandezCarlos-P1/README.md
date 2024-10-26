# Practica 1 - Metodos Numéricos II 2024-2025 Otoño

Este fichero incluye una guia de uso de los programas, la memoria se encuentra en el archivo [MEMORIA.pdf](MEMORIA.pdf).

## Guia de uso

### Gauss-Seidel

Este programa esta pensado para poder resolver cualquier problema como el planteado (que tenga solucion). Para ello se ha separado la declaración de las funciones y constantes necesarias. Por esto, para usar el programa hay que crear un archivo que las contenga, vease "f1.c" como ejemplo, donde se implementan las funciones del punto 4 de la practica.

Una vez se ha archivo anterior, se compilan por separado dicho archivo y "gauss-seidel.c". A continuación se montan juntos: 

``` 
	gcc -c -ansi -Wall f1.c
	gcc -c -ansi -Wall gauss-seidel.c
	gcc f1.o gauss-seidel.o -o gauss-seidel.exe -lm
```

Una vez montado ya tenemos el ejecutable que necesitamos. Mediante `./gauss-seidel.exe` ejecutamos el archivo. Introducimos el valor de N deseado y la tolerancia que se utilizara como condicion de parada. 
Seguidamente se ejecutará el método iterativo que parará cuando la norma infinito entre terminos consecutivos sea menor a la tolerancia. Se ha definido un numero maximo de iteraciones como medida de seguridad, su valor predeterminado es 100.000, si se requere de mas iteraciones cambie el valor de la constante `ITER_MAX` y recompile.
El programa le mostrara si la iteracion ha convergido, en cuantas iteraciones y a que valor de la norma infinito. Adicionalmente se incluye una aproximación del radio espectral de la matriz de iteración que se utilizará más adelante. 
Finalmente, le pedira un nombre de archivo para guardar la solución, nosotros tomaremos "gauss-seidel.res" a modo de ejemplo. El formato se corresponde con el especificado en el punto 3 de la practica. 

### SOR

Analogamente al caso anterior, se ha de escribir las condiciones del problema en un archivo, como "f1.c". Se ha de compilar y montar como el caso anterior los archivos "sor-find-omega.c" y "sor.c" para obtener los ejecutables "sor-find-omega.exe" y "sor.exe".
Se ejecutara "sor-find-omega.exe" para probar los valores posibles de omega y se seleccionara el que converja mas rapido.
Ahora se ejecuta el archivo "sor.exe" y se introducen los parametros anteriores junto al valor de omega. Se obtienen los resultados de forma analoga al metodo Gauss-Seidel.

### Comprobar Errores

Para comprobar si las soluciones dadas por uno de los metodos anteriores se ha de compilar y montar el archivo "check.c" (utilizando el "f1.c" tambien). Entonces se ejecuta y se pasa el nombre del archivo que contiene los datos devueltos por uno de los programas anteriores. Este devuelve la norma infinito del vector diferencia del vector del archivo y el calculado por la funcion 'solution'.
