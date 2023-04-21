#include "class.h"
#include "char.h"



Parametre mesParametres; 
Position mesPositions; 
Hero monHero(&mesPositions); 
Mechant monMechant(&mesPositions); 
SecondaryScreen monEcranSecondaire(&monHero); 
void setup()
{
  mesParametres.initialisation(hero,mechant,obstacle,key,door,life,trap,arrow); 
  mesPositions.generatePosition(1,3,2,2,1,1,1,1,1,1,1,1); 
  mesPositions.setSize(25,10);
  mesPositions.typeZelda(); 
  monMechant.createMechant(); 

}
void loop()
{
  mesPositions.manualShiftBorder();
  
  monHero.move();
  monHero.pullWithRequest(1); 
  monHero.interaction(); 
  monMechant.circle();
  //monMechant.allMechants(&Mechant::goRandom);
  monEcranSecondaire.displaySecondaryScreen(2);
  delay(500);
  
  //monHero.jumpWithRequest(1);
  // Serial.print(mesPositions.ary[6][0][0]); 
  // Serial.print("-"); 
  // Serial.print(mesPositions.ary[6][0][1]); 
  // Serial.print(" "); 
  // Serial.print(mesPositions.ary[7][0][0]); 
  // Serial.print("-"); 
  // Serial.println(mesPositions.ary[7][0][1]); 
} 



