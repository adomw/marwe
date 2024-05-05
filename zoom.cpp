#include<math.h>
#include"zoom.h"

void Zoom::reset(int w, int h){
    CurrentZoom = 1;
    Width = w;
    Height = h;
    updateView(w / 2, h / 2);
}
int Zoom::currentZoom(){
    return CurrentZoom;
}
void Zoom::updateView(float centerX, float centerY){
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
void Zoom::zoomIn(float centerX, float centerY){
    if(CurrentZoom < MaxZoom) CurrentZoom++;
    updateView(centerX, centerY);
}
void Zoom::zoomOut(float centerX, float centerY){
    if(CurrentZoom > 1) CurrentZoom--;
    updateView(centerX, centerY);
}
sf::View* Zoom::view(){
    return &View;
}


