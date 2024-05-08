#include"world.h"
//#include<cstdio>


void World::addToFoodMarker(int x, int y, float f){
    FoodMarker[x][y] += f;
}
void World::addToHomeMarker(int x, int y, float f){
    HomeMarker[x][y] += f;
}

float World::toFoodMarker(int x, int y){
    return FoodMarker[x][y];
}
float World::toHomeMarker(int x, int y){
    return HomeMarker[x][y];
}

void World::create(){
    Creature c;

    creatures.clear();
    for(int i = 0; i < OBJECTS; i++){
        /*
        bool isInsideObstacle = false;
        do{
            c.resetCreature(i);
            for(auto o : obstacles){
                if(1){
                    isInsideObstacle = true;//yet to be developed
                    break;
                }
            }
        }while(isInsideObstacle);//while c is inside any obstacle
        */

        c.resetCreature(i);

        creatures.push_back(c);
    }

    for(int i = 0; i < POINTER_ARRAY_EDGE_X; i++)
        for(int j = 0; j < POINTER_ARRAY_EDGE_Y; j++){
            HomeMarker[i][j] = 0.0;
            FoodMarker[i][j] = 0.0;
        }

}
void World::print(){
    for(auto &c : creatures)
        c.printEntity();
    for(auto c : nonEmptyAreas){
        c.printPair();
        //for(int i = 0; i < ; i++)
        printf("Creatures in this area: %d\n", creaturesInArea[c.x][c.y].size());
    }
}
void World::assignPointers(){//assigning objects to their proper squares
    Pair p;
    //clear all the creaturesInArea pointer vectors
    nonEmptyAreas.clear();
    //for(int i = 0; i < 100; i++)for(int j = 0; j < 100; j++)creaturesInArea[i][j].clear();
    for(int i = 0; i < POINTER_ARRAY_EDGE_X; i++)
        for(int j = 0; j < POINTER_ARRAY_EDGE_Y; j++)
            creaturesInArea[i][j].clear();

    for(auto creature : creatures){//assign creatures to containers
        p.x = creature.newAreaX();
        p.y = creature.newAreaY();
        creaturesInArea[p.x][p.y].insert(creature.key());
        nonEmptyAreas.insert(p);
    }
}
void World::updatePointers(
                           int key /*mod 0-9*/
                           ){//updates pointers and entities' area coords
    for(int i = 0; i < creatures.size(); i++){
    ///for(auto &creature : creatures){
        if( ((creatures[i].key() % UPDATE_INERVAL) == key) && creatures[i].areaChanged())
        {
            Pair alt, neu;//using German words as "new" is a C++ keyword
            alt.x = creatures[i].oldAreaX();
            alt.y = creatures[i].oldAreaY();
            neu.x = creatures[i].newAreaX();
            neu.y = creatures[i].newAreaY();
            /*printf("Alt: (%d, %d), Neu: (%d, %d)\n",
                   alt.x, alt.y, neu.x, neu.y
                   );*/
            int keyAux = creatures[i].key();

            //first, unassign creature from old area
            creaturesInArea[alt.x][alt.y].erase(keyAux);

            //then, if there are no more creatures in this area, indicate that fact in nonEmptyAreas
            if(creaturesInArea[alt.x][alt.y].empty())
                nonEmptyAreas.erase(alt);

            //then insert to new area
            creaturesInArea[neu.x][neu.y].insert(keyAux);
            nonEmptyAreas.insert(neu);

            creatures[i].setAreaCoordinates(neu.x, neu.y);

        }
    }



/*
    Pair p;//"new" p

    //for each creature, insert its pointer to the proper container

    for(auto creature : creatures){
        p.x = creature.areaX();
        p.y = creature.areaY();
        if(
           std::find(
                     creaturesInArea[p.x][p.y].begin(),
                     creaturesInArea[p.x][p.y].end(),
                     &creature
                     )
                    ==
                    creaturesInArea[p.x][p.y].end()
            )// if cannot find that element there already,
           creaturesInArea[p.x][p.y].push_back(&creature);
        nonEmptyAreas.insert(p);//it's a SET, so no need to check if it's already there or not.
        //Adding an element to a set which already contains it, doesn't change the set.
    }

    //now we need to REMOVE the pointers which are no longer correct

    //considering a given X,Y

    for(auto &p : nonEmptyAreas){
        printf("ASSERT 1 LOL\n");
        Pair p2;//p2 will represent a creature in its current state, so
        for(auto &c : creaturesInArea[p.x][p.y]){
            printf("ASSERT 2 LOL\n");
            p2.x = (*c).areaX();
            p2.y = (*c).areaY();printf("%d %d\n", p2.x, p2.y);
            if(
               (p2.x != p.x) ||
               (p2.y != p.y)
               )
                creaturesInArea[p.x][p.y].erase(
                                                std::find(
                                                          creaturesInArea[p.x][p.y].begin(),
                                                          creaturesInArea[p.x][p.y].end(),
                                                          c
                                                          )
                                                );
        }
        if(creaturesInArea[p.x][p.y].empty())
            nonEmptyAreas.erase(p);
    }
*/
}
void World::process(bool w, bool s, bool a, bool d){
    int Size = creatures.size();//Number of creatures
    ///printf("Size: %d\n", Size);

            /*printf("BB Speed: %.1f, %.1f\nBB Mass: %.1f\n",
                   creatures[0].currentSpeed().x(),
                   creatures[0].currentSpeed().y(),
                   creatures[0].mass()
                   );*/

    //update the direction of each creature
    for(int i = 0; i < Size; i++)
    //for(auto &creature : creatures)
        creatures[i].updateDirection();

    //clear the forces from the previous turn
    for(int i = 0; i < Size; i++)
    //for(auto &creature : creatures)
        creatures[i].clearForces();

    //apply creature against creature collision forces
    ///TU ZNAJDUJE SIE PROBLEM Z WEJSCIEM DO OBSZARU KOLUMNY 0. O DZIWO WIERSZA NIE, TYLKO KOLUMNY
    for(int i = 0; i < Size; i++){//for every creature
        Pair p, p2;
        p.x = creatures[i].newAreaX();
        p.y = creatures[i].newAreaY();

        for(int x = floorZero(p.x - 1); x <= (p.x + 1); x++) for(int y = floorZero(p.y - 1); y <= (p.y + 1); y++)
            ///^^for every square (of the maximum of 9) around this creature
            {
                //if(creatures[i].key() == 0) printf("P = (%d, %d)\n", x, y);
                for(auto j : creaturesInArea[x][y]){//for every OTHER creature in this area
                    //if(creatures[i].key() == 0) printf("i = %d, j = %d, size = %d\n", i, j, creaturesInArea[x][y].size());
                    if(i != j)
                    if(touching(creatures[i], creatures[j]))//if creature[i] and given creature in this area are touching
                    {
                        //i - stworzenie zrodlowe, ktore bedzie aplikowalo sile. j - stworzenie bedace celem, odbiorca sily od i
                        //if(i > j) printf("These are touching: %d, %d\n", creatures[i].key(), creatures[j].key());
                        //the touching determining is correct
                        /*creatures[j].addForce(creatures[i].momentum()
                                              * (-1)
                                              );*/
                        vector2d auxV;
                        auxV.setValue(creatures[i].x() - creatures[j].x(), creatures[i].y() - creatures[j].y());
                        auxV = auxV / auxV.length();//only the direction, vector's length = 1.0;
                        auxV = auxV * (creatures[i].radius() + creatures[j].radius() - auxV.length());
                        auxV = auxV * OBSTACLE_MASS;//obstacles should have larger mass than objects

                        creatures[j].addForce(auxV * (-1 / 10.0));//so that they don't bounce off each other too strongly


                    }//if(creatures[i].key() == 0) printf("ASSERT LOL\n");
                }
            }
    }

    //apply creature-against-obstacle forces
    for(int i = 0; i < Size; i++)
    {
        for(auto o : obstacles){
            double x1 = o.x();
            double y1 = o.y();

            double x2 = o.x2();
            double y2 = o.y2();

            double dx = o.x2() - o.x();//delta x of the obstacle's coords
            double dy = o.y2() - o.y();//delta y of the obstacle's coords

            double xa = creatures[i].x();//creature's coords
            double ya = creatures[i].y();

            double x0 = //point of crossing of the obstacle's line and the line perpendicular to it (which goes through the point A, which is the creature being considered)
                    (ya * dx  * dy + xa * dx * dx - y1 * dx * dy + x1 * dy * dy) /
                    (dy * dy + dx * dx);
            double y0 =
                    (y1 * dx  * dx + ya * dy * dy + xa * dx * dy - x1 * dx * dy) /
                    (dy * dy + dx * dx);

            double dist;
            vector2d auxV;//auxiliary vector

            dist = distance(x0, y0, xa, ya);//how far the creature is from the axis of the obstacle

            if(//if creature is in the rectangle
               (dist < (o.radius() + creatures[i].radius())) &&
                (((x0 >= x1) && (x0 <= x2)) || ((x0 <= x1) && (x0 >= x2))) &&
                (((y0 >= y1) && (y0 <= y2)) || ((y0 <= y1) && (y0 >= y2))) //if the point (x0, y0) is between P1 and P2
               ){
                //expel from rectangle
                //if(i == 0) printf("x, y: %.1f, %.1f\n", creatures[i].x(), creatures[i].y());
                auxV.setValue(xa - x0, ya - y0);
                auxV = auxV / auxV.length();//only the direction, vector's length = 1.0;
                auxV = auxV * (creatures[i].radius() + o.radius() - dist);
                auxV = auxV * OBSTACLE_MASS;//obstacles must have larger mass than objects

                creatures[i].addForce(auxV * OBSTACLE_FORCE_MODIFIER);
            }
            else{//if NOT in rectangle
                dist = distance(xa, ya, x1, y1);
                //if within circle1
                if(dist < (o.radius() + creatures[i].radius())){//if within circle1 of the obstacle
                    //expel from circle1
                    auxV.setValue(xa - x1, ya - y1);
                    auxV = auxV / auxV.length();//only the direction, vector's length = 1.0;
                    auxV = auxV * (creatures[i].radius() + o.radius() - dist);
                    auxV = auxV * OBSTACLE_MASS;//obstacles must have larger mass than objects

                    creatures[i].addForce(auxV * OBSTACLE_FORCE_MODIFIER);
                }
                else{//not in circle1
                    dist = distance(xa, ya, x2, y2);
                    if(dist < (o.radius() + creatures[i].radius())){
                        //expel from circle2
                        auxV.setValue(xa - x2, ya - y2);
                        auxV = auxV / auxV.length();//only the direction, vector's length = 1.0;
                        auxV = auxV * (creatures[i].radius() + o.radius() - dist);
                        auxV = auxV * OBSTACLE_MASS;//obstacles must have larger mass than objects

                        creatures[i].addForce(auxV * OBSTACLE_FORCE_MODIFIER);
                    }
                }//if NOT in circle1
            }//if NOT in rectangle
        //if((i == 0) && (o.key() == 4)) printf("P1 = (%.1f, %.1f), P2 = (%.1f, %.1f), Pa = (%.1f, %.1f), P0 = (%.1f, %.1f)\n", o.x(), o.y(), o.x2(), o.y2(), xa, ya, x0, y0);
        }//for each obstacle
    }//for each creature

    //apply each creature's momentum to their total forces pool
    for(int i = 0; i < Size; i++)
    //for(auto &creature : creatures)
        creatures[i].addMomentum();

    //after all forces have been considered, perform move based off them
    for(int i = 0; i < Size; i++)
    //for(auto &creature : creatures)//
        creatures[i].move();

    for(int i = 0; i < Size; i++){
    //for(auto &creature : creatures)//
        creatures[i].setSpeedAsForces();
        creatures[i].limitSpeed();
    }

    for(int i = 0; i < Size; i++){
        if(creatures[i].stance() == 1)
            HomeMarker
            [creatures[i].newAreaX()]
            [creatures[i].newAreaY()]
            += 1.0;
        else if(creatures[i].stance() == 2)
            FoodMarker
            [creatures[i].newAreaX()]
            [creatures[i].newAreaY()]
            += 1.0;
    }

    //apply movement algorithm
    for(int i = 0; i < Size; i++){
        creatures[i].calculateMovement();
    }

    //steer, for the next turn
    for(int i = 0; i < Size; i++){
    //for(auto &creature : creatures){
        ///printf("EEE KEY = %d\n", creatures[i].key());
        if(creatures[i].key() == USER_KEY){
            //printf("KEY = %d\n", creature.key());
            //printf("KEYS: = %d %d %d %d\n", w, s, a, d);
            creatures[i].adjustSpeed(w, s, a, d);
            ///creatures[i].printEntity();
            /*printf("Speed: %.1f, %1.f\n",
                   creatures[i].currentSpeed().x(),
                   creatures[i].currentSpeed().y()
                   );*/
            ///vector2d DDD = creatures[i].coordinates();
            //creature.currentSpeed().print();
            ///DDD.print();
        }
        else
            creatures[i].adjustSpeed(
                                     creatures[i].w(),
                                     creatures[i].s(),
                                     creatures[i].a(),
                                     creatures[i].d()
                                     /*(bool)random(8),
                                     (bool)random(2),
                                     (bool)random(2),
                                     (bool)random(2)*/
                                     //0,0,0,0
                                     );
        ///printf("------------\n");
    }


    //this goes at the end of processing
    //for(auto &creature : creatures){}
        /*creature.adjustSpeed(
                          //!(bool)(rand() % 4),
                          //!(bool)(rand() % 3),
                          //!(bool)(rand() % 2),
                          //!(bool)(rand() % 2)
                             0, 0, 0, 0
                                );*/

}
void World::allocateMemory(){
    creatures.reserve(OBJECTS);
    //for(int i = 0; i < 100; i++) for(int j = 0; j < 100; j++) creaturesInArea[i][j].reserve(20);
}

