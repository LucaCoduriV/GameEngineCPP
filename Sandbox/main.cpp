#include "TestLayer.hpp"
#include "../Engine/header/App.hpp"

int main(){
   auto* app = new App();
   TestLayer layer;
   app->pushLayer((Layer*)&layer);
   app->run();
   delete app;
}