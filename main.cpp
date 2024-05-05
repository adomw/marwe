//TEMPLATE VERSION 22.04.2024


//Angles are mirror reflections of those on a complex numbers graph, so clockwise and starting with a flat horizontal line for 0.
//Obviously, the Y axis is also a mirror reflection. Point (0, 0) is i the upper-left corner.



//#include<SFML/Graphics.hpp>
#include"SFML/Graphics.hpp"
//#include<stdio.h>
//#include<math.h>
//#include"support_lib.h"
//#include"vector2d.h"
#include"zoom.h"
#include"keyflag.h"
//#include"entities.h"

#include"world.h"


///koncepocja jest taka zeby calosc sie rozgrywala niezaleznie od ekranu, "zaciec", lagow itp, zeby calosc dzialala bazujac o "ture" ktora bedzie bardzo krotka jednostka czasu (np. 10ms) i obraz bedzie jedynie reprezentacja wizualna tego, co sie dzieje, ukazujac te 100 "tur" na sekunde


sf::CircleShape creatureShape(
                      Creature c
                      ){
    sf::CircleShape s;
    s.setRadius(c.radius());
    if(c.key() != USER_KEY){
        s.setOutlineColor(sf::Color(15, 15, 240, 128));
        s.setFillColor(sf::Color(255, 255, 255));
    }
    else{
        s.setOutlineColor(sf::Color(255, 102, 204, 255));
        s.setFillColor(sf::Color(240, 255, 0));
    }
    s.setOutlineThickness(1.2);
    s.setOrigin(c.radius(), c.radius());
    s.setPosition(c.x(), c.y());
    return s;
}
sf::CircleShape obstacleEnd1(
                      Obstacle o
                      ){
    sf::CircleShape s;
    s.setRadius(o.radius());
    s.setFillColor(sf::Color(160, 20, 20));
    s.setOutlineThickness(0);
    s.setOrigin(o.radius(), o.radius());
    s.setPosition(o.x(), o.y());
    return s;
}
sf::CircleShape obstacleEnd2(
                      Obstacle o
                      ){
    sf::CircleShape s;
    s.setRadius(o.radius());
    s.setFillColor(sf::Color(160, 20, 20));
    s.setOutlineThickness(0);
    s.setOrigin(o.radius(), o.radius());
    s.setPosition(o.x2(), o.y2());
    return s;
}
sf::RectangleShape obstacleInside(
                      Obstacle o
                      ){
    double cx = (o.x() + o.x2()) / 2.0;
    double cy = (o.y() + o.y2()) / 2.0;
    double w = sqrt(
                    (o.x() - o.x2()) * (o.x() - o.x2()) +
                    (o.y() - o.y2()) * (o.y() - o.y2())
                    );
    double rotation = asin((o.y() - o.y2()) / w);


    sf::RectangleShape s;
    s.setSize(
              sf::Vector2f(w, 2 * o.radius())
                );
    s.setOrigin(w / 2.0, o.radius());
    s.setFillColor(sf::Color(160, 20, 20));
    s.setOutlineThickness(0);
    s.rotate(rotation * 180.0 / M_PI);
    s.setPosition(cx, cy);
    return s;
}


vector2d difference(vector2d v1, vector2d v2){
    vector2d v3;
    v3.setValue(v1.x() - v2.x(), v1.y() - v2.y());
    return v3;
}


