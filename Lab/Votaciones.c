#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxPartidos 4
// Cambio
int pass_admin= 9898;

typedef struct Partido
{
    int codigo;
    char nombrePartido[100];
    unsigned long int cant_votos_presi;
    unsigned long int cant_votos_gober;
    int Borrado;
}Partidos;

typedef struct Mesa
{
    long int nroMesa;
    unsigned long int votos_impug;
    unsigned long int votos_blanco;
    unsigned long int votos; // Sumatoria total de votos en blanco, impugnados y cada voto que exista dentro de cada partido de la mesa
    Partidos par[maxPartidos];
    int borrado;
}mesas;

// partidos
int altaPartido(); // OK
long keyPartido(FILE*pf,int key); // OK
int listarPartidos(); // OK
int modificarPar(); // OK
int removerPartido(); // OK
int limpiezaPar(); // OK
// mesas
long keyMesas(FILE*pf,long int key); // OK
int mostrarMesas(); // OK
int limpiarMesa(); // OK
int Baja_Mesa(); // OK
int escribirMesa(); // Falta agregar ordenamiento por inserción
int actualizar_mesas();
int info_Mesa(); // OK
int ordenar_mesas();
int Resultados();
long int total_votos_presidente_general();
long int total_votos_gobernador_general();
long int total_votos_general();

int menu1()
{
        int opcion;
        int pass;
        int control;
        system("cls");
        do
        {
            system("cls");
            printf("\n[1]. Ingresar Partidos");
            printf("\n[2]. Listar Partidos");
            printf("\n[3]. Modificar partidos");
            printf("\n[4]. Borrar partidos");
            printf("\n[5]. Mesas");
            printf("\n[7]. Salir");
            printf("\nOpcion: ");
            fflush(stdin);
            scanf("%d",&opcion);

            if ((opcion == 1) || (opcion == 4) || (opcion == 3))
            {   printf("Contrase%ca\n>> ",164);
                fflush(stdin);
                scanf("%i", &pass);
                if (pass == pass_admin){
                    control = 1;
                }else
                {
                    printf("Contrase%ca incorrecta!\n", 164);
                    control = 0;
                    system("pause");
                }
            }
            else
                control = 1;

        } while (control == 0);

        return opcion;
}
int menu2()
{
    int control, opcion;
    int pass;
    do
    {
        system("cls");
        printf("\n[1]. Cargar Mesa");
        printf("\n[2]. Listar Mesas");
        printf("\n[4]. Relevamiento de Mesa"); // Relevamiento de mesas: Permitir ver información de una mesa en particular ordenado de mayor a menor según la cantidad de votos de cada cargo y poniendo el porcentaje correspondiente.
        printf("\n[5]. Borrar Mesa");
        printf("\n[6]. Resultado");
        printf("\n[7]. salir\nOpcion: ");
        fflush(stdin);
        scanf("%d",&opcion);
        if (opcion == 5)
        {   printf("Contrase%ca\n>> ",164);
            fflush(stdin);
            scanf("%i", &pass);
            if (pass == pass_admin){
                control = 1;
            }else
            {
                printf("Contrase%ca incorrecta!\n", 164);
                control = 0;
                system("pause");
            }
        }
        else
            control = 1;

        } while (control == 0);

        return opcion;
}

int main()
{   int opcion,op1;
    do
    {
        opcion = menu1();
        switch (opcion)
        {
        case 1:
            altaPartido();
            break;
        case 2:
            listarPartidos();
            break;
        case 3:
            modificarPar();
            break;
        case 4:
            removerPartido();
            break;

        case 5:// MESAS
            do
            {   op1 = menu2();
                switch(op1)
                {
                case 1:
                    escribirMesa();
                    break;
                case 2:
                    mostrarMesas();
                    printf("\n");
                    system("pause");
                    break;
                case 4:
                    info_Mesa(); // TODO;
                    break;
                case 5:
                    Baja_Mesa();

                    break;
                case 6:
                    Resultados();
                    break;
                case 7:
                    printf("\nSaliendo...\n");
                    system("pause");
                    break;
                default :
                    printf("\nOpcion invalida");
                    break;
                }
            }while(op1 != 7);
            break;
        case 7:
            puts("saliendo...");
            break;
        default:
            puts("Opcion invalida");
            break;

        }
    }while(opcion != 7);
    return 0;

}
long keyPartido(FILE*pf,int key)
{
    Partidos partido;
    long posReg = -1;
    fseek(pf,0,SEEK_SET);
    fread(&partido,sizeof(partido),1,pf);
    while(!feof(pf))
    {
        if (key == partido.codigo)
        {
            posReg = ftell(pf)-sizeof(Partidos);
        }
        fread(&partido,sizeof(partido),1,pf);
    }
    return posReg;
}

