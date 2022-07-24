# Prueba algorítmica.

Dado que el embudo se provoca a la hora de usar la función que guarda en la base de datos, se propone el uso de hilos, de esta forma el programa principal asigna la tarea a los hilos y no se detiene mientras que se guarda cada dato, el programa principal se encarga de repartir el trabajo en hilos y se detiene unicamente a esperar que todos los hilos hayan terminado la tarea.

En la carpeta first, el archivo original.cpp contiene el codigo original en c++, en solution1.cpp se hace el uso de una cantidad N hilos, esto permite evidenciar el tiempo que toma el proceso con diferente numeros de hilos, por ultimo en solution2.cpp se refactoriza el codigo original asignando un unico dato a cada hilo, tambien se cambia el arreglo por una lista, de esta forma es posible eliminar el dato una vez que es guardado en la base de datos.

Para procesar 1000 datos con programa original se demoraba aproximadamente 500 segundos, con el uso de 500 hilos en la segunda solucion se tarda aproximadamente 2 segundos, mientras con la segunda solucion, usando un hilo por cada dato tarda al rededor de 1 segundo