void World::updateMarkers(){//markers degrade over time
    for(int i = 0; i < POINTER_ARRAY_EDGE_X; i++)
        for(int j = 0; j < POINTER_ARRAY_EDGE_Y; j++){
            HomeMarker[i][j] = HomeMarker[i][j] - (HomeMarker[i][j] / 2000.0) - 0.001;
            if(HomeMarker[i][j] < 0) HomeMarker[i][j] = 0;
            FoodMarker[i][j] = FoodMarker[i][j] - (FoodMarker[i][j] / 2000.0) - 0.001;
            if(FoodMarker[i][j] < 0) FoodMarker[i][j] = 0;
        }
}

void World::updateSensors(){//for each creature, detect sensor values and pass them to the creature itself for further treatment
    for(int i = 0; i < creatures.size(); i++){
            //float LH = 0, MH = 0, RH = 0, LF = 0, MF = 0, RF = 0, LO = 0, MO = 0, RO = 0;
            float LH, MH, RH, LF, MF, RF, LO, MO, RO;
            vector2d p1, p2;
            int x1, x2, y1, y2;

            //if(i == USER_KEY) printf("Creature Coords: (%.2f, %.2f)\n", creatures[i].x(), creatures[i].y());

            //mid
            p1 = creatures[i].coordinates() + (creatures[i].direction() * 1.5 * creatures[i].radius());
            p2 = creatures[i].coordinates() + (creatures[i].direction() * 2.5 * creatures[i].radius());
            x1 = p1.x() / sizeOfArea; y1 = p1.y() / sizeOfArea;
            x2 = p2.x() / sizeOfArea; y2 = p2.y() / sizeOfArea;
            //if(i == USER_KEY) printf("Middle : (%.2f, %.2f), (%.2f, %.2f)\n", p1.x(), p1.y(), p2.x(), p2.y());
            MF = FoodMarker[x1][y1] + FoodMarker[x2][y2];
            MH = HomeMarker[x1][y1] + HomeMarker[x2][y2];
            MO = 0;

            //left
            p1 = creatures[i].coordinates() + (creatures[i].direction() * 1.5 * creatures[i].radius() * angle(-60));
            p2 = creatures[i].coordinates() + (creatures[i].direction() * 2.5 * creatures[i].radius() * angle(-60));
            x1 = p1.x() / sizeOfArea; y1 = p1.y() / sizeOfArea;
            x2 = p2.x() / sizeOfArea; y2 = p2.y() / sizeOfArea;
            //if(i == USER_KEY) printf("Left   : (%.2f, %.2f), (%.2f, %.2f)\n", p1.x(), p1.y(), p2.x(), p2.y());
            MF = FoodMarker[x1][y1] + FoodMarker[x2][y2];
            MH = HomeMarker[x1][y1] + HomeMarker[x2][y2];
            MO = 0;

            //right
            p1 = creatures[i].coordinates() + (creatures[i].direction() * 1.5 * creatures[i].radius() * angle(60));
            p2 = creatures[i].coordinates() + (creatures[i].direction() * 2.5 * creatures[i].radius() * angle(60));
            x1 = p1.x() / sizeOfArea; y1 = p1.y() / sizeOfArea;
            x2 = p2.x() / sizeOfArea; y2 = p2.y() / sizeOfArea;
            //if(i == USER_KEY) printf("Right  : (%.2f, %.2f), (%.2f, %.2f)\n", p1.x(), p1.y(), p2.x(), p2.y());
            MF = FoodMarker[x1][y1] + FoodMarker[x2][y2];
            MH = HomeMarker[x1][y1] + HomeMarker[x2][y2];
            MO = 0;

            creatures[i].assignSensorValues(LF, MF, RF, LH, MH, RH, LO, MO, RO);

            //system("pause");


            //MH +=

        }
}

