#pragma once


#include <iostream>
#include <string>
#include <fstream>    //forse non serve
#include "Fratture.hpp"

using namespace std;

namespace LibreriaFratture {

bool ImportaCoordinate(const string &filename, FrattureMesh& mesh );

bool EquazioneDelPiano(FrattureMesh& mesh);

}
