/**
 * I2cController.hpp
 * 
 * Patrick Hock 
 * June 5, 2018
 */

#ifndef I2CCONTROLLER_HPP
#define I2CCONTROLLER_HPP

#include <Arduino.h>
#include "Model/I2c/I2c.hpp"


class I2cController
{
    public:
        ~I2cController(void); // Destructor
        static I2cController* getInstance();
        void init(void);

    private:
        // Constructor
        I2cController(void){};     

        static I2cController* _pInstance;

        I2c* I2cModel;
        
};

#endif  //I2CCONTROLLER_HPP