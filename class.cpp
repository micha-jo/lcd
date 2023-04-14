#include <arduino.h>
#include <LiquidCrystal_I2C.h>

#include "class.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);
int highLimite = 1000; 
int lowLimite = 23; 
int sizeScreenOnX = 16 ; 
int sizeScreenOnY = 3 ;


/*************************Parametre****************************************/
//configuration of the differente equipements: screen and joystick
Parametre::Parametre(){
  highLimite = 1000; 
  lowLimite = 23; 
  sizeScreenOnX = 16; 
  sizeScreenOnY = 3;
  horizontale = A1; 
  verticale= A0; 
  bouton = 2; 
}
Parametre::Parametre(int highLimite, int lowLimite, int sizeScreenOnX, int sizeScreenOny, int horizontale, int verticale, int bouton){
  highLimite = highLimite; 
  lowLimite = lowLimite; 
  sizeScreenOnX = sizeScreenOnX; 
  sizeScreenOny = sizeScreenOny;
  horizontale = horizontale; 
  verticale= verticale; 
  bouton = bouton; 
}

// initialisation of the programme 
// CETTE METHODE DOIT ETRE OBLIGATOIREMENT PRESENTE DANS LE SETUP
void Parametre::initialisation(uint8_t *hero, uint8_t *mechant, uint8_t *obstacle, uint8_t *key, uint8_t *door, uint8_t *life,uint8_t *trap, uint8_t *arrow)
{
  Serial.begin(115200);

  pinMode(bouton, INPUT_PULLUP);  
  
  lcd.init();
  lcd.backlight();
  lcd.clear(); 
  lcd.createChar(0, hero);
  lcd.createChar(1, mechant);
  lcd.createChar(2, obstacle);
  lcd.createChar(3, key);
  lcd.createChar(4, door);
  lcd.createChar(5, life);
  lcd.createChar(6, trap);
  lcd.createChar(7, arrow);

  timeCpt = millis(); 
  timeCpt2 = millis(); 
  timeCpt3 = millis(); 
  timeCpt4 = millis(); 
}

void Parametre::display(int id, int x, int y){
  lcd.setCursor(x,y);
  if(id == 8){
    lcd.print("="); 
  }else if(id == 9){
    lcd.print("-"); 
  }else if(id == 10){
    lcd.print("o"); 
  }else if(id == 11){
    lcd.print("*"); 
  }else if(id == 12){
    lcd.print(")");
  }else if(id == 13){
  lcd.print("L");
  }else if(id == 14){
  lcd.print(" ");
  }else if(id == 20){
  lcd.print("$");
  }else {
    lcd.write(id); 
  }
}
void Parametre::notDisplay(int x, int y){
  lcd.setCursor(x,y);
  lcd.print(" ");
} 


/********************************Position************************************/
Position::Position(){
  sizeX = sizeScreenOnX; 
  sizeY = sizeScreenOnY; 

  runningSpeed= 1000; 
  sizeXCpt = 0; 
  sizeYCpt = 0; 
}
/*
*Setter 
*/
void Position::setSize(int x, int y){
  sizeX = x; 
  sizeY = y;
}
void Position::setRunningSpeed(int runningSpeed){
  runningSpeed = runningSpeed; 
}

//créé le tableau contenant la position de l'ensemble des caractères
void Position::generatePosition(int numberOfHero, int numberOfmechant ,int numberOfObstacle, int numberOfKey, int numberOfDoor, int numberOfLife, int numberOfTrap, int numberOfArrow, int numberOfEqual, int numberOfMinus, int numberOfO, int numberOfStar){
  _numberOfEatchCaractere[0] = 1;
  _numberOfEatchCaractere[1] = numberOfmechant;
  _numberOfEatchCaractere[2] = numberOfObstacle;
  _numberOfEatchCaractere[3] = numberOfKey;
  _numberOfEatchCaractere[4] = numberOfDoor;
  _numberOfEatchCaractere[5] = numberOfLife;
  _numberOfEatchCaractere[6] = numberOfTrap;
  _numberOfEatchCaractere[7] = numberOfArrow;
  _numberOfEatchCaractere[8] = numberOfEqual;
  _numberOfEatchCaractere[9] = numberOfMinus;
  _numberOfEatchCaractere[10] = numberOfO;
  _numberOfEatchCaractere[11] = numberOfStar;

  ary = new int **[12]; 
  for(int i = 0; i < 12; i++){
    ary[i] = new int *[_numberOfEatchCaractere[i]]; 
    for (int j = 0 ; j< _numberOfEatchCaractere[i]; j++){
      ary[i][j] = new int [3];
    }
  }
}

