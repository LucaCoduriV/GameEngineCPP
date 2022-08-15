#include <App.hpp>
#include <main/TestLayer.hpp>

int main(){
   auto* app = new App();
   TestLayer layer;
   app->pushLayer((Layer*)&layer);
   app->run();
   delete app;
}