#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

struct nodoArbol {
    char info;
    struct nodoArbol *izq;
    struct nodoArbol *der;
};
typedef struct nodoArbol *AB;
int cont;

AB creaNodo(char valor)
{
   AB aux;
   aux = (AB)malloc(sizeof(struct nodoArbol));
   if (aux != NULL)
   {
      aux->info = valor;
      aux->izq = NULL;
      aux->der = NULL;
   }
   else
   {
       printf("\nMemoria insuficiente. Terminando programa...");
       exit(1);
   }
   return aux;
}

AB creaAB()
{
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

bool buscaElemento(AB T, char a) {
    if (T == NULL) { return false; }
    if (T -> info == a) { return true; }
    return buscaElemento(T -> izq, a) || buscaElemento(T -> der, a);
}

void charAMorse(AB T, FILE *f, char a) {
    if (a == ' ') {
        fprintf(f, " ");
        return;
    }
    if (a == T -> info) { 
        fprintf(f, " ");
        return; 
    }
    if (buscaElemento(T -> izq, a)) {
        fprintf(f, ".");
        return charAMorse(T -> izq, f, a);
    }
    else {
        fprintf(f, "-");
        return charAMorse(T -> der, f, a);
    }
}

void morseAChar(AB T, FILE *f, char caracter[1000]) {
    if (caracter[cont] == ' ') {
        fprintf(f, "%c", T->info);
        cont++;
        return;
    }
    if (caracter[cont] == '.') {
        cont++;
        return morseAChar(T -> izq, f, caracter);
    }
    if (caracter[cont] == '-') {
        cont++;
        return morseAChar(T -> der, f, caracter);
    }
}

void opcion1(AB T, char nom[200]) {
    char linea[2000];
    FILE *f = fopen(nom, "r");
    if (f == NULL) {
        printf("\nArchivo inválido. Terminando programa.");
        exit(1);
    }
    fgets(linea, 2000, f);
    fclose(f);

    f = fopen(nom, "w");

    if (linea[strlen(linea)-1] == '\n') { linea[strlen(linea)-1] = ' '; }

    fprintf(f, linea);
    fprintf(f, "\n");

    for (int i = 0; i < strlen(linea); i++) {
        charAMorse(T, f, linea[i]);
    }
    fclose(f);

    printf("Codificación realizada.");
}

void opcion2(AB T, char nom[200]) {
    char linea[10000], caracter[1000];
    int carCont = 0;
    FILE *f = fopen(nom, "r");
    if (f == NULL) {
        printf("\nArchivo inválido. Terminando programa.");
        exit(1);
    }
    fgets(linea, 10000, f);
    fclose(f);

    f = fopen(nom, "w");
    if (linea[strlen(linea)-1] == '\n') { linea[strlen(linea)-1] = ' '; }

    fprintf(f, linea);
    fprintf(f, "\n");

    strcpy(caracter, "");
    for (int i = 0; i < strlen(linea); i++) {
        if (linea[i] == ' ' && linea[i+1] == ' ') {
            caracter[carCont] = ' ';
                morseAChar(T, f, caracter);
                memset(caracter, 0, sizeof(caracter));
                cont = 0;
                carCont = 0;
                fprintf(f, " ");
                i++;
        } else {
            if (linea[i] == ' ') {
                caracter[carCont] = ' ';
                morseAChar(T, f, caracter);
                memset(caracter, 0, sizeof(caracter));
                cont = 0;
                carCont = 0;
            } else {
                caracter[carCont] = linea[i];
                carCont++;
            }
        }
    }

    fclose(f);

    printf("Decodificación realizada.");
}

void menu(AB T) {
    int sel;
    char nom[200], temp;
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
            printf("\n\nHasta luego! :D");
            exit(0);
    }
}

int main() {
    setlocale(LC_ALL, "");
    AB T = creaAB();

    cont = 0;
    menu(T);

    printf("\n\n");
    return 0;
}