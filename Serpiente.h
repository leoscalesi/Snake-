#ifndef SERPIENTE_H_INCLUDED
#define SERPIENTE_H_INCLUDED

#include "Auxiliar.h"
#include "Comida.h"
#include <conio.h>


//Los valores que se le asignan a cada palabra son los valores del código ascii asociados a las flechas del teclado.
#define ARRIBA      72
#define IZQUIERDA   75
#define DERECHA     77
#define ABAJO       80
#define ESC         27


class Serpiente{

    int x,y;              //COORDENADAS DE LA CABEZA.

    int cuerpo[200][2];   //CUERPO DE LA SERPIENTE. COMO NO SABEMOS DE ANTEMANO QUE TAMANIO TENDRA LA SERPIENTE, DEBEMOS PONER UN TAMANIO TAL VEZ EXAGERADO.
                          //EN ESTA MATRIZ DE ENTEROS GUARDAREMOS LAS CORRDENADAS, Y LUEGO TENIENDO ESAS COORDENADAS DIBUJAMOS.

    int controlindice;   //ESTA VARIABLE SERVIRA A LA HORA DE GUARDAR LAS COORDENADAS DE LA CABEZA DE LA SERPIENTE, PARA CONTROLAR QUE SE GUARDEN DICHAS COORDENADAS HASTA IGUALAR EL TAMAÑO
                          //ACTUAL DE LA SERPIENTE.


    int tamanio;          //TAMANIO DE LA SERPIENTE. EN EL CONSTRUCTOR DEFINIMOS QUE SEA 3.

    int direccion;        //CONTROLA LA DIRECCION DE LA SERPIENTE. EN EL CONSTRUCTOR DEFINIMOS QUE SEA 3, ES DECIR QUE SE MUEVA HACIA LA DERECHA.

    int puntos;

    int controlvelocidad;

    int velocidad;

    char tecla;

public:

    Serpiente(int _x,int _y);
    void guardarPosicion();
    void dibujarCuerpo();
    void borrarCuerpo();
    void teclear();
    void cambiarPosicion();
    bool compararCoordenadas(Comida&);
    bool gameOver();
    //int cambiarVelocidad();
    void dibujarPuntaje();

    int getVelocidad(){return velocidad;}
    void setVelocidad(int _velocidad){velocidad = _velocidad;}

    int getPuntaje(){return puntos;}

};


Serpiente::Serpiente(int _x,int _y):x(_x),y(_y),tamanio(3),controlindice(0),direccion(3),puntos(0),controlvelocidad(1),velocidad(100){}


//ESTA FUNCION SE ENCARGA DE CONTROLAR QUE SE GUARDEN PARES ORDENADOS EN BASE AL TAMAÑO DE LA SERPIENTE, SIN IMPORTAR EL TAMAÑO.
//PERO NO HACE EL CAMBIO DE LA POSICION, SOLO GUARDA LA POSICION ANTERIOR DE LA CABEZA.

void Serpiente::guardarPosicion(){

    cuerpo[controlindice][0] = x;
    cuerpo[controlindice][1] = y;

    controlindice ++;

    if(controlindice == tamanio){

        controlindice = 0;
    }
}


void Serpiente::dibujarCuerpo(){

     Auxiliar::gotoxy(x,y); printf("*");
}


//CON BORRAR LA COLA ALCANZA, YA QUE SI BORRAMOS TODO EL CUERPO SE LOGRARA UN PARPADEO DESAGRADABLE.

void Serpiente::borrarCuerpo(){

     Auxiliar::gotoxy(cuerpo[controlindice][0],cuerpo[controlindice][1]); printf(" ");

}

