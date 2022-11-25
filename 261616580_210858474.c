/*
 * Universidad Andrés Bello
 * Algoritmos y Estructura de Datos
 * NRC 7384 - Campus Antonio Varas
 * Andrés Caraballo, Karina Quilaqueo
 */

#include <stdio.h> // Entrada y salida de datos
#include <stdlib.h> // Funciones de reserva de memoria y misceláneas
#include <string.h> // Manejo de strings con funciones como strcat(), strcpy() y strcmp() 
#include <locale.h> // Uso de tildes y caracteres de otros locales (idiomas) en nuestro programa
#include <stdbool.h> // Uso del tipo de dato 'bool' (V/F)

struct nodoArbol { // Estructura básica de un nodo de un árbol binario
    char info; // Contiene el dato que almacena el nodo
    struct nodoArbol *izq; // Referencia/puntero al subárbol izquierdo
    struct nodoArbol *der; // Referencia/puntero al subárbol derecho
};
typedef struct nodoArbol *AB; // Por conveniencia, designamos un tipo de dato AB, el cual corresponde a un puntero a la estructura de un nodo
int cont; // Contador global, utilizado al convertir de morse a lenguaje natural

/**
 * Función creaNodo
 * Recibe: un caracter, el cual corresponderá al valor almacenado por el nodo
 * Devuelve: un árbol binario con un único nodo y dos referencias nulas a sus hijos
*/
AB creaNodo(char valor) {
   AB aux; // Variable auxiliar
   aux = (AB)malloc(sizeof(struct nodoArbol)); // Reservamos memoria
   if (aux != NULL) { // Si pudimos reservar la memoria sin problemas
      aux->info = valor; // Almacenamos el caracter recibido en el campo 'info' del nodo
      aux->izq = NULL; // Referencia izquierda nula
      aux->der = NULL; // Referencia derecha nula
   }
   else { // En caso de que no hayamos podido reservar la memoria necesaria
       printf("\nMemoria insuficiente. Terminando programa..."); // Finalizamos programa
       exit(1); // Código 1 para indicar al OS que algo salió mal
   }
   return aux; // Si todo salió bien, devolvemos el árbol auxiliar
}

/**
 * Función creaAB
 * Recibe: nada
 * Devuelve: el árbol binario que corresponde al código morse
*/
AB creaAB() {
    AB T;
    T = creaNodo('#');
    T->izq = creaNodo('E');
    T->der = creaNodo('T');
    T->izq->izq = creaNodo('I');
    T->izq->der = creaNodo('A');
    T->der->izq = creaNodo('N');
    T->der->der = creaNodo('M');
    T->izq->izq->izq = creaNodo('S');
    T->izq->izq->der = creaNodo('U');
    T->izq->der->izq = creaNodo('R');
    T->izq->der->der = creaNodo('W');
    T->der->izq->izq = creaNodo('D');
    T->der->izq->der = creaNodo('K');
    T->der->der->izq = creaNodo('G');
    T->der->der->der = creaNodo('O');
    T->izq->izq->izq->izq = creaNodo('H');
    T->izq->izq->izq->der = creaNodo('V');
    T->izq->izq->der->izq = creaNodo('F');
    T->izq->izq->der->der = creaNodo('#');
    T->izq->der->izq->izq = creaNodo('L');
    T->izq->der->izq->der = creaNodo('#');
    T->izq->der->der->izq = creaNodo('P');
    T->izq->der->der->der = creaNodo('J');
    T->der->izq->izq->izq = creaNodo('B');
    T->der->izq->izq->der = creaNodo('X');
    T->der->izq->der->izq = creaNodo('C');
    T->der->izq->der->der = creaNodo('Y');
    T->der->der->izq->izq = creaNodo('Z');
    T->der->der->izq->der = creaNodo('Q');
    T->der->der->der->izq = creaNodo('#');
    T->der->der->der->der = creaNodo('#');
    T->izq->izq->izq->izq->izq = creaNodo('5');
    T->izq->izq->izq->izq->der = creaNodo('4');
    T->izq->izq->izq->der->der = creaNodo('3');
    T->izq->izq->der->der->izq = creaNodo('#');
    T->izq->izq->der->der->der = creaNodo('2');
    T->izq->der->izq->izq->izq = creaNodo('&');
    T->izq->der->izq->izq->der = creaNodo('#');
    T->izq->der->izq->der->izq = creaNodo('+');
    T->izq->der->der->izq->der = creaNodo('#');
    T->izq->der->der->der->der = creaNodo('1');
    T->der->izq->izq->izq->izq = creaNodo('6');
    T->der->izq->izq->izq->der = creaNodo('=');
    T->der->izq->izq->der->izq = creaNodo('/');
    T->der->izq->der->izq->der = creaNodo('#');
    T->der->izq->der->der->izq = creaNodo('(');
    T->der->der->izq->izq->izq = creaNodo('7');
    T->der->der->izq->izq->der = creaNodo('#');
    T->der->der->izq->der->der = creaNodo(165);// �
    T->der->der->der->izq->izq = creaNodo('8');
    T->der->der->der->der->izq = creaNodo('9');
    T->der->der->der->der->der = creaNodo('0');
    T->izq->izq->der->der->izq->izq = creaNodo('?');
    T->izq->izq->der->der->izq->der = creaNodo('_');
    T->izq->der->izq->izq->der->izq = creaNodo('"');
    T->izq->der->izq->der->izq->der = creaNodo('.');
    T->izq->der->der->izq->der->izq = creaNodo('@');
    T->izq->der->der->der->der->izq = creaNodo(39); // '
    T->der->izq->izq->izq->izq->der = creaNodo('-');
    T->der->izq->der->izq->der->izq = creaNodo(';');
    T->der->izq->der->izq->der->der = creaNodo('!');
    T->der->izq->der->der->izq->der = creaNodo(')');
    T->der->der->izq->izq->der->der = creaNodo(',');
    T->der->der->der->izq->izq->izq = creaNodo(':');

    return T;
}

