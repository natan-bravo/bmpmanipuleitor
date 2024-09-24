#include "funciones_bravo.h"
#include "funciones_medina.h"

int posImagen (int argc, char* argv [])
{
    int i = 1;
    size_t largo;
    while (i < argc)
    {
        largo = strlen (argv [i]);
        if (largo > 4 && strncmp(argv [i]+ largo - 4, ".bmp", 4) == 0) //compara los ultimos 4 caracteres para verificar si es .bmp
            return i;                                                  // devuelve la pos
        i++;
    }
    return 0;                                                          //devuelve 0 si no encontro un parametro que sea la imagen
}

tArgumento argumentoValido (char argv[])
{
    tArgumento arg;
    arg.pos = 0;
    size_t longitud;
    const char* comandoValido [] = {"--escala-de-grises","--espejar-horizontal","--espejar-vertical","--rotar-derecha","--rotar-izquierda","--concatenar-horizontal","--concatenar-vertical","--comodin"};
    const char* comandoValidoParcial [] = {"--aumentar-contraste=","--reducir-contraste=","--tonalidad-azul=","--tonalidad-verde=","--tonalidad-roja=","--recortar=","--achicar="};

    for (int i = 0; i < sizeof (comandoValido)/sizeof (comandoValido [0]); i++)
    {
        if (strcmp (argv, comandoValido [i]) == 0)                   //compara con las opciones de comandoValido
            arg.pos = i + 1;                                         // agrega la posicion del parametro que luego se usa como dato para el switch
    }
    int c;
    char* p = NULL;
    if (!arg.pos)

        for (int a = 0; a < sizeof (comandoValidoParcial)/sizeof (comandoValidoParcial [0]); a++)
        {
            longitud = strlen (comandoValidoParcial [a]);
            if (strncmp (argv,comandoValidoParcial [a],longitud) == 0)          // compara si la primera parte es igual a algun dato de comandoValidoParcial
            {
                p = strchr (argv, '=');                                         //posiciona el puntero p en el caracter =
                c = atoi (p+1);                                                 //tomamos el numero en la variable c
                if (c)                                                          // verificamos si la funcion atoi funciono para poner los datos en arg
                {
                    arg.porcentaje = c;
                    arg.pos = a + 9;
                }
            }
        }
    return arg;
}

void copiarImagen (tPixel** matriz, tHeader header, tHeaderExt headerExt, char nombre [])
{
    unsigned char byte = 0;
    int i, j, a;
    FILE *pf = fopen(nombre, "wb");
    if(!pf)
    {
        puts("Error al crear la nueva imagen");
        return;
    }

    fwrite(&header, sizeof(tHeader), 1, pf);
    if (headerExt.existe)
        fwrite(&headerExt.headerExt, sizeof(headerExt.headerExt), 1, pf);

    int padding = (4 - (header.ancho * 3) % 4) % 4;

    for(i = 0; i < header.alto; i++)
    {
        for(j = 0; j < header.ancho; j++)
            fwrite(&matriz[i][j], sizeof(tPixel), 1, pf);
        if (padding)
            for (a = 0; a < padding; a++)
                fwrite (&byte, sizeof (byte),1,pf);
    }
    fclose (pf);
}

void tonalidadAzul (tDatosBMP datoBMP,char nombre[],int porcentaje)
{
    char nuevonombre [125]= "VARIABLE_tonalidad-azul_";
    strcat(nuevonombre,nombre);
    int i, j, a, azul;

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
            azul = copia[i][a].azul;
            azul = azul + (azul * porcentaje / 100);
            if (azul > 255)
                azul = 255;
            copia[i][a].azul = (unsigned char) azul;
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}

void tonalidadRoja (tDatosBMP datoBMP,char nombre[],int porcentaje)
{
    char nuevonombre [125]= "VARIABLE_tonalidad-roja_";
    strcat(nuevonombre,nombre);
    int i, j, a, rojo;

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
            rojo = copia[i][a].rojo;
            rojo = rojo + (rojo * porcentaje / 100);
            if (rojo > 255)
                rojo = 255;
            copia[i][a].rojo = (unsigned char) rojo;
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}

void tonalidadVerde (tDatosBMP datoBMP,char nombre[],int porcentaje)
{
    char nuevonombre [126]= "VARIABLE_tonalidad-verde_";
    strcat(nuevonombre,nombre);
    int i, j, a, verde;

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
            verde = copia[i][a].verde;
            verde = verde + (verde * porcentaje / 100);
            if (verde > 255)
                verde = 255;
            copia[i][a].verde = (unsigned char) verde;
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}

