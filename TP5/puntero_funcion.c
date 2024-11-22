#include <stdio.h>

int mifunc(int i); /* prototipo de mifunc */
void sufunc(int (*f) (int)); /* prototipo de sufunc */

void main()
{
    int a = 1 ;
    int *pt1 = &a;

    int **pt2 = &pt1;


    printf("Direccion de a: %p\n", &a);
    printf("Direccion de pt1: %p\n", &pt1);
    printf("Direccion de pt2: %p\n", &pt2);

    printf("Direccion de a desde pt1: %p\n", pt1);
    printf("Direccion de a desde pt2: %p\n", *pt2);
    printf("-----\n");
    printf("Valor de a: %i\n", a);
    printf("Valor de a desde pt1: %i\n", *pt1);
    printf("Valor de a desde pt2: %i\n", **pt2); // **pt2 -> *pt1 -> a

    printf("Dir. a = %p - v a l o r =%d \nDireccion pt1: %p = %p", *pt2 ,**pt2, pt2, &pt1);

    return 0;
}
//
//int mifunc(int i)
//{
//return 5*i;
//}
//
//
//void sufunc(int (*f)(int))
//{
//    int j = f(10);
//    printf("%i", j);
//}

//#include <stdio.h>
//#include <math.h>
//
//double suma_cuadrados(double (*f)(double), int, int);
//double inversa ( double x) { return 1.0/x; }
//int main() {
//    double s;
//    double (*f[3])(double) = {sin,cos, inversa};
//
//     for (int i=0; i<3; i++) {
//         s = suma_cuadrados(f[i], 1, 100);
//         printf("suma de 1 a 100 de f[%d](i) = %lf\n", i, s);
//     }
//    return 0;
//}
//
//double suma_cuadrados(double (*f)(double), int, int)
//{
//    double s = 0,x;
//    int i;
//
//    for (i=i0; i<=if; i++)
//    {
//        x = i;
//        s += f(x)*f(x);
//
//     }
//    return s;
//}
