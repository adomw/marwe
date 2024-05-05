class KeyFlag{//Flagi wcisniecia wybranych klawiszy - przechowuja informacje o tym czy klawisz jest wcisniety czy nie (eventy SFML moga byc obslugiwane tylko pojedynczo, wiec nie czyta np. dwoch klawiszy wcisnietych "jednoczesnie")
protected:
    bool ScrollUp, ScrollDown;
    bool Left, Right, Up, Down;
    bool W, S, A, D, Q, E;
    bool Num1, Num2, Num3, Num4, Num5;

    bool Plus, Minus;
    bool LControl, RControl, LAlt, RAlt, LShift, RShift;
    bool Escape, Backspace, Del;
    bool Enter, Space, Tab;
    bool F1, F2, F3, F4;

public:
    //scroll
    bool scrollUp();
    void setScrollUp(bool x);

    bool scrollDown();
    void setScrollDown(bool x);

    //arrows
    bool left();
    void setLeft(bool x);

    bool right();
    void setRight(bool x);

    bool up();
    void setUp(bool x);

    bool down();
    void setDown(bool x);

    //wsadeq
    bool w();
    void setW(bool x);

    bool s();
    void setS(bool x);

    bool a();
    void setA(bool x);

    bool d();
    void setD(bool x);

    bool e();
    void setE(bool x);

    bool q();
    void setQ(bool x);

    //num 1-5
    bool num1();
    void setNum1(bool x);

    bool num2();
    void setNum2(bool x);

    bool num3();
    void setNum3(bool x);

    bool num4();
    void setNum4(bool x);

    bool num5();
    void setNum5(bool x);

    //math operators
    bool plus();
    void setPlus(bool x);

    bool minus();
    void setMinus(bool x);

    //ctrl, shift, alt
    bool lControl();
    void setLControl(bool x);

    bool rControl();
    void setRControl(bool x);

    bool lAlt();
    void setLAlt(bool x);

    bool rAlt();
    void setRAlt(bool x);

    bool lShift();
    void setLShift(bool x);

    bool rShift();
    void setRShift(bool x);

    //system buttons
    bool escape();
    void setEscape(bool x);

    void setBackspace(bool x);
    bool backspace();

    void setDel(bool x);
    bool del();

    void setEnter(bool x);
    bool enter();

    void setSpace(bool x);
    bool space();

    void setTab(bool x);
    bool tab();

    //function buttons 1-4
    bool f1();
    void setF1(bool x);

    bool f2();
    void setF2(bool x);

    bool f3();
    void setF3(bool x);

    bool f4();
    void setF4(bool x);

    //reset all
    void reset();
};
