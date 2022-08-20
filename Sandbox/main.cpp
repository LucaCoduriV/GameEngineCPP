#include <ModelLoaderLayer.hpp>
#include "../Engine/header/App.hpp"

int main(){
   auto* app = new App();
   ModelLoaderLayer layer;
   app->pushLayer((Layer*)&layer);
   app->run();
   delete app;
}