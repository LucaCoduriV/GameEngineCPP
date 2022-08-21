/*
-----------------------------------------------------------------------------------
Nom du fichier  : Random.hpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_RANDOM_HPP
#define SANDBOX_RANDOM_HPP

#include <random>

namespace GE{
   class Random {
   public:
      static double genDouble(double begin, double end);
//      static int genInt(int begin, int end);
//      static unsigned int genUnsignedInt(unsigned int begin, unsigned int end);
   private:
      static std::default_random_engine engine;
   };


}




#endif //SANDBOX_RANDOM_HPP
