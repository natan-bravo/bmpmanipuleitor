#ifndef FUNCIONES_BRAVO_H_INCLUDED
#define FUNCIONES_BRAVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funciones_medina.h"
#pragma pack(push,1)


typedef struct
{
    int pos;
    int porcentaje;
} tArgumento;



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
