#include<math.h>
#include<stdio.h>
//#include"support_lib.h"
#include"vector2d.h"

vector2d angle(double a){
    vector2d v;
    v.setValue(cos(a * M_PI / 180.0), sin(a * M_PI / 180.0));
    return v;
}
double vector2d::x(){
    return X;
}
double vector2d::y(){
    return Y;
}
void vector2d::reset(){
    X = 0.0;
    Y = 0.0;
}
void vector2d::setValue(double x, double y){
    X = x;
    Y = y;
}
bool vector2d::zero(){
    if((X == 0) && (Y == 0))
        return true;
    else
        return false;
}

void vector2d::operator = (const vector2d &a){
    X = a.X;
    Y = a.Y;
}
vector2d vector2d::operator + (const vector2d &a){
    vector2d b;
    b.X = X + a.X;
    b.Y = Y + a.Y;
    return b;
}
vector2d vector2d::operator + (const double &a){
    vector2d b;
    if(zero()){
        b.X = a;
        b.Y = 0;
        b = b * angle(random(3600) / 10.0);
    }
    else{
        b.X = X;
        b.Y = Y;
        b = b * (
                 (length() + a) / length()
                 );
    }
    return b;
}
vector2d vector2d::operator - (const vector2d &a){
    vector2d b;
    b.X = X - a.X;
    b.Y = Y - a.Y;
    return b;
}
vector2d vector2d::operator - (const double &a){
    vector2d b;
    b.X = X;
    b.Y = Y;
    if(length() > 0){
        if(a > length()){
            b.X = 0;
            b.Y = 0;
        }
        else
            b = b + ((-1) * a);
    }
    return b;
}
vector2d vector2d::operator * (const vector2d &a){
    vector2d b;
    b.X = X * a.X - Y * a.Y;
    b.Y = Y * a.X + X * a.Y;
    return b;
}
vector2d vector2d::operator * (const double &a){
    vector2d b;
    b.X = X * a;
    b.Y = Y * a;
    return b;
}
vector2d vector2d::operator / (const double &a){
    vector2d b;
    b.X = X / a;
    b.Y = Y / a;
    return b;
}
/*void vector2d::addAngle(double a){
    vector2d v1, v2, v3;
    v1.setValue(X, Y);
    v2.setValue(cos(deg(a)), sin(deg(a)));
    v3 = v1 * v2;
    X = v3.x();
    Y = v3.y();
}*/

double vector2d::length(){
    return sqrt((X * X) + (Y * Y));
}
void vector2d::even(){
    if(length() < Vmax){
        vector2d b;
        b.setValue(X, Y);
        b = b * (1.0 * Vmax / length());
        X = b.x();
        Y = b.y();
    }

}
/*void vector2d::addLength(double d){
    if(length() != 0){
        X *= (length() + d) / length();
        Y *= (length() + d) / length();
    }
    else{
        double a = M_PI * random(360) / 180.0;
        X = d * cos(a);
        Y = d * sin(a);
    }
}*/

void vector2d::print(){
    printf("(%.2f, %.2f)\n", X, Y);
}
void vector2d::example(){
    vector2d a, b, c, d, e, f;
    a.setValue(3, 4);
    b.setValue(-3, 3);
    c.setValue(5, -1);
    d = a + b + c;
    e = a * c;
    f = a;
    f = f * 90;
    a.print();
    b.print();
    c.print();
    d.print();
    e.print();
    f.print();
}
