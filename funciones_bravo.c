#include "funciones_bravo.h"

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
        return 0;                                                      //devuelve 0 si no encontro un parametro que sea la imagen
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
        puts ("error al asignar memoria");
        datosBMP.flag = false;
        fclose (pf);
        return datosBMP;
    }

    for (int a = 0; a < datosBMP.header.alto; a++)
    {
        datosBMP.matriz [a] = (tPixel*) malloc (datosBMP.header.ancho * sizeof (tPixel));
        if (datosBMP.matriz [a] == NULL)
        {
            puts ("error al asignar memoria");
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

void copiarImagen (tDatosBMP datoBMP) // funcion prototipo para verificar que los datos devuelto en la funcion datoImagen sean correcto y se pueda hacer una copia
{
    unsigned char byte = 0;
    FILE *pf = fopen("resultado.bmp", "wb");
    if(!pf)
    {
        puts("Error al abrir archivo para escribir el resultado.bmp");
        return;
    }

    fwrite(&datoBMP.header, sizeof(tHeader), 1, pf);
    if (datoBMP.headerExt.existe)
        fwrite(&datoBMP.headerExt.headerExt, sizeof(datoBMP.headerExt.headerExt), 1, pf);

    int padding = (4 - (datoBMP.header.ancho * 3) % 4) % 4;

    for(int i=0; i < datoBMP.header.alto; i++)
    {
        for(int j=0; j < datoBMP.header.ancho; j++)
            fwrite(&datoBMP.matriz[i][j], sizeof(tPixel), 1, pf);
        if (padding)
            for (int a = 0; a < padding; a++)
                fwrite (&byte, sizeof (byte),1 ,pf);
    }
    fclose (pf);
    return;
}
