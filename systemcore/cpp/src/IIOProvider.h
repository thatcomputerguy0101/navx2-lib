/*
 * IIOProvider.h
 *
 *  Created on: Jul 29, 2015
 *      Author: Scott
 */

#ifndef SRC_IIOPROVIDER_H_
#define SRC_IIOPROVIDER_H_

#include "hertz_u8.h"
#include <wpi/units/frequency.hpp>

class IIOProvider {
public:
    IIOProvider() {}
    virtual bool   IsConnected() = 0;
    virtual double GetByteCount() = 0;
    virtual double GetUpdateCount() = 0;
    virtual void   SetUpdateRate(wpi::units::hertz_u8_t update_rate) = 0;
    virtual void   ZeroYaw() = 0;
    virtual void   ZeroDisplacement() = 0;
    virtual void   Run() = 0;
    virtual void   Stop() = 0;
    virtual void   EnableLogging(bool enable) = 0;
};

#endif /* SRC_IIOPROVIDER_H_ */
