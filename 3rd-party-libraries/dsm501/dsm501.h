/*
    Histroy

    Jun 7 2013  getParticles(&，&)方法中参数数据类型从int修改为unsigned long, 重载的那个方法返回值的数据类型也做相应修改

*/

#ifndef DSM501_H
#define DSM501_H

#include "Arduino.h"

#define sampleTime_ms 30000
#define filterlen 10

//#define DEBUGGING

class dsm501
{
public:
    dsm501();
    dsm501(int dataPin);
    virtual ~dsm501();
    void setDatapin(int pin) ;
    unsigned long  getParticles() ;
    void getParticles(unsigned long &originValue, unsigned long &filteredValue); //可以对比滤波前后的数据变化
    void enableFilter();
    void disableFilter();
protected:
    unsigned long Filter1(unsigned long lowpulse);
    unsigned long Array_Average( unsigned long* Array,int length);
private:
    int pinData;
    unsigned long  particles;
    bool filterEnabled;
};

#endif // DSM501_H
