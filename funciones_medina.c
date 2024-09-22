#include "funciones_bravo.h"
#include "funciones_medina.h"

tDatosBMP datoImagen (const char nombre [])
{
    tDatosBMP datosBMP = {0};

    FILE *pf = fopen(nombre, "rb");
    if(!pf)
    {
        puts("Error al abrir imagen");
        datosBMP.flag = false;
        return datosBMP;
    }
    fread(&datosBMP.header, sizeof(tHeader), 1, pf);

    int offsetArchivo = datosBMP.header.offset - sizeof (tHeader);

    if(offsetArchivo)
    {
        fread(&datosBMP.headerExt.headerExt, sizeof(datosBMP.headerExt.headerExt), 1, pf);
        datosBMP.headerExt.existe = true;
    }

    else
        datosBMP.headerExt.existe = false;

    int padding = (4 - (datosBMP.header.ancho * 3) % 4) % 4;

    datosBMP.matriz = (tPixel**) malloc (datosBMP.header.alto * sizeof (tPixel*));
    if (datosBMP.matriz == NULL)
    {
        puts ("Error al asignar memoria");
        datosBMP.flag = false;
        fclose (pf);
        return datosBMP;
    }

    for (int a = 0; a < datosBMP.header.alto; a++)
    {
        datosBMP.matriz [a] = (tPixel*) malloc (datosBMP.header.ancho * sizeof (tPixel));
        if (datosBMP.matriz [a] == NULL)
        {
            puts ("Error al asignar memoria");
            datosBMP.flag = false;
            for (int b = 0; b < a; b++)
                free (datosBMP.matriz [b]);
            free (datosBMP.matriz);
            fclose (pf);
            return datosBMP;
        }
    }


    for (int i=0; i < datosBMP.header.alto; i++)
    {
        for (int j = 0; j < datosBMP.header.ancho; j++)
            fread (&datosBMP.matriz [i][j],sizeof (tPixel), 1, pf);
        fseek (pf, padding, SEEK_CUR);
    }
    datosBMP.flag = true;
    fclose (pf);

    return datosBMP;
}


void achicar (tDatosBMP datoBMP,char nombre[],int porcentaje)
{
    char nuevonombre [118]= "VARIABLE_achicar_";
    strcat(nuevonombre,nombre);
    int i, j, a, x, y;

    float porAchicar = (float)porcentaje / 100;
    int nuevoAlto = (int) (datoBMP.header.alto * porAchicar);
    int nuevoAncho = (int) (datoBMP.header.ancho * porAchicar);

    tPixel** copia = malloc(nuevoAlto * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }

    for (i = 0; i < nuevoAlto; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(nuevoAncho * sizeof(tPixel));
        if (copia[i] == NULL)
        {
            puts("Error al asignar memoria");
            // Liberar la memoria previamente asignada si falla
            for (j = 0; j < i; j++)
            {
                free(copia[j]);
            }
            free(copia);
            return;
        }

        // Copiar los datos de la fila original a la fila de copia
        for (a = 0; a < nuevoAncho; a++)
        {
            x = (int)(i * ((float)datoBMP.header.alto / nuevoAlto));
            y = (int)(a * ((float)datoBMP.header.ancho / nuevoAncho));
            copia[i][a] = datoBMP.matriz[x][y];
        }
    }

    datoBMP.header.alto = nuevoAlto;
    datoBMP.header.ancho = nuevoAncho;

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}

void recortar (tDatosBMP datoBMP,char nombre[],int porcentaje)
{
    char nuevonombre [119]= "VARIABLE_recortar_";
    strcat(nuevonombre,nombre);
    int i, j, a;

    float porAchicar = (float) porcentaje / 100;
    int nuevoAlto = (int) (datoBMP.header.alto * porAchicar);
    int nuevoAncho = (int) (datoBMP.header.ancho * porAchicar);

    tPixel** copia = malloc(nuevoAlto * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }
    for (i = 0; i < nuevoAlto; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(nuevoAncho * sizeof(tPixel));
        if (copia[i] == NULL)
        {
            puts("Error al asignar memoria");
            // Liberar la memoria previamente asignada si falla
            for (j = 0; j < i; j++)
            {
                free(copia[j]);
            }
            free(copia);
            return;
        }

        // Copiar los datos de la fila original a la fila de copia
        for (a = 0; a < nuevoAncho; a++)
        {
            copia[i][a] = datoBMP.matriz[i][a];
        }
    }

    datoBMP.header.alto = nuevoAlto;
    datoBMP.header.ancho = nuevoAncho;

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}


