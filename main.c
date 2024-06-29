// Bibliotecas a utilizar.
#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 101

// Definición de la estructura contraseña.
typedef struct {
  char *contra;  // Variable de contraseña única
  char *sitio;   // Variable que almacena el sitio que ingresa el usuario
  int seguridad; // 1: bajo, 2: medio, 3: alto
  char *link;    // Variable que almacena el link del sitio
  bool permiteMasContra; // Booleano que prevee las colisiones
  List *contrasenas;     // Lista de contraseñas
} contrasena;

const char caracteres[] =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789!@#$%^&*()_+"; // Todos los caracteres que se pueden usar en genContraAzar
                              
// Función que genera una contraseña aleatoria.
void genContraAzar(char *contra, int longitud) {
  int num_caracteres = sizeof(caracteres) - 1;
  srand(time(0));

  int tiene_mayuscula = 0;
  int tiene_minuscula = 0;
  int tiene_numero = 0;
  // En el ciclo do while se van insertando las letras aleatorias en la
  // contraseña.
  do {
    for (int i = 0; i < longitud; i++) {
      contra[i] = caracteres[rand() % num_caracteres];
    }
    contra[longitud] = '\0';

    tiene_mayuscula = 0;
    tiene_minuscula = 0;
    tiene_numero = 0;
    // En este for se analiza la contraseña para ver si cumple con los
    // requisitos
    for (int i = 0; i < longitud; i++) {
      if (isupper(contra[i])) { // Si tiene mayúscula
        tiene_mayuscula = 1;
      } else if (islower(contra[i])) { // Si tiene minúscula
        tiene_minuscula = 1;
      } else if (isdigit(contra[i])) { // Si contiene un digito
        tiene_numero = 1;
      }
    }
  } while (!(tiene_mayuscula && tiene_minuscula && tiene_numero));
}

// Función que verifica la seguridad de la contraseña.
int verificarSeguridad(const char *contra, int *faltan_mayuscula,
                       int *faltan_minuscula, int *faltan_numero) {
  int longitud = 0;
  int tiene_mayuscula = 0;
  int tiene_minuscula = 0;
  int tiene_numero = 0;

  *faltan_mayuscula = 1;
  *faltan_minuscula = 1;
  *faltan_numero = 1;
  // En el ciclo va verificando todos los criterios de seguridad que debe tener
  // la contraseña ingresada.
  while (contra[longitud] != '\0') {
    if (isupper(contra[longitud])) {
      tiene_mayuscula = 1;
      *faltan_mayuscula = 0;
    } else if (islower(contra[longitud])) {
      tiene_minuscula = 1;
      *faltan_minuscula = 0;
    } else if (isdigit(contra[longitud]) != 0) {
      tiene_numero = 1;
      *faltan_numero = 0;
    }
    longitud++;
  }
  // Se determina el nivel de seguridad de la contraseña.
  if (longitud < 5) {
    return 1; // Seguridad baja
  } else if (tiene_mayuscula && tiene_minuscula && tiene_numero) {
    return 3; // Seguridad alta
  } else {
    return 2; // Seguridad media
  }
}

// Función para mostrar los sitios web de las contraseñas.
void mostrarMapa(Map *map) {

  MapPair *iter = map_first(map);
  int i = 1;
  // Se recorre el mapa y se imprimen los sitios web.
  while (iter != NULL) {
    char *sitio = (char *)iter->key;
    printf("%d) Sitio: %s\n", i, sitio);
    iter = map_next(map);
    i++;
  }
}

// Función para buscar un sitio web en el mapa.
MapPair *buscarClaveMapa(Map *map, int sitio) {
  MapPair *pair = map_first(map);
  for (int i = 1; i < sitio; i++) {
    pair = map_next(map);
  }
  return pair;
}

