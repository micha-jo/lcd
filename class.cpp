#include <arduino.h>
#include <LiquidCrystal_I2C.h>

#include "class.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);

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

  //initialisation des variables pour les  bouton 
  //appui unique 
  _stateButton = false;
  //appui long 
  _buttonPressed = false; 
  _pressStart = 0; 
}
Parametre::Parametre(int highLimite, int lowLimite, int sizeScreenOnX, int sizeScreenOny, int horizontale, int verticale, int bouton){
  highLimite = highLimite; 
  lowLimite = lowLimite; 
  sizeScreenOnX = sizeScreenOnX; 
  sizeScreenOny = sizeScreenOny;
  horizontale = horizontale; 
  verticale= verticale; 
  bouton = bouton; 

  //initialisation des variables pour les  bouton 
  //appui unique 
  _stateButton = false;
  //appui long 
  _buttonPressed = false; 
  _pressStart = 0; 
}

// INITILISATION OF THE PROGRAMME 
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
  timeCpt1 = millis(); 
  timeCpt2 = millis(); 
  timeCpt3 = millis(); 
  timeCpt4 = millis(); 
}
//END INITILISATION OF THE PROGRAMME 

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

//SETUP REQUEST: ensemble de booléen qui renvoie true si la commande est réalisé
bool Parametre::boutonLeft(){
  if (analogRead(horizontale) > highLimite ){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::boutonRight(){
  if (analogRead(horizontale) <lowLimite ){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::boutonTop(){
  if (analogRead(verticale) <lowLimite ){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::boutonBottom(){
  if (analogRead(verticale) >highLimite){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::boutonMonostable(){
  if (digitalRead(bouton) == LOW){
    if (!_stateButton){
      _stateButton = true; 
      return true ;
    }
  }else {
    if (_stateButton){
      _stateButton = false; 
    }
    return false ;
  }
}
bool Parametre::boutonShortPress(){
  if (digitalRead(bouton) == LOW ){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::specialMoveLeft(){
  if (analogRead(horizontale) > highLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::specialMoveRight(){
  if (analogRead(horizontale) <lowLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::specialMoveTop(){
  if (analogRead(verticale) <lowLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::specialMoveBottom(){
  if (analogRead(verticale) > highLimite && digitalRead(bouton) == LOW){
    return true ;
  }else {
    return false ;
  }
}
bool Parametre::boutonLongPress(){
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
//END SETUP REQUEST



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
  numberOfEatchCaractere[0] = 1;
  numberOfEatchCaractere[1] = numberOfmechant;
  numberOfEatchCaractere[2] = numberOfObstacle;
  numberOfEatchCaractere[3] = numberOfKey;
  numberOfEatchCaractere[4] = numberOfDoor;
  numberOfEatchCaractere[5] = numberOfLife;
  numberOfEatchCaractere[6] = numberOfTrap;
  numberOfEatchCaractere[7] = numberOfArrow;
  numberOfEatchCaractere[8] = numberOfEqual;
  numberOfEatchCaractere[9] = numberOfMinus;
  numberOfEatchCaractere[10] = numberOfO;
  numberOfEatchCaractere[11] = numberOfStar;

  ary = new int **[12]; 
  for(int i = 0; i < 12; i++){
    ary[i] = new int *[numberOfEatchCaractere[i]]; 
    for (int j = 0 ; j< numberOfEatchCaractere[i]; j++){
      ary[i][j] = new int [3];
    }
  }
}

void Position::deletePosition(){
  for(int i =0; i< numberOfEatchCaractere[i]; i++){
    for (int j = 0 ; j< numberOfEatchCaractere[i]; j++){
      delete [] ary[i][j];
    }
    delete [] ary[i];
  }
  delete [] ary;
}

/*
*TYPE OF DISPLAY: le type de jeu 
*/
void Position::typeZelda(){
  lcd.clear(); 
  int starCounter; 
  for (int i = 0 ; i < 12 ; i++){
    for (int j =0 ; j < numberOfEatchCaractere[i]; j++ ){
      
      if (i == 0){
        ary[i][j][0] = 0 ;
        ary[i][j][1] = random(0,4) ;
        ary[i][j][2] = 1;
        if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt && ary[i][j][1]>=sizeYCpt && ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
          display(i, ary[i][j][0], ary[i][j][1]);
        }
      }
      else if (i == 4){
        ary[i][j][0] = sizeX ;
        ary[i][j][1] = random(0,sizeY) ;
        ary[i][j][2] = 1;
        if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt &&ary[i][j][1]>=sizeYCpt && ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
          display(i, ary[i][j][0], ary[i][j][1]);
        }

      }else  {
        int y, x; 
        do{
          x = random(2,sizeX-1) ;
          y = random(0,sizeY) ;
          
        }while (!compareAll(x, y));
         
        ary[i][j][0] = x ;
        ary[i][j][1] = y ;
        ary[i][j][2] = 1;
        if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt &&ary[i][j][1]>=sizeYCpt &&ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
          display(i, ary[i][j][0], ary[i][j][1]);
        }
      }
    }
  }
}

//compare la position d'un aux  parametre x et y à l'ensemble du tableau ary
bool Position::compareAll(int x, int y){
  for (int i = 0; i < 12; i++){
    for (int j = 0; j< numberOfEatchCaractere[i]; j++){
      if (ary[i][j][0] == x && ary[i][j][1] == y ){
        return false; 
      }
    }
  }
  return true; 
}

/*
*MODE OF DISPLAY: gére le deffilement de l'écran
*/
void Position::shiftToLeft(){ 
  if (sizeXCpt + sizeScreenOnX <sizeX){
    if (millis () > timeCpt + runningSpeed){
      sizeXCpt ++;
      for(int i = 0; i < 12; i++){
        for (int j = 0 ; j< numberOfEatchCaractere[i]; j++){
          if (i==0){
            if (noCharacterRight(i,j,2)){
              ary[i][j][0] ++;
            }
          }else if (i ==1 ){
            for (int k = 1; k<14; k++){
              if (noCharacterRight(i,j,k))
                ary[i][j][0] ++;
            }
          }else{
            if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt &&ary[i][j][1]>=sizeYCpt && ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
              display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt );
              notDisplay(ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
            }
            else {
              notDisplay(ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
            }
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
        for (int j = 0 ; j< numberOfEatchCaractere[i]; j++){
          if (i==0){
            if (noCharacterLeft(i,j,2)){
              ary[i][j][0] --;
            }
          }else if (i ==1 ){
            for (int k = 1; k<14; k++){
              if (noCharacterLeft(i,j,k))
                ary[i][j][0] --;
            }
          }else{
            if (ary[i][j][0]>=sizeXCpt-1 && ary[i][j][0]<= sizeScreenOnX+sizeXCpt &&ary[i][j][1]>=sizeYCpt && ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
              display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt);
              notDisplay(ary[i][j][0]-sizeXCpt-1, ary[i][j][1]-sizeYCpt);
            }
            else {
              notDisplay(ary[i][j][0]-sizeXCpt-1, ary[i][j][1]-sizeYCpt);
            }
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
      for(int i = 0; i < 12; i++){
        for (int j = 0 ; j< numberOfEatchCaractere[i]; j++){
          if (i==0){
            if (noCharacterBottom(i,j,2)){
              ary[i][j][1] ++;
            }
          }else if (i ==1 ){
            for (int k = 1; k<14; k++){
              if (noCharacterBottom(i,j,k))
                ary[i][j][1] ++;
            }
          }else{
            if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt && ary[i][j][1]>=sizeYCpt &&ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
              display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt);
              notDisplay(ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt+1);
            }
            else {
              notDisplay(ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt+1);
            }
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
        for (int j = 0 ; j< numberOfEatchCaractere[i]; j++){
          if (i==0){
            if (noCharacterTop(i,j,2)){
              ary[i][j][1] --;
            }
          }else if (i ==1 ){
            for (int k = 1; k<14; k++){
              if (noCharacterTop(i,j,k))
                ary[i][j][1] --;
            }
          }else{
            if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt && ary[i][j][1]>=sizeYCpt &&ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
              display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt);
              notDisplay(ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt-1);
            }
            else {
              notDisplay(ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt-1);
            }
          }
        }
      }
      timeCpt = millis();
    }
  }
}

//si le hero est en x et Y l'affiche est statique sinon il défile 
void Position::manualShift(int x, int y ){
  if (ary[0][0][0]-sizeXCpt>x){
    shiftToLeft(); 
  }
  if (ary[0][0][0]-sizeXCpt<x){
    shiftToRight(); 
  }
  if (ary[0][0][1]-sizeYCpt>y){
      shiftToTop(); 
    }
  if (ary[0][0][1]-sizeYCpt<y){
    shiftToBottom(); 
  }
}
//si le hero est un des 4 coté il défile 
void Position::manualShiftBorder(){
  if (ary[0][0][0]==sizeScreenOnX+sizeXCpt){
    shiftToLeft(); 
  }
  if (ary[0][0][0]==sizeXCpt){
    shiftToRight(); 
  }
  if (ary[0][0][1]==sizeScreenOnY+sizeYCpt){
      shiftToTop(); 
    }
  if (ary[0][0][1]==sizeYCpt){
    shiftToBottom(); 
  }
}

void Position::infinite(){ 
  if (millis () > timeCpt + runningSpeed){
    sizeXCpt ++;
    for(int i = 0; i < 12; i++){
      for (int j = 0 ; j< numberOfEatchCaractere[i]; j++){
        if (i==0){
          if (ary[i][j][0] < sizeScreenOnX+sizeXCpt && noCharacterRight(i,j,2)){
            ary[i][j][0] ++;
          }
        }else if (i ==1 ){
          for (int k = 1; k<14; k++){
            if (ary[i][j][0] < sizeScreenOnX+sizeXCpt && noCharacterRight(i,j,k))
              ary[i][j][0] ++;
          }
        }else{
          if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt &&ary[i][j][1]>=sizeYCpt && ary[i][j][1]<= sizeScreenOnY+sizeYCpt){
            display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt );
            notDisplay(ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
          }
          else {
            notDisplay(ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
          }
        }
      }
    }
    timeCpt = millis();
  }
}

//END MODE OF DISPLAY

//CHECKED NEXT CHARACTER: renvoie true si la case d'à coter est vide
bool Position::noCharacterLeft(int id , int number, int numberOfObstacle){
  for (int i =0; i < numberOfEatchCaractere[numberOfObstacle]; i++){
    if ((ary[id][number][0]-1==ary[numberOfObstacle][i][0])&&(ary[id][number][1]==ary[numberOfObstacle][i][1])&&ary[numberOfObstacle][i][2]==1){
      return false ; 
    }
  }
  return true;
}
bool Position::noCharacterRight(int id , int number, int numberOfObstacle){
  for (int i =0; i < numberOfEatchCaractere[numberOfObstacle]; i++){
    if ((ary[id][number][0]+1==ary[numberOfObstacle][i][0])&&(ary[id][number][1]==ary[numberOfObstacle][i][1])&&ary[numberOfObstacle][i][2]==1){
      return false ; 
    }
  }
  return true;
}
bool Position::noCharacterTwoRight(int id , int number, int numberOfObstacle){
  for (int i =0; i < numberOfEatchCaractere[numberOfObstacle]; i++){
    if ((ary[id][number][0]+2==ary[numberOfObstacle][i][0])&&(ary[id][number][1]==ary[numberOfObstacle][i][1])&&ary[numberOfObstacle][i][2]==1){
      return false ; 
    }
  }
  return true;
}
bool Position::noCharacterTop(int id , int number, int numberOfObstacle){
  for (int i =0; i < numberOfEatchCaractere[numberOfObstacle]; i++){
    if ((ary[id][number][0]==ary[numberOfObstacle][i][0])&&(ary[id][number][1]-1==ary[numberOfObstacle][i][1])&&ary[numberOfObstacle][i][2]==1){
      return false ; 
    }
  }
  return true;
}
bool Position::noCharacterBottom(int id , int number, int numberOfObstacle){
  for (int i =0; i < numberOfEatchCaractere[numberOfObstacle]; i++){
    if ((ary[id][number][0]==ary[numberOfObstacle][i][0])&&(ary[id][number][1]+1==ary[numberOfObstacle][i][1])&&ary[numberOfObstacle][i][2]==1){
      return false ; 
    }
  }
  return true;
}
//END CHECKED NEXT CHARACTER 

/****************************Hero**********************************/
Hero::Hero(Position *position) {
  this->position = position; 
  id = 0; 
  number = 0; 
  heroSpeedOnX = 400; 
  heroSpeedOnY = 400;
  heroJumpSpeed = 300;

  fire = false; 

  numberOfLife = 1; 
  numberOfMonster = 0; 
  numberOfKey = 0; 
  numberOfdoor = 0; 
  numberOfArrow = 0; 
  numberOfEqual = 0;
  numberOfMinus = 1; 
  numberOfCoin = 0; 
  numberOfLevel = 1; 
}

/*
*Setters 
*/
void Hero::setHeroSpeed(int speendOnX, int speedOnY){
  heroSpeedOnX = speendOnX; 
  heroSpeedOnY = speedOnY;
}

//MOVE OF HERO: ensemble de fonction qui permettent au hero d'aller a gauche à droite en haut et en bas
void Hero::goLeft(){
  if (boutonLeft()){
    if (position->ary[this->id][this->number][0] > position->sizeXCpt && position->noCharacterLeft( this->id, this->number,2)){
      display(this->id, position->ary[this->id][this->number][0]-1-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][0] --;
      timeCpt = millis();  
    }
  }
}
void Hero::goRight(){
  if (boutonRight()){
    if (position->ary[this->id][this->number][0] < sizeScreenOnX+position->sizeXCpt && position->noCharacterRight(this->id, this->number, 2)){
      display(this->id, position->ary[this->id][this->number][0]+1-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][0] ++;
      timeCpt = millis();  
    }
  }
}
void Hero::goTop(){
  if (boutonTop()){
    if (position->ary[this->id][this->number][1] > position->sizeYCpt && position->noCharacterTop(this->id, this->number, 2)){
      display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-1-position->sizeYCpt);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][1] --;
      timeCpt = millis();  
    }
  }
}
void Hero::goBottom(){
  if (boutonBottom()){
    if (position->ary[this->id][this->number][1] < sizeScreenOnY+position->sizeYCpt && position->noCharacterBottom(this->id, this->number, 2)){
      display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]+1-position->sizeYCpt);
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      position->ary[this->id][this->number][1] ++;
      timeCpt = millis();  
    }
  }
}


void Hero::moveLeftRight(){
  display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
  if (millis()> timeCpt + heroSpeedOnX){
    goRight();
    goLeft(); 
  }
}
void Hero::move(){
  //display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
  if (millis()> timeCpt + heroSpeedOnX){
    goRight();
    goLeft(); 
  }
  if (millis()> timeCpt + heroSpeedOnY){
   goBottom();
   goTop(); 
  }
}
//END MOVE OF HERO


//JUMP FORWARD: le hero fait un avance de deux case vers la droite
void Hero::jumpForward(bool (Hero::*callback)()) {
  if (millis() > timeCpt + heroJumpSpeed) {
    if ((this->*callback)()) {
      if (position->ary[this->id][this->number][0] < sizeScreenOnX + position->sizeXCpt - 1 && position->noCharacterTwoRight(this->id, this->number, 2)) {
        display(this->id, position->ary[this->id][this->number][0] + 2 - position->sizeXCpt, position->ary[this->id][this->number][1] - position->sizeYCpt);
        notDisplay(position->ary[this->id][this->number][0] - position->sizeXCpt, position->ary[this->id][this->number][1] - position->sizeYCpt);
        position->ary[this->id][this->number][0] = position->ary[this->id][this->number][0] + 2;
        timeCpt = millis();
      }
    }
  }
}
//si request = 1 declenchement de l'action après un appui unique le bouton du millieu,si request = 1 declenchement de l'action après un appui court sur le bouton du millieu, si request = 0 declenchement de l'action après un appui long sur le bouton du millieu, si request = 3 declenchement de l'action apres un appui sur bouton haut et bouton droit si request = 4 declenchement de l'action apres un appui sur bouton haut et bouton du milieu 
void Hero::jumpForwardWithRequest(int request){
  switch (request)
  {
  case 0:
    this->jumpForward(&Hero::boutonMonostable);
    break;
  case 1:
    this->jumpForward(&Hero::boutonShortPress);
    break;
  case 2:
    this->jumpForward(&Hero::boutonLongPress);
    break;
  case 3:
    this->jumpForward(&Hero::specialMoveRight);
    break;
  case 4:
    this->jumpForward(&Hero::specialMoveTop);
    break;
  
  default:
    break;
  }
}
//END JUMP FORWARD

//JUMP: Le hero monte d'une case
///!\ Le sizeY ne doit pas etre plus grand que 3 pour cette utiliser cette fonction 
void Hero::jump(bool (Hero::*callback)()){
  //display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
  if (millis()> timeCpt1 + heroJumpSpeed){
    if ((this->*callback)()){
      if (position->ary[this->id][this->number][1]>0 && position->noCharacterTop(this->id, this->number, 2)){
        display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-1-position->sizeYCpt);
        notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
        position->ary[this->id][this->number][1] = position->ary[this->id][this->number][1]-1;
        timeCpt1 = millis();
      }
    }
    if (millis()> timeCpt1 + (heroJumpSpeed/10)){
      if (position->ary[this->id][this->number][1] < position->sizeY && position->noCharacterBottom(this->id, this->number, 2)){
        display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]+1-position->sizeYCpt);
        notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
        position->ary[this->id][this->number][1] = position->ary[this->id][this->number][1]+1;
        timeCpt1 = millis();
      }
    }
  }
}
//si request = 1 declenchement de l'action après un appui unique le bouton du millieu, si request = 1 declenchement de l'action après un appui court sur le bouton du millieu, si request = 2 declenchement de l'action après un appui long sur le bouton du millieu, si request = 3 declenchement de l'action apres un appui sur bouton haut et bouton du milieu
void Hero::jumpWithRequest(int request){
  switch (request)
  {
  case 0:
    this->jump(&Hero::boutonMonostable);
    break;
  case 1:
    this->jump(&Hero::boutonShortPress);
    break;
  case 2:
    this->jump(&Hero::boutonLongPress);
    break;
  case 3:
    this->jump(&Hero::specialMoveTop);
    break;
  default:
    break;
  }
}

//PULL: la variable fire prend la valeur de true lorsque pull est declancher, renvoie aussi la direction
void Hero::pull(bool (Hero::*callback)()){
  if (millis()> timeCpt2 + heroFireSpeed){
    if ((this->*callback)()){
      if (fire == false){
        fire = true;
        direction =1;    
        timeCpt2 = millis();
        timeCpt = millis(); 
      }
    }
  }
}
//si request = 1 declenchement de l'action après un appui unique le bouton du millieu, si request = 1 declenchement de l'action après un appui court sur le bouton du millieu, si request = 2 declenchement de l'action après un appui long sur le bouton du millieu, si request = 3 declenchement de l'action apres un appui sur bouton de droite et bouton du milieu
void Hero::pullWithRequest(int request){
  switch (request)
  {
  case 0:
    this->pull(&Hero::boutonMonostable);
    break;
  case 1:
    this->pull(&Hero::boutonShortPress);
    break;
  case 2:
    this->pull(&Hero::boutonLongPress);
    break;
  case 3:
    this->pull(&Hero::specialMoveRight);
    break;
  default:
    break;
  }
}
//END PULL

//INTERACTION: dans le cas ou le hero est sur la même case qu'un autre caractère cela engendre des interactions
///!\ PENSER A BIEN LA METTRE DANS LE LOOP SINON ça NE MARCHE PAS 
void Hero::interaction(){
  for (int i =0; i <12; i ++){
    for (int j = 0 ; j<position->numberOfEatchCaractere[i]; j++){
      if ((position->ary[this->id][this->number][0]==position->ary[i][j][0]&&position->ary[this->id][this->number][1]==position->ary[i][j][1])&&position->ary[i][j][2]>=1){
        switch (i)
        {
        case 1:
          if (position->ary[i][j][2]==1){
            numberOfLife = numberOfLife - 1;
            display(1, position->ary[i][j][0],position->ary[i][j][1]);
            
            position->ary[this->id][this->number][0]=0;
            position->ary[this->id][this->number][1]=0;
            position->sizeXCpt = 0; 
            position->sizeYCpt = 0; 
            display(0, position->ary[this->id][this->number][0],position->ary[this->id][this->number][1]);
            }
            else if(position->ary[i][j][2]==2){
              position->ary[i][j][2] = 0;
              numberOfMonster = numberOfMonster + 1;
            }
            
          break;
        case 2:
          numberOfMonster = numberOfMonster + 1;
          position->ary[i][j][2]= 0;
          break;
        case 3:
          numberOfKey ++;
          position->ary[i][j][2]= 0; 
          break;
        case 4:
          numberOfdoor ++;
          position->ary[i][j][2]= 0; 
          break;
        case 5: 
          numberOfLife = numberOfLife + 1;
          position->ary[i][j][2]= 0;
          break; 
        case 6:
          numberOfLife = numberOfLife - 1;
            display(6, position->ary[i][j][0],position->ary[i][j][1]);
            
            position->ary[this->id][this->number][0]=0;
            position->ary[this->id][this->number][1]=0;
            position->sizeXCpt = 0; 
            position->sizeYCpt = 0; 
            display(0, position->ary[this->id][this->number][0],position->ary[this->id][this->number][1]);
          break; 
        case 7: 
          numberOfArrow ++;
          position->ary[i][j][2]= 0; 
          break; 
        case 8: 
          numberOfEqual ++;
          position->ary[i][j][2]= 0; 
          break; 
        case 9: 
          numberOfMinus ++;
          position->ary[i][j][2]= 0; 
          break; 
        case 10:
          numberOfCoin ++;
          position->ary[i][j][2]= 0;
          break;
        case 11:
          numberOfMonster ++;
          position->ary[i][j][2]= 0;
          break;
        default:
          break;
        }
      }
    }
  }
  this->concequencies(); 
}

void Hero::concequencies(){
  if (numberOfLife<=0){
    lcd.setCursor(0,0); 
    lcd.print("GAME OVER"); 
    numberOfLevel = 1; 
  }
}
//END INTERACTION
/******************************Mechant********************************/
Mechant::Mechant(Position *position) {
  this->position = position; 
  id = 0; 
  number = 0; 
  mechantSpeedOnX = 400; 
  mechantSpeedOnY = 400;
  mechantJumpSpeed = 300;

  fire = false; 
}
Mechant::Mechant(Position *position, int number) {
  this->position = position; 
  id = 1; 
  this->number = number; 
  mechantSpeedOnX = 400; 
  mechantSpeedOnY = 400;
  mechantJumpSpeed = 300;

  fire = false; 
}

/*
*MECHANTS: créé un tableau de mechant 
*/
void Mechant::createMechant(){
  arrayOfMechants = new Mechant*[position->numberOfEatchCaractere[1]];
  for (int i = 0; i < position->numberOfEatchCaractere[1]; i++) {
    arrayOfMechants[i] = new Mechant(this->position, i);

    Serial.print("Numero du mechant ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(arrayOfMechants[i]->number);
  }
}

void Mechant::allMechant(void (Mechant::*callback)()) {
  for (int i = 0; i < position->numberOfEatchCaractere[1]; i++) {
    (arrayOfMechants[i]->*callback)();
  }
}
//END MECHANTS 

/******************************Menu********************************/





SecondaryScreen::SecondaryScreen(Hero *hero)  {
  this->hero = hero; 
}
void SecondaryScreen::displaySecondaryScreen(int i){
  switch (i)
  {
  case 0:
    display(5, sizeScreenOnX+1, 0); 
    lcd.setCursor((sizeScreenOnX+2), 0); 
    lcd.print(hero->numberOfLife); 
    display(20, sizeScreenOnX+1, 1); 
    lcd.setCursor((sizeScreenOnX+2), 1); 
    lcd.print(hero->numberOfCoin);
    display(9, sizeScreenOnX+1, 2); 
    display(8, sizeScreenOnX+2, 2); 
    display(7, sizeScreenOnX+3, 2); 
    lcd.setCursor((sizeScreenOnX+1), 3);
    lcd.print(hero->numberOfMinus);
    lcd.setCursor((sizeScreenOnX+2), 3); 
    lcd.print(hero->numberOfEqual);
    lcd.setCursor((sizeScreenOnX+3), 3); 
    lcd.print(hero->numberOfArrow);
    break;
  case 1:
    display(5, sizeScreenOnX+1, 0); 
    lcd.setCursor((sizeScreenOnX+2), 0); 
    lcd.print(hero->numberOfLife); 
    display(20, sizeScreenOnX+1, 1);
    lcd.setCursor((sizeScreenOnX+2), 1); 
    lcd.print(hero->numberOfCoin);
    display(9, sizeScreenOnX+1, 2); 
    lcd.setCursor((sizeScreenOnX+2),2); 
    lcd.print(hero->numberOfMinus);
    display(11, sizeScreenOnX+1, 3);
    lcd.setCursor((sizeScreenOnX+2),3); 
    lcd.print(hero->numberOfMonster);
    break;
  case 2:
    display(5, sizeScreenOnX+1, 0); 
    display(20, sizeScreenOnX+2, 0);
    lcd.setCursor((sizeScreenOnX+3),0); 
    lcd.print("L");
    lcd.setCursor((sizeScreenOnX+1),1); 
    lcd.print(hero->numberOfLife);
    lcd.setCursor((sizeScreenOnX+2),1); 
    lcd.print(hero->numberOfCoin);
    lcd.setCursor((sizeScreenOnX+3),1); 
    lcd.print(hero->numberOfLevel);
    display(9, sizeScreenOnX+1, 2); 
    display(8, sizeScreenOnX+2, 2); 
    display(7, sizeScreenOnX+3, 2);  
    lcd.setCursor((sizeScreenOnX+1),3);
    lcd.print(hero->numberOfMinus);
    lcd.setCursor((sizeScreenOnX+2),3); 
    lcd.print(hero->numberOfEqual);
    lcd.setCursor((sizeScreenOnX+3),3); 
    lcd.print(hero->numberOfArrow);
    break;
  default:
    break;
  }
}

