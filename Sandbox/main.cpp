#include "LightLayer.hpp"
#include "../Engine/header/App.hpp"

int main(){
   auto* app = new App();
   LightTestLayer layer;
   app->pushLayer((Layer*)&layer);
   app->run();
   delete app;
}