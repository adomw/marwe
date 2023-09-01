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

class KeyFlag{//Flagi wcisniecia wybranych klawiszy - przechowuja informacje o tym czy klawisz jest wcisniety czy nie (eventy SFML moga byc obslugiwane tylko pojedynczo, wiec nie czyta np. dwoch klawiszy wcisnietych "jednoczesnie")
private:
    bool ScrollUp;
    bool ScrollDown;

    bool Left, Right, Up, Down;
    bool W, S, A, D, Q, E;
    bool Num1, Num2, Num3, Num4, Num5;
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
    float Angle;//kat wektora ruchu, 0 = "12" na zegarze, zgodnie z ruchem wskazowek zegara
    float V;//obecna predkosc
    const float Vmax = 1.0;
    int LastDrop;//liczba "tur", klatek symulacji, od ostatnio dropnietego sygnalu
    int Energy;//energia, uzupelniana jedzeniem i zmniejszana ruchem
    const float M = 2.0;//masa stworzenia, potrzebna by wyliczyc ped (fonetycznie "pend"); pozniej byc moze bedzie zmienna
    sf::CircleShape shape;//pozniej to zrobie na wskaznikach lepiej... na razie trzymam sie obecnej koncepcji, zeby cos pociagnac do konca
public:

    void updateParameters(float x, float y){//setter zmiennych obiektu, z zewnatrz
        X = x;
        Y = y;
    }
    void updateShape(){//aktualizacja zmiennej graficznej SFML na podstawie parametrow tego obiektu
        shape.setRadius(sqrt(M));
        shape.setOutlineColor(sf::Color::Blue);
        shape.setOutlineThickness(1.25);
        shape.setPosition(X, Y);
    }

