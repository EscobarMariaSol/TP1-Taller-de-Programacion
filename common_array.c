#include "common_array.h"

/*********Funciones Auxiliares**********/

void arrayInit(array_t *array, char *buffer, size_t size) {
    array->buffer = buffer;
    array->pos = 0;
    array->size = size;
}

/*********Primitivas del arreglo**********/

array_t* arrayCreate(size_t size) {
    array_t* new_array = calloc(sizeof(array_t), sizeof(char));
    if (!new_array) return NULL;
    char *new_buffer = calloc(sizeof(char), size);
    if (!new_buffer) {
        free(new_array);
        return NULL;
    }
    arrayInit(new_array, new_buffer, size);
    return new_array;
}

int arrayAdd(array_t *self, const char *msg, size_t len) {
    if ((self->pos + len) > self->size) {
        int new_size = (self->pos + len) + 1;
        char* new_buffer = realloc(self->buffer, new_size);
        if (!new_buffer) return -1;
        self->buffer = new_buffer;
        memset(((self->buffer) + self->pos), 0, (len + 1));
        self->size = new_size;
    }
    memmove(((self->buffer) + self->pos), msg, len);
    self->pos = (self->pos + len);
    return 0;
}

char *arrayGetContent(array_t *self) {
    return self->buffer;
}

int arrayClear(array_t *self) {
    void *new_buffer = calloc(sizeof(char), 0);
    if (!new_buffer) return -1;
    free(self->buffer);
    arrayInit(self, new_buffer, 0);
    return 0;
}

size_t arrayGetSize(array_t *self) {
    return self->size;
}

char arrayGetElement(array_t *self, size_t index) {
    if (index <= self->pos) return self->buffer[index];
    return -1;
}

void arrayDestroy(array_t *self) {
    free(self->buffer);
    free(self);
}