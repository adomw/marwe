//TEMPLATE WERSJA 14.08.2023

//co na razie dziala:
///przy pomocy WSADu mozna ruszac duzym testowym kolkiem XD oprocz tego wyswietla pierwsze pozadane obiekty klasy Stworzonko/Creature, acz w dziwnej formacji

//tryb 'ide z zarciem' tryb 'ide z surowcem' tryb 'ide PO cos (ale nie mam sciezki, szukam, zostawiam markery zeby inni bez sensu nie szukali w tym samym miejscu)', tryb 'ide do domu'?


#include<SFML/Graphics.hpp>
#include<stdio.h>
#include<math.h>
#include<iostream>
#include<vector>

///koncepocja jest taka zeby calosc sie rozgrywala niezaleznie od ekranu, "zaciec", lagow itp, zeby calosc dzialala bazujac o "ture" ktora bedzie bardzo krotka jednostka czasu (np. 10ms) i obraz bedzie jedynie reprezentacja wizualna tego, co sie dzieje, ukazujac te 100 "tur" na sekunde

bool isWithin(float x0, float x1, float x2){// czy x0 jest pomiedzy x1 i x2, wlacznie
    if(
       ((x0 <= x1) && (x0 >= x2)) ||
       ((x0 >= x1) && (x0 <= x2))
       )
        return true;
    else return false;
}

class KeyFlag{//Flagi wcisniecia wybranych klawiszy - przechowuja informacje o tym czy klawisz jest wcisniety czy nie (eventy SFML moga byc obslugiwane tylko pojedynczo, wiec nie czyta np. dwoch klawiszy wcisnietych "jednoczesnie")
private:
    bool ScrollUp;
    bool ScrollDown;

    bool Left, Right, Up, Down;
    bool W, S, A, D, Q, E;
    bool Num1, Num2, Num3, Num4, Num5;
    bool Plus, Minus;
    bool LControl, RControl, LAlt, RAlt, LShift, RShift;
    bool Escape, Backspace, Del;
    bool Enter, Space, Tab;
    bool F1, F2, F3, F4;

public:
    bool scrollUp(){return ScrollUp;}
    bool scrollDown(){return ScrollDown;}
    void setScrollUp(bool x){ScrollUp = x;}
    void setScrollDown(bool x){ScrollDown = x;}

    bool left(){return Left;}
    bool right(){return Right;}
    bool up(){return Up;}
    bool down(){return Down;}
    bool w(){return W;}
    bool s(){return S;}
    bool a(){return A;}
    bool d(){return D;}
    bool e(){return E;}
    bool q(){return Q;}
    bool num1(){return Num1;}
    bool num2(){return Num2;}
    bool num3(){return Num3;}
    bool num4(){return Num4;}
    bool num5(){return Num5;}
    bool plus(){return Plus;}
    bool minus(){return Minus;}
    bool lControl(){return LControl;}
    bool rControl(){return RControl;}
    bool lAlt(){return LAlt;}
    bool rAlt(){return RAlt;}
    bool lShift(){return LShift;}
    bool rShift(){return RShift;}
    bool escape(){return Escape;}
    bool backspace(){return Backspace;}
    bool del(){return Del;}
    bool enter(){return Enter;}
    bool space(){return Space;}
    bool tab(){return Tab;}
    bool f1(){return F1;}
    bool f2(){return F2;}
    bool f3(){return F3;}
    bool f4(){return F4;}
    /*
    bool (){return ;}
    */
    void setLeft(bool x){Left = x;}
    void setRight(bool x){Right = x;}
    void setUp(bool x){Up = x;}
    void setDown(bool x){Down = x;}
    void setW(bool x){W = x;}
    void setS(bool x){S = x;}
    void setA(bool x){A = x;}
    void setD(bool x){D = x;}
    void setE(bool x){E = x;}
    void setQ(bool x){Q = x;}
    void setNum1(bool x){Num1 = x;}
    void setNum2(bool x){Num2 = x;}
    void setNum3(bool x){Num3 = x;}
    void setNum4(bool x){Num4 = x;}
    void setNum5(bool x){Num5 = x;}
    void setPlus(bool x){Plus = x;}
    void setMinus(bool x){Minus = x;}
    void setLControl(bool x){LControl = x;}
    void setRControl(bool x){RControl = x;}
    void setLAlt(bool x){LAlt = x;}
    void setRAlt(bool x){RAlt = x;}
    void setLShift(bool x){LShift = x;}
    void setRShift(bool x){RShift = x;}
    void setEscape(bool x){Escape = x;}
    void setBackspace(bool x){Backspace = x;}
    void setDel(bool x){Del = x;}
    void setEnter(bool x){Enter = x;}
    void setSpace(bool x){Space = x;}
    void setTab(bool x){Tab = x;}
    void setF1(bool x){F1 = x;}
    void setF2(bool x){F2 = x;}
    void setF3(bool x){F3 = x;}
    void setF4(bool x){F4 = x;}
    /*
    void set(bool x){ = x;}
    */
    void reset(){
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

        ScrollUp = false;
        ScrollDown = false;

    }
};