void Position::deletePosition(){
  for(int i =0; i<_numberOfEatchCaractere[i]; i++){
    for (int j = 0 ; j< _numberOfEatchCaractere[i]; j++){
      delete [] ary[i][j];
    }
    delete [] ary[i];
  }
  delete [] ary;
}


/*
*Type of display 
*/
void Position::typeZelda(){
  lcd.clear(); 
  int starCounter; 
  for (int i = 0 ; i < 12 ; i++){
    for (int j =0 ; j < _numberOfEatchCaractere[i]; j++ ){
      
      if (i == 0){
        ary[i][j][0] = 0 ;
        ary[i][j][1] = random(0,4) ;
        ary[i][j][2] = 1;
        if (ary[i][j][0]>=0 && ary[i][j][0]<= sizeScreenOnX && ary[i][j][1]>=0 && ary[i][j][1]<= sizeScreenOnY){
          display(i, ary[i][j][0], ary[i][j][1]);
        }
      }
      else if (i == 4){
        ary[i][j][0] = sizeX ;
        ary[i][j][1] = random(0,sizeY) ;
        ary[i][j][2] = 1;
        if (ary[i][j][0]>=0 && ary[i][j][0]<= sizeScreenOnX &&ary[i][j][1]>=0 && ary[i][j][1]<= sizeScreenOnY){
          display(i, ary[i][j][0], ary[i][j][1]);
        }

      }else  {
        int y, x; 
        do{
          x = random(2,sizeX) ;
          y = random(0,sizeY) ;
        }while (!compareAll(x, y ));
        ary[i][j][0] = x ;
        ary[i][j][1] = y ;
        ary[i][j][2] = 1;
        if (ary[i][j][0]>=0 && ary[i][j][0]<= sizeScreenOnX &&ary[i][j][1]>=0 &&ary[i][j][1]<= sizeScreenOnY){
          display(i, ary[i][j][0], ary[i][j][1]);
        }
      }
    }
  }
}

bool Position::compareAll(int x, int y){
  for (int i = 0; i < 12; i++){
    for (int j = 0; j< _numberOfEatchCaractere[i]; j++){
      if (ary[i][j][0] == x && ary[i][j][1] == y){
        return false; 
      }
      else {
        return true; 
      }
    }
  }
}




/*
*Mode of Display
*/
void Position::shiftToLeft(){ 
  if (sizeXCpt + sizeScreenOnX <sizeX){
    if (millis () > timeCpt + runningSpeed){
      sizeXCpt ++;
      for(int i = 0; i < 12; i++){
        for (int j = 0 ; j< _numberOfEatchCaractere[i]; j++){
          if (i==0){
            ary[i][j][0] ++;
          }else if (i ==1 ){
            ary[i][j][0] ++;
          }else{
            display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt );
            notDisplay(ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
          }
        }
      }
      timeCpt = millis();
    }
  }
}
void Position::shiftToRight(){ 
  if (sizeXCpt > 0){
    if (millis () > timeCpt + runningSpeed){
      sizeXCpt --;
      for(int i = 0; i < 12; i++){
        for (int j = 0 ; j< _numberOfEatchCaractere[i]; j++){
          if (i==0){
            ary[i][j][0] --;
          }else if (i ==1 ){
            ary[i][j][0] --;
          }else{
            display(i, ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
            notDisplay(ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt);
          }
        }
      }
      timeCpt = millis();
    }
  }
}
void Position::shiftToTop(){ 
  if (sizeYCpt + sizeScreenOnY <sizeY){
    if (millis () > timeCpt + runningSpeed){
      sizeYCpt ++;
      Serial.println (sizeYCpt);
      for(int i = 0; i < 12; i++){
        for (int j = 0 ; j< _numberOfEatchCaractere[i]; j++){
          if (i==0){
            ary[i][j][1] ++;
          }else if (i ==1 ){
            ary[i][j][1] ++;
          }else{
            display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt-1);
            notDisplay(ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt);
          }
        }
      }
      timeCpt = millis();
    }
  }
}
void Position::shiftToBottom(){ 
  if (sizeYCpt > 0){
    if (millis () > timeCpt + runningSpeed){
      sizeYCpt --;
      for(int i = 0; i < 12; i++){
        for (int j = 0 ; j< _numberOfEatchCaractere[i]; j++){
          if (i==0){
            ary[i][j][1] --;
          }else if (i ==1 ){
            ary[i][j][1] --;
          }else{
            display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt+1);
            notDisplay(ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt);
          }
        }
      }
      timeCpt = millis();
    }
  }
}
void Position::manualShift(){
  // if (ary[0][0][0]-sizeXCpt>1){
  //   shiftToLeft(); 
  // }
  // if (ary[0][0][0]-sizeXCpt<1){
  //   shiftToRight(); 
  // }
  if (ary[0][0][1]-sizeYCpt>2){
      shiftToTop(); 
    }
  // if (ary[0][0][1]-sizeYCpt<2){
  //   shiftToBottom(); 
  // }
}












