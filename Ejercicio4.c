#include <stdio.h>
#include <stdlib.h>

int partir_tuercas(int tuercas[], int bajo, int alto, int tornilloPivote) {
    int i = bajo;
    for (int j = bajo; j < alto; j++) {
        if (tuercas[j] < tornilloPivote) {
            int temp = tuercas[i];
            tuercas[i] = tuercas[j];
            tuercas[j] = temp;
            i++;
        } else if (tuercas[j] == tornilloPivote) {
            int temp = tuercas[j];
            tuercas[j] = tuercas[alto];
            tuercas[alto] = temp;
            j--;
        }
    }
    int temp = tuercas[i];
    tuercas[i] = tuercas[alto];
    tuercas[alto] = temp;
    return i;
}

int partir_tornillos(int tornillos[], int bajo, int alto, int tuercaPivote) {
    int i = bajo;
    for (int j = bajo; j < alto; j++) {
        if (tornillos[j] < tuercaPivote) {
            int temp = tornillos[i];
            tornillos[i] = tornillos[j];
            tornillos[j] = temp;
            i++;
        } else if (tornillos[j] == tuercaPivote) {
            int temp = tornillos[j];
            tornillos[j] = tornillos[alto];
            tornillos[alto] = temp;
            j--;
        }
    }
    int temp = tornillos[i];
    tornillos[i] = tornillos[alto];
    tornillos[alto] = temp;
    return i;
}

void emparejar_recursivo(int tuercas[], int tornillos[], int bajo, int alto) {
    if (bajo < alto) {
        int indicePivoteTuercas = partir_tuercas(tuercas, bajo, alto, tornillos[alto]);
        int indicePivoteTornillos = partir_tornillos(tornillos, bajo, alto, tuercas[indicePivoteTuercas]);
        
        emparejar_recursivo(tuercas, tornillos, bajo, indicePivoteTuercas - 1);
        emparejar_recursivo(tuercas, tornillos, indicePivoteTuercas + 1, alto);
    }
}

void emparejar_tuercas_y_tornillos(int tuercas[], int tornillos[], int n) {
    if (n <= 0) return;
    emparejar_recursivo(tuercas, tornillos, 0, n - 1);
}

void imprimir_arreglo(const char *etiqueta, int arr[], int n) {
    printf("%s: ", etiqueta);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int m;
    printf("Ingrese el numero de pares (tuerca + tornillo): ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        fprintf(stderr, "Error: m invalido.\n");
        return 1;
    }

    int *tuercas = (int *)malloc(m * sizeof(int));
    int *tornillos = (int *)malloc(m * sizeof(int));
    if (!tuercas || !tornillos) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        free(tuercas); free(tornillos);
        return 1;
    }

    int n_tuercas = 0, n_tornillos = 0;

    printf("Ingrese %d pares (tipo valor), donde 0=tuerca, 1=tornillo:\n", m * 2);
    for (int i = 0; i < m * 2; i++) {
        int tipo, valor;
        printf("Pieza %d: ", i + 1);
        if (scanf("%d %d", &tipo, &valor) != 2) {
            fprintf(stderr, "Error: entrada invalida.\n");
            free(tuercas); free(tornillos);
            return 1;
        }
        if (tipo == 0) {
            tuercas[n_tuercas++] = valor;
        } else if (tipo == 1) {
            tornillos[n_tornillos++] = valor;
        } else {
            fprintf(stderr, "Error: tipo debe ser 0 (tuerca) o 1 (tornillo).\n");
            free(tuercas); free(tornillos);
            return 1;
        }
    }

    if (n_tuercas != n_tornillos) {
        fprintf(stderr, "Error: cantidad desigual de tuercas (%d) y tornillos (%d).\n",
                n_tuercas, n_tornillos);
        free(tuercas); free(tornillos);
        return 1;
    }

    int n = n_tuercas;
    emparejar_tuercas_y_tornillos(tuercas, tornillos, n);

    imprimir_arreglo("Tuercas", tuercas, n);
    imprimir_arreglo("Tornillos", tornillos, n);

    free(tuercas);
    free(tornillos);
    return 0;
}