int main()
{
    srand(time(NULL));

    Creature c1, c2;
    c1.resetCreature(1);
    c2.resetCreature(2);
    c1.setCoordinates(500, 400);
    c2.setCoordinates(500, 403.5);
    printf("C1 and C2 are touching: %d\n", touching(c1, c2));

    printf("START\n");
    World world;
    world.create();
    world.assignPointers();
    //world.print();

    //boundaries of the window
    world.addObstacle(0,        0,          WIDTH,  0,          15.0, 0);
    world.addObstacle(WIDTH,    0,          WIDTH,  HEIGHT,     15.0, 1);
    world.addObstacle(WIDTH,    HEIGHT,     0,      HEIGHT,     15.0, 2);
    world.addObstacle(0,        HEIGHT,     0,      0,          15.0, 3);


    //other obstacles
    //world.addObstacle(213.7, 148.8, 696.9, 420, 10.0, 4);

    world.addObstacle(700, 0, 600, 400, 5.0, 4);
    world.addObstacle(400, 260, 400, 540, 5.0, 5);
    world.addObstacle(400, 580, 400, HEIGHT, 5.0, 6);
    world.addObstacle(130, HEIGHT - 200, 200, HEIGHT - 100, 5.0, 7);
    world.addObstacle(370, 550, 420, 545, 5.0, 8);
    world.addObstacle(380, 580, 420, 580, 5.0, 9);
    world.addObstacle(400, 260, 350, 150, 5.0, 10);
    world.addObstacle(100, 200, 300, 360, 5.0, 11);
    world.addObstacle(300, 360, 370, 290, 5.0, 12);
    world.addObstacle(820, HEIGHT - 150, WIDTH - 80, HEIGHT - 150, 5.0, 13);
    world.addObstacle(600, HEIGHT - 80, 820, 540, 5.0, 14);
    world.addObstacle(820, 540, WIDTH - 120, 540, 5.0, 15);
    world.addObstacle(530, 260, 440, 150, 5.0, 16);
    world.addObstacle(530, 260, 600, 150, 5.0, 17);
    world.addObstacle(480, 580, 720, 580, 5.0, 18);
    world.addObstacle(WIDTH - 105, 540, WIDTH, 540, 5.0, 19);
    world.addObstacle(950, 650, 1100, 800, 5.0, 20);

    //world.allocateMemory();

    int KeyCounter = 0;

    sf::Clock clock;
    sf::Time time;

    Zoom zoom;
    zoom.reset(WIDTH, HEIGHT);

    sf::CircleShape mainBaseShape;
    mainBaseShape.setRadius(MAIN_BASE_RADIUS);
    mainBaseShape.setFillColor(sf::Color(160, 120, 220));
    mainBaseShape.setOutlineColor(sf::Color(160, 120, 220, 200));
    mainBaseShape.setOutlineThickness(10.0);
    mainBaseShape.setOrigin(MAIN_BASE_RADIUS, MAIN_BASE_RADIUS);
    mainBaseShape.setPosition(MAIN_BASE_X, MAIN_BASE_Y);
    mainBaseShape.setPointCount(100);

    sf::RectangleShape areaSprite;
    areaSprite.setFillColor(sf::Color(53, 122, 230, 192));
    areaSprite.setSize(sf::Vector2f(sizeOfArea - 0.2, sizeOfArea - 0.2));

    sf::RectangleShape markerSprite;
    markerSprite.setSize(sf::Vector2f(sizeOfArea - 0.2, sizeOfArea - 0.2));

    KeyFlag keyFlag;//moja autorska klasa ustawiajaca zerojedynkowo czy dane przyciski sa wcisniete - bo eventy klas event w sfml moga byc obslugiwane tylko pojedynczo (nie da sie odczytac np. Alt+cos)
    keyFlag.reset();

    sf::ContextSettings windowSettings;//window settings
    windowSettings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Marwë 0.5", sf::Style::Default, windowSettings);//declare window with above settings

    sf::Texture backgroundTexture;
    //backgroundTexture.loadFromFile("images/1._FC_Magdeburg.png");
    backgroundTexture.loadFromFile("images/grass.jpg");

    sf::Sprite backgroundSprite(backgroundTexture);
    sf::RectangleShape backgroundShadow;
    backgroundShadow.setFillColor(sf::Color(0, 0, 0, 192));
    backgroundShadow.setSize(sf::Vector2f(WIDTH, HEIGHT));
    backgroundShadow.setPosition(0, 0);

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



///WYSWIETLANIE WSZYSTKIEGO
///I PRZESUWANIE WSZYSTKIEGO
        time = clock.getElapsedTime();//obsluga zegara, tj. ile uplynelo czasu od ostatniego update'u ekranu
        if(time.asMilliseconds() > 17){//jezeli uplynelo juz X milisekund, to jazda, jedziemy dalej. a jezeli nie, to pozwalamy SFML ominac dzialania az uplynie (chodzi o to zeby szybkosc nie byla uzalezniona od ilosci elementow, a co najwyzej z jednej strony - jezeli bedzie odpowiednio za duzo, to wiadomo ze spowolni)

            {//dodalem klamry tylko po to zeby zwijac w edytorze
            clock.restart();//reset zegara
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
            ///KWADRATY

            window.draw(mainBaseShape);

            for(auto &c : world.toAreas()){
                areaSprite.setPosition(c.x * sizeOfArea + 0.1, c.y * sizeOfArea + 0.1);
                window.draw(areaSprite);
            }

            for(int i = 0; i < POINTER_ARRAY_EDGE_X; i++)
                for(int j = 0; j < POINTER_ARRAY_EDGE_Y; j++)
                    if(world.toMarkers(i, j) > 0)
                    {
                        markerSprite.setFillColor(sf::Color(53, 230, 122, 192));
                        markerSprite.setPosition(i * sizeOfArea + 0.1, j * sizeOfArea + 0.1);
                        window.draw(markerSprite);
                    }


            ///RYSOWANIE
            for(auto o : world.toObstacles()){
                ///draw obstacles
                window.draw(obstacleEnd1(o));
                window.draw(obstacleEnd2(o));
                window.draw(obstacleInside(o));
            }

            for(auto &c : world.toCreatures())
                ///draw creatures
                window.draw(creatureShape(c));


            }//dodalem klamry tylko po to zeby zwijac w edytorze


                window.setView(*zoom.view());

///OBSLUGA MROWEK
                world.process(
                              keyFlag.w(),
                              keyFlag.s(),
                              keyFlag.a(),
                              keyFlag.d()
                              );
                world.updatePointers(KeyCounter);
                KeyCounter++;
                KeyCounter %= UPDATE_INERVAL;
                //^ jesli odkomentujesz to na dole, to zakomentuj to na gorze

///RYSOWANIE OBIEKTOW W OKNIE
                //rysowanie creatures


                ///   !!! SFML Vertex !!!

///WYSWIETLENIE ZAWARTOSCI OKNA
                window.display();
                //system("pause");

        }
        //koniec if(czas >16ms)

    }
    //koniec while(window is open)



    return 0;

}
///KONIEC KODU
