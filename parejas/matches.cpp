//Saúl Enrique Labra Cruz A01020725
//Técnica: Backtracking
//Complejidad: O(n^2)

#include <iostream>
#include <string>
#include <vector>
#include <string>
/*
 LAS PAREJAS ESTABLES

Supongamos que tenemos n hombres y n mujeres y dos matrices M y H que contienen las preferencias de los unos
 por los otros. Más concretamente, la fila M[i,·] es una ordenación (de mayor a menor) de las mujeres según
 las preferencias del i-ésimo hombre y, análogamente, la fila H[i,·] es una ordenación (de mayor a menor) de
 los hombres según las preferencias de la i-ésima mujer.

Diseñe un algoritmo que encuentre, si es que existe, un emparejamiento de hombres y mujeres tal que todas las
parejas formadas sean estables. Una pareja (h,m) es estable si no se da ninguna de estas dos circunstancias:

Existe una mujer m’ (que forma la pareja (h’,m’)) tal que el hombre h la prefiere sobre la mujer m y además
 la mujer m’ también prefiere a h sobre h’.
Existe un hombre h” (que forma la pareja (h”,m”)) tal que la mujer m lo prefiere sobre el hombre h y además el
hombre h” también prefiere a m sobre la mujer m”.

Complejidad: O(n^2) porque se recorre la matriz para actualizar la pareja de cada hombre y mujer n veces.
Técnica: Backtracking

*/

#include <iostream>
#include <vector>

/*

 Complejidad: O(n^2) porque se recorre la matriz para actualizar la pareja de cada hombre y mujer n veces.
 Técnica: Backtracking
*/

bool checaMejorHombre(std::vector<std::vector<int>> pref, int hombre, int mujer, int hombre1, int n);

void asignarParejas(std::vector<std::vector<int>> pref, int columnas);

int main() {

  //tam de columnas y columnas de las matrices de hombres y mujeres
  int columnas = 4;

  //matriz de preferencias de hombres y mujeres
  std::vector<std::vector<int>> pref(2 * columnas, std::vector<int>(columnas));

  //se llena la matriz con las preferencias
  pref =
  {
    //hombres
    { 4, 5, 6, 7 }, //hombre 0
    { 5, 6, 7, 4 }, //hombre 1
    { 7, 6, 4, 5 }, //hombre 2
    { 5, 4, 7, 6 }, //hombre 3

    //mujeres
    { 0, 1, 2, 3 }, //mujer 4
    { 1, 3, 2, 0 }, //mujer 5
    { 2, 1, 0, 3 }, //mujer 6
    { 3, 2, 1, 0 }, //mujer 7

  };

  asignarParejas(pref, columnas);

}//cierre del main


void asignarParejas(std::vector<std::vector<int>> pref, int columnas) {

  std::vector<int> parejaMujeres;
  std::vector<bool> asignadosH;

  //se ponen a todas las mujeres y hombres disponibles
  for (int i = 0; i < columnas; i++) {

    parejaMujeres.push_back(-1);
    asignadosH.push_back(false);

  }//cierre del for

  int solteros = columnas;

  while (solteros > 0) {

    int hombre;

    for (int i = 0; i < columnas; i++) {

      if (asignadosH[i] == false) {
        hombre = i;
        i = columnas;
      }//cierre del if

    }//cierre del for

    for (int i = 0; (i < columnas) && (asignadosH[hombre] == false); i++) {

      int mujer = pref[hombre][i];

      if (parejaMujeres[mujer - columnas] == -1) {
        parejaMujeres[mujer - columnas] = hombre;
        asignadosH[hombre] = true;
        solteros--;
      }

      else {

        int otroHombre = parejaMujeres[mujer - columnas];

        if (checaMejorHombre(pref, hombre, mujer, otroHombre, columnas) == false) {
          parejaMujeres[mujer - columnas] = hombre;
          asignadosH[hombre] = true;
          asignadosH[otroHombre] = false;
        }

      }//cierre del else

    }//cierre del for

  }//cierre del while

  for (int i = 0; i < columnas; i++) {
    std::cout << "La mujer no." << i + columnas << " fue asignada al hombre no." << parejaMujeres[i] << std::endl;
  }

}//cierre de asignarParejas


bool checaMejorHombre(std::vector<std::vector<int>> pref, int hombre, int mujer, int otroHombre, int columnas) {

  for (int i = 0; i < columnas; i++) {

    if (pref[mujer][i] == otroHombre) {
      return true;
    }
    if (pref[mujer][i] == hombre) {
      return false;
    }

  }//cierre del for

  return false;

}//cierre de checaMejorHombre
