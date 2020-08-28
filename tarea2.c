#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define N 10

//Definition of structure
typedef struct
{
    char *titulo;
    int paginas;
} Libro;

//Funciones
typedef void (*printer)(void *);
typedef void (*iterator)(void *, printer *, size_t);

void recorre(void *, iterator *, printer *, size_t);

void *begin(void *, size_t);
void *end(void *, size_t);
void *next(void *, size_t);
void *prev(void *, size_t);

void forward(void *, printer *, size_t);
void backward(void *, printer *, size_t);
void bidirectional(void *, printer *, size_t);

void printInt(void *);
void printFloat(void *);
void printLibro(void *);

int main()
{
    int *array = (int *)malloc(N * sizeof(int));
    int i = 1;
    int *last = array + N;

    for (int *aux = array; aux < last; ++aux)
    {
        *aux = i++;
    }
    printer *toPrint = (printer *)malloc(sizeof(printer));
    *toPrint = printInt;

    iterator *it = (iterator *)malloc(sizeof(iterator));
    *it = forward;

    size_t position = sizeof(int);

    recorre(array, it, toPrint, position);

    Libro *libros = (Libro *)malloc(N * sizeof(Libro));
    Libro *ultimoLibro = libros + N;
    int j = 0;
    int k = 0;
    char titulo[12];

    for (Libro *libro = libros; libro < ultimoLibro; ++libro)
    {
        libro->titulo = (char *)malloc(sizeof(char) * 30);
        snprintf(titulo, 12, "titulo%d", k += 1);
        strcpy(libro->titulo, titulo);
        j += 100;
        libro->paginas = j;
    }
    position = sizeof(Libro);
    *it = bidirectional;
    *toPrint = printLibro;
    recorre(libros, it, toPrint, position);

    free(array);
    free(it);
    free(toPrint);

    for (Libro *libro = libros; libro < ultimoLibro; libro++)
    {
        free(libro->titulo);
    }
    free(libros);

    return 0;
}

void recorre(void *vector, iterator *it, printer *toPrint, size_t position)
{
    (*it)(vector, toPrint, position);
}

void *begin(void *array, size_t position)
{
    void *aux = array;
    return aux;
}
void *end(void *array, size_t position)
{
    void *aux = array;
    int i = 0;
    while (i < 10)
    {
        i++;
        aux = aux + position;
    }
    return aux - position;
}
void *next(void *array, size_t position)
{
    void *aux = array + position;
    if (aux == NULL)
    {
        return NULL;
    }
    return aux;
}
void *prev(void *array, size_t position)
{
    void *aux = array - position;
    if (aux == NULL)
    {
        return NULL;
    }
    return aux;
}

void forward(void *vector, printer *toPrint, size_t position)
{
    printf("Forward Iteration: \n");
    void *aux = begin(vector, position);
    int i = 0;
    do
    {
        (*toPrint)(aux);
        aux = next(aux, position);
        i++;
    } while (i < 10);
    printf("\n");
}
void backward(void *vector, printer *toPrint, size_t position)
{
    printf("Backward Iteration: \n");
    void *aux = end(vector, position);
    int i = 0;
    do
    {
        (*toPrint)(aux);
        aux = prev(aux, position);
        i++;
    } while (i < 10);
    printf("\n");
}
void bidirectional(void *vector, printer *toPrint, size_t position)
{
    forward(vector, toPrint, position);
    backward(vector, toPrint, position);
}

void printInt(void *position)
{
    int *value = (int *)position;
    printf("%d \n", *value);
}
void printLibro(void *position)
{
    Libro *aux = position;
    printf("titulo :%s\n", aux->titulo);
    printf("paginas: %d\n", aux->paginas);
    printf("\n");
}