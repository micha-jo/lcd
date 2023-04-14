#include "class.h"
#include "char.h"



Parametre mesParametres; 
Position mesPositions; 
Hero monHero(&mesPositions); 

void setup()
{
  mesParametres.initialisation(hero,mechant,obstacle,key,door,life,trap,arrow); 
  mesPositions.generatePosition(1,5,10,1,1,1,1,1,1,1,1,1); 
  mesPositions.setSize(25,10);
  mesPositions.typeZelda(); 
}
void loop()
{
  mesPositions.manualShift();
  
  monHero.move();
  Serial.print(mesPositions.ary[0][0][0]); 
  Serial.print("-"); 
  Serial.println(mesPositions.ary[0][0][1]); 
} 



