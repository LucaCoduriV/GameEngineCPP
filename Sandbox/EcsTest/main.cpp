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

//int ECS::s_componentCounter = 0;

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

   scene.assign<TransformComponent>(voiture1);
   scene.assign<TransformComponent>(voiture2);

   auto t1  = scene.get<TransformComponent>(voiture1);
   t1->x = 10;
   t1->y = 30;
   t1->z = 50;
   auto t2  = scene.get<TransformComponent>(voiture2);
   t2->x = 5;
   t2->y = 3;
   t2->z = 2;

   std::cout << t1->x << " " << t1->y << " " << t1->z << std::endl;
   std::cout << t2->x << " " << t2->y << " " << t2->z << std::endl;

   auto t3 = scene.get<TransformComponent>(voiture1);
   auto t4 = scene.get<TransformComponent>(voiture2);

   std::cout << t3->x << " " << t3->y << " " << t3->z << std::endl;
   std::cout << t4->x << " " << t4->y << " " << t4->z << std::endl;

   return EXIT_SUCCESS;
}

