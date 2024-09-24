/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Medina, Ramiro
    DNI: 45400641
    Entrega: Si
    -----------------
    Apellido: Bravo, Pablo
    DNI: 40258506
    Entrega: Si
    -----------------
    Apellido: De Brito, Ariel
    DNI: 44396739
    Entrega: No
    -----------------
*/
 #include "funciones_grupo.h"

int solucion(int argc, char* argv[])
{
    tArgumento argumento;
    int funcionUsada [15] = {0};
    char img [100];
    char imgConcaCH [100];
    char imgConcaCV [100];
    int posCH = 0;
    int posCV = 0;
    int j, cantCV = 0, cantCH = 0, lugarCV = 2, lugarCH = 2;
    int pos = posImagen (argc, argv); // busca la posicion de la imagen en los parametros enviados
    if (pos)
    {
        strcpy (img,argv [pos]);
    }

    else
    {
        puts ("No se ha mandado la imagen");
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
                //"escala de grises"
                if (funcionUsada [0] == 0)
                {
                    escalaDeGrises (datImg,img);
                    funcionUsada [0] = 1;
                }
                else
                    puts ("Escala de grises ya fue usado");
            }
            break;
            case 2:
            {
                //"espejar horizontal"
                if (funcionUsada [1] == 0)
                {
                    espejarHorizontal (datImg,img);
                    funcionUsada [1] = 1;
                }
                else
                    puts ("Espejar horizontal ya fue usado");
            }
            break;
            case 3:
            {
                //"espejar vertical"
                if (funcionUsada [2] == 0)
                {
                    espejarVertical (datImg,img);
                    funcionUsada [2] = 1;
                }
                else
                    puts ("Espejar vertical ya fue usado");
            }
            break;
            case 4:
            {
                //"rotar derecha"
                if (funcionUsada [3] == 0)
                {
                    rotarDerecha (datImg,img);
                    funcionUsada [3] = 1;
                }
                else
                    puts ("Rotar derecha ya fue usado");
            }
            break;
            case 5:
            {
                //"rotar izquierda"
                if (funcionUsada [4] == 0)
                {
                    rotarIzquierda (datImg,img);
                    funcionUsada [4] = 1;
                }
                else
                    puts ("Rotar izquierda ya fue usado");
            }
            break;
            case 6:
            {
                //"concatenar horizontal"
                if (funcionUsada [5] == 0)
                {
                    if (!cantCV)
                        posCH = posImagenConcatenar (argc, argv,lugarCH);
                    else
                        posCH = posImagenConcatenar (argc, argv,lugarCH + cantCV);
                    if (posCH)
                    {
                        strcpy (imgConcaCH,argv [posCH]);
                        tDatosBMP datImgCH = datoImagen (imgConcaCH);
                        if (datImgCH.flag)
                        {
                            concatenarHorizontal (datImg,img,datImgCH);
                            for (j = 0; j < datImgCH.header.alto; j++)
                            {
                                free(datImgCH.matriz[j]);
                            }
                            free(datImgCH.matriz);
                            cantCH++;
                            funcionUsada [5] = 1;
                        }
                        else
                        {
                            cantCH++;
                            lugarCH++;
                        }
                    }
                    else
                    {
                        puts ("No se ha mandado la segunda imagen");
                    }
                }
                else
                    puts ("Concatenar horizontal ya fue usado");
            }
            break;
            case 7:
            {
                //"concatenar vertical"
                if (funcionUsada [6] == 0)
                {
                    if (!cantCH)
                        posCV = posImagenConcatenar (argc, argv,lugarCV);
                    else
                        posCV = posImagenConcatenar (argc, argv,lugarCV + cantCH);
                    if (posCV)
                    {
                        strcpy (imgConcaCV,argv [posCV]);
                        tDatosBMP datImgCV = datoImagen (imgConcaCV);
                        if (datImgCV.flag)
                        {
                            concatenarVertical (datImg,img,datImgCV);
                            for (j = 0; j < datImgCV.header.alto; j++)
                            {
                                free(datImgCV.matriz[j]);
                            }
                            free(datImgCV.matriz);
                            cantCV++;
                            funcionUsada [6] = 1;
                        }
                        else
                        {
                            lugarCV++;
                            cantCV++;
                        }
                    }
                    else
                    {
                        puts ("No se ha mandado la segunda imagen");
                    }
                }
                else
                    puts ("Concatenar vertical ya fue usado");
            }
            break;
            case 8:
            {
                //"comodin"
                if (funcionUsada [7] == 0)
                {
                    comodin (datImg,img);
                    funcionUsada [7] = 1;
                }

                else
                    puts ("Comodin ya fue usado");
            }
            break;
            case 9:
            {
                //"aumentar contraste"
                if (funcionUsada [8] == 0)
                {
                    if (argumento.porcentaje < 100 && argumento.porcentaje > 0)
                    {
                        aumentarContraste (datImg,img,argumento.porcentaje);
                        funcionUsada [8] = 1;
                    }
                    else
                        puts ("Porcentaje fuera de los limites permitido");
                }

                else
                    puts ("Aumentar contraste ya fue usado");

            }
            break;
            case 10:
            {
                //"reducir contraste"
                if (funcionUsada [9] == 0)
                {
                    if (argumento.porcentaje < 100 && argumento.porcentaje > 0)
                    {
                        reducirContraste (datImg,img,argumento.porcentaje);
                        funcionUsada [9] = 1;
                    }
                    else
                        puts ("Porcentaje fuera de los limites permitido");
                }

                else
                    puts ("Reducir contraste ya fue usado");
            }
            break;
            case 11:
            {
                //"tonalidad azul"
                if (funcionUsada [10] == 0)
                {
                    if (argumento.porcentaje < 100 && argumento.porcentaje > 0)
                    {
                        tonalidadAzul (datImg,img,argumento.porcentaje);
                        funcionUsada [10] = 1;
                    }
                    else
                        puts ("Porcentaje fuera de los limites permitido");
                }

                else
                    puts ("Tonalidad azul ya fue usado");

            }
            break;
            case 12:
            {
                //tonalidad verde"
                if (funcionUsada [11] == 0)
                {
                    if (argumento.porcentaje < 100 && argumento.porcentaje > 0)
                    {
                        tonalidadVerde (datImg,img,argumento.porcentaje);
                        funcionUsada [11] = 1;
                    }
                    else
                        puts ("Porcentaje fuera de los limites permitido");
                }

                else
                    puts ("Tonalidad verde ya fue usado");
            }
            break;
            case 13:
            {
                //"tonalidad roja"
                if (funcionUsada [12] == 0)
                {
                    if (argumento.porcentaje < 100 && argumento.porcentaje > 0)
                    {
                        tonalidadRoja (datImg,img,argumento.porcentaje);
                        funcionUsada [12] = 1;
                    }
                    else
                        puts ("Porcentaje fuera de los limites permitido");
                }

                else
                    puts ("Tonalidad roja ya fue usado");
            }
            break;
            case 14:
            {
                //"recortar"
                if (funcionUsada [13] == 0)
                {
                    if (argumento.porcentaje < 100 && argumento.porcentaje > 0)
                    {
                        recortar (datImg,img,argumento.porcentaje);
                        funcionUsada [13] = 1;
                    }
                    else
                        puts ("Porcentaje fuera de los limites permitido");
                }

                else
                    puts ("Recortar ya fue usado");
            }
            break;
            case 15:
            {
                //"achicar"
                if (funcionUsada [14] == 0)
                {
                    if (argumento.porcentaje < 100 && argumento.porcentaje > 0)
                    {
                        achicar (datImg,img,argumento.porcentaje);
                        funcionUsada [14] = 1;
                    }
                    else
                        puts ("Porcentaje fuera de los limites permitido");
                }

                else
                    puts ("Achicar ya fue usado");
            }
            break;
            default:
            {
                if (i != pos && i != posCH && i != posCV)
                    puts ("Argumento invalido\n");
            }
            break;
            }
        }
        for (j = 0; j < datImg.header.alto; j++)
        {
            free(datImg.matriz[j]);
        }
        free(datImg.matriz);
    }

    return 0;
}
