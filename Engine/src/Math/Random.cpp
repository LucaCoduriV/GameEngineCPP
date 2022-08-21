/*
-----------------------------------------------------------------------------------
Nom du fichier  : Random.cpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Math/Random.hpp"

namespace GE{
   std::default_random_engine Random::engine;

   double Random::genDouble(double begin, double end) {
      std::uniform_real_distribution<double> dist(begin, end);
      return dist(engine);
   }

//   int Random::genInt(int begin, int end) {
//      std::uniform_int_distribution<int> dist(begin, end);
//      return dist(engine);
//   }
//
//   unsigned int Random::genUnsignedInt(unsigned int begin, unsigned int end) {
//      std::uniform_int_distribution<unsigned int> dist(begin, end);
//      return dist(engine);
//   }
}