int altaPartido()
{
    Partidos par;
    int op;
    FILE*ptr = fopen("Partidos.dat","a+b");
    if (ptr == NULL) {
        puts("error al abrir el archivo");
        return -1;
    }
    do
    {
        fseek(ptr,0,SEEK_END);
        long tam = ftell(ptr)/sizeof(Partidos);
        if (tam == maxPartidos)
        {
            puts("No se puede agregar mas partidos");
            system("pause");
            return -1;
        }
        printf("\nIngrese el Codigo del partido: ");
        fflush(stdin);
        scanf("%d",&par.codigo);
        if (keyPartido(ptr,par.codigo) == -1)
        {
            printf("Ingrese el Nombre del Partido: ");
            fflush(stdin);
            gets(par.nombrePartido);
        }
        else
        {
           printf("\nYa existe un partido con este codigo\n");
           system("pause");
           return -1;
        }
        fseek(ptr,0,SEEK_END);
        int falla = fwrite(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {
            puts("error de escritura");
            return -1;
        }
        fflush(ptr);
        printf("\nQuieres ingresar otro partido SI/1 NO/0\nOpcion: ");
        scanf("%d",&op);
    }while(op == 1);
    fclose(ptr);
    return 0;
}

int listarPartidos ()
{
    Partidos par;
    FILE*pf = fopen("Partidos.dat","rb");
    if (pf == NULL)
    {
        puts("error al abrir el archivo"); system("pause");
        return -1;
    }
    fseek(pf,0,SEEK_SET);
    fread(&par,sizeof(Partidos),1,pf);
    printf("CODIGO   |   NOMBRE DEL PARTIDO                             ");
    while(!feof(pf))
    {
        if (par.Borrado != 1)
        {
            printf("\n   %i     |   %s                                             ",par.codigo, par.nombrePartido);
            fread(&par,sizeof(Partidos),1,pf);
        }
    }
    printf("\n");
    system("pause");
    fclose(pf);

    return 0;
}
int actualizar_mesas()
{
    mesas reg;
    Partidos reg_p;
    FILE *ptr_mesas = fopen("Mesas.dat", "r+b");
    if (ptr_mesas == NULL)
    {
        printf("No se pudo abrir el archivo Mesas.dat. Comprueba si existe.");
        return -1;
    }
    FILE *ptr_part = fopen("Partidos.dat", "rb");
    if (ptr_mesas == NULL)
    {
        printf("No se pudo abrir el archivo Partidos.dat. Comprueba si existe.");
        return -1;
    }

    fread(&reg, sizeof(mesas), 1, ptr_mesas);
    while (!feof(ptr_mesas))
    {
        int cant_part = sizeof(reg.par)/sizeof(reg.par[0]);
        for(int i=0; i < cant_part; i++)
        {
            // Lectura de archivo partido
            fseek(ptr_part, 0, SEEK_SET);
            fread(&reg_p, sizeof(Partidos), 1, ptr_part);
            while (!feof(ptr_part))
            {
                if (reg_p.codigo == reg.par[i].codigo)
                    strcpy(reg.par[i].nombrePartido, reg_p.nombrePartido);
                fread(&reg_p, sizeof(Partidos), 1, ptr_part);
            }
        }
        fread(&reg, sizeof(mesas), 1, ptr_mesas);
    }
    fclose(ptr_mesas);
    return 0;
}
int modificarPar()
{
    /*
        Verificar que existan mesas
        Cuando se modifiqué el nombre (al final), recorrer el archivo Mesas.dat y modificar cada
    */
    int flag = 0;
    Partidos par;
    long int cod_part;
    int op;
    int op1;
    int existe_MesasDat=1;

    FILE*ptr = fopen("Partidos.dat","r+b");
    if (ptr == NULL)
    {
        puts("error al abrir el archivo Partidos.dat");
        system("pause");
        return -1;
    }

    FILE*ptr_mesas = fopen("Mesas.dat","rb");
    if (ptr_mesas != NULL)
        existe_MesasDat=0;

    do
    {
        printf("\nIngrese el codigo del partido que desea modifcar: ");
        fflush(stdin);
        scanf("%d",&cod_part);
        long pos = keyPartido(ptr,cod_part);
        if (pos == -1)
        {
            puts("No hay ningun partido con ese codigo");
            system("pause");
            return -1;
        }
        fseek(ptr,pos,SEEK_SET);
        int falla = fread(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {
            puts("error al leer el archivo");
            system("pause");
            return -1;
        }
        else
        {
            printf("\nCodigo: %d",par.codigo);
            printf("\nNombre del Partido: %s",par.nombrePartido);
            printf("\nEste es el partido que quieres modificar SI/1 NO/0");
            printf("\n>>> ");
            fflush(stdin);
            scanf("%d",&op1);
            if (op1 == 0)
            {
                puts("saliendo...");
                system("pause");
                return -1;
            }

        }
        printf("Ingrese el Nombre del Partido: ");
        fflush(stdin);
        gets(par.nombrePartido);
        fseek(ptr,pos,SEEK_SET);
        int falla1 = fwrite(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {
            puts("error de escritura");
            system("pause");
            return -1;
        }
        fflush(ptr);
        printf("\nEl nuevo partido con sus modificaciones es: ");
        printf("\nNombre del Partido: %s",par.nombrePartido);
        printf("\nQuieres modificar otro partido SI/1 NO/0\nOpcion: ");
        fflush(stdin);
        scanf("%d",&op);


    }while(op == 1);
    fclose(ptr);
    if (!existe_MesasDat)
        actualizar_mesas();

    return 0;
}

int removerPartido()
{
    Partidos par;
    long int cod_part;
    int op,op1;
    FILE*ptr = fopen("Partidos.dat","r+b");
    if (ptr == NULL)
    {   puts("error al abrir el archivo");
        return -1;
    }
    do
    {
        fseek(ptr,0,SEEK_SET);
        int falla = fread(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {   puts("error de lectura");
            return -1;
        }
        // Mostrar información de posibles partidos a borrar
        while(!feof(ptr))
        {
            if (par.Borrado != 1)
            {
                printf("\nPartidos: ");
                printf("\nCodigo: %d",par.codigo);
                printf("\nNombre del Partido: %s",par.nombrePartido);
            }
            fread(&par,sizeof(Partidos),1,ptr);
        }

        printf("\nIngrese el codigo del partido: ");
        fflush(stdin);
        scanf("%d",&cod_part);
        long posArch = keyPartido(ptr,cod_part);
        if (posArch != -1)
        {
           fseek(ptr,posArch,SEEK_SET);
           int falla1 = fread(&par,sizeof(Partidos),1,ptr);
           if (falla1 != 1)
           {
              puts("error de lectura");
              return -1;
           }
            printf("\nCodigo: %d",par.codigo);
            printf("\nNombre del Partido: %s",par.nombrePartido);

            printf("\n\nEste es el partido que quieres eliminar SI/1 NO/0\nOpcion: ");
            fflush(stdin);
            scanf("%d",&op1);
            if (op1 == 0)
            {
                puts("saliendo...");
                system("pause");
                return 0;
            }
            par.Borrado = 1;
            fseek(ptr,posArch,SEEK_SET);
            int falla2 = fwrite(&par,sizeof(Partidos),1,ptr);
            if (falla2 != 1)
            {   puts("No se pudo eliminar el registro.");
                return -1;
            }
            fflush(ptr);
        }
        else
        {
            puts("no hay un partido con ese codigo");
            system("pause");
            return 0;
        }

        printf("\nQuiere eliminar otro partido SI/1 NO/0 \nOpcion: ");
        fflush(stdin);
        scanf("%d",&op);

    }while(op == 1);
    fclose(ptr);
    limpiezaPar();

    return 0;
}

int limpiezaPar()
{
    FILE *pf = fopen("Partidos.dat", "rb");
    if (pf == NULL)
    {
        puts("error de apertura del archivo Partidos.dat");
        return -1;
    }
    FILE*pf1 = fopen("Temporal.tmp","wb");
    if (pf1 == NULL)
    {
        puts("error de apertura");
        return -1;
    }

    Partidos par;

    fseek(pf,0,SEEK_SET);

    int falla = fread(&par,sizeof(Partidos),1,pf);
    if (falla != 1)
    {
        puts("error de lectura");
        return -1;
    }
    while(!feof(pf))
    {
        if (par.Borrado != 1)
        {
            fseek(pf1,0,SEEK_END);
            int falla1 = fwrite(&par,sizeof(Partidos),1,pf1);
            if(falla1 != 1)
            {
                puts("error de escritura");
                return -1;
            }
            fflush(pf1);
        }
        fread(&par,sizeof(Partidos),1,pf);
    }

    fclose(pf);
    fclose(pf1);

    if( remove("Partidos.dat") == 0)
    {
        printf("\nSe elimino Partidos.dat\n");
        if ( rename("Temporal.tmp", "Partidos.dat") == 0)
            printf("\nSe renombró Temporal.tmp a Partidos.dat\n");
        else
            printf("\nNo se pudo renombrar el archivo Temporal.tmp\n");
    }
    else
        puts("No se pudo eliminar Partidos.dat porque el archivo no existe.");

    system("pause");
    return 0;
}
long keyMesas(FILE*pf,long int key)
{
    mesas mesa;
    long int posReg = -1;
    fseek(pf,0,SEEK_SET);
    fread(&mesa,sizeof(mesas),1,pf);
    while(!feof(pf))
    {
        if (key == mesa.nroMesa)
        {
            posReg = ftell(pf) - sizeof(mesas);
        }
        fread(&mesa,sizeof(mesas),1,pf);
    }
    return posReg;
}
int limpiarMesa()
{
    FILE *pf = fopen("Mesas.dat", "rb");
    if (pf == NULL)
    {
        printf("\nError al abrir el archivo Mesas.dat\n");
        return -1;
    }
    FILE*pf1 = fopen("TemporalMesa.tmp","wb");
    if (pf1 == NULL)
    {
        puts("error de apertura");
        return -1;
    }
    mesas mesa;

    fseek(pf,0,SEEK_SET);
    int falla = fread(&mesa,sizeof(mesas),1,pf);
    if (falla != 1)
    {
        puts("error de lectura");
        return -1;
    }
    while(!feof(pf))
    {
        if (mesa.borrado != 1)
        {
            fseek(pf1,0,SEEK_END);
            int falla1 = fwrite(&mesa,sizeof(mesas),1,pf1);
            if(falla1 != 1)
            {
                puts("error de escritura");
                return -1;
            }
            fflush(pf1);
        }
        fread(&mesa,sizeof(mesas),1,pf);
    }
    fclose(pf1);
    fclose(pf);

    if( remove("Mesas.dat") == 0)
    {
        printf("\nSe elimino Mesas.dat\n");
        if ( rename("TemporalMesa.tmp", "Mesas.dat") == 0)
            printf("\nSe renombró TemporalMesa.tmp a Mesas.dat\n");
        else
            printf("\nNo se pudo renombrar el archivo TemporalMesa.tmp\n");
    }
    else
        puts("No se pudo eliminar Mesas.dat");

    system("pause");
    return 0;

}

int escribirMesa()
{
    FILE *ptr_M = fopen("Mesas.dat","a+b");
    if (ptr_M == NULL)
    {
        puts("error al abrir el archivo");
        return -1;
    }
    FILE *ptr_P = fopen("Partidos.dat","rb");
    if (ptr_P == NULL)
    {
        puts("error al abrir el archivo");
        return -1;
    }
    int op;
    long int accum = 0;
    int i=0;
    mesas mesa;
    Partidos par;
 /* Info de mesas */
    do
    {
        printf("\nIngrese el numero de la mesa: ");
        fflush(stdin);
        scanf("%ld",&mesa.nroMesa);
        if (keyMesas(ptr_M,mesa.nroMesa) != -1 )
            printf("\nYa existe la mesa %ld",mesa.nroMesa);

    } while (keyMesas(ptr_M,mesa.nroMesa) != -1);

    fseek(ptr_P,0,SEEK_END);

    long cant_par = ftell(ptr_P)/sizeof(Partidos);

    if (cant_par == 0) {
        printf("\nDebe existir al menos un partido para crear la mesa\n");
        return -1;
    }
    fseek(ptr_P,0,SEEK_SET);
    int falla = fread(&par,sizeof(Partidos),1,ptr_P);
    if (falla != 1)
    {   puts("error de lectura");
        return -1;
    }
    while (!feof(ptr_P))
    {
        mesa.par[i] = par;
        i++;
        fread(&par,sizeof(Partidos),1,ptr_P);
    }
    /* Info de mesas */
    /* Ingreso de votos */
    printf("\nIngrese la cantidad de votos de cada partido\n ");
    for (i =0; i < cant_par; i++)
    {
        int votos_presi, votos_gob;

        printf("Partido [%li]\n", mesa.par[i].codigo);
        printf("Nombre [%s]\n", mesa.par[i].nombrePartido);
        printf("\nVotos a Presidente: ");
        fflush(stdin);
        scanf("%i", &votos_presi);
        mesa.par[i].cant_votos_presi = votos_presi;

        printf("\nVotos a Gobernador: ");
        fflush(stdin);
        scanf("%i", &votos_gob);

        mesa.par[i].cant_votos_gober = votos_gob;

        accum += mesa.par[i].cant_votos_presi;
        accum += mesa.par[i].cant_votos_gober;
    }
    printf("\nIngrese la cantidad de votos en blanco: ");
    fflush(stdin);
    scanf("%ld",&mesa.votos_blanco);
    printf("\nIngrese la cantidad de votos impugnados: ");
    fflush(stdin);
    scanf("%ld",&mesa.votos_impug);
    system("pause");

    accum += mesa.votos_blanco;
    accum += mesa.votos_impug;

    mesa.votos = accum;

    printf("\n");
    fseek(ptr_M,0,SEEK_END);
    fwrite(&mesa,sizeof(mesas),1,ptr_M);
    fflush(ptr_M);
    fclose(ptr_M);
    fclose(ptr_P);
    ordenar_mesas();

    return 0;
}
int mostrarMesas()
{
    FILE *ptr_M = fopen("Mesas.dat","rb");
    if (ptr_M == NULL)
    {
        puts("No hay mesas cargadas todavia...\n");
        return -1;
    }
    FILE *ptr_P = fopen("Partidos.dat","rb");
    if (ptr_P == NULL)
    {
        puts("No existen partidos para cargar las mesas...\n");
        return -1;
    }
    mesas mesa;
    Partidos par;
    fseek(ptr_P,0,SEEK_END);
    long cant_par = ftell(ptr_P)/sizeof(Partidos);

    fseek(ptr_M,0,SEEK_SET);
    int falla = fread(&mesa,sizeof(mesas),1,ptr_M);

    if (falla != 1)
    {
        puts("error de lectura");
        return -1;
    }
    while(!feof(ptr_M))
    {
        printf("\nID MESA [%li]\n", mesa.nroMesa);
        printf("\n      PARTIDO       |  VOTOS PRESI   | VOTOS GOBER\n");
        for(int i = 0; i < cant_par ;i++ )
        {
            printf("%s              |       %li      |     %li   \n", mesa.par[i].nombrePartido, mesa.par[i].cant_votos_presi, mesa.par[i].cant_votos_gober);
        }
        fread(&mesa,sizeof(mesas),1,ptr_M);
        printf("\n");
    }
    fclose(ptr_M);
    fclose(ptr_P);

    return 0;
}


int Baja_Mesa() // Baja lógica de la mesa
{
    FILE*ptr_M = fopen("Mesas.dat","r+b");
    if (ptr_M == NULL)
    {   puts("error al abrir el archivo1");
        return -1;
    }
    int op1;
    mesas mesa;
    long int cod_mesa;
    long int pos;
    do
    {
        printf("\nIngresa en numero de mesa: ");
        fflush(stdin);
        scanf("%li",&cod_mesa);
        pos = keyMesas(ptr_M,cod_mesa);
        if (pos == -1)
        {
            puts("Mesa inexistente");
            system("pause");
        }

    } while(pos == -1);

    fseek(ptr_M,pos,SEEK_SET);
    int falla = fread(&mesa,sizeof(mesas),1,ptr_M);
    if (falla != 1)
    {
        puts("error de lectura");
        return -1;
    }
    printf("\nNro. de Mesa: [%li]",mesa.nroMesa);

    printf("¿\nEsta es la mesa que deseas borrar? [1]SI [0]NO\nOpcion: ");
    fflush(stdin);
    scanf("%d",&op1);
    if(op1 == 0)
       return -1;
    else
    {
        mesa.borrado = 1;
        fseek(ptr_M,pos,SEEK_SET);
        fwrite(&mesa,sizeof(mesas),1,ptr_M);
        fflush(ptr_M);
    }
    fclose(ptr_M);
    limpiarMesa(); // Proceso de baja fisica

    return 0;
}

int info_Mesa()
{
    FILE *ptr_M = fopen("Mesas.dat", "rb");
    if (ptr_M == NULL){
        printf("No hay mesas para visualizar.\n");
        system("pause");
        return -1;
    }
    FILE *ptr_P = fopen("Partidos.dat", "rb");
    if (ptr_P == NULL) {
        printf("No existen partidos asociados...\n");
        system("pause");
        return -1;
    }

    int op;
    mesas mesa;
    Partidos par;
    long int codigo_mesa;
    fseek(ptr_P,0,SEEK_END);

    int cant_par = ftell(ptr_P)/sizeof(Partidos);
    do
    {

        printf("\nIngrese el numero de mesa: ");
        fflush(stdin);
        scanf("%ld",&codigo_mesa);
        long int pos = keyMesas(ptr_M,codigo_mesa);
        if (pos == -1)
        {
            printf("\nMesa inexistente\n");
            system("pause");
            return -1;
        }
        fseek(ptr_M,pos,SEEK_SET);
        int falla = fread(&mesa,sizeof(mesas),1,ptr_M);
        if (falla != 1)
        {
            puts("error de lectura");
            return -1;
        }
        system("cls");
        printf("\nMesa [%li]", mesa.nroMesa);
        printf("\nNro. de votos en la mesa: [%li]", mesa.votos);
        printf("\n\nPARTIDO\t\t\tVOTOS PRESIDENTE\n");
        for(int i=0;i<cant_par;i++)
        {
            printf("[%s]", mesa.par[i].nombrePartido);
            printf("\t\t[%li] [%.2f%c]", mesa.par[i].cant_votos_presi, (((float)mesa.par[i].cant_votos_presi/(float)mesa.votos)*100), 37 );
            printf("\n");
        }

        printf("\n\nPARTIDO\t\t\tVOTOS GOBERNADOR\n");
        for(int i=0;i<cant_par;i++)
        {
            printf("[%s]", mesa.par[i].nombrePartido);
            printf("\t\t[%li] [%.2f%c]", mesa.par[i].cant_votos_gober, (((float)mesa.par[i].cant_votos_gober/(float)mesa.votos)*100), 37);
            printf("\n");
        }

        printf("\nVotos en Blanco: %ld\t%.2f%c", mesa.votos_blanco, (((float)mesa.votos_blanco/(float)mesa.votos)*100), 37);
        printf("\nVotos Impugnados: %ld\t%.2f%c", mesa.votos_impug, (((float)mesa.votos_impug/(float)mesa.votos)*100), 37);
        printf("\n\n");
        printf("\nQuieres buscar otra mesa?\nSI/1 NO/0\n>>>");
        fflush(stdin);
        scanf("%d",&op);

    }while(op != 0);

    return 0;
}

int ordenar_mesas()
{
    int long i,j,index;
    mesas mesa;
    FILE*ptr_mesas = fopen("Mesas.dat","r+b");
    if (ptr_mesas == NULL)
    {
        puts("error de apertura");
        return -1;
    }

    fseek(ptr_mesas,0,SEEK_END);
    int cant_mesas = ftell(ptr_mesas)/sizeof(mesas);
    fseek(ptr_mesas,0,SEEK_SET);
    if (cant_mesas <= 1)
    {
        puts("Mesas insuficientes para ordenar");
        return -1;
    }
    mesas *aux = (mesas*)malloc(cant_mesas*sizeof(mesas));
    if (aux == NULL)
    {
        puts("error al asignar memoria");
        return -1;
    }
    for (i=0;i<cant_mesas;i++)
    {
        int falla = fread(&aux[i],sizeof(mesas),1,ptr_mesas);
        if (falla != 1)
        {
            free(aux);
            fclose(ptr_mesas);
            puts("error de lectura");
            return -1;
        }
    }
    for(i=1;i<cant_mesas;i++)
    {
        index = aux[i].nroMesa;
        j = i - 1;
        while(j >= 0 && aux[j].nroMesa > index)
        {
            aux[j+1].nroMesa = aux[j].nroMesa;
            j--;
        }
        aux[j+1].nroMesa = index;
    }
    fseek(ptr_mesas,0,SEEK_SET);
    for (i=0;i<cant_mesas;i++)
    {
        fwrite(&aux[i],sizeof(mesas),1,ptr_mesas);
    }

    fclose(ptr_mesas);
    free(aux);
}
long int total_votos_general()
{
    mesas reg;
	FILE *ptr_mesas = fopen("Mesas.dat", "rb");
	if (ptr_mesas == NULL)
    {
        printf("\nNo se pudo conectar con el archivo Mesas.dat\n");
        return -1;
    }
    long int total_votos = 0;
    int k;

    fseek(ptr_mesas, 0, SEEK_SET);
    fread(&reg,sizeof(mesas),1,ptr_mesas);
    while (!feof(ptr_mesas))
    {
        total_votos += reg.votos;
        fread(&reg,sizeof(mesas),1,ptr_mesas);
    }
    fclose(ptr_mesas);
    return total_votos;
}

long int total_votos_presidente_general()
{
    mesas reg;
	FILE *ptr_mesas = fopen("Mesas.dat", "rb");
	if (ptr_mesas == NULL)
    {
        printf("\nNo se pudo conectar con el archivo Mesas.dat\n");
        return -1;
    }
    long int total_votos_presi = 0;
    int k;

    fseek(ptr_mesas, 0, SEEK_SET);
    fread(&reg,sizeof(mesas),1,ptr_mesas);
    while (!feof(ptr_mesas))
    {
        k=0;
        long int total_votos_presi_x_mesa=0;
        int cant_part = sizeof(reg.par) / sizeof(reg.par[0]);
        while (k < cant_part)
        {
            total_votos_presi_x_mesa += reg.par[k].cant_votos_presi;
            k++;
        }
        total_votos_presi += total_votos_presi_x_mesa;
        fread(&reg,sizeof(mesas),1,ptr_mesas);
    }
    fclose(ptr_mesas);
    return total_votos_presi;
}

long int total_votos_gobernador_general()
{
    mesas reg;
	FILE *ptr_mesas = fopen("Mesas.dat", "rb");
	if (ptr_mesas == NULL)
    {
        printf("\nNo se pudo conectar con el archivo Mesas.dat\n");
        return -1;
    }
    long int total_votos_gober = 0;
    int k;

    fseek(ptr_mesas, 0, SEEK_SET);
    fread(&reg,sizeof(mesas),1,ptr_mesas);
    while (!feof(ptr_mesas))
    {
        k=0;
        long int total_votos_gober_x_mesa=0;
        int cant_part = sizeof(reg.par) / sizeof(reg.par[0]);
        while (k < cant_part)
        {
            total_votos_gober_x_mesa += reg.par[k].cant_votos_gober;
            k++;
        }
        total_votos_gober += total_votos_gober_x_mesa;
        fread(&reg,sizeof(mesas),1,ptr_mesas);
    }
    fclose(ptr_mesas);
    return total_votos_gober;
}

int Resultados(){
    long int total_votos_presi = total_votos_presidente_general();
    long int total_votos_gober = total_votos_gobernador_general();
    long int total_votos_gen = total_votos_general();
    long int mayor_presi = 0;
    long int mayor_gober=0;
    mesas reg;
    Partidos par_aux[maxPartidos];
    Partidos ganador_presi;
    Partidos ganador_gober;

    for (int i=0;i < maxPartidos; i++)
    {
        par_aux[i].cant_votos_presi = 0;
        par_aux[i].cant_votos_gober = 0;
    }


    FILE *ptr_mesas = fopen("Mesas.dat", "rb");
    if (ptr_mesas == NULL)
    {
        printf("Error al abrir el archivo Mesas.dat como rb\n");
        system("pause");
        return -1;
    }

    system("cls");
    printf("Total de votos: %li\n", total_votos_gen);
    printf("Total de votos para Presidente: %li\n", total_votos_presi);
    printf("Total de votos para Gobernador: %li\n", total_votos_gober);

    fread(&reg, sizeof(mesas), 1, ptr_mesas);
    while(!feof(ptr_mesas))
    {
        for (int k =0; k < maxPartidos; k++)
        {
            strcpy(par_aux[k].nombrePartido, reg.par[k].nombrePartido);
            par_aux[k].cant_votos_presi += reg.par[k].cant_votos_presi;
            par_aux[k].cant_votos_gober += reg.par[k].cant_votos_gober;
        }
        fread(&reg, sizeof(mesas), 1, ptr_mesas);
    }

    printf("PARTIDO     |     PRESIDENTE  \n");
    for (int i=0; i < maxPartidos; i++)
        printf("%s          |  %li [%.2f%c]      \n", par_aux[i].nombrePartido,par_aux[i].cant_votos_presi, ((float)par_aux[i].cant_votos_presi*100)/(float)total_votos_presi, 37);

    printf("\n\n");
    printf("PARTIDO     |     GOBERNADOR  \n");
    for (int i=0; i < maxPartidos; i++)
        printf("%s          |  %li [%.2f%c]      \n", par_aux[i].nombrePartido,par_aux[i].cant_votos_gober, ((float)par_aux[i].cant_votos_gober*100)/(float)total_votos_gober, 37);
    system("pause");

    // Algoritmo Presidente ganador
     for (int j= 0; j < maxPartidos; j++){
        if (par_aux[j].cant_votos_presi > mayor_presi){
            mayor_presi = par_aux[j].cant_votos_presi;
            ganador_presi = par_aux[j];
        }

     }
     for (int j= 0; j < maxPartidos; j++){

        if (par_aux[j].cant_votos_gober > mayor_gober){
            mayor_gober = par_aux[j].cant_votos_gober;
            ganador_gober = par_aux[j];
        }
     }
    system("cls");
    printf("GANADORES\n\n");
    printf("Eleccion Presidencial\n\n");
    printf("%s\t con el [%.2f%c] de los votos.\n", ganador_presi.nombrePartido, (((float)ganador_presi.cant_votos_presi*100)/(float)total_votos_presi), 37);
    printf("\n");

    printf("Eleccion de Gobernador\n\n");
    printf("%s\t con el [%.2f%c] de los votos.\n", ganador_gober.nombrePartido, (((float)ganador_gober.cant_votos_gober*100)/(float)total_votos_gober), 37);
    printf("\n");
    system("pause");
    return 0;
}
