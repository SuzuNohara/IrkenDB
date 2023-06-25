#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un nodo del árbol AVL
struct AVLNode {
    int id;
    int dato;
    char clave[13];
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Función para obtener la altura de un nodo
int getHeight(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Función para obtener el máximo entre dos números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Función para crear un nuevo nodo del árbol AVL
struct AVLNode* newNode(int id, int dato, char clave[]) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->id = id;
    node->dato = dato;
    strncpy(node->clave, clave, 12);
    node->clave[12] = '\0';
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Función para rotar a la derecha un subárbol
struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    // Realizar la rotación
    x->right = y;
    y->left = T2;

    // Actualizar las alturas
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Devolver la nueva raíz
    return x;
}

// Función para rotar a la izquierda un subárbol
struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    // Realizar la rotación
    y->left = x;
    x->right = T2;

    // Actualizar las alturas
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Devolver la nueva raíz
    return y;
}

// Función para obtener el factor de equilibrio de un nodo
int getBalance(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Función para insertar un nodo en el árbol AVL
struct AVLNode* insertNode(struct AVLNode* node, int id, int dato, char clave[]) {
    // Realizar la inserción de forma normal
    if (node == NULL)
        return newNode(id, dato, clave);

    if (id < node->id)
        node->left = insertNode(node->left, id, dato, clave);
    else if (id > node->id)
        node->right = insertNode(node->right, id, dato, clave);
    else
        return node; // No se permiten elementos duplicados

    // Actualizar la altura del nodo actual
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Obtener el factor de equilibrio del nodo actual
    int balance = getBalance(node);

    // Realizar las rotaciones según el factor de equilibrio
    if (balance > 1 && id < node->left->id)
        return rightRotate(node);

    if (balance < -1 && id > node->right->id)
        return leftRotate(node);

    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Función para encontrar el nodo con el ID dado
struct AVLNode* findNode(struct AVLNode* node, int id) {
    if (node == NULL || node->id == id)
        return node;

    if (id < node->id)
        return findNode(node->left, id);

    return findNode(node->right, id);
}

// Función para encontrar el nodo con el ID mínimo (utilizado en la eliminación)
struct AVLNode* findMinimumNode(struct AVLNode* node) {
    struct AVLNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Función para eliminar un nodo del árbol AVL
struct AVLNode* deleteNode(struct AVLNode* root, int id) {
    // Realizar la eliminación de forma normal
    if (root == NULL)
        return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct AVLNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            struct AVLNode* temp = findMinimumNode(root->right);

            root->id = temp->id;
            root->dato = temp->dato;
            strncpy(root->clave, temp->clave, 12);
            root->clave[12] = '\0';

            root->right = deleteNode(root->right, temp->id);
        }
    }

    // Si el árbol tenía solo un nodo, devolverlo
    if (root == NULL)
        return root;

    // Actualizar la altura del nodo actual
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Obtener el factor de equilibrio del nodo actual
    int balance = getBalance(root);

    // Realizar las rotaciones según el factor de equilibrio
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
        root->right = rightRotate(root->right);
        return leftRotate(root);
}

// Función para imprimir el árbol AVL en orden ascendente
void printInorder(struct AVLNode* node) {
    if (node != NULL) {
        printInorder(node->left);
        printf("ID: %d, Dato: %d, Clave: %s\n", node->id, node->dato, node->clave);
        printInorder(node->right);
    }
}

// Función para guardar el árbol AVL en un archivo de texto
void saveTreeToFile(struct AVLNode* node, FILE* file) {
    if (node != NULL) {
        saveTreeToFile(node->left, file);
        fprintf(file, "%d %d %s\n", node->id, node->dato, node->clave);
        saveTreeToFile(node->right, file);
    }
}

// Función para cargar el árbol AVL desde un archivo de texto
struct AVLNode* loadTreeFromFile(struct AVLNode* root, FILE* file) {
    int id, dato;
    char clave[13];
    while (fscanf(file, "%d %d %s", &id, &dato, clave) != EOF) {
        root = insertNode(root, id, dato, clave);
    }
    return root;
}

int main() {
    struct AVLNode* root = NULL;
    int choice;
    int id, dato;
    char clave[13];
    FILE* file;

    do {
        printf("Menu:\n");
        printf("1. Insertar en el árbol\n");
        printf("2. Eliminar nodo del árbol\n");
        printf("3. Buscar en el árbol\n");
        printf("4. Ver árbol en consola\n");
        printf("5. Leer datos de archivo de texto\n");
        printf("6. Guardar árbol en archivo de texto\n");
        printf("0. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ingrese el ID: ");
                scanf("%d", &id);
                printf("Ingrese el dato: ");
                scanf("%d", &dato);
                printf("Ingrese la clave: ");
                scanf("%s", clave);
                root = insertNode(root, id, dato, clave);
                printf("Nodo insertado correctamente.\n");
                break;
            case 2:
                printf("Ingrese el ID del nodo a eliminar: ");
                scanf("%d", &id);
                root = deleteNode(root, id);
                printf("Nodo eliminado correctamente.\n");
                break;
            case 3:
                printf("Ingrese el ID del nodo a buscar: ");
                scanf("%d", &id);
                struct AVLNode* node = findNode(root, id);
                if (node != NULL) {
                    printf("Nodo encontrado:\n");
                    printf("ID: %d, Dato: %d, Clave: %s\n", node->id, node->dato, node->clave);
                } else {
                    printf("Nodo no encontrado.\n");
                }
                break;
            case 4:
                printf("Árbol en orden ascendente:\n");
                printInorder(root);
                break;
            case 5:
                file = fopen("arbol.txt", "r");
                if (file == NULL) {
                    printf("No se pudo abrir el archivo.\n");
                } else {
                    root = loadTreeFromFile(root, file);
                    printf("Datos del archivo cargados correctamente.\n");
                    fclose(file);
                }
                break;
            case 6:
                file = fopen("arbol.txt", "w");
                if (file == NULL) {
                    printf("No se pudo abrir el archivo.\n");
                } else {
                    saveTreeToFile(root, file);
                    printf("Árbol guardado en el archivo correctamente.\n");
                    fclose(file);
                }
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
                break;
        }

        printf("\n");

    } while (choice != 0);

    return 0;
}

