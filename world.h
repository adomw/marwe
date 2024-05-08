#include<vector>
#include<set>
#include<algorithm>
#include"entities.h"
//#include"support_lib.h"

class World{//Klasa pojedynczego obiektu bedacego swiatem programu
private:
    //vector Weather
    //std::vector<Creature> creaturesInArea[100][100];//2D tablica wskaznikow na zywe obiekty. int tylko jako placeholder. 100x100 jako tutalne maximum
    int W, H;
    std::vector<Creature> creatures;
    std::set<int> creaturesInArea[POINTER_ARRAY_EDGE_X][POINTER_ARRAY_EDGE_Y];//KEYS!
    std::set<Pair> nonEmptyAreas;
    std::set<Obstacle> obstacles;
    float FoodMarker[POINTER_ARRAY_EDGE_X][POINTER_ARRAY_EDGE_Y];
    float HomeMarker[POINTER_ARRAY_EDGE_X][POINTER_ARRAY_EDGE_Y];
    std::vector<Resource> resources;
public:
    void create();
    void print();
    void assignPointers();
    void updatePointers(int key);
    void process(bool w, bool s, bool a, bool d);
    std::vector<Creature> toCreatures();
    std::vector<Resource> toResources();
    std::set<Pair> toAreas();
    std::set<Obstacle> toObstacles();
    void addObstacle(double x1, double y1, double x2, double y2, double radius, int key);
    void addResource(float x, float y, float s);
    void allocateMemory();

    void updateMarkers();
    void adjustStances();
    void updateSensors();

    float toHomeMarker(int x, int y);
    float toFoodMarker(int x, int y);
    void addToFoodMarker(int x, int y, float f);
    void addToHomeMarker(int x, int y, float f);
};
