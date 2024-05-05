#include<stdio.h>
#include<math.h>
#include"support_lib.h"

int floorZero(int x){//the short code of this function is the best explanation in itself
    if(x < 0) return 0;
    else return x;
}
/*double deg(double a){//return arc measure of an angle based on the degree value, which is what c++ trigonometric functions take as their argument
    return a * M_PI / 180.0;
}*/
int random(int Size){//attempt to improve randomization, yet to be implemented
    return rand() % Size;
}

void Pair::printPair(){
    printf("Pair: %d, %d\n", x, y);
}
bool Pair::operator < (const Pair &a) const{
    if(x < a.x) return true;
    else if(x > a.x) return false;
    else if(y < a.y) return true;
    else return false;
}
