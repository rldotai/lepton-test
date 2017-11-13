# Lepton Test

Short programs for working with the FLIR Lepton on the Raspberry Pi.

## test_version

This program uses the Lepton SDK to check the kind of Lepton Module is in use.

We can check via the part number (which we can then look up on the Internet) or via the region-of-interest.

The part number is a useful thing to know, but while it is mentioned in the documentation the `LEPTON_OEM.c` and `LEPTON_OEM.h` files are not present in the SDK for the Raspberry Pi mentioned by GroupGets.
So I had to find them elsewhere, and then modify the Makefile to get them compiled and linked.

The part number is pretty self-explanatory.
You can look up your result on Google or on somewhere more specialized, like DigiKey.

Here are some part numbers I found:

| ---- | ---- |
Lepton 3 | 500-0726-01
Radiometric Lepton | 500-0763-01
Lepton 2 | 500-0643-00
 |  500-0659-01
 | 500-0690-00



----

The program finds the region-of-interest using the `LEP_GetSysSceneRoi` function
The region of interest is, if you're not restricting it, the resolution of the sensor.
The Lepton v3 has a resolution of 160x120, while the other versions have 80x60.

It first connects to the Lepton, tests that it's working via flat-field correction calibration (you should hear the sensor "click" due to the shutter cycling), prints the serial number, and then gets the ROI, which it prints.
It then attempts to *set* the ROI to 160x120, after which it prints the ROI again.

Depending on what kind of sensor you have, you should get different results:

```
# Lepton 2
[...]
Rows: 0 - 59     Columns: 0 - 79

# Lepton 3
[...]
Rows: 0 - 119     Columns: 0 - 159
```



### Build and Run

```
# on a Raspberry Pi (tested with Raspi 3 and Lepton breakout v 1.4)
make
./bin/test_version
```

