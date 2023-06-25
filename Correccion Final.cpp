#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro {
    int id;
    char nombre[50];
    int cantidad;
    char descripcion[100];
    char contrasena[20];
    struct Registro* izq;
    struct Registro* der;
    int altura;
} Registro;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(Registro* nodo) {
    if (nodo == NULL)
        return 0;
    return nodo->altura;
}

Registro* nuevoRegistro(int id, const char* nombre, int cantidad, const char* descripcion, const char* contrasena) {
    Registro* nodo = (Registro*)malloc(sizeof(Registro));
    nodo->id = id;
    strcpy(nodo->nombre, nombre);
    nodo->cantidad = cantidad;
    strcpy(nodo->descripcion, descripcion);
    strcpy(nodo->contrasena, contrasena);
    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->altura = 1;
    return nodo;
}

Registro* rotarDerecha(Registro* y) {
    Registro* x = y->izq;
    Registro* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;

    return x;
}

Registro* rotarIzquierda(Registro* x) {
    Registro* y = x->der;
    Registro* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;

    return y;
}

int obtenerBalance(Registro* nodo) {
    if (nodo == NULL)
        return 0;
    return altura(nodo->izq) - altura(nodo->der);
}

Registro* insertarRegistro(Registro* nodo, int id, const char* nombre, int cantidad, const char* descripcion, const char* contrasena) {
    if (nodo == NULL)
        return nuevoRegistro(id, nombre, cantidad, descripcion, contrasena);

    if (id < nodo->id)
        nodo->izq = insertarRegistro(nodo->izq, id, nombre, cantidad, descripcion, contrasena);
    else if (id > nodo->id)
        nodo->der = insertarRegistro(nodo->der, id, nombre, cantidad, descripcion, contrasena);
    else
        return nodo; // No se permiten registros duplicados

    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && id < nodo->izq->id)
        return rotarDerecha(nodo);

    if (balance < -1 && id > nodo->der->id)
        return rotarIzquierda(nodo);

    if (balance > 1 && id > nodo->izq->id) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && id < nodo->der->id) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void guardarEnArchivo(FILE* archivo, Registro* nodo) {
    if (nodo != NULL) {
        fprintf(archivo, "%d,%s,%d,%s,%s\n", nodo->id, nodo->nombre, nodo->cantidad, nodo->descripcion, nodo->contrasena);
        guardarEnArchivo(archivo, nodo->izq);
        guardarEnArchivo(archivo, nodo->der);
    }
}

void guardarArbolEnArchivo(const char* nombreArchivo, Registro* arbol) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    guardarEnArchivo(archivo, arbol);

    fclose(archivo);
}

void liberarArbol(Registro* nodo) {
    if (nodo != NULL) {
        liberarArbol(nodo->izq);
        liberarArbol(nodo->der);
        free(nodo);
    }
}

int main() {
    Registro* arbol = NULL;
    int opcion;

    do {
        printf("1. Agregar registro\n");
        printf("2. Guardar registros en archivo\n");
        printf("3. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int id, cantidad;
                char nombre[50], descripcion[100], contrasena[20];

                printf("Ingrese el ID: ");
                scanf("%d", &id);
                printf("Ingrese el nombre: ");
                scanf("%s", nombre);
                printf("Ingrese la cantidad: ");
                scanf("%d", &cantidad);
                printf("Ingrese la descripción: ");
                scanf("%s", descripcion);
                printf("Ingrese la contraseña: ");
                scanf("%s", contrasena);

                arbol = insertarRegistro(arbol, id, nombre, cantidad, descripcion, contrasena);

                printf("Registro agregado exitosamente.\n\n");
                break;
            }
            case 2: {
                char nombreArchivo[50];

                printf("Ingrese el nombre del archivo: ");
                scanf("%s", nombreArchivo);

                guardarArbolEnArchivo(nombreArchivo, arbol);

                printf("Registros guardados en el archivo exitosamente.\n\n");
                break;
            }
            case 3: {
                // Salir del programa
                liberarArbol(arbol);
                printf("Saliendo del programa.\n");
                break;
            }
            default:
                printf("Opción inválida. Intente nuevamente.\n\n");
                break;
        }
    } while (opcion != 3);


    return 0;
}
