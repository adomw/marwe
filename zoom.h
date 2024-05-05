#include<SFML/Graphics.hpp>

class Zoom{//Klasa odpowiadajaca za zoom
private:
    int CurrentZoom; //aktualny poziom przyblizenia, zaczyna sie od 1
    int MaxZoom = 7; //maksymalny poziom przyblizenia
    float ZoomBase = 1.6; //proporcja miedzy kolejnymi poziomami przyblizenia
    sf::View View;
    int Width;
    int Height;
public:
    void reset(int w, int h);
    int currentZoom();
    void updateView(float centerX, float centerY);
    void zoomIn(float centerX, float centerY);
    void zoomOut(float centerX, float centerY);
    sf::View* view();
};

