#include <stdio.h>
#include <stdlib.h>

/*
  Ejercicio: QuickSort con pivote = promedio de los valores en el subarreglo.

  Requisitos:
    - El pivote es el promedio (double) de los valores del segmento actual.
    - El pivote puede NO pertenecer al arreglo.
    - En el arreglo de salida solo pueden aparecer valores del arreglo original
      (NO se inserta el pivote como elemento).

  Sugerencia de diseño (no obligatorio):
    - calcular_promedio_segmento(arr, bajo, alto) -> double
    - particion_por_promedio(arr, bajo, alto, pivote) -> índice final (int)
      (reorganizar comparando cada arr[i] con el pivote)
    - quicksort_promedio(arr, bajo, alto) -> recursivo
*/
static inline void intercambiar(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

/* Devuelve el promedio (double) de arr[bajo..alto] */
double calcular_promedio_segmento(int arr[], int bajo, int alto) {
     // Escribe aquí tu función
    // Pista:
    //   - Acumula en (long long) o (double) para evitar overflow
    //   - Devuelve suma / cantidad como doube

    if (bajo > alto) return 0.0;
    
    long long suma = 0;
    int count = 0;
    
    for (int i = bajo; i <= alto; i++) {
        suma += arr[i];
        count++;
    }
    
    return (double)suma / count;
}

/*
  Partición usando pivote = promedio.
  Objetivo:
    - Reordenar in-place arr[bajo..alto] comparando cada elemento con "pivote".
    - Colocar a la izquierda los elementos < pivote
      y a la derecha los elementos >= pivote (o la convención que elijas).
    - NO insertar el pivote en el arreglo (solo se usa para decidir posiciones).
    
  Nota:
    - Define y documenta tu convención de partición para manejar duplicados:
      por ejemplo, (< pivote) a la izquierda y (>= pivote) a la derecha.
    - Asegura progreso (evitar ciclos infinitos cuando todos son iguales).
*/

int particion_por_promedio(int arr[], int bajo, int alto, double pivote) {
      // Escribe aquí tu función
    // Puedes implementar un esquema tipo Hoare o Lomuto pero guiado por pivot double.
    // Recuerda: NO escribas 'pivote' dentro del arreglo; solo compáralo contra arr[i].
  
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
/*
  QuickSort con pivote = promedio:
    - Caso base: si bajo >= alto, terminar.
    - Paso:
        1) pivote = promedio de arr[bajo..alto]
        2) k = particion_por_promedio(arr, bajo, alto, pivote)
        3) Llamar recursivamente a los segmentos definidos por k
*/

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
