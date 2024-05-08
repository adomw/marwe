//a collection of minor functions of simple use, it's not worth making a separate library for each

const int OBJECTS = 1250;//number of objects
const int sizeOfArea = 15;//edge of area
const float MASS = 1.0;//creature's mass, needed to calculate momentum
const float Vmax = 3.5;//top speed
const int WIDTH = 1600;//...of the window
const int HEIGHT = 1000;//...of the window
const int USER_KEY = 9999;//9999;//key of the creature who is to be controlled by the user
const double OBSTACLE_MASS = 1.0;//Mass parameter of an obstacle
const int UPDATE_INERVAL = 5;//every $interval turns, the pointers are updated
const int POINTER_ARRAY_EDGE_X = 110;
const int POINTER_ARRAY_EDGE_Y = 80;
const float MAIN_BASE_RADIUS = 40.0;
const float MAIN_BASE_X = 1400.0;
const float MAIN_BASE_Y = 900.0;
const float OBSTACLE_FORCE_MODIFIER = 1.5;



int floorZero(int x);
//double deg(double a);
int random(int Size);

class Pair{
public:
    int x;
    int y;

    void printPair();
    bool operator < (const Pair &a) const;
};