class Creature{//Klasa zyjacego stworzonka
private:
    float X, Y;//obecne wspolrzedne
    float PlusX, PlusY;//to, ile zostanie dodane w tej turze, deltaX deltaY jakby
    float Angle;//kat wektora ruchu, 0 = "12" na zegarze, zgodnie z ruchem wskazowek zegara
    float V;//obecna predkosc
    const float Vmax = 1.0;//maksymalna predkosc
    int LastDrop;//liczba "tur", klatek symulacji, od ostatnio dropnietego sygnalu
    int Energy;//energia, uzupelniana jedzeniem i zmniejszana ruchem
    const float M = 2.0;//masa stworzenia, potrzebna by wyliczyc ped (fonetycznie "pend"); pozniej byc moze bedzie zmienna
    sf::CircleShape shape;
public:
    void updateShape(){//aktualizacja zmiennej graficznej SFML na podstawie parametrow tego obiektu
        shape.setRadius(M / 2);
        shape.setOutlineColor(sf::Color::Blue);
        shape.setOutlineThickness(1.2);
        shape.setPosition(X, Y);
    }
    void updateCoords(){//aktualizacja zmiennej graficznej SFML na podstawie parametrow tego obiektu
        shape.setPosition(X, Y);
    }
    void performMovement(bool w, bool s, bool a, bool d){//dokonanie akcji na podstawie wcisnietych klawiszy: wsad oczywiste, inne - podniesienie itema, opuszczenie itema, zostawianie markerow
        //if(w) <==> "jezeli w jest wcisniete", to...

        ///najpierw dokonaj ruchu na bazie zmiennych z poprzedniej tury
        PlusX = sin(Angle * M_PI / 180) * V;
        PlusY = -cos(Angle * M_PI / 180) * V;// Y jest z minusem, bo tutaj kat 0 to godizna "12" na zegarze, zas SFML liczy 0,0 od lewego gornego rogu (czyli w dol, nie do gory)

        ///W i S
        if(!(w || s)){//jezeli W ani S nie jest wcisniete, to powoli zmniejsz predkosc, ostatecznie do 0
            V -= 0.02;
            if(V < 0) V = 0.0;
        }
        else{//jezeli cos ze WS jest wcisniete
            if(w){
                if(!s){
                    //printf("%.2f, ", V);
                    V += 0.11;
                    //printf("%.2f\n", V);
                    if(V > Vmax) V = Vmax;
                }
                //jezeli oba W i S, to utrzymuj stabilna predkosc
            }
            else{//zostaje jedna opcja - S wcisniete, W nie
                V -= 0.2;
                if(V < 0) V = 0.0;
            }
        }
        ///A i D
        if(a != d){//lewo i prawo
            if(a){
                Angle -= 1.9;
                if(Angle < 0) Angle += 360;
            }
            else{
                Angle += 1.9;
                if(Angle > 360) Angle -= 360;
            }
        }
        //printf("v = %.2f; alpha = %.0f; [%.0f, %.0f]\n", V, Angle, X, Y);
    }
    /*void testoweUstawienie(int a, int b){
        X = 18.0 * a;
        Y = 15.0 * b;
        setShape();
    }*/
    sf::CircleShape* shapePointer(){//pointer na zmienna graficzna typu CircleShape reprezentujaca ten obiekt wizualnie
        return &shape;
    }