/*Función Introducir Contraseña Usuario
Función auxiliar que lleva al usuario a crear su propia contraseña.*/
char *FICU(char *contra) {
  // Declaración de una variable estática para almacenar la contraseña segura
  static char contraSegura[MAX];

  // Muestra los criterios de seguridad para la contraseña
  puts("Criterios del sistema para una contraseña segura:");
  puts("- Debe contener al menos 5 caracteres");
  puts("- Debe contener un caracter numérico");
  puts("- Debe contener una mayúscula");
  puts("- Debe contener una minúsucla");
  int condicion = 0;
  
  do {
    // Solicita al usuario que ingrese una contraseña
    printf("Contraseña: ");
    scanf("%100s", contra);
    // Variables para verificar la falta de ciertos tipos de caracteres
    int faltanMayuscula = 0, faltanMinuscula = 0, faltanNumero = 0;
    // Verifica la seguridad de la contraseña y actualiza las variables de falta de caracteres
    int seguridad = verificarSeguridad(contra, &faltanMayuscula,
                                       &faltanMinuscula, &faltanNumero);
    if (seguridad == 1) {
      // Si la contraseña no es segura, muestra mensajes de error
      puts("Su contraseña no es segura, por favor intente de nuevo.");
      if (faltanMayuscula)
        puts("Falta una mayúscula.");
      if (faltanMinuscula)
        puts("Falta una minúscula.");
      if (faltanNumero)
        puts("Falta un número.");
      if (strlen(contra) < 5)
        puts("Son menos de 5 caracteres.");
    } else if (seguridad == 2) {
      // Si la contraseña es medianamente segura, muestra mensajes de error
      puts("Su contraseña es medianamente segura, por favor intente de nuevo.");
      if (faltanMayuscula)
        puts("Falta una mayúscula.");
      if (faltanMinuscula)
        puts("Falta una minúscula.");
      if (faltanNumero)
        puts("Falta un número.");
    } else {
      // Si la contraseña es completamente segura, muestra un mensaje de éxito y guarda la contraseña
      puts("Su contraseña es completamente segura!");
      condicion = 3;
      strcpy(contraSegura, contra);
    }
  } while (condicion != 3);

  return contraSegura;
}

/*Función Introducir Contraseña Aleatoria
Función auxiliar que crea una contraseña aleatoria para el usuario*/
char *FICA(char *contra) {
  static char contraSegura[MAX];
  int longitud = 0;
  printf("Introduce la longitud de la contraseña (longitud mínima: 5): ");
  while (longitud < 5) {
    if (longitud > 0)
      printf("Ingrese longitud de contraseña: ");
    scanf("%d", &longitud);
    if (longitud < 5) {
      puts(
          "Longitud de contraseña menor al mínimo seguro, intente nuevamente.");
    }
  }
  genContraAzar(contra, longitud);
  strcpy(contraSegura, contra);
  printf("Contraseña generada: %s\n", contra);
  return contraSegura;
}

/* Función para insertar un nuevo sitio en el mapa */
void insertarSitioNew(void *map) {
  char sitio[MAX];
  char link[MAX];
  int respuesta2;
  int respuesta1;
  char contra[MAX];
  
  // Solicita al usuario ingresar el nombre del sitio web 
  printf("\nIngrese nombre del sitio web y link:\n");
  printf("Sitio: ");
  getchar();
  scanf("%[^\n]s", sitio);

  if (map_search(map, sitio) != NULL) {
    printf("El sitio ya existe, por favor ingrese otro sitio!\n");
    return;
  }

  contrasena *nuevaContrasena = malloc(sizeof(contrasena));
  nuevaContrasena->contrasenas = NULL;
  nuevaContrasena->contra = NULL;

  printf("Link: ");
  scanf("%100s", link);

  printf("¿Este sitio permite más contraseñas?\n");
  printf("1) Si\n");
  printf("2) No\n");
  printf("Ingrese una opción: ");
  scanf("%d", &respuesta1);

  printf("¿Desea crear una contraseña aleatoria?\n");
  printf("1) Si\n");
  printf("2) No\n");
  printf("Ingrese una opción: ");
  scanf("%d", &respuesta2);

  if (respuesta2 == 1) {

    char *contraSegura = FICA(contra);
    nuevaContrasena->contra = malloc(strlen(contraSegura) + 1);
    strcpy(nuevaContrasena->contra, contraSegura);
  } else {
    char *contraSegura = FICU(contra);
    nuevaContrasena->contra = malloc(strlen(contraSegura) + 1);
    strcpy(nuevaContrasena->contra, contraSegura);
  }
  nuevaContrasena->seguridad = 3;

  if (respuesta1 == 1) {
    nuevaContrasena->permiteMasContra = 1;
    nuevaContrasena->contrasenas = list_create();
    nuevaContrasena->contra = NULL;
    char *nuevaContra = malloc(strlen(contra) + 1);
    strcpy(nuevaContra, contra);

    list_pushFront(nuevaContrasena->contrasenas, nuevaContra);
  } else {

    nuevaContrasena->permiteMasContra = 0;
  }

  nuevaContrasena->sitio = malloc(strlen(sitio) + 1);
  strcpy(nuevaContrasena->sitio, sitio);
  nuevaContrasena->link = malloc(strlen(link) + 1);
  strcpy(nuevaContrasena->link, link);

  map_insert(map, nuevaContrasena->sitio, nuevaContrasena);
  presioneTeclaParaContinuar();
}

