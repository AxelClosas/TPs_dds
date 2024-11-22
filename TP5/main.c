#include <stdio.h>

int main()
{
    int a = 4;

    int *p;
    p = &a;

    printf("Valor de a desde puntero p: %i\n", *p);
    printf("Dirección de memoria de a real: %p\n", &a);
    printf("Dirección de memoria de a que tiene p: %p\n", p);
    printf("Dirección de memoria de puntero p: %p\n", &p);

//
//    int n = 75;
//    int* p = &n; /* p variable puntero, tiene dirección de n */
//    printf("n = %d, &n = %p, p = %p\n",n,&n,p);
//    printf ("&p = %p\n",&p);

    /* Punteros y Arrays */

//    int arr[5];
//
//    for (int i=0;i<5;i++)
//        arr[i] = i+1;
//
//    for (int i=0;i<5;i++)
//        printf("%i ", arr[i]);
//    printf("\n----------- con indireccion ----\n");
//    for (int i=0;i<5;i++)
//        *(arr+i) = i+1;
//
//    for (int i=0;i<5;i++)
//        printf("%i ", *(arr+i));

//}
//
//
}
