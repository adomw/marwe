#include"support_lib.h"
#include<math.h>

class vector2d{//class for 2D vectors containing a pair of numbers; operations are based on complex numbers
private:
    double X, Y;
public:
    double x();
    double y();
    void reset();
    void setValue(double x, double y);
    bool zero();

    void operator = (const vector2d &a);
    vector2d operator + (const vector2d &a);
    vector2d operator + (const double &a);
    vector2d operator - (const vector2d &a);
    vector2d operator - (const double &a);
    vector2d operator * (const vector2d &a);
    vector2d operator * (const double &a);
    vector2d operator / (const double &a);
    //void addAngle(double a);

    double length();
    void even();
    //void addLength(double d);
    //void multiply(double d);

    void print();
    void example();
};

vector2d angle(double a);
