#include "dsm501.h"


void DebugLog(char* msg, unsigned long value)
{
    Serial.println(" ");
    Serial.print(msg);
    Serial.print("\t");
    Serial.println(value);
    Serial.println( " ");
}

dsm501::dsm501()
{
    filterEnabled=false ;
}

dsm501::dsm501(int dataPin)
{
    filterEnabled=false ;
    pinData=dataPin;
    pinMode(pinData,INPUT);
}

dsm501::~dsm501()
{
}

void dsm501::setDatapin(int pin)
{
    pinData = pin;
    pinMode(pinData,INPUT);
}

unsigned long  dsm501::getParticles()
{
    unsigned long  fv;
    unsigned long  ov;
    getParticles(ov,fv);

    return fv; 
}


void dsm501::enableFilter()
{
    filterEnabled=true ;
}

void dsm501::disableFilter()
{
    filterEnabled=false ;
}

unsigned long dsm501::Array_Average( unsigned long* Array,int length)
{
    int x;
    unsigned long returnVal;
    unsigned long result=0;
    for(x=0; x<length; x++)
    {
        result+=Array[x];
    }
    returnVal=result/length;
    return returnVal;
}

unsigned long dsm501::Filter1(unsigned long lowpulse)
{
    static unsigned long sfiterArray[filterlen];
    static int sindex=0;
    int x;

#ifdef DEBUGGINGFILTER
    Serial.println("filter1 begin:");
#endif

    if(filterlen>sindex)
    {
        sindex++;


#ifdef DEBUGGINGFILTER
        Serial.println(sindex);
#endif

        sfiterArray[sindex]=lowpulse;

#ifdef DEBUGGINGFILTER
        Serial.println("filter1 END");
#endif

        return lowpulse;
    }
    else
    {
        for(x=0; x<filterlen-1; x++)
        {
            sfiterArray[x]=sfiterArray[x+1];
        }
        sfiterArray[filterlen-1]=lowpulse;


#ifdef DEBUGGINGFILTER
        for(x=0; x<filterlen; x++)
        {
            Serial.println(sfiterArray[x]);
        }
        Serial.println("Aver:");
        Serial.println(Array_Average(sfiterArray,filterlen));
        Serial.println("filter1 END");
#endif


        return(Array_Average(sfiterArray,filterlen));

    }
}

unsigned long  calculateConcentration(unsigned long value)
{
    float r=0.0;
    unsigned long  retVal=0;

    r=value / (sampleTime_ms*10.0);
    retVal=1.1*pow(r,3)-3.8*pow(r,2)+520*r+0.62;

#ifdef DEBUGGING
    Serial.print("Ratio: ");
    Serial.println(r);
#endif // DEBUGGING

    return retVal;

}

void dsm501::getParticles(unsigned long  &originValue, unsigned long  &filteredValue)
{
    unsigned long  concentration=0;
    float ratioPWM=0.0 ;
    unsigned long lowPulseOccupancy=0;
    unsigned long startTime=0;
    unsigned long duration=0;

    startTime= millis();

    while ((millis()-startTime)<= sampleTime_ms)//独占30秒
    {
        duration =pulseIn(pinData, LOW); 
        lowPulseOccupancy += duration;


#ifdef DEBUGGINGFILTER
//下面代码会影响传感器的返回值，因此工作状态要注释掉
        int t=millis();
        Serial.print("D/L");
        Serial.print("\t");
        Serial.print(duration);
        Serial.print("\t");
        Serial.println(lowPulseOccupancy);
        Serial.println(" ");
        Serial.print("milliseconds used: ");
        Serial.println(millis()-t);
        Serial.println(" ");
#endif

    }//采样结束

    //计算颗粒物浓度
    //如果采样时间长于规定的长度--30s
    originValue=calculateConcentration(lowPulseOccupancy);

#ifdef DEBUGGING
    DebugLog("Original Low Pulse Occupancy: ", lowPulseOccupancy);
#endif

    if (filterEnabled)
    {
        lowPulseOccupancy=Filter1(lowPulseOccupancy);

#ifdef DEBUGGING
        DebugLog("Filtered Low Pulse Occupancy, if filtered: ", lowPulseOccupancy);
#endif

        filteredValue=calculateConcentration(lowPulseOccupancy);
    }
    else
    {
        filteredValue=originValue;
    }


#ifdef DEBUGGING
    DebugLog("Original concentraction: ", originValue);
    DebugLog("Filtered concentration, if applicable: ", filteredValue);
#endif

}