/*Función que inserta la contraseña en un sitio ya registrado
Para efectuarla, se necesita que el/los sitios ingresados permitan más de una contraseña */
void insertarSitioReg(Map *map) {
  char *contraSegura;
  printf("\nSitios Registrados:\n");
  if (map_first(map) == NULL) {
    puts("No hay sitios registrados.");
    presioneTeclaParaContinuar();
    return;
  }//Verficamos si hay sitios registrados
  mostrarMapa(map);
  int sitio;
  printf("\nIngrese el indice del sitio al cual le desee crear una nueva "
         "contraseña: ");
  scanf("%d", &sitio);
  puts("");

  MapPair *pair = buscarClaveMapa(map, sitio);
//Se busca el sitio y se efectuan los condicionales
  if (pair != NULL) {
    contrasena *contra = (contrasena *)pair->value;
    if (contra->permiteMasContra == true) {

      int respuesta1;
      printf("¿Desea crear una contraseña aleatoria?\n");
      printf("1) Si\n");
      printf("2) No\n");
      printf("Ingrese una opción: ");
      scanf("%d", &respuesta1);

      char contra1[MAX];
      int condicion;

      if (respuesta1 == 1) {
        char *contraSegura = FICA(contra1);
        char *nuevaContra = malloc(strlen(contraSegura) + 1);
        strcpy(nuevaContra, contraSegura);
        list_pushBack(contra->contrasenas, contraSegura);
      } else {
        char *contraSegura = FICU(contra1);
        char *nuevaContra = malloc(strlen(contraSegura) + 1);
        strcpy(nuevaContra, contraSegura);
        list_pushBack(contra->contrasenas, contraSegura);
      }
    } else {//Si el booleano de la estructura es false
      printf("El sitio ingreaso no permite más contraseñas\n");
    }

  } else {//Si el sitio no existe
    printf("El sitio ingreaso no existe\n");
  }
  presioneTeclaParaContinuar();
}

