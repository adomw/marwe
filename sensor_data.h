class DataSet{
public:
    float LeftFoodMarkerSensor, MiddleFoodMarkerSensor, RightFoodMarkerSensor;
    float LeftHomeMarkerSensor, MiddleHomeMarkerSensor, RightHomeMarkerSensor;
    float LeftObstacleMarkerSensor, MiddleObstacleMarkerSensor, RightObstacleMarkerSensor;
    void reset();
    void assignValues(
                      float LF, float MF, float RF,
                      float LH, float MH, float RH,
                      float LO, float MO, float RO
                      );
};
