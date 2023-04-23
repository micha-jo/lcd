#include "class.h"
#include "char.h"



Parametre mesParametres; 
Position mesPositions; 
Hero monHero(&mesPositions); 
Mechant monMechant(&mesPositions); 
Bullet mesBullet(&mesPositions);
Shot mesTire(&mesPositions, &monHero, &monMechant); 
SecondaryScreen monEcranSecondaire(&monHero); 
void setup()
{
  mesParametres.initialisation(hero,mechant,obstacle,key,door,life,trap,arrow); 
  mesPositions.generatePosition(1,2,0,0,0,0,0,0,0,0,0,0); 
  mesPositions.setSize(25,3);
  mesPositions.typeZelda(); 
  monMechant.createMechant(); 

}
void loop()
{
  mesPositions.manualShiftBorder();
  
  monHero.move();
  monHero.pullWithRequest(1); 
  monHero.interaction(); 
  //monMechant.chassing();
  monMechant.concequencies();
  //monMechant.pullBack(); 
  monMechant.allMechants(&Mechant::chassing);
  monEcranSecondaire.displaySecondaryScreen(2);
  mesTire.heroShot();
  mesTire.mechantShot(); 
  //mesTire.onlyMechantShot();
  
  //monHero.jumpWithRequest(1);
  // Serial.print(mesPositions.ary[6][0][0]); 
  // Serial.print("-"); 
  // Serial.print(mesPositions.ary[6][0][1]); 
  // Serial.print(" "); 
  // Serial.print(mesPositions.ary[7][0][0]); 
  // Serial.print("-"); 
  // Serial.println(mesPositions.ary[7][0][1]); 
  delay(10);
} 


