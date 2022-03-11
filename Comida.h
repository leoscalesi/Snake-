#ifndef COMIDA_H_INCLUDED
#define COMIDA_H_INCLUDED



class Comida{

    int x,y;

public:

    Comida(int _x,int _y);
    int X(){return x;}
    int Y(){return y;}
    void pintarComida();
    void asignaNuevasCoordenadas(int,int);

};


Comida::Comida(int _x,int _y):x(_x),y(_y){}


void Comida::pintarComida(){

   Auxiliar::gotoxy(x,y); printf("%c",4); //DIBUJA UN ROMBO.

}


void Comida::asignaNuevasCoordenadas(int _x,int _y){

       x = _x;
       y = _y;
}

#endif // COMIDA_H_INCLUDED
