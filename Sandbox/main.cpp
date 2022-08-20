#include "../Engine/header/App.hpp"
#include "modelLoader/ModelLoaderLayer.hpp"

int main(){
   auto* app = new App();
   ModelLoaderLayer layer;
   app->pushLayer((Layer*)&layer);
   app->run();
   delete app;
}