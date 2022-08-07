#include <iostream>
#include <cstdlib>
#include "GameEngine.hpp"


int main() {

   GE::SWindowCreateInfo windowInfos = {};
   windowInfos.windowTitle = "GameEngine";
   windowInfos.windowHeight = 720;
   windowInfos.windowWidth = 1280;

   GE::SRendererCreateInfo rendererInfos = {};
   rendererInfos.windowCreateInfo = &windowInfos;
   rendererInfos.rendererType = GE::ERendererType::Opengl33;

   GE::SRenderingEngineCreateInfo renderingEngineInfos = {};
   renderingEngineInfos.renderingEnginyType =
      GE::ERenderingEnginyType::Rasterization;
   renderingEngineInfos.pRendererCreateInfo = &rendererInfos;

   GE::SGameEngineCreateInfo gameEngineInfos = {};
   gameEngineInfos.pRenderingEngineCreateInfo = &renderingEngineInfos;

   GE::GameEngine ge;

   try {
      ge.Initialize(gameEngineInfos);
      ge.run();

   } catch (const std::runtime_error &error) {
      std::cerr << "Exception: " << error.what() << std::endl;
      return EXIT_FAILURE;
   } catch (const std::bad_alloc &error) {
      std::cerr << "Exception: " << error.what() << std::endl;
      return EXIT_FAILURE;
   }


   return EXIT_SUCCESS;
}
