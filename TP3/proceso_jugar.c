void ubicar_fichas(TABLERO *jug)
{
    int i, j, k;
    int fila, columna;

//    printf("Observa el tablero y luego ingresa la fila y columna para ubicar tu ficha.\n\n");

    for (i=0; i < cant_fichas; i++)
    {
//        printf("Jugador [%i]\n\n", jug->jugador);
        pintar_tablero(jug);
//        printf("\n\n");
//        printf("Tienes %d fichas disponibles...\n\n", cant_fichas - i);
//        printf("\n");
        do
        {
//            printf("Fila: ");
            scanf("%d", &fila);
//            printf("\n");
//            printf("Columna: ");
            scanf("%d", &columna);
//            if ((fila < 1 || fila > T) || (columna < 1 || columna > T))
//            {
//                printf("Posiciones fuera de rango... Vuelve a ingresarlas...");
//                printf("\n\n");
//            }

        } while ((fila < 1 || fila > T) || (columna < 1 || columna > T ));

        for (j = 0; j < T; j++)
            for (k = 0; k < T; k++)
                if (j == fila - 1 && k == columna - 1)
                    if (jug -> tablero[fila - 1][columna - 1] != 1)
                        jug -> tablero[fila - 1][columna - 1] = 1;
                    else
                    {
//                        printf("Ya has ingresado esas coordenadas, prueba a ingresar otras...\n");
                        i--;
                    }


//        system("PAUSE");
//        system("CLS");
    }
}
