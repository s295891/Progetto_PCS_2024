#pragma once

#include <map>
#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

namespace LibreriaFratture{


// voglio costruire una struttura che includa sia il numero di fratture presenti sia una mappa che ad una chiave associ uan matrice
struct FrattureMesh
{
    unsigned int NumeroFratture = 0;
    map < unsigned int, MatrixXd > CoordinateFratture ={};

    map < unsigned int, VectorXd, double > EquazionePiano = {};


};

}
