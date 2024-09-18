#include "funciones_medina.h"

void achicar(tDatosBMP* Imagen, tArgumento* argumento)
{
    int nuevoAncho = Imagen->header.ancho * (argumento->porcentaje/100.0);
    int nuevoAlto = Imagen->header.alto * (argumento->porcentaje/100.0);
    float factor = 100.0/(float)argumento->porcentaje;
    int i, j, x, y;

    for(i = 0; i < nuevoAlto; i++)
        for(j = 0; j < nuevoAncho; j++)
        {
            y = (int)(i * factor);
            x = (int)(j * factor);

            if(y >= nuevoAlto)
                y--;
            if(x >= nuevoAncho)
                x--;

            Imagen->matriz[i][j] = Imagen->matriz[y][x];
        }

    Imagen->header.ancho = nuevoAncho;
    Imagen->header.alto = nuevoAlto;
    Imagen->header.tamImagen = Imagen->header.ancho * Imagen->header.alto * Imagen->header.tamPixel;
}

void recortar(tDatosBMP* Imagen, tArgumento* argumento)
{
    Imagen->header.ancho *= argumento->porcentaje/100.0;
    Imagen->header.alto *= argumento->porcentaje/100.0;
    Imagen->header.tamImagen = Imagen->header.ancho * Imagen->header.alto * Imagen->header.tamPixel;
}

void negativo(tDatosBMP* Imagen)
{
    int i, j;

    for(i = 0; i < Imagen->header.alto; i++)
    {
        for(j = 0; j < Imagen->header.ancho; j++)
        {
            Imagen->matriz[i][j].rojo = 255 - Imagen->matriz[i][j].rojo;
            Imagen->matriz[i][j].verde = 255 - Imagen->matriz[i][j].verde;
            Imagen->matriz[i][j].azul = 255 - Imagen->matriz[i][j].azul;
        }
    }
}


void invertirVertical(tDatosBMP* Imagen)
{
    int i, j, fin;
    tPixel aux;

    fin = Imagen->header.alto - 1;

    for(i = 0; i < Imagen->header.alto/2; i++)
    {
        fin--;
        for(j = 0; j < Imagen->header.ancho; j++)
        {
            aux = Imagen->matriz[i][j];
            Imagen->matriz[i][j] = Imagen->matriz[fin][j];
            Imagen->matriz[fin][j] = aux;
        }
    }
}

void invertirHorizontal(tDatosBMP* Imagen)
{
    int i, j, fin;
    tPixel aux;

    for(i = 0; i < Imagen->header.alto; i++)
    {
        fin = Imagen->header.ancho - 1;

        for(j = 0; j < Imagen->header.ancho/2; j++)
        {
            aux = Imagen->matriz[i][j];
            Imagen->matriz[i][j] = Imagen->matriz[i][fin];
            Imagen->matriz[i][fin] = aux;

            fin--;
        }
    }
}

void escalaGrises(tDatosBMP* Imagen)
{
    int prom, i, j;

    for(i = 0; i < Imagen->header.alto; i++)
    {
        for(j = 0; j < Imagen->header.ancho; j++)
        {
            prom = (Imagen->matriz[i][j].rojo + Imagen->matriz[i][j].azul + Imagen->matriz[i][j].verde)/3;

            Imagen->matriz[i][j].rojo = prom;
            Imagen->matriz[i][j].azul = prom;
            Imagen->matriz[i][j].verde = prom;
        }
    }
}
