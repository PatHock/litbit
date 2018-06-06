/**
 * RtcController.hpp
 * MCP7490N Real-time-clock
 * 
 * Patrick Hock 
 * June 4, 2018
 */

#ifndef RTCCONTROLLER_HPP
#define RTCCONTROLLER_HPP

#include <Arduino.h>
#include "Model/Rtc/Rtc.hpp"

class RtcController
{
    public:
        // Destructor
        ~RtcController(void); 

        // Returns the instance of EepromController
        static RtcController* getInstance();

        // Initializes, since constructor cannot be called (to enforce singletons)
        void init(void);
        
    
    private:
        // Constructor
        RtcController(void){};

        // Pointer to the single instance of EepromController 
        static RtcController* _pInstance;

        Rtc* RtcModel;

        // Current date and time
        DateTime now;

};

#endif  //RTCCONTROLLER_HPP