std::vector<Creature> World::toCreatures(){
    return creatures;
}
std::vector<Resource> World::toResources(){
    return resources;
}
std::set<Pair> World::toAreas(){
    return nonEmptyAreas;
}
std::set<Obstacle> World::toObstacles(){
    return obstacles;
}

/*void World::adjustStances(){
    for(int i = 0; i < creatures.size(); i++)
        for(int j = 0; j < resources.size(); j++){
            if(creatures[i].stance() == 1)
                //if(touching)
                if(
                   (sqrt(resources[j].size()) + creatures[i].radius())
                   >=
                   sqrt(
                        ((resources[j].x() - creatures[i].x()) * (resources[j].x() - creatures[i].x())) +
                        ((resources[j].y() - creatures[i].y()) * (resources[j].y() - creatures[i].y()))
                        )
                   ){
                        creatures[i].setStance(2);
                        resources[j].decrease();
                        break;
                   };
            else if(creatures[i].stance() == 2)//this "else" is referring to the "if stance == 1", not "if touching"
                if(
                   (MAIN_BASE_RADIUS + creatures[i].radius())
                   >=
                   sqrt(
                        ((MAIN_BASE_X - creatures[i].x()) * (MAIN_BASE_X - creatures[i].x())) +
                        ((MAIN_BASE_Y - creatures[i].y()) * (MAIN_BASE_Y - creatures[i].y()))
                        )
                   ){
                        creatures[i].setStance(1);
                        //resources[j].decrease();
                        break;
                   };
        }
}*/

