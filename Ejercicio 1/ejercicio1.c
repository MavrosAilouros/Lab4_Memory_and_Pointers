/*=========================================================
 *  ejercicio1.c, Laboratorio 4.
 *  Busca la secuencia más larga de 1s consecutivos en una
 *  matriz binaria cuadrada, usando pura aritmética de
 *  punteros y memoria dinámica.
 *=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*---------------------------------- CONSTANTES --------------------------------*/
static const int EXIT_MALLOC = 2;

/*---------------------------------- PROTOTIPOS --------------------------------*/
int  allocateMatrix(int ***matrix, int size);
void fillMatrix(int **matrix, int size);
void printMatrix(int **matrix, int size);
void findLargestLine(int **matrix, int size, int *result);
void freeMatrix(int ***matrix, int size);

/*-------------------------------- IMPLEMENTACIÓN ------------------------------*/

/**
 * @brief Reserva memoria para una matriz cuadrada de enteros.
 *
 * @param[out] matrix  triple‑puntero que recibirá la dirección de la matriz.
 * @param[in]  size    dimensión N de la matriz (NxN).
 *
 * @return 0 en éxito; -1 en caso de error.
 */
int allocateMatrix(int ***matrix, int size)
{
    if (!matrix || size <= 0) return -1; /* pointer guard */

    *matrix = malloc(size * sizeof(**matrix));
    if (!*matrix) return -1;

    for (int i = 0; i < size; ++i) {
        *(*matrix + i) = calloc(size, sizeof(int));
        if (!*(*matrix + i)) {
            /* fallo parcial ⇒ liberar lo reservado y abortar */
            for (int k = 0; k < i; ++k) free(*(*matrix + k));
            free(*matrix);
            *matrix = NULL;
            return -1;
        }
    }
    return 0;
}

/**
 * @brief Llena la matriz con números binarios aleatorios (0/1).
 */
void fillMatrix(int **matrix, int size)
{
    if (!matrix || size <= 0) return;

    srand((unsigned)time(NULL));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            *(*(matrix + i) + j) = rand() % 2;
}

/**
 * @brief Imprime la matriz en stdout.
 */
void printMatrix(int **matrix, int size)
{
    if (!matrix || size <= 0) return;

    printf("Matrix (%dx%d):\n", size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            printf("%d ", *(*(matrix + i) + j));
        putchar('\n');
    }
}

/**
 * @brief Encuentra la longitud de la secuencia más larga de 1s consecutivos.
 *
 * Recorre la matriz por filas usando aritmética de punteros. El contador
 * *no* se reinicia al cambiar de fila, de modo que una racha puede continuar
 * desde el final de una fila hasta la primera columna de la siguiente.
 *
 * @param[in]  matrix  matriz binaria NxN.
 * @param[in]  size    dimensión N.
 * @param[out] result  longitud de la racha más larga encontrada.
 */
void findLargestLine(int **matrix, int size, int *result)
{
    if (!matrix || size <= 0 || !result) return;

    int count = 0;
    *result = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (*(*(matrix + i) + j) == 1) {
                ++count;
                if (count > *result) *result = count;
            } else {
                count = 0;
            }
        }
    }
}

/**
 * @brief Libera la matriz y pone el puntero a NULL.
 */
void freeMatrix(int ***matrix, int size)
{
    if (!matrix || !*matrix) return;

    for (int i = 0; i < size; ++i) {
        free(*(*matrix + i));
        *(*matrix + i) = NULL;
    }
    free(*matrix);
    *matrix = NULL; /* pointer‑to‑null */
}

/*---- MAIN ----*/
int main(void)
{
    int size = 0, largestLine = 0;
    int **matrix = NULL;

    printf("Ingrese el tamaño de la matriz: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fputs("Tamaño inválido. Debe ser un entero positivo.\n", stderr);
        return EXIT_FAILURE;
    }

    if (allocateMatrix(&matrix, size) != 0) {
        fputs("Fallo al reservar memoria.\n", stderr);
        return EXIT_MALLOC;
    }

    fillMatrix(matrix, size);
    printMatrix(matrix, size);
    findLargestLine(matrix, size, &largestLine);

    printf("La secuencia de 1s más larga es de longitud: %d\n", largestLine);

    freeMatrix(&matrix, size);
    return EXIT_SUCCESS;
}
