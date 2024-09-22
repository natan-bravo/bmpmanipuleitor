#ifndef FUNCIONES_BRAVO_H_INCLUDED
#define FUNCIONES_BRAVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma pack(push,1)


typedef struct
{
    int pos;
    int porcentaje;
} tArgumento;

typedef struct
{
    unsigned short tipoFichero;
    unsigned int tamFichero;
    unsigned short reservado1;
    unsigned short reservado2;
    unsigned int offset;
    unsigned int tamHeader;
    unsigned int ancho;
    unsigned int alto;
    unsigned short planos;
    unsigned short tamPixel;
    unsigned int compresion;
    unsigned int tamImagen;
    unsigned int resHorizontal;
    unsigned int resVertical;
    unsigned int tamTablaColor;
    unsigned int contadorColores;
} tHeader;

typedef struct
{
    bool existe;
    unsigned char headerExt [84];
} tHeaderExt;

typedef struct
{
    unsigned char azul;
    unsigned char verde;
    unsigned char rojo;
} tPixel;

int posImagen (int, char* []);
tArgumento argumentoValido (char []);
void copiarImagen (tPixel**, tHeader, tHeaderExt, char []);

void tonalidadAzul (tDatosBMP,char [],int);
void tonalidadVerde (tDatosBMP,char [],int);
void tonalidadRoja (tDatosBMP,char [],int);
void reducirContraste (tDatosBMP,char [],int);
void aumentarContraste (tDatosBMP,char [],int);
void rotarDerecha (tDatosBMP,char []);
void rotarIzquierda (tDatosBMP,char []);
int posImagenConcatenar (int, char*[], int);
void concatenarHorizontal (tDatosBMP,char [],tDatosBMP);
void concatenarVertical (tDatosBMP,char [],tDatosBMP);





#endif // FUNCIONES_BRAVO_H_INCLUDED
