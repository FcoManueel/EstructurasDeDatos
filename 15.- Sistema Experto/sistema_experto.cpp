/********************************************
*                                           *
*   Nombre: Sistema "experto"               *
*   Autor:  Francisco Manuel Valle Ruiz     *
*   Fecha:  Abril 2013                      *
*                                           *
*********************************************/

#include <iostream>
#include "sistema_experto.h"
using namespace std;

int main()
{
    SistemaExperto SE;
    SE.agregar_nodo(1, "Tiene pelo?", -1);
    SE.agregar_nodo(2, "Da leche?", -1);
    SE.agregar_nodo(3, "Tiene plumas?", -1);
    SE.agregar_nodo(4, "Vuela?", -1);
    SE.agregar_nodo(5, "Pone huevos?", -1);
    SE.agregar_nodo(6, "Come carne?", -1);
    SE.agregar_nodo(7, "Tiene dientes agudos?", -1);
    SE.agregar_nodo(8, "Tiene garras?", -1);
    SE.agregar_nodo(9, "Tiene ojos que miran hacia adelante?", -1);
    SE.agregar_nodo(10, "Tiene pezunias?", -1);
    SE.agregar_nodo(11, "Rumia?", -1);
    SE.agregar_nodo(12, "Tiene color leonado?", -1);
    SE.agregar_nodo(13, "Tiene manchas obscuras?", -1);
    SE.agregar_nodo(14, "Tiene franjas negras?", -1);
    SE.agregar_nodo(15, "Tiene patas largas?", -1);
    SE.agregar_nodo(16, "Tiene cuello largo?", -1);
    SE.agregar_nodo(17, "Es de color blanco?", -1);
    SE.agregar_nodo(18, "Nada?", -1);
    SE.agregar_nodo(19, "Vuela muy bien?", -1);
    SE.agregar_nodo(20, "Es blanco y negro?", -1);

    SE.agregar_nodo(21, "Es mamifero" , 0);
    SE.agregar_nodo(22, "Es ave"      , 0);
    SE.agregar_nodo(23, "Es carnivoro", 1);
    SE.agregar_nodo(24, "Es angulado" , 1);
    SE.agregar_nodo(25, "", 1);
    SE.agregar_nodo(26, "", 1);
    SE.agregar_nodo(27, "", 1);
    SE.agregar_nodo(28, "", 1);
    SE.agregar_nodo(29, "", 1);

    SE.agregar_nodo(30, "Es una onza"    , 1);
    SE.agregar_nodo(31, "Es un tigre"    , 1);
    SE.agregar_nodo(32, "Es una jirafa"  , 1);
    SE.agregar_nodo(33, "Es una cebra"   , 1);
    SE.agregar_nodo(34, "Es una avestruz", 1);
    SE.agregar_nodo(35, "Es un pinguino" , 1);
    SE.agregar_nodo(36, "Es un albatros" , 1);

    SE.agregar_arco(1  ,21, 1);
    SE.agregar_arco(2  ,21, 1);
    SE.agregar_arco(3  ,22, 1);
    SE.agregar_arco(3  ,25, 1);
    SE.agregar_arco(4  ,28, 1);
    SE.agregar_arco(4  ,22, 1);
    SE.agregar_arco(4  ,25, 1);
    SE.agregar_arco(4  ,29, 1);
    SE.agregar_arco(4  ,34, 0);
    SE.agregar_arco(4  ,35, 0);
    SE.agregar_arco(5  ,34, 1);
    SE.agregar_arco(5  ,35, 1);
    SE.agregar_arco(5  ,36, 1);
    SE.agregar_arco(6  ,26, 1);
    SE.agregar_arco(7  ,27, 1);
    SE.agregar_arco(8  ,27, 1);
    SE.agregar_arco(9  ,27, 1);
    SE.agregar_arco(10 ,32, 1);
    SE.agregar_arco(10 ,33, 1);
    SE.agregar_arco(11 ,29, 1);
    SE.agregar_arco(12 ,30, 1);
    SE.agregar_arco(12 ,31, 1);
    SE.agregar_arco(12 ,32, 1);
    SE.agregar_arco(13 ,30, 1);
    SE.agregar_arco(13 ,32, 1);
    SE.agregar_arco(14 ,31, 1);
    SE.agregar_arco(14 ,33, 1);
    SE.agregar_arco(15 ,32, 1);
    SE.agregar_arco(15 ,34, 1);
    SE.agregar_arco(16 ,34, 1);
    SE.agregar_arco(16 ,32, 1);
    SE.agregar_arco(17 ,33, 1);
    SE.agregar_arco(18 ,35, 1);
    SE.agregar_arco(19 ,36, 1);
    SE.agregar_arco(20 ,34, 1);
    SE.agregar_arco(20 ,35, 1);

    SE.agregar_arco(21, 27, 1);
    SE.agregar_arco(21, 28, 1);
    SE.agregar_arco(21, 29, 1);
    SE.agregar_arco(21, 26, 1);
    SE.agregar_arco(22, 34, 1);
    SE.agregar_arco(22, 35, 1);
    SE.agregar_arco(22, 27, 1);
    SE.agregar_arco(22, 36, 1);
    SE.agregar_arco(23, 30, 1);
    SE.agregar_arco(23, 31, 1);
    SE.agregar_arco(24, 32, 1);
    SE.agregar_arco(24, 33, 1);
    SE.agregar_arco(25, 22, 1);
    SE.agregar_arco(26, 23, 1);
    SE.agregar_arco(27, 23, 1);
    SE.agregar_arco(28, 24, 1);
    SE.agregar_arco(29, 24, 1);

    SE.comenzar();

    cin.ignore();
    cin.get();
}
