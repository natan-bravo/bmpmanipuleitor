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
#include "funciones_medina.h"

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
        puts ("No hay imagen.");
        return 0;
    }
    tDatosBMP datImg = datoImagen (img);  //copia los datos de la imagen en un struct


    if (datImg.flag)
    {
        for (int i = 1; i < argc; i++)
        {
            argumento = argumentoValido (argv [i]);
            switch (argumento.pos)
            {
                case 1:
                    {
                        escalaGrises(&datImg);
                        puts ("Escala de Grises\n");
                    }
                    break;
                case 2:
                    {
                        invertirHorizontal(&datImg);
                        puts ("Espejar Horizontal\n");
                    }
                    break;
                case 3:
                    {
                        invertirVertical(&datImg);
                        puts ("Espejar Vertical\n");
                    }
                    break;
                case 4:
                    {
                        puts ("Rotar Derecha\n");
                    }
                    break;
                case 5:
                    {
                        puts ("Rotar Izquierda\n");
                    }
                    break;
                case 6:
                    {
                        puts ("Concatenar Horizontal\n");
                    }
                    break;
                case 7:
                    {
                        puts ("Concatenar Vertical\n");
                    }
                    break;
                case 8:
                    {
                        negativo(&datImg);
                        puts ("Comodin(Negativo)\n");
                    }
                    break;
                case 9:
                    {
                        puts ("Aumentar Contraste\n");
                    }
                    break;
                case 10:
                    {
                        puts ("Reducir Contraste\n");
                    }
                    break;
                case 11:
                    {
                        puts ("Tonalidad Azul\n");
                    }
                    break;
                case 12:
                    {
                        puts ("Tonalidad Verde\n");
                    }
                    break;
                case 13:
                    {
                        puts ("Tonalidad Roja\n");
                    }
                    break;
                case 14:
                    {
                        if(argumento.porcentaje> 0 && argumento.porcentaje< 100)
                        {
                            recortar(&datImg, &argumento);
                            puts ("Recortar\n");
                        }
                        else
                            printf("Argumento Invalido\n");
                    }
                    break;
                case 15:
                    {
                        if(argumento.porcentaje> 0 && argumento.porcentaje< 100)
                        {
                            achicar(&datImg, &argumento);
                            puts ("Achicar\n");
                        }
                        else
                            printf("Argumento Invalido\n");
                    }
                    break;
                default:
                    {
                        if (i != pos)
                            puts ("Argumento Anvalido\n");
                    }
                    break;
            }
        }

        copiarImagen (datImg);
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