void World::adjustStances(){//if creatures reaches food or base, the stance changes
    for(int i = 0; i < creatures.size(); i++)
    {
        if(creatures[i].stance() == 1){
            for(int j = 0; j < resources.size(); j++)
                //if(touching)
                if(
                   (sqrt(resources[j].size()) + creatures[i].radius())
                   >=
                   sqrt(
                        ((resources[j].x() - creatures[i].x()) * (resources[j].x() - creatures[i].x())) +
                        ((resources[j].y() - creatures[i].y()) * (resources[j].y() - creatures[i].y()))
                        )
                   ){
                        creatures[i].setStance(2);
                        resources[j].decrease();
                        break;
                   }
        }

        else if(creatures[i].stance() == 2)//this "else" is referring to the "if stance == 1", not "if touching"
            if(
               (MAIN_BASE_RADIUS + creatures[i].radius())
               >=
               sqrt(
                    ((MAIN_BASE_X - creatures[i].x()) * (MAIN_BASE_X - creatures[i].x())) +
                    ((MAIN_BASE_Y - creatures[i].y()) * (MAIN_BASE_Y - creatures[i].y()))
                    )
               ){
                    creatures[i].setStance(1);
               }
    }
}

void World::addObstacle(double x1, double y1, double x2, double y2, double radius, int key){
    Obstacle o;
    o.setKey(key);
    o.setRadius(radius);
    o.setCoordinates(x1, y1, x2, y2);
    o.fixEnds();
    obstacles.insert(o);
}

void World::addResource(float x, float y, float s){
    Resource r;
    r.resetResource(x, y, s);
    resources.push_back(r);
}
