/*=========================================================
 *  ejercicio2.c, Laboratorio 4.
 *  Busca el palíndromo más largo en un archivo de texto
 *  ignorando puntuación y usando memoria dinámica segura.
 *=========================================================*/

#define _POSIX_C_SOURCE 200809L   /* strdup (POSIX.1-2008) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/* ------------------  CONST y MACROS  ------------------ */
static const size_t MAX_TOKEN = 1024;   /* longitud máxima de palabra */

/* ------------------ PROTOTIPOS / FORWARD ------------------ */
static char  *clean_token(const char *raw);
static bool   is_palindrome(const char *s);
static char  *dupstr(const char *s);
static void   replace_longest(char **longest, const char *candidate);

/**
 * @brief  Programa principal: lee "input.txt" (o argv[1]) y muestra
 * el palíndromo más largo encontrado.
 */
int main(int argc, char *argv[])
{
    const char *fname = (argc > 1) ? argv[1] : "input.txt";
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        perror(fname);
        return EXIT_FAILURE;
    }

    char  raw[MAX_TOKEN];   /* Buffer donde fscanf coloca cada token */
    char *longest = NULL;   /* Palíndromo más largo hallado hasta ahora */

    /*--------------------  Bucle principal de lectura  ---------------*/
    while (fscanf(fp, "%1023s", raw) == 1) {
        char *clean = clean_token(raw);        /* minúsculas + alfanumérico */
        if (clean && *clean && is_palindrome(clean))
            replace_longest(&longest, clean);
        free(clean);       /* es seguro pasar NULL a free() */
    }

    fclose(fp);

    if (longest) {
        printf("Palíndromo más largo: %s\n", longest);
        free(longest);
        longest = NULL;
    } else {
        puts("No se encontró ningún palíndromo.");
    }
    return EXIT_SUCCESS;
}

/** 
 * @brief  Convierte un token a minúsculas y conserva solo caracteres
 *         alfanuméricos. Devuelve una nueva cadena con malloc.
 * @param  raw  Cadena original (puede ser NULL).
 * @return  Puntero a la nueva cadena o NULL si raw es NULL o falla.
 */
static char *clean_token(const char *raw)
{
    if (!raw) return NULL;                /* pointer‑guard */

    size_t len = strlen(raw);
    char *out  = malloc(len + 1);         /* el mismo tamaño basta */
    if (!out) {
        perror("malloc");
        return NULL;
    }

    size_t k = 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = (unsigned char)raw[i];
        if (isalnum(c))
            out[k++] = (char)tolower(c);
    }
    out[k] = '\0';
    return out;   /* el llamante debe free() */
}

/**
 * @brief  Comprueba si la cadena es palíndromo.
 */
static bool is_palindrome(const char *s)
{
    if (!s) return false;

    const char *left = s;
    const char *right = s + strlen(s) - 1;
    while (left < right) {
        if (*left != *right)
            return false;
        ++left;
        --right;
    }
    return true;
}

/**
 *  Versión local de strdup
 */
static char *dupstr(const char *s)
{
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *p = malloc(len);
    if (p) memcpy(p, s, len);
    return p;
}

/**
 * @brief  Actualiza el puntero *longest si candidate es más largo.
 */
static void replace_longest(char **longest, const char *candidate)
{
    if (!candidate || !*candidate) return;   /* nada que hacer */

    if (!*longest || strlen(candidate) > strlen(*longest)) {
        free(*longest);
        *longest = dupstr(candidate);
        if (!*longest) {
            perror("dupstr");
            exit(EXIT_FAILURE);
        }
    }
}
