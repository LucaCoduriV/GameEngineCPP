/*
-----------------------------------------------------------------------------------
Nom du fichier  : GameEngine.hpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_GAMEENGINE_HPP
#define GAMEENGINE_GAMEENGINE_HPP

#include "Rendering/IRenderingEngine.hpp"

namespace GE{

   struct SGameEngineCreateInfo{
      SRenderingEngineCreateInfo* pRenderingEngineCreateInfo;
   };

   class GameEngine {
   public:
      ~GameEngine();
      void Initialize(const SGameEngineCreateInfo& createInfo);
      void release();
      void run();

   private:
      bool isInitialized = false;
      IRenderingEngine* pRenderingEngine = nullptr;
   };
}




#endif //GAMEENGINE_GAMEENGINE_HPP