    void move(bool w, bool s, bool a, bool d){//dokonanie akcji na podstawie wcisnietych klawiszy: wsad oczywiste, inne - podniesienie itema, opuszczenie itema, zostawianie markerow
        //if(w) <==> "jezeli w jest wcisniete", to...

        ///najpierw dokonaj ruchu na bazie zmiennych z poprzedniej tury
        X += sin(Angle) * V;
        Y -= cos(Angle) * V;// Y jest z minusem, bo tutaj kat 0 to godizna "12" na zegarze, zas SFML liczy 0,0 od lewego gornego rogu (czyli w dol, nie do gory)

        ///W i S
        if(!(w || s)){//jezeli W ani S nie jest wcisniete, to powoli zmniejsz predkosc, ostatecznie do 0
            V -= 0.03;
            if(V < 0) V = 0.0;
        }
        else{//jezeli cos ze WS jest wcisniete
            if(w){
                if(!s){
                    //printf("%.2f, ", V);
                    V += 0.12;
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
                Angle -= 1.7;
                if(Angle < 0) Angle += 360;
            }
            else{
                Angle += 1.7;
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
        X = rand() % 500 + 100;
        Y = rand() % 400 + 100;;
        Angle = rand() % 3600;
        Angle *= 0.1;
        V = 0.0;
        LastDrop = 0;
        Energy = 10000;
        updateShape();
    }

};
class Food{//Klasa jedzonka
private:
    float X, Y;//wspolrzedne
    int Remaining;//ile zarcia pozostalo w tym obiekcie
    float R;//promien jedzonka, zmienny w zaleznosci od tego ile pozostalo
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
    //std::vector<Obstacle> obstacle;
    std::vector<Scent> scentVector;
public:
    std::vector<Creature>* creaturePointer(){
        return &creatureVector;
    };
    std::vector<Food>* foodPointer(){
        return &foodVector;
    };
    //std::vector<Obstacle>* obstaclePointer;
    std::vector<Scent>* scentPointer(){
        return &scentVector;
    };
    /*void setTest(){
        srand(time(NULL));
        Creature c;
        int x, y;
        for(int i = 0; i < 100; i++)
        {
            x = rand() % 500 + 100;
            y = rand() % 400 + 100;
            c.updateParameters(x, y);
            c.updateShape();
            creatureVector.push_back(c);
        }
    }*/
    void reset(){//stworzenie X obiektow i wlozenie ich do wektora
        Creature c;
        for(int i = 0; i < 70; i++)
        {
            c.reset();
            creatureVector.push_back(c);
        }
    }
    void process(){
        //ddd
    }

};

class Zoom{//Klasa odpowiadajaca za zoom
private:
    int CurrentZoom; //aktualny poziom przyblizenia, zaczyna sie od 1
    int MaxZoom = 7; //maksymalny poziom przyblizenia
    float ZoomBase = 1.5; //proporcja miedzy kolejnymi poziomami przyblizenia
public:
    void reset(){CurrentZoom = 1;}
    int currentZoom(){return CurrentZoom;}
    void zoomIn(){if(CurrentZoom < MaxZoom) CurrentZoom++;printf("AktualnyZoom: %d\n", CurrentZoom);}
    void zoomOut(){if(CurrentZoom > 1) CurrentZoom--;printf("AktualnyZoom: %d\n", CurrentZoom);}
    bool isMax(){if(CurrentZoom == MaxZoom) return true; else return false;}
    bool isMin(){if(CurrentZoom == 1) return true; else return false;}
    float skaluj(float x){
        float f = x * 1.0f;
        for(int i = 1; i < CurrentZoom; i++) f /= ZoomBase;
        return f;
    }
};

int main()
{
    srand(time(NULL));//seed do randomowych liczb

    World world;//deklaracja swiata
    world.reset();

    short int CURR_WIDTH = 1024;//deklaracja rozmarow okna
    short int CURR_HEIGHT = 768;

    KeyFlag keyFlag;//moja autorska klasa ustawiajaca zerojedynkowo czy dane przyciski sa wcisniete - bo eventy klas event w sfml moga byc obslugiwane tylko pojedynczo (nie da sie odczytac np. Alt+cos)
    keyFlag.reset();

    sf::Clock zegar;//deklaracja zegara
    sf::Time czas;

    sf::ContextSettings windowSettings;//deklaracja ustawien okna i deklaracja okna z tymi ustawieniami
    windowSettings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(CURR_WIDTH, CURR_HEIGHT), "Marwë 0.2", sf::Style::Default, windowSettings);


    sf::View view(sf::FloatRect(0.f, 0.f, CURR_WIDTH, CURR_HEIGHT));

    Zoom zoom;//moja klasa odpowiadajaca za zoom
    zoom.reset();

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
                    //view.move(10.f, 10.f);
                    keyFlag.setScrollUp(true);

                else
                    keyFlag.setScrollDown(true);
                    //view.move(-10.f, -10.f);
                    //view.zoom(1.05f);

                std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheel.y << std::endl;
            }
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
        if(czas.asMilliseconds() > 16){//jezeli uplynelo juz 16 milisekund, to jazda, jedziemy dalej. a jezeli nie, to pozwalamy SFML ominac dzialania az uplynie

            zegar.restart();//reset zegara
            window.clear();//czyszczenie okna

                view.setCenter(sf::Vector2f(350.f, 300.f));//to jest view, klasa ulatwiajaca rzeczy takie jak zoomowanie i przesuwanie ekranu, ale na razie tylko istnieje zeby istniec



                if(keyFlag.scrollDown() == true){
                    if(!zoom.isMin())
                        view.zoom(powf(0.8f, zoom.currentZoom()));
                    zoom.zoomOut();
                    keyFlag.setScrollUp(false);
                    keyFlag.setScrollDown(false);
                }
                if(keyFlag.scrollUp() == true){
                    if(!zoom.isMax())
                        view.zoom(powf(1.25f, zoom.currentZoom()));
                    zoom.zoomIn();
                    keyFlag.setScrollUp(false);
                    keyFlag.setScrollDown(false);
                }




/*
                sf::View view1;
                view1.reset(sf::FloatRect(200.f, 200.f, 300.f, 200.f));

                sf::View view2;
                view2.setCenter(sf::Vector2f(350.f, 300.f));
                view2.setSize(sf::Vector2f(200.f, 200.f));
*/



                window.setView(view);

///OBSLUGA MROWEK
                int LLL = 0;
                for(auto &creature: *world.creaturePointer()){//comment from forum: You need to reference the vector's object with a pointer, otherwise you're just modifying a local copy. -> for (auto &i : vec) {...}
                    if(LLL == 0) creature.move(
                                               keyFlag.w(),
                                               keyFlag.s(),
                                               keyFlag.a(),
                                               keyFlag.d()
                                               );
                    else
                    creature.move(
                                  rand() % 4,
                                  rand() % 2,
                                  rand() % 2,
                                  rand() % 2
                                  );
                    creature.updateShape();
                    LLL++;
                }




///RYSOWANIE OBIEKTOW W OKNIE
                //rysowanie creatures
                for(auto creature: *world.creaturePointer()){
                        window.draw(
                                    *creature.shapePointer()
                                    );
                }


///WYSWIETLENIE ZAWARTOSCI OKNA
                window.display();


        }
        //koniec if(czas >16ms)

    }
    //koniec while(window is open)


    return 0;

}

    //rozdzielczosc ekranu
    //printf("%dx%d\n", sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);


//przeciez moze istniec objekt circle w obiekcie stworzonki, a w klasie world bedzie setter w postaci procedury ktora bedzie rysowac to badziewie... chyba?
//^ na dole musi byc funkcja zwracajaca wskaznik na obiekt, a u gory musi byc guwienko ktore korzystajac z tego wskaznika, kaze sie zachowac obiektowi, na ktory ten wskaznik wskazuje

//^^wsiaznik bedzie do rysowania obiektu, a samo ustawianie typu wsporzedne mozna robic zwyklym getterem setterem


    /*sf::Font font;
    font.loadFromFile("images/arialbd.ttf");

    sf::Text text;*/




    /*sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineThickness(4);
    shape.setOutlineColor(sf::Color(255, 240, 0));
    shape.setPointCount(200);*/


                /*if(event.mouseWheel.delta == 1){}
                else {}*/


                      /*          if(event.mouseWheel.delta == 1)
                    //view.move(10.f, 10.f);
                    view.zoom(0.95f);

                else
                    //view.move(-10.f, -10.f);
                    view.zoom(1.05f);
                    */





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
