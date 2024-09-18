#ifndef FUNCIONES_MEDINA_H_INCLUDED
#define FUNCIONES_MEDINA_H_INCLUDED

#include "funciones_bravo.h"

void escalaGrises(tDatosBMP* Imagen);
void invertirHorizontal(tDatosBMP* Imagen);
void invertirVertical(tDatosBMP* Imagen);
void negativo(tDatosBMP* Imagen);
void recortar(tDatosBMP* Imagen, tArgumento* argumento);
void achicar(tDatosBMP* Imagen, tArgumento* argumento);
void concatenarHorizontal(tDatosBMP* Imagen1, tDatosBMP* Imagen2);
void concatenarVertical(tDatosBMP* Imagen1, tDatosBMP* Imagen2);

#endif // FUNCIONES_MEDINA_H_INCLUDED
