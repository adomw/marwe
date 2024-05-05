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
void Creature::adjustSpeed(bool w, bool s, bool a, bool d){
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
                CurrentSpeed = CurrentSpeed * angle(-1.9);
            else
                CurrentSpeed = CurrentSpeed * angle(1.9);
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
void Creature::setSpeedAsForces(){
    if(Forces.length() != 0)
    CurrentSpeed = Forces * (CurrentSpeed.length() / Forces.length());
}
void Creature::updateDirection(){
    if(CurrentSpeed.length() != 0)
        Direction = CurrentSpeed / CurrentSpeed.length();
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