/**
 * Función buscaElemento (RECURSIVA)
 * Recibe: un árbol binario y el caracter a buscar dentro del árbol binario
 * Devuelve: verdadero si el caracter se encuentra dentro del árbol recibido
*/
bool buscaElemento(AB T, char a) {
    if (T == NULL) { return false; } // Si nos encontramos en un árbol vacío, retornamos falso
    if (T -> info == a) { return true; } // Si hemos llegado al nodo que buscábamos, devolvemos verdadero
    return buscaElemento(T -> izq, a) || buscaElemento(T -> der, a); // Por recursividad, queremos reejecutar esta función y revisar si en algún momento retornó verdadero
}

/**
 * Función charAMorse (RECURSIVA)
 * Recibe: un árbol binario, una dirección a un archivo y un caracter a convertir a lenguaje morse
 * Devuelve: vacío
 * Función: imprimir directamente en el archivo los puntos, guiones y espacios correspondientes en morse a un caracter natural
*/
void charAMorse(AB T, FILE *f, char a) {
    if (a == ' ') { // Si el caracter es un espacio
        fprintf(f, " "); // Imprimimos un espacio en el archivo
        return; // Fin de la función
    }
    if (a == T -> info) {  // Si hemos llegado al nodo correspondiente al caracter (ya hemos impreso todos los puntos y guiones que le corresponden)
        fprintf(f, " "); // Imprimimos un espacio en el archivo
        return;  // Fin de la función
    }
    if (buscaElemento(T -> izq, a)) { // Si el caracter se encuentra en el subárbol izquierdo
        fprintf(f, "."); // Imprimimos un punto en el archivo
        return charAMorse(T -> izq, f, a); // Reejecutamos la función entregándole esta vez el subárbol izquierdo
    }
    else { // Si el caracter se encuentra en el subárbol derecho
        fprintf(f, "-"); // Imprimimos un guión en el archivo
        return charAMorse(T -> der, f, a); // Reejecutamos la función entregándole esta vez el subárbol derecho
    }
}

