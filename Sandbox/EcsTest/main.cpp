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

   scene.assign<TransformComponent>(voiture1);

   scene.assign<Transform2Component>(voiture2);

   scene.assign<TransformComponent>(voiture3);
   scene.assign<Transform2Component>(voiture3);

   auto t1  = scene.get<TransformComponent>(voiture1);
   t1->x = 10;
   t1->y = 30;
   t1->z = 50;
   auto t2  = scene.get<Transform2Component>(voiture2);
   t2->x = 5;
   t2->y = 3;
   t2->z = 2;

   auto t3  = scene.get<Transform2Component>(voiture3);
   t3->x = 5;
   t3->y = 3;
   t3->z = 2;

   auto t4  = scene.get<TransformComponent>(voiture3);
   t4->x = 5;
   t4->y = 3;
   t4->z = 2;

   for(ECS::EntityID id : ECS::SceneView<TransformComponent>(scene)){
      std::cout << ECS::getEntityIndex(id) + 1 << std::endl;
   }

   return EXIT_SUCCESS;
}

