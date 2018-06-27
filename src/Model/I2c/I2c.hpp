/**
 * I2c.hpp
 * 
 * Patrick Hock 
 * June 5, 2018
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
        I2c(void);     // Constructor
        
    
    private:
        
};

#endif  // I2C_HPP