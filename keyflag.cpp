#include"keyflag.h"

//scroll
bool KeyFlag::scrollUp(){return ScrollUp;}
void KeyFlag::setScrollUp(bool x){ScrollUp = x;}

bool KeyFlag::scrollDown(){return ScrollDown;}
void KeyFlag::setScrollDown(bool x){ScrollDown = x;}

//arrows
bool KeyFlag::left(){return Left;}
void KeyFlag::setLeft(bool x){Left = x;}

bool KeyFlag::right(){return Right;}
void KeyFlag::setRight(bool x){Right = x;}

bool KeyFlag::up(){return Up;}
void KeyFlag::setUp(bool x){Up = x;}

bool KeyFlag::down(){return Down;}
void KeyFlag::setDown(bool x){Down = x;}

//wsadeq
bool KeyFlag::w(){return W;}
void KeyFlag::setW(bool x){W = x;}

bool KeyFlag::s(){return S;}
void KeyFlag::setS(bool x){S = x;}

bool KeyFlag::a(){return A;}
void KeyFlag::setA(bool x){A = x;}

bool KeyFlag::d(){return D;}
void KeyFlag::setD(bool x){D = x;}

bool KeyFlag::e(){return E;}
void KeyFlag::setE(bool x){E = x;}

bool KeyFlag::q(){return Q;}
void KeyFlag::setQ(bool x){Q = x;}

//num 1-5
bool KeyFlag::num1(){return Num1;}
void KeyFlag::setNum1(bool x){Num1 = x;}

bool KeyFlag::num2(){return Num2;}
void KeyFlag::setNum2(bool x){Num2 = x;}

bool KeyFlag::num3(){return Num3;}
void KeyFlag::setNum3(bool x){Num3 = x;}

bool KeyFlag::num4(){return Num4;}
void KeyFlag::setNum4(bool x){Num4 = x;}

bool KeyFlag::num5(){return Num5;}
void KeyFlag::setNum5(bool x){Num5 = x;}

//math operators
bool KeyFlag::plus(){return Plus;}
void KeyFlag::setPlus(bool x){Plus = x;}

bool KeyFlag::minus(){return Minus;}
void KeyFlag::setMinus(bool x){Minus = x;}

//ctrl, shift, alt
bool KeyFlag::lControl(){return LControl;}
void KeyFlag::setLControl(bool x){LControl = x;}

bool KeyFlag::rControl(){return RControl;}
void KeyFlag::setRControl(bool x){RControl = x;}

bool KeyFlag::lAlt(){return LAlt;}
void KeyFlag::setLAlt(bool x){LAlt = x;}

bool KeyFlag::rAlt(){return RAlt;}
void KeyFlag::setRAlt(bool x){RAlt = x;}

bool KeyFlag::lShift(){return LShift;}
void KeyFlag::setLShift(bool x){LShift = x;}

bool KeyFlag::rShift(){return RShift;}
void KeyFlag::setRShift(bool x){RShift = x;}

//system buttons
bool KeyFlag::escape(){return Escape;}
void KeyFlag::setEscape(bool x){Escape = x;}

bool KeyFlag::backspace(){return Backspace;}
void KeyFlag::setBackspace(bool x){Backspace = x;}

bool KeyFlag::del(){return Del;}
void KeyFlag::setDel(bool x){Del = x;}

bool KeyFlag::enter(){return Enter;}
void KeyFlag::setEnter(bool x){Enter = x;}

bool KeyFlag::space(){return Space;}
void KeyFlag::setSpace(bool x){Space = x;}

bool KeyFlag::tab(){return Tab;}
void KeyFlag::setTab(bool x){Tab = x;}

//function buttons 1-4
bool KeyFlag::f1(){return F1;}
void KeyFlag::setF1(bool x){F1 = x;}

bool KeyFlag::f2(){return F2;}
void KeyFlag::setF2(bool x){F2 = x;}

bool KeyFlag::f3(){return F3;}
void KeyFlag::setF3(bool x){F3 = x;}

bool KeyFlag::f4(){return F4;}
void KeyFlag::setF4(bool x){F4 = x;}

void KeyFlag::reset(){
    ScrollUp = false;
    ScrollDown = false;

    Left = false;
    Right = false;
    Up = false;
    Down = false;

    W = false;
    S = false;
    A = false;
    D = false;
    E = false;
    Q = false;

    Num1 = false;
    Num2 = false;
    Num3 = false;
    Num4 = false;
    Num5 = false;

    Plus = false;
    Minus = false;

    LControl = false;
    RControl = false;
    LAlt = false;
    RAlt = false;
    LShift = false;
    RShift = false;

    Escape = false;
    Backspace = false;
    Del = false;

    Enter = false;
    Space = false;
    Tab = false;

    F1 = false;
    F2 = false;
    F3 = false;
    F4 = false;
}

