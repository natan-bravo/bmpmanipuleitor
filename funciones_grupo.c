/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
*/
#include "funciones_bravo.h"

int solucion(int argc, char* argv[])
{
    tArgumento argumento;
    char img [100];
    int pos = posImagen (argc, argv); // busca la posicion de la imagen en los parametros enviados
    if (pos)
    {
        strcpy (img,argv [pos]);
    }

    else
    {
        puts ("no hay imagen");
        return 0;
    }
    tDatosBMP datImg = datoImagen (img);  //copia los datos de la imagen en un struct

    copiarImagen (datImg);  //prueba para ver si los datos de la imagen se copiaron correctamente


    if (datImg.flag)
    {
        for (int i = 1; i < argc; i++)
        {
            argumento = argumentoValido (argv [i]);
            switch (argumento.pos)
            {
                case 1:
                    {
                        puts ("escala de grises\n");
                    }
                    break;
                case 2:
                    {
                        puts ("espejar horizontal\n");
                    }
                    break;
                case 3:
                    {
                        puts ("espejar vertical\n");
                    }
                    break;
                case 4:
                    {
                        puts ("rotar derecha\n");
                    }
                    break;
                case 5:
                    {
                        puts ("rotar izquierda\n");
                    }
                    break;
                case 6:
                    {
                        puts ("concatenar horizontal\n");
                    }
                    break;
                case 7:
                    {
                        puts ("concatenar vertical\n");
                    }
                    break;
                case 8:
                    {
                        puts ("comodin\n");
                    }
                    break;
                case 9:
                    {
                        puts ("aumentar contraste\n");
                    }
                    break;
                case 10:
                    {
                        puts ("reducir contraste\n");
                    }
                    break;
                case 11:
                    {
                        puts ("tonalidad azul\n");
                    }
                    break;
                case 12:
                    {
                        puts ("tonalidad verde\n");
                    }
                    break;
                case 13:
                    {
                        puts ("tonalidad roja\n");
                    }
                    break;
                case 14:
                    {
                        puts ("recortar\n");
                    }
                    break;
                case 15:
                    {
                        puts ("achicar\n");
                    }
                    break;
                default:
                    {
                        if (i != pos)
                            puts ("argumento invalido\n");
                    }
                    break;
            }
        }

    }

    for (int j = 0; j < datImg.header.alto; j++)
    {
        free(datImg.matriz[j]);
    }
    free(datImg.matriz);


    /*
        Aquí deben hacer el código que solucione lo solicitado.
        Todas las funciones utilizadas deben estar declaradas en este archivo, y en su respectivo .h
    */
    return 0;
}