    void reset(){//reset
        for(int s = 0; s < 2137; s++) rand();//run pustych randomow zeby polepszyc seed losowosci
        while(rand() % 14) while(rand() % 16) X = rand() % 512 + 256;
        while(rand() % 14) while(rand() % 16) Y = rand() % 384 + 192;
        Angle = rand() % 3600;
        Angle *= 0.1;
        V = 0.0;
        LastDrop = 0;
        Energy = 10000;
        updateShape();
    }
    void turnYellow(){
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineColor(sf::Color::Yellow);
    }
    void resetMovementVectors(){
        PlusX = 0;
        PlusY = 0;
    }
    void addMovementVector(float x, float y){
        PlusX += x;
        PlusY += y;
    }
    void moveCreature(){
        X += PlusX;
        Y += PlusY;
    }
    float x(){
        return X;
    }
    float y(){
        return Y;
    }

};

class Obstacle{//Klasa przeszkody
private:
    float X1, Y1, X2, Y2, R;//wspolrzedne i grubosc (wlasciwie polowa grubosci) linii ktora jest zarazem promieniem okregow na koncach
    sf::CircleShape Circle1, Circle2;
    sf::RectangleShape Rectangle;
    float Angle;
public:
    void updateShape(){//aktualizacja zmiennych graficznych SFML na podstawie parametrow tego obiektu
        Circle1.setRadius(R);
        Circle1.setOrigin(R, R);
        Circle1.setPosition(X1, Y1);
        Circle1.setFillColor(sf::Color(127, 127, 127));
        Circle2.setRadius(R);
        Circle2.setOrigin(R, R);
        Circle2.setPosition(X2, Y2);
        Circle2.setFillColor(sf::Color(127, 127, 127));
        Rectangle.setSize(sf::Vector2f(sqrt(
                                            (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2)
                                            ), 2 * R));
        Rectangle.setOrigin(
                            sqrt(
                                            (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2)
                                            )

                             / 2, R);

        Rectangle.setRotation(
                                Angle
                                     );
        Rectangle.setPosition((X1 + X2) * 0.5, (Y1 + Y2) * 0.5);
        Rectangle.setFillColor(sf::Color(127, 127, 127));
    }
    void setParams(float x1, float y1, float x2, float y2, float r){
        X1 = x1;
        Y1 = y1;
        X2 = x2;
        Y2 = y2;
        R = r;
        Angle = 180.0 *
                                acos(
                                   (X2 - X1) *
                                    //(Y2 - Y1) / fabs(Y2 - Y1) //znak +/i
                                     ((Y2 - Y1) < 0 ? -1 : 1)
                                   / sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2))
                                   )
                                    / M_PI;
        updateShape();
    }
    sf::CircleShape* circle1Pointer(){//pointer na zmienna graficzna typu CircleShape reprezentujaca ten obiekt wizualnie
        return &Circle1;
    }
    sf::CircleShape* circle2Pointer(){//pointer na zmienna graficzna typu CircleShape reprezentujaca ten obiekt wizualnie
        return &Circle2;
    }
    sf::RectangleShape* rectanglePointer(){//pointer na zmienna graficzna typu CircleShape reprezentujaca ten obiekt wizualnie
        return &Rectangle;
    }

    /*void reset(){//reset
        for(int s = 0; s < 2137; s++) rand();//run pustych randomow zeby polepszyc seed losowosci
        updateShape();
    }*/
    bool baseWithin(float x, float y){//sprawdzenie czy punkt POTENCJALNIE MOZE SIE ZNAJDOWAC w tej przeszkodzie, a nie "czy sie znajduje"
        /*if(
           ((x > X1) && (x > X2))
           ||
           ((x < X1) && (x < X2))
           ) return false;// x nalezy do [X1; X2]
        else         if(
           ((y > Y1) && (y > Y2))
           ||
           ((y < Y1) && (y < Y2))
           ) return false;// y nalezy do [Y1; Y2]

        else return true;*/

        /// ^^^^ TA FUNKCJA JEST ZLE NAPISANA!!! MUSI UWZGLEDNIAC JESZCZE PROMIEN WYSTAJACY POZA KONTURY

        float minx = (X1 > X2 ? X2 : X1) - R;
        float maxx = (X1 < X2 ? X2 : X1) + R;
        float miny = (Y1 > Y2 ? Y2 : Y1) - R;
        float maxy = (Y1 < Y2 ? Y2 : Y1) + R;

        if(
           (x >= minx) &&
           (x <= maxx) &&
           (y >= miny) &&
           (y <= maxy)
           ) return true;
        else return false;

    }
    bool withinRectangle(float x, float y){
        //nie sprawdzam baseWithin, bo zakladamy ze jest basewithin, co sprawdzamy warunkiem w innej czesci kodu przed wywolaniem tej metody
        float a = Y2 - Y1;
        float b = X1 - X2;
        float c = - a * X1 - b * Y1;
        float d = fabs(a * x + b * y + c)
                    /
                    sqrt(a * a + b * b);
        float xd = (b * (b * x - a * y) - a * c)
                    /
                    (a * a + b * b);
        float yd = (a * (a * y - b * x) - b * c)
                    /
                    (a * a + b * b);
        if((d < R) && isWithin(xd, X1, X2) && isWithin(yd, Y1, Y2)) return true;
        else return false;

    }
    float distanceFromStraight(float x, float y){
        //nie sprawdzam baseWithin, bo zakladamy ze jest basewithin, co sprawdzamy warunkiem w innej czesci kodu przed wywolaniem tej metody
        float a = Y2 - Y1;
        float b = X1 - X2;
        float c = - a * X1 - b * Y1;
        float d = fabs(a * x + b * y + c)
                    /
                    sqrt(a * a + b * b);
        return d;

    }
    float angle(){
        return Angle;
    }

    float r(){
        return R;
    }
};

