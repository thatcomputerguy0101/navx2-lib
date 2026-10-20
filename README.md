# NavX2 for Systemcore

A port of the NavX2 library to Systemcore and WPILib 2027, derived from [https://github.com/kauailabs/navxmxp].

## Notice

This will probably not continue to be maintained, since its intended use case is mostly for DIY Systemcores ahead of official hardware availability. Official Systemcore hardware has a built-in IMU that should be comparable or better than the NavX2. Better IMU performance can be gotten from other currently supported third-party products.

## Installation

This is not an officially released library, so using it will require building from source and using a locally-published artifact.

On each computer that you intend on building your robot project from:

```bash
git clone https://github.com/thatcomputerguy0101/navx
cd navx/systemcore
./gradlew installSystemCoreToolchain # Only needed if using C++
./gradlew publishToMavenLocal
```

From one of the devices that you just built the library on, copy the generated vendor JSON from `navx/systemcore/build/generated/vendordeps/navx_frc.json` into your robot project's `vendordeps` folder. You may also need to add your resolved maven local path (the expansion of `~/.m2/repository`) to the `mavenUrls` list in the vendordep file.

## API Changes

The API should be the same as the last release of navx_frc, except the implementations for `Gyro` and `PIDSource` were dropped, and the implementation of `Sendable` was exchanged for `TelemetryLoggable`.

## Wiring

The only protocol supported by both NavX2 and WPILib 2027_a7 is I2C. Theoretically, USB should also eventually be supported, but it isn't at the time of writing.

### Official Systemcore

Connect V+, GND, SDA, and SCL to either of the I2C ports on Systemcore. Note, SDA and SCL are in the opposite order on NavX2 compared to Systemcore, so it may be necessary to rearrange pins if using a pre-wired cable. https://www.revrobotics.com/rev-11-1729/ has the correct pin arrangement.

### DIY Systemcore (RPi5)

Connect V+ and GND from the NavX to 5V and GND on the Pi. Using I2C port 1 on Pi GPIO 2 (SDA) and 3 (SCL) is recommended, since hardware pullup resistors are present on those pins.

Some software setup is also required to enable I2C. Connect to Systemcore via SSH, then run

```bash
echo "i2c-dev" | sudo tee /etc/modules-load.d/i2c.conf
sudo mkdir /boot/firmware # May already exist if you did an update through the web console
sudo mount /dev/mmcblk0p$(($(cat /proc/cmdline | grep -oP 'root=/dev/mmcblk0p\K\d') - 3 )) /boot/firmware
```

Then edit `/boot/firmware/config.txt` (`vim` and `nano` are both available, `sudo` is necessary). Uncomment `dtoverlay=i2c_arm=on`, and comment out `dtoverlay=i2c1,pins_10_11`.

Reboot when done by running `sudo reboot`.

You can verify that configuration was successful by running `i2cdetect` and `sudo pinctrl | grep -E "SDA|SCL"`. The former shows the loaded I2C busses, the latter lists which pins they are active on (SDA1/SCL1 correspond to I2C1).
