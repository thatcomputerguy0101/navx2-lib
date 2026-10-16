/*
 * SimIO.h
 *
 *  Created on: Jan 28, 2020
 *      Author: Scott
 */

#ifndef SRC_SIMIO_H_
#define SRC_SIMIO_H_

#include <stdint.h>
#include "IIOProvider.h"
#include "IMUProtocol.h"
#include "AHRSProtocol.h"
#include "IBoardCapabilities.h"
#include "IIOCompleteNotification.h"
#include <wpi/units/time.hpp>
#include <wpi/system/Timer.hpp>

#include <wpi/hal/SimDevice.hpp>

class SimIO : public IIOProvider {
private:
    bool stop;
    bool is_connected;
    wpi::units::second_t start_seconds;  
    IIOCompleteNotification *notify_sink;         
    wpi::units::hertz_u8_t update_rate; 

    wpi::hal::SimDevice *sim_device;
    wpi::hal::SimBoolean simConnected;
    wpi::hal::SimDouble simRate;
    wpi::hal::SimDouble simYaw;
    wpi::hal::SimDouble simPitch;
    wpi::hal::SimDouble simRoll;
    wpi::hal::SimDouble simCompassHeading;
    wpi::hal::SimDouble simFusedHeading;    
    wpi::hal::SimDouble simLinearWorldAccelX;
    wpi::hal::SimDouble simLinearWorldAccelY;
    wpi::hal::SimDouble simLinearWorldAccelZ;

    float last_yaw;
    float last_linear_world_accel_x;
    float last_linear_world_accel_y;

    AHRSProtocol::BoardID board_id;
    IIOCompleteNotification::BoardState board_state;    
    AHRSProtocol::AHRSPosUpdate ahrs_update;    
    IMUProtocol::GyroUpdate raw_data_update;

public:
    SimIO( wpi::units::hertz_u8_t update_rate,
                IIOCompleteNotification *notify_sink,
                wpi::hal::SimDevice *sim_device);
    bool   IsConnected();
    double GetByteCount();
    double GetUpdateCount();
    void   SetUpdateRate(wpi::units::hertz_u8_t update_rate);
    void   ZeroYaw();
    void   ZeroDisplacement();
    void   Run();
    void   Stop();
    void   EnableLogging(bool enable);
    virtual ~SimIO();

    double GetRate();
private:
    void UpdatePeriodicFromSimVariables(long sensor_timestamp);
    float CalculateNormal(float in1, float in2);
};

#endif /* SRC_SIMIO_H_ */
