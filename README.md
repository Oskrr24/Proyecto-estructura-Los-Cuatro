# Proyecto-estructura-Los-Cuatro
# Sistema de Gestión de Contraseñas

# Descripción

Este proyecto implementa un sistema de gestión de contraseñas utilizando un mapa para almacenar las contraseñas asociadas a diferentes sitios web. Los sitios pueden tener una o múltiples contraseñas, y el sistema permite agregar, buscar, eliminar, cambiar, copiar al portapapeles, importar y exportar contraseñas.

---
# Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Usa el link de abajo que te llevará directamente a la aplicación
3. [Repl.it](https://replit.com/@oscarruizf/Tarea-1-estructura).
4. Presiona el botón "Run" para compilar y ejecutar la aplicación.

# Funciones propias del programa

Estas son las funciones principales del programa y sus funcionalidades:

- imprimirMenu1: Esta funcion muestra el menú relacionado con las funciones "Insertar/crear nueva contraseña", donde se puede:

1) Insertar un sitio y contraseña nuevas: Esta función nos permite insertar un sitio nuevo junto a una nueva contraseña, se preguntara al usuario si desea que el sitio solo permita una contraseña o si el sitio permite mas de una contraseña.
   
2) Insertar constraseña en un sitio ya registrado: El programa le preguntara al usuario el sitio al cuál desee agregar una nueva contraseña, siempre que el sitio permita mas de una contraseña, caso contrario, se le avisara al usuario que el sitio no permite más contraseñas.

3) Salir de este menú: Se regresa al menú principal.

- buscarContrasena: Esta función mostrara los sitios registrados, se le pedira al usuario que ingrese el número del sitio al cuál desee buscar la contraseña, despues de eso el programa mostrara la/las contraseñas que contenga el sitio.

- eliminarContrasena: El programa le pedira al usuario el numero del sitio al cuál desee eliminar la contraseña, si el sitio solo tiene una contraseña, el sitio tambien se eliminara.

- cambiarContrasena: Se mostraran los sitios registrados, el usuario debera ingresar el nombre del sitio al que desee cambiar la contraseña, una vez seleccionado el sitio, el usuario debera ingresar en numero de la contraseña a cambiar, se preguntara si se desea crear una contraseña nueva aleatoria o una original creada por el usuario, dependiendo de la opción escogida se realizara la operación correspondiente.

- copiarContrasenaAlPortapapeles: Esta función copia la contraseña al portapapeles del sistema del sitio que el usuario escoja. Si no se tienen sitios registrados, se mostrará un mensaje acusando la situación. Esta función solo funcióna en sistemas Linux.

- importarContrasenas: Esta función copia las contraseñas del archivo csv que el usuario tiene que subir previamente al programa. Si el archivo está vacío, no se importará nada.

- exportarContrasenas: Esta función copia las contraseñas actuales registradas en la aplicación a un archivo csv que previamente el usuario tiene que subir, si el usuario no tiene contraseñas registradas, no se copiara nada.

# Funcionando correctamente

- Todas las funciones nombradas anteriormente (desde insertar, hasta salir del programa)

# Problemas conocidos

- Cuando pones un caracter no numerico en la funcion "insertarSitioNew" el programa colapsa y entra en un ciclo infinito.
- Si el nombre del archivo para importar o exportar contraseñas es distinto a "Importar" o "Exportar", se mostrará el nombre de "Importar" o "Exportar" igualmente, aunque el archivo subido no se llame así.

# A mejorar

- Se podria mejorar un aspecto en varias funciones, en donde el usuario coloca una opcion no disponible, la funcion arroja al usuario al menú principal.
  
- Se podrian mejorar los problemas conocidos anteriormende dichos.

# Como interactuar con el programa.

Al ejecutar el programa se mostrara el menú principal:

````
========================================
|   Sistema de Gestión de Contraseñas  |
========================================
1) Insertar/crear nueva contraseña
2) Buscar contraseña
3) Eliminar contraseña
4) Cambiar contraseña
5) Copiar contraseña al portapapeles
6) Importar contraseñas
7) Exportar contraseñas
8) Salir
*AVISO* Si sale del programa sin exportar sus contraseñas estás se eliminaran.
Ingrese su opción: 
````
El Usuario deberá seleccionar la opción que desee para administrar sus contraseñas, a continuación se mostrara un ejemplo de como el usuario debe interactuar con el programa:

## Para la opción 1:

Al seleccionar la primera opción se mostrara el siguiente menú:

````
1) Insertar/crear nueva contraseña:
    1) Insertar un sitio y contraseña nuevas
    2) Insertar constraseña en un sitio ya registrado
    3) Salir de este menú
Ingrese su opción: 
````
Al seleccionar la opción 1, el usuario podra ingresar un sitio nuevo junta a su contraseña, la cual puede ser generada aleatoriamente o creada por él mismo.

Ejemplo de uso:

````
Ingrese nombre del sitio web y link:
Sitio: Youtube
Link: https://www.youtube.com
¿Este sitio permite más contraseñas?
1) Si
2) No
Ingrese una opción: 1
¿Desea crear una contraseña aleatoria?
1) Si
2) No
Ingrese una opción: 1
Introduce la longitud de la contraseña (longitud mínima: 5): 9
Contraseña generada: cW9#(e_!k
Presione una tecla para continuar...
````
Al seleccionar la opción 2, el usuario podra seleccionar un sitio ya registrado y crear una nueva contraseña (siempre que el sitio permita más de una contraseña).

Ejemplo de uso:

````
Sitios Registrados:
1) Sitio: Youtube

