# NavX2 for Systemcore

A port of the NavX2 library to Systemcore and WPILib 2027, derived from [https://github.com/kauailabs/navxmxp].

## Notice

This will probably not continue to be maintained, since its intended use case is mostly for DIY Systemcores ahead of official hardware availability. Official Systemcore hardware has a built-in IMU that should be comparable or better than the NavX2. Better IMU performance can be gotten from other currently supported third-party products.

## Usage

This is not an officially released library, so using it will require building from source and using a locally-published artifact.

On each computer that you intend on building your robot project from:

```bash
$ git clone https://github.com/thatcomputerguy0101/navx
$ cd navx/systemcore
$ ./gradlew installSystemCoreToolchain # Only needed if using C++
$ ./gradlew publishToMavenLocal
```

From one of the devices that you just built the library on, in your robot project, import the generated vendor JSON from `navx/systemcore/build/generated/vendordeps/navx_frc.json`.