/*
Lo que hace esta función es recorrer toda la matriz en los espacios que están ocupados interpretarlos como coordenadas y poner un espacio vacío en ellas lo cual hasta cierto punto resulta fácil de ver que funciona pero nos toparemos con un efecto
visual desagradable, cuando el tamaño de la serpiente sea muy grande notaremos un pardeo desagradable pues estaremos borrando toda la serpiente y después pintándola lo cual no es ni por mucho necesario, pues bastaría con borrar sólo “la cola de
la serpiente” y es cuando debemos preguntarnos ¿en qué lugar de la matriz se encuentran dichas coordenadas?

Esta no es una pregunta trivial pues el lugar donde estén dichas coordenadas depende del orden en que sean llamadas estas 3 últimas funciones.

Si llamamos a estas 3 funciones dentro da la rutina del juego con el siguiente orden:

borrar_cuerpo();
guardar_posicion();
dibujar_cuerpo();


void serpiente::borrar_cuerpo() const{
     for(int i = 0 ; i < tam ; i++){
         gotoxy(cuerpo[i][0],cuerpo[i][1]); printf(" ");
     }
}
*/


//PARA LA FUNCION teclear TENER EN CUENTA LO SIGUIENTE:
/*
dir = 1 se moverá hacia arriba
dir = 2 se moverá hacia abajo
dir = 3 se moverá a la derecha
dir = 4 se moverá a la izquierda
*/


void Serpiente::teclear(){

     if(kbhit()){

        tecla = getch();

        switch(tecla){

            case ARRIBA:  if(direccion != 2) direccion = 1; break; //ESTO QUIERE DECIR QUE SI LA SERPIENTE SE MUEVE HACIA ABAJO, NO PODRA IR HACIA ARRIBA.
            case ABAJO:  if(direccion != 1) direccion = 2; break;  //ESTO QUIERE DECIR QUE SI LA SERPIENTE SE MUEVE HACIA ARRIBA, NO PODRA IR HACIA ABAJO.
            case DERECHA:  if(direccion != 4) direccion = 3; break;  //ESTO QUIERE DECIR QUE SI LA SERPIENTE SE MUEVE HACIA LA IZQUIERDA, NO PODRA IR HACIA LA DERECHA.
            case IZQUIERDA:  if(direccion != 3) direccion = 4; break;  //ESTO QUIERE DECIR QUE SI LA SERPIENTE SE MUEVE HACIA LA DERECHA, NO PODRA IR HACIA LA IZQUIERDA.
        }
     }
}


//FUNCION QUE SE ENCARGA DE EFECTIVIZAR EL MOVIMIENTO DE LA SERPIENTE.
void Serpiente::cambiarPosicion(){

    if(direccion == 3) x++;
    if(direccion == 4) x--;
    if(direccion == 1) y--;
    if(direccion == 2) y++;
}


//FUNCION QUE SE ENCARGA DE VER SI LA SERPIENTE TOCA LA COMIDA.
bool Serpiente::compararCoordenadas(Comida& comida){

    if(x == comida.X() && y == comida.Y()){

        puntos += 5;
        tamanio++;
        //velocidad = cambiarVelocidad();
        comida.asignaNuevasCoordenadas(rand()% (SCREEN_WIDTH-10) + 10,rand()% (SCREEN_HEIGHT-4) + 4);
        comida.pintarComida();
        dibujarPuntaje();

    }
}


//EL JUEGO SE TERMINA SI LA SERPIENTE CHOCA CONTRA LOS LIMITES DE LA PANTALLA O CONSIGO MISMA.
bool Serpiente::gameOver(){

     if (x == 8 || x == SCREEN_WIDTH - 1 || y == 3 || y == SCREEN_HEIGHT - 4) return true;

     //FALTA CUANDO CHOCA CONSIGO MISMA.
}

/*
int Serpiente::cambiarVelocidad(){

     if(puntos = controlvelocidad*5){ //CADA 50 PUNTOS CAMBIARA LA VELOCIDAD.

        velocidad += 150;
        controlvelocidad ++;
     }

     return velocidad;
}
*/

void Serpiente::dibujarPuntaje(){

     Auxiliar::gotoxy(8,1); printf("Puntos:    %d ",puntos);
}



#endif // SERPIENTE_H_INCLUDED
