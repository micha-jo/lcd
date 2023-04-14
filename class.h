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

    long timeCpt; //pour les deplacement des mechant et du hero 
    long timeCpt2;  //pour les tirs du hero 
    long timeCpt3; //pour les tirs du mechant 
    long timeCpt4; //pour les tirs du mechant 

    Parametre(); 
    Parametre(int highLimite, int lowLimite, int sizeScreenOnX, int sizeScreenOny, int horizontale, int verticale, int bouton); 

    void initialisation(uint8_t *hero, uint8_t *mechant, uint8_t *obstacle, uint8_t *key, uint8_t *door, uint8_t *life,uint8_t *trap, uint8_t *arrow);
    
    void display(int id, int x, int y); 
    void notDisplay( int x, int y);
    
  protected: 
    
};


class Position: virtual public Parametre
{
  protected: 
    
     
  public:
    int ***ary = NULL; 
    int _numberOfEatchCaractere[12]; 

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
    void manualShift(); 
};


class Hero: public Parametre
{
  protected:
    Position *position;
    //déclaration des variables pour les appuis long 
    int _pressStart; 
    bool _buttonPressed ; 
    
  public:
    int id;
    int number;
    int heroSpeedOnX; 
    int heroSpeedOnY; 

    Hero(Position *position); 

    void setHeroSpeed(int speendOnX, int speedOnY); 

    bool boutonLeft(); 
    bool boutonRight(); 
    bool boutonTop(); 
    bool boutonBottom(); 
    bool boutonShortPress(); 
    bool specialMoveLeft(); 
    bool specialMoveRight (); 
    bool specialMoveTop();
    bool specialMoveBottom(); 
    bool boutonLongPress(); 
    
    void goLeft(); 
    void goRight(); 
    void goTop(); 
    void goBottom(); 
    void move(); 
};






#endif

