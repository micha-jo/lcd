#include "class.h"
#include "char.h"



Parametre mesParametres; 
Position mesPositions; 
Hero monHero(&mesPositions); 

void setup()
{
  mesParametres.initialisation(hero,mechant,obstacle,key,door,life,trap,arrow); 
  mesPositions.generatePosition(1,1,1,1,1,1,1,1,1,1,1,1); 
  mesPositions.setSize(25,5);
  mesPositions.typeZelda(); 
}
void loop()
{
  delay(1000);
  mesPositions.shiftToLeft();
  
  monHero.move();
  
} 