void aumentarContraste (tDatosBMP datoBMP,char nombre[],int porcentaje)
{
    char nuevonombre [129]= "VARIABLE_aumentar-contraste_";
    strcat(nuevonombre,nombre);
    float contraste = porcentaje * 2.55;
    float factor =  (259 * (contraste + 255)) / (255 * (259 - contraste));
    int i, j, a, verde, rojo, azul;

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
            verde = copia[i][a].verde;
            verde = factor * (verde - 128) + 128;
            if (verde > 255)
                verde = 255;
            if (verde < 0)
                verde = 0;
            copia[i][a].verde = (unsigned char) verde;

            rojo = copia[i][a].rojo;
            rojo = factor * (rojo - 128) + 128;
            if (rojo > 255)
                rojo = 255;
            if (rojo < 0)
                rojo = 0;
            copia[i][a].rojo = (unsigned char) rojo;

            azul = copia[i][a].azul;
            azul = factor * (azul - 128) + 128;
            if (azul > 255)
                azul = 255;
            if (azul < 0)
                azul = 0;
            copia[i][a].azul = (unsigned char) azul;
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}

void reducirContraste (tDatosBMP datoBMP,char nombre[],int porcentaje)
{
    char nuevonombre [129]= "VARIABLE_reducir-contraste_";
    strcat(nuevonombre,nombre);
    float contraste = porcentaje * (-2.55);
    float factor =  (259 * (contraste + 255)) / (255 * (259 - contraste));
    int i, j, a, verde, rojo, azul;

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
            verde = copia[i][a].verde;
            verde = factor * (verde - 128) + 128;
            if (verde > 255)
                verde = 255;
            else if (verde < 0)
                verde = 0;
            copia[i][a].verde = (unsigned char) verde;

            rojo = copia[i][a].rojo;
            rojo = factor * (rojo - 128) + 128;
            if (rojo > 255)
                rojo = 255;
            else if (rojo < 0)
                rojo = 0;
            copia[i][a].rojo = (unsigned char) rojo;

            azul = copia[i][a].azul;
            azul = factor * (azul - 128) + 128;
            if (azul > 255)
                azul = 255;
            else if (azul < 0)
                azul = 0;
            copia[i][a].azul = (unsigned char) azul;
        }
    }

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}

void rotarIzquierda (tDatosBMP datoBMP,char nombre[])
{
    char nuevonombre [126]= "VARIABLE_rotar-izquierda_";
    strcat(nuevonombre,nombre);
    int i, j, a;

    tPixel** copia = malloc(datoBMP.header.ancho * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }
    for (i = 0; i < datoBMP.header.ancho; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(datoBMP.header.alto * sizeof(tPixel));
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
    }

    // Rellenar la nueva matriz con los píxeles rotados
    for ( i = 0; i < datoBMP.header.alto; i++)
    {
        for (a = 0; a < datoBMP.header.ancho; a++)
        {
            copia[a][datoBMP.header.alto - i - 1] = datoBMP.matriz[i][a];
        }
    }

    int aux = datoBMP.header.ancho;
    datoBMP.header.ancho = datoBMP.header.alto;
    datoBMP.header.alto = aux;

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.ancho; j++)
    {
        free(copia[j]);
    }
    free(copia);
}


void rotarDerecha (tDatosBMP datoBMP,char nombre[])
{
    char nuevonombre [124]= "VARIABLE_rotar-derecha_";
    strcat(nuevonombre,nombre);
    int i, j, a;

    tPixel** copia = malloc(datoBMP.header.ancho * sizeof(tPixel*));
    if (copia == NULL)
    {
        puts("Error al asignar memoria");
        return;
    }
    for (i = 0; i < datoBMP.header.ancho; i++)
    {
        // Reservar memoria para cada fila
        copia[i] = malloc(datoBMP.header.alto * sizeof(tPixel));
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
    }

    // Rellenar la nueva matriz con los píxeles rotados
    for ( i = 0; i < datoBMP.header.alto; i++)
    {
        for (a = 0; a < datoBMP.header.ancho; a++)
        {
            copia[datoBMP.header.ancho - a - 1][i] = datoBMP.matriz[i][a];
        }
    }

    int aux = datoBMP.header.ancho;
    datoBMP.header.ancho = datoBMP.header.alto;
    datoBMP.header.alto = aux;

    copiarImagen (copia,datoBMP.header,datoBMP.headerExt,nuevonombre);

    for (j = 0; j < datoBMP.header.ancho; j++)
    {
        free(copia[j]);
    }
    free(copia);
}


int posImagenConcatenar (int argc, char* argv [], int ordinal)
{
    int i = 1,j = 1;
    size_t largo;
    while (i < argc)
    {
        largo = strlen (argv [i]);
        if (largo > 4 && strncmp(argv [i]+ largo - 4, ".bmp", 4) == 0)
        {
            if (j == ordinal )
                return i;
            else
                j++;
        }

        i++;
    }
    return 0;
}

