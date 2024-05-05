#include"vector2d.h"
//#include"support_lib.h"
#include<stdio.h>

class Entity{
private:
    Pair AreaCoordinates;
    double Radius;
    int Key;
public:
    vector2d Coordinates;
    vector2d coordinates();

    void resetEntity(int key);
    double x();
    double y();
    int oldAreaX();//these return the coords which craeture is currently assigned to, stored
    int oldAreaY();
    int newAreaX();//these return the coords which creature SHOULD be assigned to, calculated
    int newAreaY();
    void setCoordinates(double x, double y);

    bool areaChanged();
    int key();
    void setKey(int k);
    double radius();
    void setRadius(double r);
    void printEntity();
    void setAreaCoordinates(int x, int y);
    bool operator < (const Entity &a) const;
};

class Creature : public Entity{
private:
    vector2d CurrentSpeed;
    vector2d Forces;
    vector2d Direction;
    double Mass;
    int Stance;
public:
    vector2d currentSpeed();
    void adjustSpeed(bool w, bool s, bool a, bool d);

    vector2d forces();
    void clearForces();
    void addForce(vector2d f);
    void setDirection(double x, double y);
    void setDirection(double a);
    void updateDirection();

    vector2d momentum();
    void addMomentum();

    void move();
    void setSpeedAsForces();
    void limitSpeed();

    double mass();
    int stance();
    void resetCreature(int key);
};

class Resource : public Entity{
private:
    int Type;// 1 - food, 2 - building material
};
class Obstacle : public Entity{
private:
    vector2d Coordinates2;
public:
    vector2d coordinates2();
    double x2();
    double y2();
    void setCoordinates(double x1, double y1, double x2, double y2);
    void fixEnds();
};

double distance(Entity a, Entity b);
double distance(double x1, double y1, double x2, double y2);
bool touching(Entity a, Entity b);

//vector2d: coords, currentspeed, forces
//entities: creature, obstacle, food, resource, scent, weather
//stance: different for each type of entity
//^^^^^^: for creatures: "carrying food", "carrying resource", "searching" etc.