/**
 * Función morseAChar (RECURSIVA)
 * Recibe: un árbol binario, una dirección a un archivo y un string de hasta 1000 caracteres que contiene el código morse de un caracter natural
 * Devuelve: vacío
 * Función: imprimir directamente en el archivo recibido el caracter natural correspondiente al código morse designado
*/
void morseAChar(AB T, FILE *f, char caracter[1000]) {
    if (caracter[cont] == ' ' || caracter[cont] == '\n' || caracter[cont] == '\0') { // Si el caracter en la posición actual es un espacio, un retorno o un fin de string (ya hemos procesado el código morse necesario para el caracter)
        fprintf(f, "%c", T->info); // Imprimimos el caracter que se encuentre en el nodo actual
        cont++; // Aumentamos en una unidad el contador
        return; // Fin de la función
    }
    if (caracter[cont] == '.') { // Si el caracter en la posición actual es un punto
        cont++; // Aumentamos en una unidad el contador
        return morseAChar(T -> izq, f, caracter); // Reejecutamos la función, esta vez entregándole el subárbol izquierdo
    }
    if (caracter[cont] == '-') { // Si el caracter en la posición actual es un guión
        cont++; // Aumentamos en una unidad el contador
        return morseAChar(T -> der, f, caracter); // Reejecutamos la función, esta vez entregándole el subárbol derecho
    }
}

/**
 * Función opcion1
 * Recibe: un árbol binario y un string de hasta 200 caracteres con el nombre del archivo a procesar
 * Devuelve: vacío
 * Función: traducir una frase de lenguaje natural a código morse
*/
void opcion1(AB T, char nom[200]) {
    char linea[2000]; // Declaramos un string de hasta 2000 caracteres donde almacenar la frase en cuestión
    FILE *f = fopen(nom, "r"); // Abrimos el archivo designado en modalidad lectura para leer la frase
    if (f == NULL) { // Si no pudimos abrir el archivo
        printf("\nArchivo inválido. Terminando programa."); // Notificamos al usuario
        exit(1); // Finalizamos el programa con código 1 para indicar que algo salió mal
    }
    fgets(linea, 2000, f); // Leemos la línea con la función fgets()
    fclose(f); // Cerramos el archivo para evitar problemas a futuro

    f = fopen(nom, "w"); // Abrimos de nuevo el archivo, en esta ocasión en modalidad de escritura
    if (linea[strlen(linea)-1] == '\n') { linea[strlen(linea)-1] = ' '; } // Por conveniencia, si la línea recibida termina en un retorno, lo sustituímos por un espacio
    fprintf(f, linea); // Reimprimimos la línea en el archivo, sobreescribiendo la que tenía previamente (esto no cambia nada a ojos del usuario)
    fprintf(f, "\n"); // Posicionamos el cursor en la siguiente línea con un retorno

    for (int i = 0; i < strlen(linea); i++) { // Para cada caracter de la línea
        charAMorse(T, f, linea[i]); // Lo convertimos a morse
    }
    fclose(f); // Cerramos el archivo para evitar problemas a futuro
    printf("Codificación realizada.\n"); // Indicamos al usuario que la codificación fue realizada
}

