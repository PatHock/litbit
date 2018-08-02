/**
 * I2c.hpp
 * 
 * Patrick Hock 
 * August 1, 2018
 */

#ifndef I2C_HPP
#define I2C_HPP

#include <Arduino.h>
#include <Wire.h>

#define I2C_FREQ 100000

class I2c
{
    public:
        ~I2c(void); // Destructor
        static I2c* getInstance();
        void init(void);
        
        
    
    private:
        I2c(void){};     // Constructor
        static I2c* _pInstance;
        
};

#endif  // I2C_HPP