class Food{//Klasa jedzonka
private:
    float X, Y;//wspolrzedne
    int Remaining;//ile zarcia pozostalo w tym obiekcie
    float R;//promien jedzonka, zmienny w zaleznosci od tego ile pozostalo - jest wazne zeby byl zmienna, po to aby mierzyc czy jest w zasiegu
    sf::CircleShape shape;//pozniej to zrobie na wskaznikach lepiej... na razie trzymam sie obecnej koncepcji, zeby cos pociagnac do konca
public:
    void updateShape(){
        R = 1.0 + sqrt(Remaining);
        shape.setRadius(R);
    }//aktualizacja parametrow ksztaltu
    void reset(){
        Remaining = 50;
    }
    sf::CircleShape* shapePointer(){
        return &shape;
    }
};

class Scent{//klasa zapachu, markery pozostawiane przez mrowki na ziemi
private:
    float X, Y;//wspolrzedne
    const float R = 2.5;//promien markera zapachu, pozniej byc moze bedzie zmienny
    int Type;//typy; 1 - marker drogi do jedzenia; 2 - marker; 3 - marker;
    int Power;//sila zapachu, zwieksza sie gdy stworzenie ja osobiscie zwiekszy, a zmniejsza wraz z czasem
    int UpdateDue;//ile czasu - jeszcze nwm czy milisekund czy "tur" - do nastepnego update'u tj. oslabienia
public:

};

