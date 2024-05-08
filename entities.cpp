#include"entities.h"
#include<math.h>

///Auxiliary functions
double distance(Entity a, Entity b){
    return sqrt(
                ((a.x() - b.x()) * (a.x() - b.x())) +
                ((a.y() - b.y()) * (a.y() - b.y()))
                );
}
double distance(double x1, double y1, double x2, double y2){
    return sqrt(
                ((x1 - x2) * (x1 - x2)) +
                ((y1 - y2) * (y1 - y2))
                );
}
bool touching(Entity a, Entity b){
    if(
       (a.radius() + b.radius())
       >
       distance(a, b)
       )
        return true;
    else
        return false;
}

///Entity
void Entity::resetEntity(int key){
    Radius = 1.8;
    Key = key;
    /*Coordinates.setValue(
                         (random(1000) / 10.0) + 1080 + (random(5) * M_PI / 16.0) + (random(5) * M_E / 16.0),
                         (random(1000) / 10.0) + 680 + (random(5) * M_PI / 16.0) + (random(5) * M_E / 16.0)
                         );*/
    do{
            Coordinates.setValue(
                         (random(MAIN_BASE_RADIUS * 20) / 10.0) + MAIN_BASE_X - MAIN_BASE_RADIUS + (random(5) * M_PI / 16.0) - (random(5) * M_E / 16.0),
                         (random(MAIN_BASE_RADIUS * 20) / 10.0) + MAIN_BASE_Y - MAIN_BASE_RADIUS + (random(5) * M_PI / 16.0) - (random(5) * M_E / 16.0)
                         );
    }while(distance(MAIN_BASE_X, MAIN_BASE_Y, x(), y()) > MAIN_BASE_RADIUS);
}
double Entity::x(){
    return Coordinates.x();
}
double Entity::y(){
    return Coordinates.y();
}
int Entity::newAreaX(){
    return (int)(Coordinates.x() / sizeOfArea);
}
int Entity::newAreaY(){
    return (int)(Coordinates.y() / sizeOfArea);
}
int Entity::oldAreaX(){
    return AreaCoordinates.x;
}
int Entity::oldAreaY(){
    return AreaCoordinates.y;
}
void Entity::setCoordinates(double x, double y){
    Coordinates.setValue(x, y);
}

double Entity::radius(){
    return Radius;
}
void Entity::setRadius(double r){
    Radius = r;
}
vector2d Entity::coordinates(){
    return Coordinates;
}
void Entity::printEntity(){
    printf("Position: [%.2f, %.2f], Radius = %.2f\n", x(), y(), radius());
}

bool Entity::operator < (const Entity &a) const{
    if(Key < a.Key) return true;
    else return false;
}
void Entity::setAreaCoordinates(int x, int y){
    AreaCoordinates.x = x;
    AreaCoordinates.y = y;
}
bool Entity::areaChanged(){
    if(
       (newAreaX() != oldAreaX()) ||
       (newAreaY() != oldAreaY())
       )
        return true;
    else
        return false;
}
int Entity::key(){
    return Key;
}
void Entity::setKey(int key){
    Key = key;
}

///Creature
void Creature::resetCreature(int key){
    resetEntity(key);
    Mass = MASS;
    CurrentSpeed.reset();
    setAreaCoordinates(newAreaX(), newAreaY());
    setStance(1);

    vector2d dir;
    dir.setValue(1, 0);
    dir = dir * angle(random(3600) / 10.0);
    setDirection(dir.x(), dir.y());
}
vector2d Creature::currentSpeed(){
    return CurrentSpeed;
};
vector2d Creature::forces(){
    return Forces;
};
double Creature::mass(){
    return Mass;
};
int Creature::stance(){
    return Stance;
}