/**
 * Función opcion2
 * Recibe: un árbol binario y un string de hasta 200 caracteres con el nombre del archivo a procesar
 * Devuelve: vacío
 * Función: traducir una frase de código morse a lenguaje natural
*/
void opcion2(AB T, char nom[200]) {
    char linea[10000], caracter[1000]; // Declaramos una variable de hasta 10000 caracteres para la frase en código morse y un string auxiliar de hasta 1000 caracteres para procesar el caracter en código morse
    int carCont = 0; // Declaramos un contador de caracteres morse del caracter
    FILE *f = fopen(nom, "r"); // Abrimos el archivo en modalidad de lectura
    if (f == NULL) { // Si hubo algún problema al abrir el archivo
        printf("\nArchivo inválido. Terminando programa."); // Notificamos al usuario
        exit(1); // Terminamos el programa con código 1 para indicar que algo salió mal
    }
    fgets(linea, 10000, f); // Leemos la línea entera de código morse
    fclose(f); // Cerramos el archivo para evitar problemas a futuro

    f = fopen(nom, "w"); // Abrimos de nuevo el archivo, esta vez en modo de escritura
    if (linea[strlen(linea)-1] == '\n') { linea[strlen(linea)-1] = ' '; } // Por conveniencia, si la línea recibida termina en un retorno, lo sustituímos por un espacio
    fprintf(f, linea); // Imprimimos de nuevo la primera línea (esto no cambiará nada a ojos del usuario)
    fprintf(f, "\n"); // Posicionamos nuestro cursor en la siguiente línea

    strcpy(caracter, ""); // Inicializamos en vacío nuestra variable caracter
    for (int i = 0; i < strlen(linea); i++) { // Por cada caracter en la lista de la frase
        if (linea[i] == ' ' && linea[i+1] == ' ') { // Si estamos frente a un doble espacio
            caracter[carCont] = ' '; // Agregamos un espacio en blanco a la posición actual de la variable caracter
            morseAChar(T, f, caracter); // Traducimos la variable caracter a su caracter correspondiente en lenguaje natural
            memset(caracter, 0, sizeof(caracter)); // Reinicializamos la variable caracter a cero
            cont = 0; // Reinicializamos el contador general a cero
            carCont = 0; // Reinicializamos el contador de la variable caracter a cero
            fprintf(f, " "); // Imprimimos un espacio en el archivo
            i++; // Agregamos una unidad al contador del for, pues estamos en un doble espacio que no queremos procesar de nuevo
        } else { // Caso contrario
            if (linea[i] == ' ') { // Si estamos frente a un espacio simple (fin de un caracter natural)
                caracter[carCont] = ' '; // Añadimos un espacio en blanco en la posición actual del contador de la variable caracter
                morseAChar(T, f, caracter); // Traducimos la variable caracter a su contraparte en lenguaje natural
                memset(caracter, 0, sizeof(caracter)); // Reinicializamos la variable caracter a cero
                cont = 0; // Reinicializamos el contador general a cero
                carCont = 0; // Reinicializamos el contador de la variable caracter a cero
            } else { // Caso contrario
                caracter[carCont] = linea[i]; // Agregamos el punto o guión actual a la variable caracter
                carCont++; // Agregamos una unidad al contador de la variable caracter
            }
        }
    }
    fclose(f); // Cerramos el archivo para evitar problemas a futuro
    printf("Decodificación realizada.\n"); // Indicamos al usuario que la decodificación ha finalizado
}

/**
 * Función menu
 * Recibe: un árbol binario
 * Devuelve: vacío
 * Función: procesar la selección del usuario
*/
void menu(AB T) {
    int sel; // Variable que contendrá la selección del usuario
    char nom[200], temp; // Variable que contendrá el nombre del archivo a abrir, a su lado una variable temporar para limpiar el búfer de stdin
    printf("\n1. Lenguaje natural a código morse.");
    printf("\n2. Código morse a lenguaje natural.");
    printf("\n3. Salir.");
    printf("\nIngresa una opción: ");
    scanf("%i", &sel); // Recibimos un entero por parte del usuario
    
    switch(sel) {
        case 1:
            scanf("%c", &temp); // Limpiamos búfer de stdin
            printf("\nNombre del archivo de entrada: ");
            scanf("%s", &nom);
            // Natural a morse
            opcion1(T, nom);
            break;
        case 2:
            scanf("%c", &temp); // Limpiamos búfer de stdin
            printf("\nNombre del archivo de entrada: ");
            scanf("%s", &nom);
            // Morse a natural
            opcion2(T, nom);
            break;
        default:
            printf("\n\nHasta luego! :D\n\n"); // Los modales hacen al hombre (y a la mujer también en este caso)
            exit(0); // Terminamos el programa con código 0. Todo OK.
    }
}

/**
 * Función main
 * Lógica básica del programa
*/
int main() {
    setlocale(LC_ALL, "es"); // Establecemos el locale/regionalización a 'es' para poder utilizar tildes en el programa
    AB T = creaAB(); // Creamos el árbol binario de código morse

    while (true) { // Repetimos esta función hasta terminar el programa
        cont = 0; // Reinicializamos el contador global
        menu(T); // Ejecutamos la función menu
    }

    // En realidad a esta parte del programa nunca llegamos, pero se ve bonito y coqueto, así que lo dejamos c:
    printf("\n\n");
    return 0;
}