class World{//Klasa pojedynczego obiektu bedacego swiatem programu
private:
    std::vector<Creature> creatureVector;//wektor przechowujacy stworzonka
    std::vector<Food> foodVector;
    std::vector<Obstacle> obstacleVector;
    std::vector<Scent> scentVector;
    int W, H;
public:
    std::vector<Creature>* creaturePointer(){
        return &creatureVector;
    };
    std::vector<Food>* foodPointer(){
        return &foodVector;
    };
    std::vector<Obstacle>* obstaclePointer(){
        return &obstacleVector;
    };
    std::vector<Scent>* scentPointer(){
        return &scentVector;
    };
    void reset(int w, int h){//stworzenie X obiektow i wlozenie ich do wektora
        W = w;
        H = h;
        Creature c;
        for(int i = 0; i < 256; i++)
        {
            c.reset();
            creatureVector.push_back(c);
        }
        Obstacle o;
        o.setParams(0, 0, 0, H, 5);obstacleVector.push_back(o);
        o.setParams(0, H, W, H, 5);obstacleVector.push_back(o);
        o.setParams(W, H, W, 0, 5);obstacleVector.push_back(o);
        o.setParams(W, 0, 0, 0, 5);obstacleVector.push_back(o);
        //o.setParams(500+21, 400+37, 100+21, 100+37, 8);obstacleVector.push_back(o);
        o.setParams(100+21, 100+37, 500+21, 400+37, 8);obstacleVector.push_back(o);
        o.setParams(600, 315, 400+21, 700+37, 8);obstacleVector.push_back(o);
        o.setParams(900, 200, 850, 40, 8);obstacleVector.push_back(o);
        o.setParams(255, 612, 911, 112, 8);obstacleVector.push_back(o);
    }
    void process(){
        for(auto obstacle : obstacleVector){
            for(auto &creature : creatureVector)
            if(obstacle.baseWithin(creature.x(), creature.y())){

                if(obstacle.withinRectangle(creature.x(), creature.y())){
                    float d = obstacle.r() - obstacle.distanceFromStraight(creature.x(), creature.y());
                    creature.addMovementVector(
                                               2 * d * cos(obstacle.angle()), 2 * d * sin(obstacle.angle())
                                               );
                }
                /*else if(obstacle.withinCircle1(creature.x(), creature.y())){
                    //ddd
                }
                else if(obstacle.withinCircle2(creature.x(), creature.y())){
                    //ddd
                }
                */
            }
        }

    }

};

class Zoom{//Klasa odpowiadajaca za zoom
private:
    int CurrentZoom; //aktualny poziom przyblizenia, zaczyna sie od 1
    int MaxZoom = 7; //maksymalny poziom przyblizenia
    float ZoomBase = 1.6; //proporcja miedzy kolejnymi poziomami przyblizenia
    sf::View View;
    int Width;
    int Height;
public:
    void reset(int w, int h){
        CurrentZoom = 1;
        Width = w;
        Height = h;
        updateView(w / 2, h / 2);
    }
    int currentZoom(){
        return CurrentZoom;
    }
    void updateView(float centerX, float centerY){
        float X2 = centerX;
        float Y2 = centerY;
        //view.reset(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
        float W2 = Width * powf(ZoomBase, 1 - CurrentZoom);
        float H2 = Height * powf(ZoomBase, 1 - CurrentZoom);
        if((X2 + W2 * 0.5) > Width) X2 = Width - W2 * 0.5;
        else if((X2 - W2 * 0.5) < 0) X2 = W2 * 0.5;
        if((Y2 + H2 * 0.5) > Height) Y2 = Height - H2 * 0.5;
        else if((Y2 - H2 * 0.5) < 0) Y2 = H2 * 0.5;
        View.setCenter(sf::Vector2f(
                                    //Width * powf(ZoomBase, 1 - CurrentZoom) * 0.5,
                                    //Height * powf(ZoomBase, 1 - CurrentZoom) * 0.5
                                    X2,
                                    Y2
                                    ));
        View.setSize(sf::Vector2f(
                                  W2,
                                  H2
                                  ));
    }
    void zoomIn(float centerX, float centerY){
        if(CurrentZoom < MaxZoom) CurrentZoom++;
        updateView(centerX, centerY);
    }
    void zoomOut(float centerX, float centerY){
        if(CurrentZoom > 1) CurrentZoom--;
        updateView(centerX, centerY);
    }
    sf::View* view(){
        return &View;
    }
};

