#ifndef CLASS_H
#define CLASS_H 


class Parametre
{
  public: 
    int highLimite; 
    int lowLimite; 
    int sizeScreenOnX; 
    int sizeScreenOnY;
    int horizontale; 
    int verticale; 
    int bouton;
     
  //initialisation des variables pour les  bouton 
  //appui unique 
  bool _stateButton;
  //appui long 
  bool _buttonPressed; 
  int _pressStart; 

    long timeCpt; //pour les deplacement des mechant et du hero 
    long timeCpt1; //saut du hero
    long timeCpt2;  //pour les tirs du hero 
    long timeCpt3; //pour les tirs du mechant 
    long timeCpt4; //pour les tirs du mechant 

    Parametre(); 
    Parametre(int highLimite, int lowLimite, int sizeScreenOnX, int sizeScreenOny, int horizontale, int verticale, int bouton); 

    void initialisation(uint8_t *hero, uint8_t *mechant, uint8_t *obstacle, uint8_t *key, uint8_t *door, uint8_t *life,uint8_t *trap, uint8_t *arrow);
    
    void display(int id, int x, int y); 
    void notDisplay( int x, int y);

    bool boutonLeft(); 
    bool boutonRight(); 
    bool boutonTop(); 
    bool boutonBottom(); 
    bool boutonMonostable(); 
    bool boutonShortPress(); 
    bool specialMoveLeft(); 
    bool specialMoveRight (); 
    bool specialMoveTop();
    bool specialMoveBottom(); 
    bool boutonLongPress(); 

    
  protected: 
    
};


class Position: virtual public Parametre
{
  protected: 
    
     
  public:
    int ***ary = NULL; 
    int numberOfEatchCaractere[12]; 

    int sizeX; 
    int sizeY; 
    int runningSpeed; 
    
    int sizeXCpt; 
    int sizeYCpt;
    
    Position(); 
    
    void setSize(int x, int y); 
    void setRunningSpeed(int runningSpeed); 

    void generatePosition(int numberOfHero, int numberOfmechant ,int numberOfObstacle, int numberOfKey, int numberOfDoor, int numberOfLife, int numberOfTrap, int numberOfArrow, int numberOfEqual, int numberOfMinus, int numberOfO, int numberOfStar); 
    void deletePosition(); 
    bool compareAll(int x, int y); 
    void typeZelda(); 
    void shiftToLeft (); 
    void shiftToRight (); 
    void shiftToTop (); 
    void shiftToBottom (); 
    void manualShift(int x, int y ); 
    void manualShiftBorder(); 
    void infinite(); 

    bool noCharacterLeft(int id , int number, int numberOfObstacle); 
    bool noCharacterRight(int id , int number, int numberOfObstacle); 
    bool noCharacterTwoRight(int id , int number, int numberOfObstacle); 
    bool noCharacterTop(int id , int number, int numberOfObstacle); 
    bool noCharacterBottom(int id , int number, int numberOfObstacle); 
    
};


class Hero: public Parametre
{
  protected:
    Position *position;
    
  public:
    int id;
    int number;

    int heroSpeedOnX; 
    int heroSpeedOnY; 
    int heroJumpSpeed; 
    int heroFireSpeed; 

    bool fire; 
    int direction; 

    int numberOfLife; 
    int numberOfMonster; 
    int numberOfKey; 
    int numberOfdoor; 
    int numberOfArrow; 
    int numberOfEqual;
    int numberOfMinus; 
    int numberOfCoin; 
    int numberOfLevel; 

    Hero(Position *position); 

    void setHeroSpeed(int speendOnX, int speedOnY);
    
    void goLeft(); 
    void goRight(); 
    void goTop(); 
    void goBottom(); 
    void moveLeftRight(); 
    void move(); 
    void jumpForward(bool (Hero::*callback)());
    void jumpForwardWithRequest(int request);
    void jump(bool (Hero::*callback)());
    void jumpWithRequest(int request);
    void pull(bool (Hero::*callback)());
    void pullWithRequest(int request);

    //reste a faire
    void protect(bool (Hero::*callback)());
    void protectedWithRequest(int request);
    void kick(bool (Hero::*callback)());
    void kickWithRequest(int request);

    void interaction(); 
    void concequencies(); 
};


class Mechant: public Parametre
{
  protected:
    Position *position;
    
  public:
    Mechant **arrayOfMechants;

    int id;
    int number;

    int mechantSpeedOnX; 
    int mechantSpeedOnY; 
    int mechantJumpSpeed; 
    int mechantFireSpeed; 

    bool fire; 
    int direction; 
    
    Mechant(Position *position); 
    Mechant(Position *position, int number); 
    void createMechant(); 
    void allMechant(void (Mechant::*callback)()); 
};


class SecondaryScreen: virtual public Parametre
{
  protected: 
    Hero *hero;
  public: 
    SecondaryScreen(Hero *hero);
    void displaySecondaryScreen(int i);  
}; 






#endif