/****************************Hero**********************************/
Hero::Hero(Position *position) {
  this->position = position; 
  id = 0; 
  number = 0; 
  heroSpeedOnX = 400; 
  heroSpeedOnY = 400;

  //initialisation des variables pour les  appuis long
  _buttonPressed = false; 
  _pressStart = 0; 
  
}

/*
*Setters 
*/
void Hero::setHeroSpeed(int speendOnX, int speedOnY){
  heroSpeedOnX = speendOnX; 
  heroSpeedOnY = speedOnY;
}

//ensemble de booléen qui renvoie true si la commande est réalisé
bool Hero::boutonLeft(){
  if (analogRead(horizontale) > highLimite ){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::boutonRight(){
  if (analogRead(horizontale) <lowLimite ){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::boutonTop(){
  if (analogRead(verticale) <lowLimite ){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::boutonBottom(){
  if (analogRead(verticale) >highLimite){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::boutonShortPress(){
  if (digitalRead(bouton) == LOW ){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::specialMoveLeft(){
  if (analogRead(horizontale) > highLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::specialMoveRight(){
  if (analogRead(horizontale) <lowLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::specialMoveTop(){
  if (analogRead(verticale) <lowLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::specialMoveBottom(){
  if (analogRead(verticale) > highLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Hero::boutonLongPress(){
  if (digitalRead(bouton) == LOW && !_buttonPressed){
    _buttonPressed = true;
    _pressStart = millis(); 
  }else if (digitalRead(bouton) == HIGH ) {
    _pressStart = 0; 
    _buttonPressed = false;
    return false; 
  }
  if (digitalRead(bouton) == LOW && _buttonPressed && millis() - _pressStart >= 500) {
    // Un appui long a été détecté
    _pressStart = 0; 
    return true;
    
  }
}

//
void Hero::goLeft(){
  if (boutonLeft()){
    if (1==1/*noObstacleRight(2)*/){
      display(this->id, position->ary[this->id][this->number][0]-1-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][0] --;
      timeCpt = millis();  
    }
  }
}
void Hero::goRight(){
  if (boutonRight()){
    if (1==1/*noObstacleRight(2)*/){
      display(this->id, position->ary[this->id][this->number][0]+1-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][0] ++;
      timeCpt = millis();  
    }
  }
}
void Hero::goTop(){
  if (boutonTop()){
    if (1==1/*noObstacleRight(2)*/){
      display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt-1);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][1] --;
      timeCpt = millis();  
    }
  }
}
void Hero::goBottom(){
  if (boutonBottom()){
    if (1==1/*noObstacleRight(2)*/){
      display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]+1-position->sizeYCpt);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][1] ++;
      timeCpt = millis();  
    }
  }
}

void Hero::move(){
  if (millis()> timeCpt + heroSpeedOnX){
    goRight();
    goLeft(); 
  }
  
  if (millis()> timeCpt + heroSpeedOnY){
   goBottom();
   goTop(); 
  }
}



/******************************Menu********************************/