int main()
{
    srand(time(NULL));//seed do randomowych liczb
    for(int i = 0; i < 2137; i++) rand();

    short int CURR_WIDTH = 1024;//deklaracja rozmarow okna
    short int CURR_HEIGHT = 768;

    World world;//deklaracja swiata
    world.reset(CURR_WIDTH, CURR_HEIGHT);

    KeyFlag keyFlag;//moja autorska klasa ustawiajaca zerojedynkowo czy dane przyciski sa wcisniete - bo eventy klas event w sfml moga byc obslugiwane tylko pojedynczo (nie da sie odczytac np. Alt+cos)
    keyFlag.reset();

    sf::Clock zegar;//deklaracja zegara
    sf::Time czas;

    sf::ContextSettings windowSettings;//deklaracja ustawien okna i deklaracja okna z tymi ustawieniami
    windowSettings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(CURR_WIDTH, CURR_HEIGHT), "Marwë 0.3", sf::Style::Default, windowSettings);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/1._FC_Magdeburg.png");
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::RectangleShape backgroundShadow;
    backgroundShadow.setFillColor(sf::Color(0, 0, 0, 192));
    backgroundShadow.setSize(sf::Vector2f(CURR_WIDTH, CURR_HEIGHT));
    backgroundShadow.setPosition(0, 0);

    Zoom zoom;//moja klasa odpowiadajaca za zoom
    zoom.reset(CURR_WIDTH, CURR_HEIGHT);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) //obsluga eventow - gola obsluga eventow, tj. interakcji inputu (klikniec, klawiatury itp) z programem
        {
            //KRZYZYK ZAMYKAJACY
            if (event.type == sf::Event::Closed)
                window.close();
            //PRZYCISK WCISNIETY
            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code){
                case sf::Keyboard::Left:
                    keyFlag.setLeft(true);
                    break;
                case sf::Keyboard::Right:
                    keyFlag.setRight(true);
                    break;
                case sf::Keyboard::Up:
                    keyFlag.setUp(true);
                    break;
                case sf::Keyboard::Down:
                    keyFlag.setDown(true);
                    break;
                case sf::Keyboard::W:
                    keyFlag.setW(true);
                    break;
                case sf::Keyboard::S:
                    keyFlag.setS(true);
                    break;
                case sf::Keyboard::A:
                    keyFlag.setA(true);
                    break;
                case sf::Keyboard::D:
                    keyFlag.setD(true);
                    break;
                case sf::Keyboard::E:
                    keyFlag.setE(true);
                    break;
                case sf::Keyboard::Q:
                    keyFlag.setQ(true);
                    break;
                case sf::Keyboard::Num1:
                    keyFlag.setNum1(true);
                    break;
                case sf::Keyboard::Num2:
                    keyFlag.setNum2(true);
                    break;
                case sf::Keyboard::Num3:
                    keyFlag.setNum3(true);
                    break;
                case sf::Keyboard::Num4:
                    keyFlag.setNum4(true);
                    break;
                case sf::Keyboard::Num5:
                    keyFlag.setNum5(true);
                    break;
                case sf::Keyboard::Add:
                    keyFlag.setPlus(true);
                    break;
                case sf::Keyboard::Subtract:
                    keyFlag.setMinus(true);
                    break;
                case sf::Keyboard::LControl:
                    keyFlag.setLControl(true);
                    break;
                case sf::Keyboard::RControl:
                    keyFlag.setRControl(true);
                    break;
                case sf::Keyboard::LAlt:
                    keyFlag.setLAlt(true);
                    break;
                case sf::Keyboard::RAlt:
                    keyFlag.setRAlt(true);
                    break;
                case sf::Keyboard::LShift:
                    keyFlag.setLShift(true);
                    break;
                case sf::Keyboard::RShift:
                    keyFlag.setRShift(true);
                    break;
                case sf::Keyboard::Escape:
                    keyFlag.setEscape(true);
                    break;
                case sf::Keyboard::Backspace:
                    keyFlag.setBackspace(true);
                    break;
                case sf::Keyboard::Delete:
                    keyFlag.setDel(true);
                    break;
                case sf::Keyboard::Return:
                    keyFlag.setEnter(true);
                    break;
                case sf::Keyboard::Space:
                    keyFlag.setSpace(true);
                    break;
                case sf::Keyboard::Tab:
                    keyFlag.setTab(true);
                    break;
                case sf::Keyboard::F1:
                    keyFlag.setF1(true);
                    break;
                case sf::Keyboard::F2:
                    keyFlag.setF2(true);
                    break;
                case sf::Keyboard::F3:
                    keyFlag.setF3(true);
                    break;
                case sf::Keyboard::F4:
                    keyFlag.setF4(true);
                    break;
                default:
                    break;
                }
            }
            //MYSZ POCZATEK
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta == 1)
                    keyFlag.setScrollUp(true);
                else
                    keyFlag.setScrollDown(true);

            }
            //MYSZ KONIEC


            //PRZYCISK PUSZCZONY
            if (event.type == sf::Event::KeyReleased)
            {
                switch(event.key.code){
                /*case sf::Keyboard::A:
                    std::cout << "the A key was released" << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;
                    break;*/
                case sf::Keyboard::Left:
                    keyFlag.setLeft(false);
                    break;
                case sf::Keyboard::Right:
                    keyFlag.setRight(false);
                    break;
                case sf::Keyboard::Up:
                    keyFlag.setUp(false);
                    break;
                case sf::Keyboard::Down:
                    keyFlag.setDown(false);
                    break;
                case sf::Keyboard::W:
                    keyFlag.setW(false);
                    break;
                case sf::Keyboard::S:
                    keyFlag.setS(false);
                    break;
                case sf::Keyboard::A:
                    keyFlag.setA(false);
                    break;
                case sf::Keyboard::D:
                    keyFlag.setD(false);
                    break;
                case sf::Keyboard::E:
                    keyFlag.setE(false);
                    break;
                case sf::Keyboard::Q:
                    keyFlag.setQ(false);
                    break;
                case sf::Keyboard::Num1:
                    keyFlag.setNum1(false);
                    break;
                case sf::Keyboard::Num2:
                    keyFlag.setNum2(false);
                    break;
                case sf::Keyboard::Num3:
                    keyFlag.setNum3(false);
                    break;
                case sf::Keyboard::Num4:
                    keyFlag.setNum4(false);
                    break;
                case sf::Keyboard::Num5:
                    keyFlag.setNum5(false);
                    break;
                case sf::Keyboard::Add:
                    keyFlag.setPlus(false);
                    break;
                case sf::Keyboard::Subtract:
                    keyFlag.setMinus(false);
                    break;
                case sf::Keyboard::LControl:
                    keyFlag.setLControl(false);
                    break;
                case sf::Keyboard::RControl:
                    keyFlag.setRControl(false);
                    break;
                case sf::Keyboard::LAlt:
                    keyFlag.setLAlt(false);
                    break;
                case sf::Keyboard::RAlt:
                    keyFlag.setRAlt(false);
                    break;
                case sf::Keyboard::LShift:
                    keyFlag.setLShift(false);
                    break;
                case sf::Keyboard::RShift:
                    keyFlag.setRShift(false);
                    break;
                case sf::Keyboard::Escape:
                    keyFlag.setEscape(false);
                    break;
                case sf::Keyboard::Backspace:
                    keyFlag.setBackspace(false);
                    break;
                case sf::Keyboard::Delete:
                    keyFlag.setDel(false);
                    break;
                case sf::Keyboard::Return:
                    keyFlag.setEnter(false);
                    break;
                case sf::Keyboard::Space:
                    keyFlag.setSpace(false);
                    break;
                case sf::Keyboard::Tab:
                    keyFlag.setTab(false);
                    break;
                case sf::Keyboard::F1:
                    keyFlag.setF1(false);
                    break;
                case sf::Keyboard::F2:
                    keyFlag.setF2(false);
                    break;
                case sf::Keyboard::F3:
                    keyFlag.setF3(false);
                    break;
                case sf::Keyboard::F4:
                    keyFlag.setF4(false);
                    break;
                default:
                    break;
                }
            }
        }
        //koniec obslugi eventow


        //WYSWIETLANIE WSZYSTKIEGO
        //I PRZESUWANIE WSZYSTKIEGO
        czas = zegar.getElapsedTime();//obsluga zegara, tj. ile uplynelo czasu od ostatniego update'u ekranu
        if(czas.asMilliseconds() > 17){//jezeli uplynelo juz X milisekund, to jazda, jedziemy dalej. a jezeli nie, to pozwalamy SFML ominac dzialania az uplynie (chodzi o to zeby szybkosc nie byla uzalezniona od ilosci elementow, a co najwyzej z jednej strony - jezeli bedzie odpowiednio za duzo, to wiadomo ze spowolni)




            zegar.restart();//reset zegara
            window.clear();//czyszczenie okna

            window.draw(backgroundSprite);
            window.draw(backgroundShadow);


                sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
                sf::Vector2f relativeMouseCoords = window.mapPixelToCoords(mouseCoords);


                if(keyFlag.scrollDown() || keyFlag.minus()){
                    zoom.zoomOut(relativeMouseCoords.x, relativeMouseCoords.y);
                    keyFlag.setScrollUp(false);
                    keyFlag.setScrollDown(false);
                    keyFlag.setMinus(false);
                }
                if(keyFlag.scrollUp() || keyFlag.plus()){
                    zoom.zoomIn(relativeMouseCoords.x, relativeMouseCoords.y);
                    keyFlag.setScrollUp(false);
                    keyFlag.setScrollDown(false);
                    keyFlag.setPlus(false);
                }




                window.setView(*zoom.view());

///OBSLUGA MROWEK

                int LLL = 0;
                for(auto &creature: *world.creaturePointer()){//comment from forum: You need to reference the vector's object with a pointer, otherwise you're just modifying a local copy. -> for (auto &i : vec) {...}
                    creature.resetMovementVectors();
                    if(LLL == 0) {
                                creature.performMovement(
                                               keyFlag.w() || keyFlag.up(),
                                               keyFlag.s() || keyFlag.down(),
                                               keyFlag.a() || keyFlag.left(),
                                               keyFlag.d() || keyFlag.right()
                                               );
                                }
                    else
                    creature.performMovement(
                                  !(bool)(rand() % 4),
                                  !(bool)(rand() % 3),
                                  !(bool)(rand() % 2),
                                  !(bool)(rand() % 2)
                                  );

                    if(LLL == 0) creature.turnYellow();
                    LLL++;
                }
                world.process();
                for(auto &creature: *world.creaturePointer()){
                    creature.moveCreature();
                    creature.updateShape();
                }

///RYSOWANIE OBIEKTOW W OKNIE
                //rysowanie creatures

                for(auto obstacle: *world.obstaclePointer()){
                        window.draw(
                                    *obstacle.circle1Pointer()
                                    );
                        window.draw(
                                    *obstacle.circle2Pointer()
                                    );
                        window.draw(
                                    *obstacle.rectanglePointer()
                                    );
                }
                for(auto creature: *world.creaturePointer()){
                        window.draw(
                                    *creature.shapePointer()
                                    );
                }

                ///   !!! SFML Vertex !!!

///WYSWIETLENIE ZAWARTOSCI OKNA
                window.display();

        }
        //koniec if(czas >16ms)

    }
    //koniec while(window is open)

    return 0;

}
///KONIEC KODU


