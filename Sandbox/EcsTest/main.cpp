/*
-----------------------------------------------------------------------------------
Nom du fichier  : main.cpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/
#include <cstdlib>
#include <iostream>
#include <Ecs.hpp>


struct TransformComponent{
   float x;
   float y;
   float z;
};

struct Transform2Component{
   float x;
   float y;
   float z;
};

int main(){


   ECS::Scene scene;

   auto voiture1 = scene.newEntity();
   auto voiture2 = scene.newEntity();
   auto voiture3 = scene.newEntity();

   scene.assign<TransformComponent>(voiture1, { 1,2,3 });
   scene.assign<Transform2Component>(voiture1, { 1,2,3 });

   scene.assign<TransformComponent>(voiture2);

   auto t1  = scene.get<TransformComponent>(voiture1);

   std::cout << t1->x << " " << t1->y << " " << t1->z  << std::endl;

   for(ECS::EntityID id : ECS::SceneView<TransformComponent, Transform2Component>(scene)){
      std::cout << ECS::getEntityIndex(id) + 1 << std::endl;
   }

   return EXIT_SUCCESS;
}

