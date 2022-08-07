/*
-----------------------------------------------------------------------------------
Nom du fichier  : RasterizationEngine.hpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_RASTERIZATIONENGINE_HPP
#define GAMEENGINE_RASTERIZATIONENGINE_HPP

#include <Rendering/IRenderingEngine.hpp>

namespace GE{
   class RasterizationEngine : public IRenderingEngine {
   public:
      ~RasterizationEngine() override;

      void initialize(const SRenderingEngineCreateInfo &renderingEngineCreateInfo) final;
      void release() final;
      void render(float lag) final;
   };
}




#endif //GAMEENGINE_RASTERIZATIONENGINE_HPP