Ingrese el indice del sitio al cual le desee crear una nueva contraseña: 1

¿Desea crear una contraseña aleatoria?
1) Si
2) No
Ingrese una opción: 1
Introduce la longitud de la contraseña (longitud mínima: 5): 9
Contraseña generada: Xp(!akZY3
Presione una tecla para continuar...
````

Y por último, al seleccionar la opción 3, el programa regresara al menú principal.


## Para la opción 2:

Al seleccionar la opción 2, se mostraran los sitios registrados y el usuario podra seleccionar el número del sitio al que desee buscar su/sus contraseñas.

Ejemplo de uso:
````
Sitios actuales registrados:
1) Sitio: Youtube

Ingrese el indice del sitio al cual le desee buscar contraseñas: 1

Contraseña 1: lEC1CecUQ

Presione una tecla para continuar...
````

## Para la opción 3

Al seleccionar la opción 3, el usuario debera seleccionar el numero del sitio al cuál desee eliminar su contraseña, si dicho sitio tiene solo una contraseña, el sitio tambien sera eliminado.

Ejemplo de uso:
````
Sitios actuales registrados:
1) Sitio: Youtube
Ingrese el sitio al cual le desee eliminar alguna contraseña: 1
CONTRASEÑAS: 

1) Contraseña: Ww9URh)(!

Solo hay una contraseña registrada, ¿Desea eliminarla?
(Si la eliminas el sitio sera eliminado)
1) Si
2) No
Ingrese una opción: 1
Contraseña eliminada y sitio eliminado
Presione una tecla para continuar...
````

## Para la opción 4

Al seleccionar la opción 4, el usuario debera seleccionar el numero del sitio al cuál desee cambiar su contraseña, una vez seleccionado se preguntara si se desea que la contraseña nueva sea creada de forma aleatoria.

Ejemplo de uso:
````
Sitios actuales registrados:
1) Sitio: Youtube
Ingrese el indice sitio para cambiar la contraseña: 1
1) Contraseña: ek5VYXV^k
Ingrese el número de la contraseña que desea cambiar: 1
¿Desea crear una contraseña aleatoria?
1) Si
2) No
Ingrese una opción: 1
Introduce la longitud de la contraseña (longitud mínima: 5): 8
Contraseña generada: 0b@II)UG
Contraseña cambiada exitosamente.
Presione una tecla para continuar...
````
## Para la opción 5

Al seleccionar esta opción, el usuario tendra que seleccionar el número del sitio junto a el número de la contraseña a la cuál desee copiar al portapapeles (Esta función unicamente funciona en los sistemas de Linux).

Ejemplo de uso (En Windows):
````
Sitios actuales registrados:
1) Sitio: Youtube
Ingrese el sitio para cambiar la contraseña: 1
1) Contraseña: !x%(F9X*z
Ingrese el número de la contraseña que desea copiar: 1
sh: 1: xclip: not found
Contraseña copiada al portapapeles.
Presione una tecla para continuar...
````
## Para la opción 6

Al seleccionar esta opción, se importaran todas las contraseñas del archivo que el usuario ingresó al codigo, mostrando un mensaje acusando si se cargaron exitosamente o hubo un erro en el camino.

Ejemplo de uso:
````
========================================
|   Sistema de Gestión de Contraseñas  |
========================================
Contraseñas cargadas exitosamente desde Importar.csv.
Presione una tecla para continuar...
````

## Para la opción 7

Al seleccionar esta opción, se mostrará al usuario un mensaje acusando si se realizo correctamente la exportación o hubieron problemas en el camino, además de que si no se tienen contraseñas registradas, también se mostrará un mensaje. Toda la magia está en el código.

Ejemplo de uso:
````
========================================
|   Sistema de Gestión de Contraseñas  |
========================================
Contraseñas exportadas exitosamente a Exportar.csv
Presione una tecla para continuar...
````


## Para la opción 8

La opción 8 "Salir" simplemente termina la ejecución del programa y de la aplicación.

Ejemplo de uso:
````
========================================
|   Sistema de Gestión de Contraseñas  |
========================================
1) Insertar/crear nueva contraseña
2) Buscar contraseña
3) Eliminar contraseña
4) Cambiar contraseña
5) Copiar contraseña al portapapeles
6) Importar contraseñas
7) Exportar contraseñas
8) Salir
*AVISO* Si sale del programa sin exportar sus contraseñas estás se eliminaran.
Ingrese su opción: 8
Saliendo del programa...
Presione una tecla para continuar...

````

# Contribucción de cada uno.

- Oscar Ruiz: Creación de las funciones “Insertar contraseña” y “Buscar contraseña”, además de aportar gratamente en las funciones de “Importar” y “Exportar”, además de una gran contribución a la interfaz general del programa. Auto-evaluación: 3 (aporte excelente)

- Marcos Cadiz: El integrante se centró en la realización de la función “Cambiar contraseña” y aportó en las funciónes “Importar contraseña” y "Exportar contraseñas"; junto al rol de testear y buscar errores en el programa. Auto-evaluación: 3 (aporte excelente)

- Milovan Fuentes: Integrante realizó funciones tales como “Ingresar contraseñas en sitios ya registrados”, “Eliminar contraseñas”, también tuvo un gran aporte en la función de “Buscar contraseñas” y realizar testeos de el programa y aporte en solución de errores y bugs. Auto-evaluación: 3 (aporte excelente)

- Amaro Fibla: El integrante se encargo en la creación de las funciones “Copiar contraseña al portapapeles”, “Exportar contraseñas” y ayudó en la función “Importar contraseña”. Auto-evaluación: 3 (aporte excelente)