//Función que imprime el menú para la primera función del main
void imprimirMenu1(Map *mapa) {
  int opcion;
  bool salir = false;
  do {
    limpiarPantalla();
    puts("1) Insertar/crear nueva contraseña:");
    puts("    1) Insertar un sitio y contraseña nuevas");
    puts("    2) Insertar constraseña en un sitio ya registrado");
    puts("    3) Salir de este menú");
    printf("Ingrese su opción: ");
    scanf(" %d", &opcion);
    switch (opcion) {
    case 1:
      insertarSitioNew(mapa);
      limpiarPantalla();
      break;
    case 2:
      insertarSitioReg(mapa);
      break;
    case 3:
      salir = true;
      puts("\nSaliendo de este menú...\n");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
  } while (!salir);
}

// Función para buscar contraseñas
void buscarContrasena(Map *map) {
  // En esta función se ingresa un sitio web y si existe se mostrará una lista
  // con las contraseñas contenidas
  limpiarPantalla();
  int i = 1;
  puts("Sitios actuales registrados:");
  if (map_first(map) == NULL) {
    puts("No hay ningun sitio registrado");
    return;
  }//Verificamos si hay sitios regitrados

  mostrarMapa(map);

  int sitio;
  printf("\nIngrese el indice del sitio al cual le desee buscar contraseñas: ");
  scanf("%d", &sitio);
  puts("");

  MapPair *pair = buscarClaveMapa(map, sitio);
  // Se busca el sitio en el mapa y si este existe se muestran sus claves y si
  // no existe se muestra un mensaje
  if (pair != NULL) {
    contrasena *contra = (contrasena *)pair->value;

    if (contra->permiteMasContra == true) {
      char *item = list_first(contra->contrasenas);
      while (item != NULL) {
        printf("Contraseña %i: %s\n", i, item);
        item = (char *)list_next(contra->contrasenas);
        i++;
      }
    } else {
      printf("Contraseña: %s\n", contra->contra);
    }
  } else {
    printf("El sitio ingresado no existe\n");
  }
  puts("");
}

//Función que elimina la contraseña del sitio que el usuario escoja
void eliminarContrasena(Map *map) {
  limpiarPantalla();
  puts("Sitios actuales registrados:");
  
  if (map_first(map) == NULL) {
    puts("No hay ningun sitio registrado");
    return;
  }//Verificamos si hay sitios regitrados
  mostrarMapa(map);

  int sitio;
  printf("Ingrese el sitio al cual le desee eliminar alguna contraseña: ");
  scanf("%d", &sitio);

  MapPair *pair = buscarClaveMapa(map, sitio);

  if (pair != NULL) {
    printf("CONTRASEÑAS: \n");
    contrasena *contra = (contrasena *)pair->value;
    puts("");
    if (contra->permiteMasContra == true) {//Si el sitio permite más contraseñas, se muestra la lista de ellas
      int cont = 1;
      char *item = (char *)list_first(contra->contrasenas);
      while (item != NULL) {
        printf("%d) Contraseña: %s\n", cont, item);
        cont++;
        item = (char *)list_next(contra->contrasenas);
      }
      if (cont == 2) {
        puts("");
        printf("Solo hay una contraseña registrada, ¿Desea eliminarla?\n(Si la "
               "eliminas el sitio sera eliminado)\n");
        printf("1) Si\n");
        printf("2) No\n");
        printf("Ingrese una opción: ");
        int respuesta;
        scanf("%d", &respuesta);
        if (respuesta == 1) {
          list_popFront(contra->contrasenas);
          map_remove(map, contra->sitio);
          printf("Contraseña eliminada y sitio eliminado\n");
        } else {
          puts("");
          printf("Contraseña no eliminada\n");
        }
      } else {
        puts("");
        int numero;
        printf("Ingrese el numero de la contraseña que desea eliminar: ");
        do {
          scanf("%d", &numero);
        } while (numero < 1 || numero >= cont);

        cont = 1;
        item = (char *)list_first(contra->contrasenas);
        while (cont != numero) {
          cont++;
          item = (char *)list_next(contra->contrasenas);
        }
        list_popCurrent(contra->contrasenas);
        printf("Contraseña eliminada\n");
      }
    } else {//Si el sitio tiene solo una contraseña
      printf("Contraseña: %s\n", contra->contra);
      puts("");
      printf("Solo hay una contraseña registrada, ¿Desea eliminarla?\n(Si la "
             "eliminas el sitio sera eliminado)\n");
      printf("1) Si\n");
      printf("2) No\n");
      printf("Ingrese una opción: ");
      int respuesta;
      scanf("%d", &respuesta);
      if (respuesta == 1) {
        free(contra->contra);
        contra->contra = NULL;
        map_remove(map, contra->sitio);
        printf("Contraseña eliminada y sitio eliminado\n");
      } else {
        printf("Contraseña no eliminada\n");
      }
    }
  } else {//Si el sitio no existe
    printf("El sitio/página no existe.\n");
  }
}

//Función que cambia la contraseña del sitio que el usuario escoja
void cambiarContrasena(Map *map) {
  limpiarPantalla();
  int i = 1;
  puts("Sitios actuales registrados:");

  if (map_first(map) == NULL) {
    puts("No hay ningún sitio registrado.");
    return;
  }//Verificamos si hay sitios regitrados

  mostrarMapa(map);

  int sitio;
  printf("Ingrese el indice sitio para cambiar la contraseña: ");
  scanf("%d", &sitio);

  MapPair *pair = buscarClaveMapa(map, sitio);

  if (pair != NULL) {
    contrasena *contra = (contrasena *)pair->value;

    if (contra->permiteMasContra == 1) {
      char *item = (char *)list_first(contra->contrasenas);
      while (item != NULL) {
        printf("%d) Contraseña: %s\n", i, item);
        i++;
        item = (char *)list_next(contra->contrasenas);
      }

      printf("Ingrese el número de la contraseña que desea cambiar: ");
      int opcion;
      scanf("%d", &opcion);

      list_first(contra->contrasenas);

      for (int j = 1; j < opcion; j++) {
        list_next(contra->contrasenas);
      }

      char nuevaContrasena[MAX];
      char contraSegura[MAX];

      int respuesta2;
      printf("¿Desea crear una contraseña aleatoria?\n");
      printf("1) Si\n");
      printf("2) No\n");
      printf("Ingrese una opción: ");
      scanf("%d", &respuesta2);

      if (respuesta2 == 1) {
        strcpy(contraSegura, FICA(nuevaContrasena));

      } else {
        strcpy(contraSegura, FICU(nuevaContrasena));
      }
      list_replaceCurrent(contra->contrasenas, strdup(contraSegura));

      printf("Contraseña cambiada exitosamente.\n");
    } else {

      char nuevaContrasena[MAX];
      char contraSegura[MAX];
      int respuesta2;
      printf("¿Desea crear una contraseña aleatoria?\n");
      printf("1) Si\n");
      printf("2) No\n");
      printf("Ingrese una opción: ");
      scanf("%d", &respuesta2);

      if (respuesta2 == 1) {
        strcpy(contraSegura, FICA(nuevaContrasena));

      } else {
        strcpy(contraSegura, FICU(nuevaContrasena));
      }

      if (contra->contra) {
        free(contra->contra);
      }
      contra->contra = strdup(contraSegura);

      printf("Contraseña cambiada exitosamente.\n");
    }
  } else {
    printf("El sitio ingresado no está registrado.\n");
  }
}

//Función que importa las contraseñas
void importarContrasenas(void *map) {
  limpiarPantalla();
  puts("========================================");
  puts("|   Sistema de Gestión de Contraseñas  |");
  puts("========================================");
  char linea[MAX];
  
  FILE *archivo = fopen("Importar.csv", "r");
  if (archivo == NULL) {
    printf("No se pudo abrir el archivo para leer.\n");
    return;
  }
  fgets(linea, MAX, archivo);
  while (fgets(linea, MAX, archivo) != NULL) {
    contrasena *nuevaContra = malloc(sizeof(contrasena));
    nuevaContra->contrasenas = NULL;
    char *token = strtok(linea, ",");

    nuevaContra->sitio = malloc(strlen(token) + 1);
    strcpy(nuevaContra->sitio, token);

    token = strtok(NULL, ",");
    nuevaContra->contra = malloc(strlen(token) + 1);
    strcpy(nuevaContra->contra, token);

    token = strtok(NULL, ",");
    nuevaContra->seguridad = atoi(token);

    token = strtok(NULL, ",");
    nuevaContra->link = malloc(strlen(token) + 1);
    strcpy(nuevaContra->link, token);

    token = strtok(NULL, ",");
    nuevaContra->permiteMasContra = (strcmp(token, "1") == 0);

    if (nuevaContra->permiteMasContra) {
      nuevaContra->contrasenas = list_create();
      token = strtok(NULL, "\n"); 
      if (token != NULL && strcmp(token, "NULL") != 0) {
        char *subtoken = strtok(token, "--");
        while (subtoken != NULL) {
          char *contra = malloc(strlen(subtoken) + 1);
          strcpy(contra, subtoken);
          list_pushBack(nuevaContra->contrasenas, contra);
          subtoken = strtok(NULL, "--");
        }
      }
    } else {
      nuevaContra->contrasenas = NULL;
    }

    map_insert(map, nuevaContra->sitio, nuevaContra);
  }
  fclose(archivo);
  printf("Contraseñas cargadas exitosamente desde Importar.csv.\n");
}

//Función que exporta las contraseñas
void exportarContrasenas(Map *map) {
  limpiarPantalla();
  puts("========================================");
  puts("|   Sistema de Gestión de Contraseñas  |");
  puts("========================================");
  if(map_first(map) == NULL){puts("No se tienen contraseñas registradas, no se exportará nada"); return;}//Verificamos si hay sitios regitrados
  FILE *archivo = fopen("Exportar.csv", "w");
  if (archivo == NULL) {
    perror("Error al abrir el archivo para exportar contraseñas");
    return;
  }

  fprintf(archivo, "Sitio,Contraseña,Seguridad,Link,PermiteMasContra,"
                   "ListaDeContraseñas\n");

  MapPair *iter = map_first(map);
  while (iter != NULL) {
    contrasena *entradaActual = (contrasena *)iter->value;

    fprintf(archivo, "%s,%s,%d,%s,%d,", entradaActual->sitio,
            entradaActual->contra, entradaActual->seguridad,
            entradaActual->link, entradaActual->permiteMasContra);

    if (entradaActual->permiteMasContra && entradaActual->contrasenas) {
      char *item = list_first(entradaActual->contrasenas);
      while (item != NULL) {
        fprintf(archivo, "%s", item);
        item = list_next(entradaActual->contrasenas);
        if (item != NULL) {
          fprintf(archivo, "--");
        }
      }
    } else {
      fprintf(archivo, "NULL");
    }
    fprintf(archivo, "\n");

    iter = map_next(map);
  }

  fclose(archivo);
  printf("Contraseñas exportadas exitosamente a %s\n", "Exportar.csv");
}

// Función que copia al portapapeles en Linux
void copiarCportapapeles(const char *texto) {
#ifdef _WIN32
  const size_t len = strlen(texto) + 1;
  HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
  memcpy(GlobalLock(hMem), texto, len);
  GlobalUnlock(hMem);
  OpenClipboard(0);
  EmptyClipboard();
  SetClipboardData(CF_TEXT, hMem);
  CloseClipboard();
  GlobalFree(hMem);
  printf("Contraseña copiada al portapapeles.\n");
#else
  char comando[512];
  snprintf(comando, sizeof(comando), "echo '%s' | xclip -selection clipboard",
           texto);
  system(comando);
  printf("Contraseña copiada al portapapeles.\n");
#endif
}

// Función que hace de "interfaz" a copiarCportapapeles
void copiarContrasenaAlPortapapeles(Map *map) {
  limpiarPantalla();
  puts("Sitios actuales registrados:");
  if (map_first(map) == NULL) {
    puts("No hay ningun sitio registrado");
    return;
  } //Verificamos si hay sitios regitrados
  mostrarMapa(map);
  //Se pregunta por el sitio, se busca y se efectuan los condicionales
  int sitio;
  printf("Ingrese el sitio para cambiar la contraseña: ");
  scanf("%d", &sitio);

  MapPair *pair = buscarClaveMapa(map, sitio);

  if (pair != NULL) {
    contrasena *contra = (contrasena *)pair->value;

    if (contra->permiteMasContra == true) {
      char *item = list_first(contra->contrasenas);
      int i = 1;
      while (item != NULL) {
        printf("%d) Contraseña: %s\n", i, item);
        i++;
        item = (char *)list_next(contra->contrasenas);
      }
      printf("Ingrese el número de la contraseña que desea copiar: ");
      int opcion;
      scanf("%d", &opcion);
      char *aux = (char *)list_first(contra->contrasenas);
      for (int j = 1; j <= opcion; j++) {
        aux = list_next(contra->contrasenas);
      }
      char *contraACopiar = aux;
      copiarCportapapeles(contraACopiar);
    } else {
      copiarCportapapeles(contra->contra);
    }
  } else {
    printf("El sitio ingresado no está registrado.\n");
  }
  presioneTeclaParaContinuar();
}

// SE MUESTRA EL MENÚ PRINCIPAL DE LA APP
void mostrarMenuPrincipal() {
  // Mediante la función puts, mostramos las opciones disponibles
  limpiarPantalla();
  puts("========================================");
  puts("|   Sistema de Gestión de Contraseñas  |");
  puts("========================================");

  puts("1) Insertar/crear nueva contraseña");
  puts("2) Buscar contraseña");
  puts("3) Eliminar contraseña");
  puts("4) Cambiar contraseña");
  puts("5) Copiar contraseña al portapapeles");
  puts("6) Importar contraseñas");
  puts("7) Exportar contraseñas");
  puts("8) Salir");
  puts("*AVISO* Si sale del programa sin exportar sus contraseñas estás se "
       "eliminaran.");
}

// Main del programa
int main() {
  int opcion;
  // Se crea la tabla hash que se usará para guardar las contraseñas
  Map *map = map_create(is_equal_str);
  do {

    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %d", &opcion);

    switch (opcion) {
    case 1:
      imprimirMenu1(map);
      break;
    case 2:
      buscarContrasena(map);
      break;
    case 3:
      eliminarContrasena(map);
      break;
    case 4:
      cambiarContrasena(map);
      break;
    case 5:
      copiarContrasenaAlPortapapeles(map);
      break;
    case 6:
      importarContrasenas(map);
      break;
    case 7:
      exportarContrasenas(map);
      break;
    case 8:
      puts("Saliendo del programa...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != 8);
  map_clean(map);

  return 0;
}