void espejarHorizontal (tDatosBMP datoBMP,char nombre[])
{
    char nuevonombre [129]= "VARIABLE_espejar-horizontal_";
    strcat(nuevonombre,nombre);
    int i, j, a;

    tPixel** copia = malloc(datoBMP.header.alto * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }
    for (i = 0; i < datoBMP.header.alto; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(datoBMP.header.ancho * sizeof(tPixel));
        if (copia[i] == NULL)
        {
            puts("Error al asignar memoria");
            // Liberar la memoria previamente asignada si falla
            for (j = 0; j < i; j++)
            {
                free(copia[j]);
            }
            free(copia);
            return;
        }

        // Copiar los datos de la fila original a la fila de copia
        for (a = 0; a < datoBMP.header.ancho; a++)
        {
            copia[i][a] = datoBMP.matriz[i][datoBMP.header.ancho - a - 1];
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}


void espejarVertical (tDatosBMP datoBMP,char nombre[])
{
    char nuevonombre [127]= "VARIABLE_espejar-vertical_";
    strcat(nuevonombre,nombre);
    int i, j, a;

    tPixel** copia = malloc(datoBMP.header.alto * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }

    for (i = 0; i < datoBMP.header.alto; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(datoBMP.header.ancho * sizeof(tPixel));
        if (copia[i] == NULL)
        {
            puts("Error al asignar memoria");
            // Liberar la memoria previamente asignada si falla
            for (j = 0; j < i; j++)
            {
                free(copia[j]);
            }
            free(copia);
            return;
        }

        // Copiar los datos de la fila original a la fila de copia
        for (a = 0; a < datoBMP.header.ancho; a++)
        {
            copia[i][a] = datoBMP.matriz[datoBMP.header.alto - i - 1][a];
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}


void escalaDeGrises (tDatosBMP datoBMP,char nombre[])
{
    char nuevonombre [127]= "VARIABLE_escala-de-grises_";
    strcat(nuevonombre,nombre);
    int i, j, a, promGris;

    tPixel** copia = malloc(datoBMP.header.alto * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }
    for (i = 0; i < datoBMP.header.alto; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(datoBMP.header.ancho * sizeof(tPixel));
        if (copia[i] == NULL)
        {
            puts("Error al asignar memoria");
            // Liberar la memoria previamente asignada si falla
            for (j = 0; j < i; j++)
            {
                free(copia[j]);
            }
            free(copia);
            return;
        }

        // Copiar los datos de la fila original a la fila de copia
        for (a = 0; a < datoBMP.header.ancho; a++)
        {
            copia[i][a] = datoBMP.matriz[i][a];
            promGris = (int) ((copia[i][a].azul + copia[i][a].rojo + copia[i][a].verde) / 3);
            copia[i][a].azul = (unsigned char) promGris;
            copia[i][a].rojo = (unsigned char) promGris;
            copia[i][a].verde = (unsigned char) promGris;
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}


void comodin (tDatosBMP datoBMP,char nombre[])
{
    char nuevonombre [118]= "VARIABLE_comodin_";
    strcat(nuevonombre,nombre);
    int i, j, a;

    tPixel** copia = malloc(datoBMP.header.alto * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }
    for (i = 0; i < datoBMP.header.alto; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(datoBMP.header.ancho * sizeof(tPixel));
        if (copia[i] == NULL)
        {
            puts("Error al asignar memoria");
            // Liberar la memoria previamente asignada si falla
            for (j = 0; j < i; j++)
            {
                free(copia[j]);
            }
            free(copia);
            return;
        }

        // Copiar los datos de la fila original a la fila de copia
        for (a = 0; a < datoBMP.header.ancho; a++)
        {
            copia[i][a] = datoBMP.matriz[i][a];
            copia[i][a].azul = 255 - copia[i][a].azul;
            copia[i][a].rojo = 255 - copia[i][a].rojo;
            copia[i][a].verde = 255 - copia[i][a].verde;
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}