void Creature::clearForces(){
    Forces.reset();
}
vector2d Creature::direction(){
    return Direction;
}
void Creature::addMomentum(){
    Forces = Forces + momentum();
}
void Creature::move(){
    vector2d b;
    b = Forces / Mass;
    Coordinates = Coordinates + b;
    //CurrentSpeed = Forces * (1 / Mass);
}
vector2d Creature::momentum(){
    vector2d v;
    v = CurrentSpeed;
    v = v * Mass;
    return v;
}
void Creature::setDirection(double x, double y){
    Direction.setValue(x, y);
    if(Direction.length() != 0)
        Direction = Direction / Direction.length();
}
void Creature::setDirection(double a){
    Direction.setValue(1, 0);
    Direction = Direction * angle(a);
}
void Creature::adjustSpeed(bool w, bool s, bool a, bool d){//adjust speed and direction based on buttons pressed
        ///W i S
        if(!(w || s))//jezeli W ani S nie jest wcisniete, to powoli zmniejsz predkosc, ostatecznie do 0
            CurrentSpeed = CurrentSpeed - 0.02;
        else//jezeli cos ze WS jest wcisniete
            if(w)
                if(!s)//jesli jest to W, bez S
                    CurrentSpeed = CurrentSpeed + 0.07;
                else;
                //jezeli oba W i S, to utrzymuj stabilna predkosc
            else//zostaje jedna opcja - S wcisniete, W nie
                CurrentSpeed = CurrentSpeed - 0.2;
        ///A i D
        if(a != d)//lewo i prawo
            if(a)
                CurrentSpeed = CurrentSpeed * angle(-10.0);
            else
                CurrentSpeed = CurrentSpeed * angle(10.0);
        //a jezeli zadne nie wcisniete lub oba wcisniete, to nie skrecaj, proste

        //CurrentSpeed.even();
}
void Creature::limitSpeed(){
    if(CurrentSpeed.length() > Vmax)
        CurrentSpeed = CurrentSpeed * (Vmax / CurrentSpeed.length());
}
void Creature::addForce(vector2d f){
    Forces = Forces + f;
}
void Creature::assignSensorValues(
                        float LF, float MF, float RF,
                        float LH, float MH, float RH,
                        float LO, float MO, float RO
                        ){
    Sensors.assignValues(
                        LF, MF, RF,
                        LH, MH, RH,
                        LO, MO, RO
                         );
}
void Creature::setSpeedAsForces(){
    if(Forces.length() != 0)
    CurrentSpeed = Forces * (CurrentSpeed.length() / Forces.length());
}
void Creature::updateDirection(){
    if(CurrentSpeed.length() != 0)
        Direction = CurrentSpeed / CurrentSpeed.length();
}
void Creature::calculateMovement(){//based on sensors, decide on the next steps for the creature
    /*//dzialajaca calosc:
     W = (bool)random(9);
     S = !((bool)random(4));
     A = !((bool)random(3));
     D = !((bool)random(3));*/

     float aux = random(25);
     float FoodSensorSum = Sensors.LeftFoodMarkerSensor + Sensors.MiddleFoodMarkerSensor + Sensors.RightFoodMarkerSensor;
     float HomeSensorSum = Sensors.LeftHomeMarkerSensor + Sensors.MiddleHomeMarkerSensor + Sensors.RightHomeMarkerSensor;

     //if(key() == 213) printf("%f, %f\n", FoodSensorSum, HomeSensorSum);

     if(Stance == 1){
        if((aux == 0) || (FoodSensorSum == 0)){//if no food marker detected or else still 4% chance to do it: perform random movement
            W = (bool)random(12);
            S = !(bool)random(4);
            A = !(bool)random(5);
            D = !(bool)random(5);
        }else{ //food is detected, 96% chance to do so
            if((Sensors.MiddleFoodMarkerSensor > Sensors.RightFoodMarkerSensor) && (Sensors.MiddleFoodMarkerSensor > Sensors.LeftFoodMarkerSensor)){
                W = true;
                S = false;
                A = false;
                D = false;
            }else //mid is not the biggest
            if(Sensors.LeftFoodMarkerSensor == Sensors.RightFoodMarkerSensor){
                W = (bool)random(5);
                S = !(bool)random(3);
                A = (bool)random(2);
                D = !A;
            }else{ // mid is not highest and A,D are different
                W = (bool)random(3);
                S = false;
                A = false;
                D = false;
                if(Sensors.LeftFoodMarkerSensor > Sensors.RightFoodMarkerSensor)
                    A = true;
                else //if(Sensors.LeftFoodMarkerSensor < Sensors.RightFoodMarkerSensor)
                    D = true;
            }
        }
     }
    else if(Stance == 2){//going back home
        if((aux == 0) || (HomeSensorSum == 0)){//if no Home marker detected or else still 4% chance to do it: perform random movement
            W = (bool)random(12);
            S = !(bool)random(4);
            A = !(bool)random(5);
            D = !(bool)random(5);
        }else{ //Home is detected, 96% chance to do so
            if((Sensors.MiddleHomeMarkerSensor > Sensors.RightHomeMarkerSensor) && (Sensors.MiddleHomeMarkerSensor > Sensors.LeftHomeMarkerSensor)){
                W = true;
                S = false;
                A = false;
                D = false;
            }else //mid is not the biggest
            if(Sensors.LeftHomeMarkerSensor == Sensors.RightHomeMarkerSensor){
                W = (bool)random(5);
                S = !(bool)random(3);
                A = (bool)random(2);
                D = !A;
            }else{ // mid is not highest and A,D are different
                W = (bool)random(3);
                S = false;
                A = false;
                D = false;
                if(Sensors.LeftHomeMarkerSensor > Sensors.RightHomeMarkerSensor)
                    A = true;
                else //if(Sensors.LeftHomeMarkerSensor < Sensors.RightHomeMarkerSensor)
                    D = true;
            }
        }
    }


}
bool Creature::w(){
    return W;
}
bool Creature::s(){
    return S;
}
bool Creature::a(){
    return A;
}
bool Creature::d(){
    return D;
}
void Creature::setStance(int s){
    Stance = s;
}


///Obstacle
vector2d Obstacle::coordinates2(){
    return Coordinates2;
}
void Obstacle::setCoordinates(double x1, double y1, double x2, double y2){
    Coordinates.setValue(x1, y1);
    Coordinates2.setValue(x2, y2);
}
double Obstacle::x2(){
    return Coordinates2.x();
}
double Obstacle::y2(){
    return Coordinates2.y();
}
void Obstacle::fixEnds(){
    if(x() < x2()){
        vector2d temp = Coordinates;
        Coordinates = Coordinates2;
        Coordinates2 = temp;
    }
}

///Resource
int Resource::size(){
    return Size;
}
void Resource::setSize(int s){
    Size = s;
}
void Resource::decrease(){
    if(Size > 0)
        Size--;
}
void Resource::resetResource(float x, float y, int S){
    Coordinates.setValue(x, y);
    Size = S;
}
