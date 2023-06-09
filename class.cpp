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
        ary[i][j][1] = random(0,sizeY+1); //random fait un nombre aléatooire >= borne inf et < borne sup
        ary[i][j][2] = 1;
        if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<= sizeScreenOnX+sizeXCpt &&ary[i][j][1]>=sizeYCpt && ary[i][j][1]<= sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
          display(i, ary[i][j][0], ary[i][j][1]);
        }

      }else  {
        int y, x; 
        do{
          x = random(2,sizeX-1) ;
          y = random(0,sizeY+1) ;
          
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
// Cette fonction est utilisée pour déplacer l'affichage vers la gauche en mettant à jour les coordonnées de tous les caractères à l'écran
void Position::shiftToLeft(){
  // Vérifier si l'écran peut être déplacé davantage vers la gauche
  if (sizeXCpt + sizeScreenOnX < sizeX){
    // Vérifier si le déplacement de l'écran est autorisé en fonction du temps
    if (millis() > timeCpt + runningSpeed){
      // Incrémenter la position de départ de l'écran
      sizeXCpt++;
      // Parcourir tous les caractères affichés à l'écran
      for(int i = 0; i < 12; i++){
        for (int j = 0 ; j < numberOfEatchCaractere[i]; j++){
          // Si c'est le premier caractère (le joueur), vérifier s'il n'y a pas d'obstacle pour se déplacer
          if (i==0){
            if (noCharacterRight(i,j,2)){
            ary[i][j][0] ++;
            }
          }
          // Si c'est un autre caractére, vérifier si le caractère doit être déplacé ou supprimé en fonction de sa position
          else{
            if (ary[i][j][0]>=sizeXCpt && ary[i][j][0]<=sizeScreenOnX+sizeXCpt && ary[i][j][1]>=sizeYCpt && ary[i][j][1]<=sizeScreenOnY+sizeYCpt && ary[i][j][2]>0){
              display(i, ary[i][j][0]-sizeXCpt, ary[i][j][1]-sizeYCpt );
              notDisplay(ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
            }
            else {
              notDisplay(ary[i][j][0]-sizeXCpt+1, ary[i][j][1]-sizeYCpt);
            }
          }
        }
      }
      // Mettre à jour le temps
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


//il faut le refaire
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
*getters 
*/
bool Hero::getFire(){
  return fire; 
}
/*
*Setters 
*/
void Hero::setHeroSpeed(int speendOnX, int speedOnY){
  heroSpeedOnX = speendOnX; 
  heroSpeedOnY = speedOnY;
}
void Hero::setFireFalse(){
  fire = false; 
}

//MOVE OF HERO: ensemble de fonction qui permettent au hero d'aller a gauche à droite en haut et en bas
// Cette fonction permet au personnage de se déplacer vers la gauche s'il appuie sur le bouton correspondant
void Hero::goLeft(){
  // Vérifie si le bouton de gauche est pressé
  if (boutonLeft()){
    // Vérifie si le personnage ne sort pas de l'écran et s'il n'y a pas d'autres personnages à gauche
    if (position->ary[this->id][this->number][0] > position->sizeXCpt && position->noCharacterLeft( this->id, this->number,2)){
      // Affiche le personnage à sa nouvelle position à gauche
      display(this->id, position->ary[this->id][this->number][0]-1-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      // Efface l'ancienne position du personnage
      notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
      // Met à jour la position du personnage dans l'array
      position->ary[this->id][this->number][0] --;
      // Met à jour le compteur de temps pour le déplacement
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
  display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
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
            numberOfLife --;
            
            position->ary[this->id][this->number][0]=0;
            position->ary[this->id][this->number][1]=0;
            position->sizeXCpt = 0; 
            position->sizeYCpt = 0; 
            lcd.clear(); 

            for (int k =0 ; k < 12; k ++ ){
              for (int l = 0 ; l < position->numberOfEatchCaractere[k]; l ++ ){
                if (position->ary[k][l][0]>=position->sizeXCpt && position->ary[k][l][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[k][l][1]>=position->sizeYCpt && position->ary[k][l][1]<= sizeScreenOnY+position->sizeYCpt && position->ary[k][l][2]>0){
                  display(k, position->ary[k][l][0], position->ary[k][l][1] );
                }
              }
            }
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
          position->ary[this->id][this->number][0]=0;
          position->ary[this->id][this->number][1]=0;
          position->sizeXCpt = 0; 
          position->sizeYCpt = 0; 
          lcd.clear(); 

          for (int k =0 ; k < 12; k ++ ){
              for (int l = 0 ; l < position->numberOfEatchCaractere[k]; l ++ ){
                if (position->ary[k][l][0]>=position->sizeXCpt && position->ary[k][l][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[k][l][1]>=position->sizeYCpt && position->ary[k][l][1]<= sizeScreenOnY+position->sizeYCpt && position->ary[k][l][2]>0){
                  display(k, position->ary[k][l][0], position->ary[k][l][1] );
                }
              }
            }
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
  id = 1; 
  number = 0; 
  mechantSpeedOnX = 800; 
  mechantSpeedOnY = mechantSpeedOnX;
  mechantJumpSpeed = 300;
  numberOfLife = 1;  
  fire = false; 
  numberOfMinus=5;
  timingOfMove = 0; 
}
Mechant::Mechant(Position *position, int number) {
  this->position = position; 
  id = 1; 
  this->number = number;
  mechantSpeedOnX = 400; 
  mechantSpeedOnY = mechantSpeedOnX;
  mechantJumpSpeed = 300;
  numberOfLife = 3;  
  fire = false; 
  numberOfMinus=5;
  timingOfMove = 0; 
}

bool Mechant::getFire(){
  return fire; 
}

void Mechant::setFireFalse(){
  fire = false; 
}

//CHECKED IF MECHANT CAN GO NEXT: renvoie true lorsque que la case voisine est disponible
bool Mechant::noElementLeft(){
  for (int i = 1; i < 12 ; i++){
    if (position->ary[this->id][this->number][0]<= position->sizeX-position->sizeX || !(position->noCharacterLeft(this->id, this->number, i))){
      return false; 
    }
  }
  return true ;
}
bool Mechant::noElementRight(){
  for (int i = 1; i < 12 ; i++){
    if (position->ary[this->id][this->number][0]>= position->sizeX || !(position->noCharacterRight(this->id, this->number, i))){
      return false; 
    }
  }
  return true ;
}
bool Mechant::noElementTop(){
  for (int i = 1; i < 12 ; i++){
    if (position->ary[this->id][this->number][1]<= position->sizeY-position->sizeY || !(position->noCharacterTop(this->id, this->number, i))){
      return false; 
    }
  }
  return true ;
}
bool Mechant::noElementBottom(){
  for (int i = 1; i < 12 ; i++){
    if (position->ary[this->id][this->number][1]>= position->sizeY ||!(position->noCharacterBottom(this->id, this->number, i))){
      return false; 
    }
  }
  return true ;
}
//END CHECKED IF MECHANT CAN GO NEXT


//MOVE MECHANT: génère l'ensemble des déplacement du ou des mechants
///!\ ça devrais fonctionner mais tout n'est pas tester 
// Méthode pour faire déplacer le méchant vers la gauche
void Mechant::goLeft(){
  // Vérification du temps écoulé depuis le dernier déplacement
  if (millis()> timeCpt + mechantSpeedOnX && position->ary[this->id][this->number][2]==1){
    // Vérification qu'il n'y a pas d'élément à gauche du méchant
    if (noElementLeft()){
      // Vérification que le méchant est bien dans les limites de l'écran
      if (position->ary[this->id][this->number][0]>=position->sizeXCpt && position->ary[this->id][this->number][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[this->id][this->number][1]>=position->sizeYCpt && position->ary[this->id][this->number][1]<= sizeScreenOnY+position->sizeYCpt){
        // Affichage du méchant à sa nouvelle position à gauche
        display(this->id, position->ary[this->id][this->number][0]-1-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
        // Suppression du méchant à sa position précédente
        notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt);
        // Mise à jour de la position du méchant
        position->ary[this->id][this->number][0]--;
        // Mise à jour du temps de compteur
        timeCpt = millis();
      }
      else {
        // Si le méchant n'est pas dans les limites de l'écran ou qu'il n'est pas actif, il se déplace simplement vers la gauche
        position->ary[this->id][this->number][0]--;
        timeCpt = millis();
        }
      }
      else{
      // Si il y a un élément à gauche, le méchant se déplace aléatoirement
      goRandom();
      }
  }
}
void Mechant::goRight(){
  if (millis()> timeCpt + mechantSpeedOnX && position->ary[this->id][this->number][2]==1){
    if (noElementRight()){
      if (position->ary[this->id][this->number][0]>=position->sizeXCpt && position->ary[this->id][this->number][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[this->id][this->number][1]>=position->sizeYCpt && position->ary[this->id][this->number][1]<= sizeScreenOnY+position->sizeYCpt && position->ary[this->id][this->number][2]>0){
        display(this->id, position->ary[this->id][this->number][0]+1-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt); 
        notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt); 
        position->ary[this->id][this->number][0]++; 
        timeCpt = millis(); 
      }
      else {
        position->ary[this->id][this->number][0]++; 
        timeCpt = millis(); 
      }
    }
    else{
      goRandom(); 
    }
  }
}
void Mechant::goTop(){
  if (millis()> timeCpt + mechantSpeedOnY && position->ary[this->id][this->number][2]==1){
    if (noElementTop()){
      if (position->ary[this->id][this->number][0]>=position->sizeXCpt && position->ary[this->id][this->number][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[this->id][this->number][1]>=position->sizeYCpt && position->ary[this->id][this->number][1]<= sizeScreenOnY+position->sizeYCpt && position->ary[this->id][this->number][2]>0){
        
        if (position->ary[this->id][this->number][1]==position->sizeYCpt) {
          notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt); 
          position->ary[this->id][this->number][1]++; 
          timeCpt = millis();
        }
        else{
          display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-1-position->sizeYCpt); 
          notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt); 
          position->ary[this->id][this->number][1]--; 
          timeCpt = millis();
        }
      }
      else {
        position->ary[this->id][this->number][1]--; 
        timeCpt = millis();
      } 
    }
    else{
      goRandom(); 
    }
  }
}
void Mechant::goBottom(){
  if (millis()> timeCpt + mechantSpeedOnY && position->ary[this->id][this->number][2]==1){
    if (noElementBottom()){
      if (position->ary[this->id][this->number][0]>=position->sizeXCpt && position->ary[this->id][this->number][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[this->id][this->number][1]>=position->sizeYCpt && position->ary[this->id][this->number][1]<= sizeScreenOnY+position->sizeYCpt && position->ary[this->id][this->number][2]>0){
        
        if (position->ary[this->id][this->number][1]== sizeScreenOnY+position->sizeYCpt) {
          notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt); 
          position->ary[this->id][this->number][1]++; 
          timeCpt = millis();
        }
        else {
          display(this->id, position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]+1-position->sizeYCpt); 
          notDisplay(position->ary[this->id][this->number][0]-position->sizeXCpt, position->ary[this->id][this->number][1]-position->sizeYCpt); 
          position->ary[this->id][this->number][1]++; 
          timeCpt = millis();
        }
      }
      else {
        position->ary[this->id][this->number][1]++; 
        timeCpt = millis(); 
      } 
    }
    else{
      goRandom(); 
    }
  }
}

void Mechant::goRandom(){
  int x = random(0, 4);
  
  switch (x)
  {
    case 0:
      goLeft();
      break;
    case 1:
      goRight();
      break;
    case 2:
      goTop();
      break;
    case 3:
      goBottom();
      break;
    default:
      break;
  }
}
void Mechant::leftToRight(){
  
  if (position->ary[this->id][this->number][0] >= position->sizeXCpt+ sizeScreenOnX){
    timingOfMove = 1; 
  }else if (position->ary[this->id][this->number][0] <= position->sizeXCpt) {
    timingOfMove = 0; 
  }
  if (timingOfMove == 0){
    goRight(); 
  }else if (timingOfMove == 1){
    goLeft(); 
  }
}
void Mechant::topToBottom(){
  if (position->ary[this->id][this->number][1] >= position->sizeYCpt+ sizeScreenOnY){
    timingOfMove = 1; 
  }else if (position->ary[this->id][this->number][1] <= position->sizeYCpt) {
    timingOfMove = 0;
  }
  if (timingOfMove == 0){
    goBottom(); 
  }else if (timingOfMove == 1){
    goTop(); 
  }
}

void Mechant::circle(){
  
  switch(timingOfMove){
    case 0:
      goBottom(); 
      timingOfMove=1;
    break; 
    case 1:
      goBottom(); 
      timingOfMove=2;
    break; 
    case 2:
      goLeft(); 
      timingOfMove=3;
    break; 
    case 3:
      goLeft(); 
      timingOfMove=4;
    break; 
    case 4:
      goTop(); 
      timingOfMove=5;
    break; 
    case 5:
      goTop(); 
      timingOfMove=6;
    break; 
    case 6:
      goRight(); 
      timingOfMove=7;
    break; 
    case 7:
      goRight(); 
      timingOfMove=0;
    break;  
  }
}
void Mechant::eight(){
  timingOfMove == 0;
  switch(timingOfMove){
    case 0:
      goRight(); 
      timingOfMove=1;
    break; 
    case 1:
      goTop(); 
      timingOfMove=2;
    break;  
    case 2:
      goLeft(); 
      timingOfMove=3;
    break;  
    case 3:
      goBottom(); 
      timingOfMove=4;
    break; 
    case 4:
      goLeft(); 
      timingOfMove=5;
    break; 
    case 5:
      goTop(); 
      timingOfMove=6;
    break;  
    case 6:
      goRight(); 
      timingOfMove=7;
    break; 
    case 7:
      goBottom(); 
      timingOfMove=0;
    break;   
  }
}

void Mechant::chassing(){
  if (position->ary[this->id][this->number][0] > position->ary[0][0][0]){goLeft();}
  if (position->ary[this->id][this->number][0] < position->ary[0][0][0]) {goRight();}
  if (position->ary[this->id][this->number][1] > position->ary[0][0][1]){goTop();}
  if (position->ary[this->id][this->number][1]< position->ary[0][0][1]){goBottom();}
}
//END MOVE MECHANT

//PULL: la variable fire prend la valeur de true lorsque pull est declancher, renvoie aussi la direction
///!\ tout pareil que au dessus
void Mechant::pullFront(){
  if (position->ary[this->id][this->number][1] == position->ary[0][0][1] && position->ary[0][0][0]<position->ary[this->id][this->number][0]) {
    if (millis()> timeCpt2 + mechantFireSpeed){
      if (fire == false && position->ary[this->id][this->number][2]==1){
        fire = true; 
        direction = 0; 
        timeCpt2 = millis();
      }
    }
  }
}
void Mechant::pullBack(){
  if (position->ary[this->id][this->number][1] == position->ary[0][0][1] && position->ary[0][0][0]>position->ary[this->id][this->number][0]) {
    if (millis()> timeCpt2 + mechantFireSpeed){
      if (fire == false && position->ary[this->id][this->number][2]==1){
        fire = true; 
        direction = 1; 
        timeCpt2 = millis();
      }
    }
  }
}
void Mechant::pullOn(){
  if (position->ary[this->id][this->number][0] == position->ary[0][0][0] && position->ary[0][0][1]<position->ary[this->id][this->number][1]) {
    if (millis()> timeCpt2 + mechantFireSpeed){
      if (fire == false && position->ary[this->id][this->number][2]==1){
        fire = true; 
        direction = 2; 
        timeCpt2 = millis();
      }
    }
  }
}
void Mechant::pullUnder(){
  if (position->ary[this->id][this->number][0] == position->ary[0][0][0] && position->ary[0][0][1]>position->ary[this->id][this->number][1]) {
    if (millis()> timeCpt2 + mechantFireSpeed){
      if (fire == false && position->ary[this->id][this->number][2]==1){
        fire = true; 
        direction = 3; 
        timeCpt2 = millis();
      }
    }
  }
}
//END PULL

void Mechant::concequencies(){
  for (int j = 0 ; j< position->numberOfEatchCaractere[1]; j++){
    if (numberOfLife<=0 && position->ary[1][j][2] == 1 ){
      position->ary[1][j][2] =2;
      display(11, position->ary[1][j][0],position->ary[1][j][1]);
    }
  }
}

/*
*MECHANTS: créé un tableau de mechant 
*/
void Mechant::createMechant(){
  arrayOfMechants = new Mechant*[position->numberOfEatchCaractere[1]];
  for (int i = 0; i < position->numberOfEatchCaractere[1]; i++) {
    arrayOfMechants[i] = new Mechant(this->position, i);
  }
}

void Mechant::allMechants(void (Mechant::*callback)()) {
  if (callback == nullptr) {
    Serial.println("Error: callback pointer is null");
  }
  
  for (int i = 0; i < position->numberOfEatchCaractere[1]; i++) {    
    Serial.println(arrayOfMechants[i]->id);
    (this->arrayOfMechants[arrayOfMechants[i]->number]->*callback)();
  }
}


//END MECHANTS 


/********************************Shot**************************************************/
Shot::Shot(Position *position, Hero *hero, Mechant *mechant)  {
  this->position = position; 
  this->hero = hero; 
  this->mechant = mechant; 
  
}

Bullet::Bullet(Position *position)  {
  this->position = position; 
}
ArrowBullet::ArrowBullet(int x, int y , int direction,Position *position): Bullet(position){
  _x =x; 
  _y = y; 
  dir = direction;
  arrowSpeed = 200;
  this->position = position; 
  
}
EqualBullet::EqualBullet(int x, int y , int direction,Position *position): Bullet(position){
  _x =x; 
  _y = y; 
  dir = direction;
  equalSpeed = 200;
  this->position = position;  
}
MinusBullet::MinusBullet(int x, int y , int direction,Position *position): Bullet(position){
  _x =x; 
  _y = y; 
  dir = direction;
  minusSpeed = 200;
  this->position = position; 
}

// Définition de la méthode element de la classe Bullet
int Bullet::element(){
  // Boucle sur les 12 caractères différents possibles
  for (int i = 0; i < 12 ; i++){
    // Boucle sur les positions de chaque caractère
    for (int j = 0 ; j< position->numberOfEatchCaractere[i]; j++){
      // Si la position actuelle de la balle correspond à la position d'un caractère activé dans le tableau position
      if (this->_x == position->ary[i][j][0]&& this->_y == position->ary[i][j][1]&&position->ary[i][j][2]==1){
        // Retourne l'indice du caractère correspondant
        return  i; 
      }
      // Si la position actuelle de la balle correspond à la position d'un caractère désactivé "blanc" dans le tableau position
      if (this->_x == position->ary[i][j][0]&& this->_y == position->ary[i][j][1]&&position->ary[i][j][2]==2){
        // Retourne l'indice de caractère blanc (11)
        return  11; 
      }
    }
  }
  // Si la balle ne correspond à aucune position connue, retourne 14
  return 14; 
}

void  Bullet::displayStar(){
  for (int i = 0; i< position->numberOfEatchCaractere[2]; i ++){
    if (position->ary[2][i][0] == _x && position->ary[2][i][1] == _y){
      position->ary[2][i][2] =2;
    }
  }
  display(11, _x-position->sizeXCpt,_y-position->sizeYCpt);
}

int Bullet::direction (){
  switch (dir)
  {
  case 0:
    return -1 ; 
    break;
  case 1:
    return 1 ; 
    break;
  case 2:
    return -1 ; 
    break;
  case 3:
    return 1 ; 
    break;
  
  default:
    break;
  }
}

//numberOfCharacterLimite = 2 pour arrow et 3 pour equal et minus 
bool Bullet::canProgress(int numberOfCharacterLimite, int numberCharacterNoChecked){ 
  switch (dir)
  {
  case 0:
    if ((element()<numberOfCharacterLimite && element()!=numberCharacterNoChecked)|| _x< position->sizeXCpt){
    return false; 
    }
    break;
  case 1:
    if ((element()<numberOfCharacterLimite && element()!=numberCharacterNoChecked)|| _x> position->sizeXCpt+sizeScreenOnX){
    return false; 
    }
    break;
  case 2:
    if ((element()<numberOfCharacterLimite && element()!=numberCharacterNoChecked)|| _y< position->sizeYCpt){
    return false; 
    } 
    break;
  case 3:
    if ((element()<numberOfCharacterLimite && element()!=numberCharacterNoChecked)|| _y> position->sizeYCpt+sizeScreenOnY){
    return false; 
    }
    break;
   
  }   
  return true; 
}
void Shot::bulletReachHero(){
  hero->numberOfLife --;
            
  position->ary[hero->id][hero->number][0]=0;
  position->ary[hero->id][hero->number][1]=0;
  position->sizeXCpt = 0; 
  position->sizeYCpt = 0; 
  lcd.clear(); 

  for (int k =0 ; k < 12; k ++ ){
    for (int l = 0 ; l < position->numberOfEatchCaractere[k]; l ++ ){
      if (position->ary[k][l][0]>=position->sizeXCpt && position->ary[k][l][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[k][l][1]>=position->sizeYCpt && position->ary[k][l][1]<= sizeScreenOnY+position->sizeYCpt && position->ary[k][l][2]>0){
        display(k, position->ary[k][l][0]-position->sizeXCpt, position->ary[k][l][1]-position->sizeYCpt );
      }
    }
  }
}
void ArrowBullet::go() {
  // Vérifie la direction de la balle
  if (dir == 2 || dir == 3) { // Si la direction est vers le haut ou vers le bas
    // Affiche la balle à sa nouvelle position verticale
    display(7, _x-position->sizeXCpt, _y + direction()-position->sizeYCpt); 
    // Récupère l'élément (ennemi ou obstacle) sur lequel la balle va arriver
    int characterToDisplay = element();
    // Si l'élément est une étoile
    if (characterToDisplay == 2) {
      // Affiche l'étoile à la nouvelle position
      displayStar(); 
    } else {
      // Sinon, affiche l'élément normal à la nouvelle position
      display(characterToDisplay, _x-position->sizeXCpt, _y-position->sizeYCpt);
    }
    // Met à jour la position verticale de la balle
    _y = _y + direction();
  } else { // Si la direction est vers la gauche ou vers la droite
    // Affiche la balle à sa nouvelle position horizontale
    display(7, _x-position->sizeXCpt + direction(), _y-position->sizeYCpt);
    // Récupère l'élément (ennemi ou obstacle) sur lequel la balle va arriver
    int characterToDisplay = element();
    // Si l'élément est une étoile
    if (characterToDisplay == 2) {
      // Affiche l'étoile à la nouvelle position
      displayStar(); 
    } else {
      // Sinon, affiche l'élément normal à la nouvelle position
      display(characterToDisplay, _x-position->sizeXCpt, _y-position->sizeYCpt);
    }
    // Met à jour la position horizontale de la balle
    _x = _x + direction();
  }
}

void  EqualBullet::go(){
  if (dir == 2 || dir ==3){
    display(8, _x-position->sizeXCpt, _y+direction());
    display(element(), _x-position->sizeXCpt,_y-position->sizeYCpt);
    _y = _y +direction();
  }
  else{
    display(8, _x+direction(), _y-position->sizeYCpt);
    display(element(), _x-position->sizeXCpt,_y-position->sizeYCpt);
    _x = _x +direction();
  } 
}
void MinusBullet::go() {
  if (dir >1) {
    display(9, _x-position->sizeXCpt, _y-position->sizeYCpt + direction());
    display(element(), _x-position->sizeXCpt, _y-position->sizeYCpt);
    _y += direction();
  }
  else {
    display(9, _x + direction()-position->sizeXCpt, _y-position->sizeYCpt);
    display(element(), _x-position->sizeXCpt, _y-position->sizeYCpt);
    _x += direction();
  }
}

void Shot::consequenciesArrow(){
  switch (arrowBullet->element()){
    case 0: 
      bulletReachHero(); 
      break; 
    case 1: 
      display(arrowBullet->element(), arrowBullet->_x-position->sizeXCpt, arrowBullet->_y-position->sizeYCpt);
      for (int j = 0 ; j< position->numberOfEatchCaractere[1]; j++){
        if (arrowBullet->_x == position->ary[1][j][0]&& arrowBullet->_y == position->ary[1][j][1]){
          mechant->numberOfLife -- ;
        }
      }
      break; 
  }
}
void Shot::consequenciesEqual(){
  switch (equalBullet->element()){
    case 0: 
      bulletReachHero();
      break; 
    case 1: 
      display(equalBullet->element(), equalBullet->_x-position->sizeXCpt, equalBullet->_y-position->sizeYCpt);
      for (int j = 0 ; j< position->numberOfEatchCaractere[1]; j++){
        if (equalBullet->_x == position->ary[1][j][0]&& equalBullet->_y == position->ary[1][j][1]){
          mechant->numberOfLife = mechant->numberOfLife -2 ;
        }
      }
      break; 
    case 2: 
      display(minusBullet->element(), minusBullet->_x, minusBullet->_y);
      break; 
  }
}
void Shot::consequenciesMinus(){
  switch (minusBullet->element()){
    case 0: 
      bulletReachHero();
      break; 
    case 1: 
      display(minusBullet->element(), minusBullet->_x-position->sizeXCpt, minusBullet->_y-position->sizeYCpt);
      for (int j = 0 ; j< position->numberOfEatchCaractere[1]; j++){
        if (minusBullet->_x == position->ary[1][j][0]&& minusBullet->_y == position->ary[1][j][1]){
          mechant->numberOfLife -- ;
        }
      }
      break; 
    case 2: 
      display(minusBullet->element(), minusBullet->_x, minusBullet->_y);
      break; 
  }
}

int Shot::typeOfMunition(){
  if (hero->getFire() && !ongoing ){
    if (hero->numberOfArrow>0){
      ongoing = true; 
      return 1; 
    }else if (hero->numberOfEqual>0 ){
      ongoing = true; 
      return 2 ;
    }else if (hero->numberOfMinus >0 ){
      ongoing = true; 
      return 3; 
    }
    ongoing = false;
    return 0; 
  }
}

void Shot::arrowShot(int numberCharacterNoChecked ){
  // Si la flèche n'a pas encore été créée, la créer avec la position et la direction du héros
  if (arrowBullet == nullptr){
    arrowBullet =  new ArrowBullet(position->ary[hero->id][hero->number][0],position->ary[hero->id][hero->number][1], hero->direction,position);
  }
  // Si la flèche peut encore avancer, la faire avancer en vérifiant si assez de temps s'est écoulé depuis le dernier déplacement
  else if (arrowBullet->canProgress(2,numberCharacterNoChecked)){
    if (millis() > timeCpt3 + arrowBullet->arrowSpeed) { 
      arrowBullet->go();
      timeCpt3 = millis(); 
    }
  }
  // Si la flèche ne peut plus avancer, la supprimer et réinitialiser les variables
  else if (!arrowBullet->canProgress(2,numberCharacterNoChecked)) {
    hero->numberOfArrow--; // décrémenter le nombre de flèches du héros
    hero->setFireFalse(); // indiquer que le héros n'est plus en train de tirer
    delete arrowBullet; // supprimer la flèche
    arrowBullet = nullptr; // réinitialiser le pointeur à null
    ongoing = false; // indiquer que le tir est terminé
  }
}

void Shot::equalShot(int numberCharacterNoChecked ){
  if (equalBullet== nullptr){
    equalBullet =  new EqualBullet(position->ary[hero->id][hero->number][0],position->ary[hero->id][hero->number][1], hero->direction,position );
  } 
  else if (equalBullet->canProgress(3,numberCharacterNoChecked)){
    if (millis() > timeCpt3 + equalBullet->equalSpeed) { 
      equalBullet->go();
      timeCpt3 = millis(); 
    }
  }
  else if (!equalBullet->canProgress(3,numberCharacterNoChecked)) {
    hero->numberOfEqual--; 
    hero->setFireFalse(); 
    delete equalBullet;
    equalBullet = nullptr;
    ongoing = false;  
  }
}
void Shot::minusShot(int numberCharacterNoChecked ){
  if (minusBullet== nullptr){
    minusBullet =  new MinusBullet(position->ary[hero->id][hero->number][0],position->ary[hero->id][hero->number][1], hero->direction,position );
  } 
  else if (minusBullet->canProgress(3,numberCharacterNoChecked)){
    if (millis() > timeCpt3 + minusBullet->minusSpeed) { 
      minusBullet->go();
      timeCpt3 = millis(); 
    }
  }
  else if (!minusBullet->canProgress(3,numberCharacterNoChecked)) {
    consequenciesMinus(); 
    hero->numberOfMinus--; 
    hero->setFireFalse(); 
    delete minusBullet;
    minusBullet = nullptr;
    ongoing = false;  
  }
}

void Shot::heroShot(){
 switch (typeOfMunition())
 {
 case 0:
  // Plus de munition 
  break;
 case 1:
  if (ongoing){
    arrowShot(0); 
  }
  break;
 case 2:
  if (ongoing){
    equalShot(0); 
  }
  break;
 case 3:
  if (ongoing){
    minusShot(0); 
  }
  break;
 }
}

void Shot::mechantShot(){
  if (mechant->getFire()&& mechant->numberOfMinus>0){
    if (bulletOfMechant== nullptr){
      bulletOfMechant =  new MinusBullet(position->ary[mechant->id][mechant->number][0],position->ary[mechant->id][mechant->number][1], mechant->direction,position );
    } 
    else if (bulletOfMechant->canProgress(3,1)){
      if (millis() > timeCpt4 + bulletOfMechant->minusSpeed) { 
        bulletOfMechant->go();
        timeCpt4 = millis(); 
      }
    }
    else if (!bulletOfMechant->canProgress(3,1)){
      
      switch (bulletOfMechant->element()){
        case 0: 
          hero->numberOfLife --;
            
          position->ary[hero->id][hero->number][0]=0;
          position->ary[hero->id][hero->number][1]=0;
          position->sizeXCpt = 0; 
          position->sizeYCpt = 0; 
          lcd.clear(); 

          for (int k =0 ; k < 12; k ++ ){
            for (int l = 0 ; l < position->numberOfEatchCaractere[k]; l ++ ){
              if (position->ary[k][l][0]>=position->sizeXCpt && position->ary[k][l][0]<= sizeScreenOnX+position->sizeXCpt &&position->ary[k][l][1]>=position->sizeYCpt && position->ary[k][l][1]<= sizeScreenOnY+position->sizeYCpt && position->ary[k][l][2]>0){
                display(k, position->ary[k][l][0], position->ary[k][l][1] );
              }
            }
          }
          break; 
        case 1: 
          display(bulletOfMechant->element(), bulletOfMechant->_x-position->sizeXCpt, bulletOfMechant->_y-position->sizeYCpt);
          for (int j = 0 ; j< position->numberOfEatchCaractere[1]; j++){
            if (bulletOfMechant->_x == position->ary[1][j][0]&& bulletOfMechant->_y == position->ary[1][j][1]){
              mechant->numberOfLife -- ;
            }
          }
          break; 
        case 2: 
          display(bulletOfMechant->element(), bulletOfMechant->_x-position->sizeXCpt, bulletOfMechant->_y-position->sizeYCpt);
          break; 
      }
      mechant->numberOfMinus--; 
      mechant->setFireFalse(); 
      delete bulletOfMechant;
      bulletOfMechant = nullptr; 
    }
  }
}
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

