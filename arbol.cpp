#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Datos {
	int dato1;
	float dato2;
	char dato3;
	
};

struct Nodo {
	Datos* datos;
	Nodo* der;
	Nodo* izq;
};

Nodo* CrearNodo(Datos);
int Insertar(Nodo*&, Datos, int, int, int);
void Mostrar(Nodo*, int, int, int);
bool Busqueda(Nodo*, Datos);
void Menu();

int cardinalidad = 0;
Nodo* arbol = NULL;
int raiz;

int main() {
	srand(time(NULL));
	// initwindow(1200, 1000);
	Menu();
}

void Menu() {
	int opcion = 0, cont = 0, nivel = 0, lado = 0;
	int tam;
	char card_cx[100];
	printf("Ingrese la cantidad de elementos a insertar: ");
	scanf("%d", &tam);
	printf("\n");
	do {
		Datos datos;
		// Ingresar los datos de la estructura para cada nodo
		datos.dato1 = 1 + rand() % tam;
		datos.dato2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		datos.dato3 = 'A' + rand() % 26;
		if (!Busqueda(arbol, datos)) {
			raiz = Insertar(arbol, datos, nivel, 600, 75);
			cont++;
		}
	} while (cont != tam);
	// outtextxy(550, 50, "ARBOL ABB");
	// outtextxy(650, 50, "raiz");
	printf("\n");
	printf("Cantidad de elementos: %d\n", cardinalidad);

	// outtextxy(100, 850, "Cantidad de elementos:");
	// itoa(cardinalidad, card_cx, 10);
	// outtextxy(275, 850, card_cx);
	// system("pause");
}

Nodo* CrearNodo(Datos datos) {
	Nodo* nuevo_nodo = static_cast<Nodo*>(malloc(sizeof(Nodo)));
	nuevo_nodo->datos = &datos;
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	return nuevo_nodo;
}

int Insertar(Nodo*& arbol, Datos datos, int nivel, int dx, int dy) {
	char cx[100];
	int valorRaiz;
	if (arbol == NULL) {
		cardinalidad += 1;
		Nodo* nuevo_nodo = CrearNodo(datos);
		arbol = nuevo_nodo;
		// setcolor(LIGHTBLUE);
		// setfillstyle(1, LIGHTBLUE);
		// circle(dx + 5, dy + 5, 15);
		// floodfill(dx + 5, dy + 5, LIGHTBLUE);
		// setbkcolor(LIGHTBLUE);
		// setcolor(WHITE);
		sprintf(cx, "%d", arbol->datos -> dato1);
		// outtextxy(dx, dy, cx);
	} else {
		valorRaiz = arbol->datos->dato1;
		if (datos.dato1 < valorRaiz) {
			// setcolor(YELLOW);
			// line(dx, dy, dx - (300 / (nivel + 1)), dy + 50);
			// circle(dx + 5, dy + 5, 16);
			Insertar(arbol->izq, datos, nivel + 1, dx - (300 / (nivel + 1)), (dy + 50));
		} else {
			// setcolor(YELLOW);
			// line(dx, dy, dx + (300 / (nivel + 1)), dy + 50);
			// circle(dx + 5, dy + 5, 16);
			Insertar(arbol->der, datos, nivel + 1, dx + (300 / (nivel + 1)), (dy + 50));
		}
	}
	return valorRaiz;
}

// void Mostrar(Nodo* arbol, int nivel, int dx, int dy) {
// 	char cx[100];
// 	if (arbol == NULL) {
// 		return;
// 	} else {
// 		printf("Nivel: %d ", nivel);
// 		printf("Dato1: %d ", arbol->datos->dato1);
// 		// Mostrar otros datos de la estructura
// 		setcolor(YELLOW);
// 		if (arbol->izq != NULL) {
// 			line(dx, dy, dx - (300 / (nivel + 1)), dy + 50);
// 		}
// 		if (arbol->der != NULL) {
// 			line(dx, dy, dx + (300 / (nivel + 1)), dy + 50);
// 		}
// 		setcolor(LIGHTBLUE);
// 		setfillstyle(1, LIGHTBLUE);
// 		circle(dx + 5, dy + 5, 15);
// 		setcolor(WHITE);
// 		sprintf(cx, "%d", arbol->datos->dato1);
// 		outtextxy(dx, dy, cx);
// 		printf("dx: %d, dy: %d\n", dx, dy);
// 		Mostrar(arbol->izq, nivel + 1, dx - (300 / (nivel + 1)), (dy + 50));
// 		Mostrar(arbol->der, nivel + 1, dx + (300 / (nivel + 1)), (dy + 50));
// 	}
// }

bool Busqueda(Nodo* arbol, Datos datos) {
	if (arbol == NULL) {
		return false;
	} else if (arbol->datos->dato1 == datos.dato1) {
		return true;
	} else if (datos.dato1 < arbol->datos->dato1) {
		return Busqueda(arbol->izq, datos);
	} else {
		return Busqueda(arbol->der, datos);
	}
}

