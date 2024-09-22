#ifndef FUNCIONES_MEDINA_H_INCLUDED
#define FUNCIONES_MEDINA_H_INCLUDED

#include "funciones_bravo.h"
#pragma pack(push,1)

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

typedef struct
{
    bool flag;
    tHeader header;
    tHeaderExt headerExt;
    tPixel** matriz;
} tDatosBMP;

tDatosBMP datoImagen (const char []);

void achicar (tDatosBMP,char [],int);
void recortar (tDatosBMP,char [],int);
void espejarHorizontal (tDatosBMP,char []);
void espejarVertical (tDatosBMP,char []);
void escalaDeGrises (tDatosBMP,char []);
void comodin (tDatosBMP,char []);

#endif // FUNCIONES_MEDINA_H_INCLUDED