void concatenarHorizontal (tDatosBMP datoBMP,char nombre[],tDatosBMP datoConcaBMP)
{
    char nuevonombre [132]= "VARIABLE_concatenar-horizontal_";
    strcat(nuevonombre,nombre);
    int nuevoAncho, nuevoAlto, i, j, a;

    nuevoAncho = datoBMP.header.ancho + datoConcaBMP.header.ancho;
    if (datoBMP.header.alto >= datoConcaBMP.header.alto)
        nuevoAlto = datoBMP.header.alto;
    else
        nuevoAlto = datoConcaBMP.header.alto;

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
            if (a < datoBMP.header.ancho)
            {
                if (i < datoBMP.header.alto)
                    copia[i][a] = datoBMP.matriz[i][a];
                else
                {
                    copia [i][a].azul = (unsigned char) 107;
                    copia [i][a].verde = (unsigned char) 134;
                    copia [i][a].rojo = (unsigned char) 120;
                }
            }
            else
            {
                if (i < datoConcaBMP.header.alto)
                    copia[i][a] = datoConcaBMP.matriz[i][a-datoBMP.header.ancho];
                else
                {
                    copia [i][a].azul = (unsigned char) 107;
                    copia [i][a].verde = (unsigned char) 134;
                    copia [i][a].rojo = (unsigned char) 120;
                }
            }
        }
    }

    datoConcaBMP.header.ancho = nuevoAncho;
    datoConcaBMP.header.alto = nuevoAlto;

    if (datoConcaBMP.headerExt.existe)
        datoConcaBMP.header.tamFichero = sizeof (datoConcaBMP.header) + sizeof (datoConcaBMP.headerExt.headerExt) + (datoConcaBMP.header.alto * datoConcaBMP.header.ancho * 3);
    else
        datoConcaBMP.header.tamFichero = sizeof (datoConcaBMP.header) + (datoConcaBMP.header.alto * datoConcaBMP.header.ancho * 3);

    datoConcaBMP.header.tamImagen = datoConcaBMP.header.alto * datoConcaBMP.header.ancho * 3;

    copiarImagen (copia,datoConcaBMP.header,datoConcaBMP.headerExt,nuevonombre);

    for (j = 0; j < datoConcaBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}


void concatenarVertical (tDatosBMP datoBMP,char nombre[],tDatosBMP datoConcaBMP)
{
    char nuevonombre [130]= "VARIABLE_concatenar-vertical_";
    strcat(nuevonombre,nombre);
    int nuevoAncho, nuevoAlto, i, j, a;

    nuevoAlto = datoBMP.header.alto + datoConcaBMP.header.alto;
    if (datoBMP.header.ancho >= datoConcaBMP.header.ancho)
        nuevoAncho = datoBMP.header.ancho;
    else
        nuevoAncho = datoConcaBMP.header.ancho;

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
            if (i < datoBMP.header.alto)
            {
                if (a < datoBMP.header.ancho)
                    copia[i][a] = datoBMP.matriz[i][a];
                else
                {
                    copia [i][a].azul = (unsigned char) 107;
                    copia [i][a].verde = (unsigned char) 134;
                    copia [i][a].rojo = (unsigned char) 120;
                }
            }
            else
            {
                if (a < datoConcaBMP.header.ancho)
                    copia[i][a] = datoConcaBMP.matriz[i-datoBMP.header.alto][a];
                else
                {
                    copia [i][a].azul = (unsigned char) 107;
                    copia [i][a].verde = (unsigned char) 134;
                    copia [i][a].rojo = (unsigned char) 120;
                }
            }
        }
    }

    datoConcaBMP.header.ancho = nuevoAncho;
    datoConcaBMP.header.alto = nuevoAlto;

    if (datoConcaBMP.headerExt.existe)
        datoConcaBMP.header.tamFichero = sizeof (datoConcaBMP.header) + sizeof (datoConcaBMP.headerExt.headerExt) + (datoConcaBMP.header.alto * datoConcaBMP.header.ancho * 3);
    else
        datoConcaBMP.header.tamFichero = sizeof (datoConcaBMP.header) + (datoConcaBMP.header.alto * datoConcaBMP.header.ancho * 3);

    datoConcaBMP.header.tamImagen = datoConcaBMP.header.alto * datoConcaBMP.header.ancho * 3;

    copiarImagen (copia,datoConcaBMP.header,datoConcaBMP.headerExt,nuevonombre);

    for (j = 0; j < datoConcaBMP.header.alto; j++)
    {
        free(copia[j]);
    }
    free(copia);
}
