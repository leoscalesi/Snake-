#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "Auxiliar.h"
#include "Serpiente.h"
#include "Comida.h"
#include <conio.h>
#include <ctime>


#define ARRIBA      72
#define IZQUIERDA   75
#define DERECHA     77
#define ABAJO       80
#define ESC         27

class Juego{

 public:

    static void jugar(int);

};


void Juego::jugar(int opc){   //LA OPCION SIRVE PARA DETERMINAR SI ES CONTRA LA MAQUINA O DE A DOS.

    srand(time(NULL));

    Auxiliar::ocultarCursor();
    Auxiliar::pintarLimites();

    Serpiente serpiente(10,10);
    serpiente.dibujarPuntaje();

    Comida comida(rand()% (SCREEN_WIDTH-10) + 10,rand()% (SCREEN_HEIGHT- 4) + 4);
    comida.pintarComida();

    bool comio = false;

    while(serpiente.gameOver() == false){

       comio = serpiente.compararCoordenadas(comida);  // CONTROL VELOCIDAD, FUNCIONA PERO VER SI SE PUEDE MEJORAR.

       if(comio){

            if(serpiente.getPuntaje()%20 == 0){

                serpiente.setVelocidad(serpiente.getVelocidad() - 20);
            }
      }

       serpiente.borrarCuerpo();

       serpiente.guardarPosicion();

       serpiente.dibujarCuerpo();

       Sleep(serpiente.getVelocidad()); // ESE DECREMENTO EN LA VELOCIDAD, LO COLOCO EN LA FUNCION Sleep, ALHABER MENOS RETARDO, AUMENTARA LA VELOCIDAD.
       //Sleep(100);
       serpiente.teclear();
       //A.teclear();
       serpiente.cambiarPosicion();

    }

    system("cls");
    Sleep(1000);

}


#endif // JUEGO_H_INCLUDED
