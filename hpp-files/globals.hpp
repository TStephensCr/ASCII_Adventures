#define CHARACTER '@'
#define ENEMY '&'
#define MONEY '0'
#define SHOOT '-'
#define POWERUP 'H'
#define SPACE ' '
#define HORIZONTAL_WALL '='
#define VERTICAL_WALL '|'
#define FULLFILL_POINT '.'
#define FOLLOWER 'F'
#define PLAYERLIFES 3
#define X_PLAYERSPAWN 2
#define Y_PLAYERSPAWN 12
#define JUMPHEIGHT 12
#define NAPTIME 30
#define FOLLOWER_DELAY 40
#define KILL_ENEMYS_POINTS 20
#define KILL_FOLLOWER_POINTS 20
#define FOLLOWER_DAMAGE 20
#define FALL_DAMAGE 20
#define SHOOT_DAMAGE 20
#define PLAYER_ENEMY_COLLISION_DAMAGE 20
#define REPELLING_XFORCE_OF_ENEMYS 10
#define REPELLING_YFORCE_OF_ENEMYS -10
#define PLAYER_COLOR 1
#define ENEMY_COLOR 2
#define MONEY_COLOR 3
#define SHOOT_COLOR 4
#define POWERUP_COLOR 5
#define FOLLOWER_COLOR 6


enum EntityType { player, enemy, money, shoot, powerup, follower };

struct entita {
  EntityType type;
  MyPosition pos;
  int xForce = 0;
  int yForce = 0;
  bool death_flag = false;
  int mappa = -1;
  int livello = -1;
  entita* next;
};
typedef entita* ens;  // e = entit�, n = nello , s = spazio

struct Node{
    MyPosition element;
    Node* next;
    Node(MyPosition pos){
      element = pos;
      next = NULL;
    }     
};
typedef Node* node; 

struct Queue{
  node front, rear;
  int size;
  Queue(){ 
    front = rear = NULL;
    size = 0;
  }

  void enqueue(MyPosition pos){
    node temp = new Node(pos);
    size++;
    if(rear == NULL){
      front = rear = temp;
      return;
    }

    rear->next = temp;
    rear = temp;
  }

  MyPosition dequeue(){
    if(front == NULL){
      MyPosition tmp;
      return tmp; //return (-1,-1)
    }
      
    size--;
    node temp = front;
    front = front->next;

    if(front == NULL){
      rear = NULL;
    }

    return temp->element;
  }

  void clear(){
    front = rear = NULL;
    size = 0;
  }

  void initialize(int queueInitialLenght){
    MyPosition nullPos;
    for(int i = 0; i < queueInitialLenght; i++){
	    enqueue(nullPos);
    }
  }
};

enum GameStatus { MenU, Game };