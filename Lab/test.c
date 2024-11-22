#include <windows.h>
#include <stdio.h>

int main() {
    // ChatGPT
    const char *fileName = "C:\\Users\\axelc\\dev\\TPs_dds\\Lab\\test.c"; // Ruta del archivo o carpeta.

    // Intenta establecer el atributo de archivo oculto.
    if (SetFileAttributes(fileName, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)) {
        printf("El archivo o carpeta se ha ocultado correctamente.\n");
    } else {
        printf("Error al intentar ocultar el archivo o carpeta. Código de error: %lu\n", GetLastError());
    }

    return 0;
}
