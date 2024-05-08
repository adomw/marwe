#include "sensor_data.h"

void DataSet::reset(){

}

void DataSet::assignValues(
                            float LF, float MF, float RF,
                            float LH, float MH, float RH,
                            float LO, float MO, float RO
                           ){
    LeftFoodMarkerSensor = LF;
    MiddleFoodMarkerSensor = MF;
    RightFoodMarkerSensor = RF;

    LeftHomeMarkerSensor = LH;
    MiddleHomeMarkerSensor = MH;
    RightHomeMarkerSensor = RH;

    LeftObstacleMarkerSensor = LO;
    MiddleObstacleMarkerSensor = MO;
    RightObstacleMarkerSensor = RO;
}
