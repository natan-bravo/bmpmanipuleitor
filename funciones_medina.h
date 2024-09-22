#ifndef FUNCIONES_MEDINA_H_INCLUDED
#define FUNCIONES_MEDINA_H_INCLUDED

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