//comment from forum: You need to reference the vector's object with a pointer, otherwise you're just modifying a local copy. -> for (auto &i : vec) {...}

    //rozdzielczosc ekranu
    //printf("%dx%d\n", sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);


    /*sf::Font font;
    font.loadFromFile("images/arialbd.ttf");

    sf::Text text;*/




    /*sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineThickness(4);
    shape.setOutlineColor(sf::Color(255, 240, 0));
    shape.setPointCount(200);*/







                /*text.setPosition(300, 250);
                text.setFont(font);
                text.setString("precz z lewusem");
                text.setCharacterSize(24); // in pixels, not points!
                text.setFillColor(sf::Color::Red);
                text.setStyle(sf::Text::Underlined);
                //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
                window.draw(text);
                window.display();*/



/*

static Vector2i sf::Mouse::getPosition	(		)
static
Get the current position of the mouse in desktop coordinates.

This function returns the global position of the mouse cursor on the desktop.

Returns
Current position of the mouse
static Vector2i sf::Mouse::getPosition	(	const Window & 	relativeTo	)
static
Get the current position of the mouse in window coordinates.

This function returns the current position of the mouse cursor, relative to the given window.

Parameters
relativeTo	Reference window
Returns
Current position of the mouse

*/



                /*std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheel.y << std::endl;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
            }
            if (event.type == sf::Event::MouseEntered)
                std::cout << "the mouse cursor has entered the window" << std::endl;

            if (event.type == sf::Event::MouseLeft)
                std::cout << "the mouse cursor has left the window" << std::endl;
*/
