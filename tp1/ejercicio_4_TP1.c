#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

int main (){

 setlocale(LC_CTYPE, "spanish");

	int heroe;
	int camino;
	char nombre[30];



	printf("Antes de adentrarte en esta historia, escribe tu nombre de heroe que protagonizará ésta aventura. \n");
	printf("El destino de este personaje estará en tus manos, y tus decisiones podrian llevarlo a la gloria... o a la perdición...");
	printf("\n\n\t- Nuevo Mensaje")
	scanf("%s", &nombre);
	printf("%s, un joven de origen humilde, caminaba por un denso bosque en un día en el que las nubes negras cubrían el cielo.\n", nombre);

	printf("%s se encuentra en cualquier lado y tienes que elegir uno de los siguientes caminos 1 2 o 3", nombre);
	scanf("%i", &heroe);
	switch (heroe)
	{
		case 1: printf("emprender un viaje peligroso.");
						printf("escoge el siguiente camino 1: pelear dragon. 2: conoce la minita");
						scanf("%i", &camino);

						if (camino == 1){
							printf("pelea con dragon");
							printf("final mata dragon");
						}
						else{
							printf("conoce la minita");
							printf("se va al campo");
						}
				break;

		case 2: printf("se quedaba a defender el pueblo");
						printf("escoge el siguiente camino 1: conocer la minita 2:pelear con el ogro.");
						scanf("%i", &camino);

						if (camino == 1){
							printf("conoce la minita");
							printf("se va al campo");
						}
						else{
							printf("pelea con el ogro");
							printf("final.lo mata al ogro");
						}
				break;
		case 3: printf("ambicion de poder. full timba");
					printf("final.la ambicion del poder lo mata");
				break;
		default : printf("default/n");



	}




}
