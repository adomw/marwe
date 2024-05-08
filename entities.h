#include"vector2d.h"
#include"sensor_data.h"
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
    bool W, S, A, D;
    int Stance;//1- looking for food, 2- looking for home
    DataSet Sensors;
public:
    vector2d currentSpeed();
    void adjustSpeed(bool w, bool s, bool a, bool d);

    vector2d forces();
    void clearForces();
    void addForce(vector2d f);

    vector2d direction();
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
    void setStance(int s);
    void resetCreature(int key);

    void calculateMovement();

    bool w();
    bool s();
    bool a();
    bool d();
    void assignSensorValues(
                            float LF, float MF, float RF,
                            float LH, float MH, float RH,
                            float LO, float MO, float RO
                            );
};

class Resource : public Entity{
private:
    int Type;// 1 - food, 2 - building material
    int Size;
public:
    int size();
    void setSize(int s);
    void decrease();
    void resetResource(float x, float y, int S);
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
