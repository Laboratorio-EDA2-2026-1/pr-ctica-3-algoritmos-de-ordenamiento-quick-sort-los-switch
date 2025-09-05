#include <stdio.h>
#include <stdlib.h>

static inline void intercambiar(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

double calcular_promedio_segmento(int arr[], int bajo, int alto) {
    if (bajo > alto) return 0.0;
    
    long long suma = 0;
    int count = 0;
    
    for (int i = bajo; i <= alto; i++) {
        suma += arr[i];
        count++;
    }
    
    return (double)suma / count;
}

int particion_por_promedio(int arr[], int bajo, int alto, double pivote) {
    int i = bajo;
    int j = alto;
    
    while (i <= j) {
        // Avanzar i hasta encontrar elemento >= pivote
        while (i <= j && arr[i] < pivote) {
            i++;
        }
        
        // Avanzar j hasta encontrar elemento < pivote
        while (i <= j && arr[j] >= pivote) {
            j--;
        }
        
        // Intercambiar elementos si es necesario
        if (i <= j) {
            intercambiar(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    
    // i marca el inicio de la partición derecha (elementos >= pivote)
    return i;
}

void quicksort_promedio(int arr[], int bajo, int alto) {
    if (bajo >= alto) return;
    
    double pivote = calcular_promedio_segmento(arr, bajo, alto);
    int k = particion_por_promedio(arr, bajo, alto, pivote);
    
    // Llamadas recursivas
    quicksort_promedio(arr, bajo, k - 1);
    quicksort_promedio(arr, k, alto);
}

void imprimir_arreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: n inválido.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: entrada inválida en la posición %d.\n", i + 1);
            free(arr);
            return 1;
        }
    }

    quicksort_promedio(arr, 0, n - 1);
    imprimir_arreglo(arr, n);

    free(arr);
    return 0;
}
