#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <limits.h>

// Lepton SDK
#include <LEPTON_SDK.h>
#include <LEPTON_SYS.h>
#include <LEPTON_Types.h>

// Default spidev device

int _connected = 0;
LEP_CAMERA_PORT_DESC_T _port;

LEP_RESULT lepton_connect() {
    LEP_RESULT ret;
    ret = LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
    _connected = 1;
    return ret;
}

void lepton_perform_ffc() {
    if(!_connected) {
        lepton_connect();
    }
    LEP_RunSysFFCNormalization(&_port);
}



int main(int argc, char * argv[]) {
    // result object
    LEP_RESULT res;

    // Attempt to connect to the Lepton
    printf("Connected?: %d\n", _connected);
    printf("Connecting...\n");
    res = lepton_connect();
    printf("Result: %d\n", res);

    // Information about the port
    printf("Port Information:\n");
    printf("ID: %d\n", _port.portID);
    printf("Baud Rate: %d\n", _port.portBaudRate);
    printf("Device Address: %d\n", _port.deviceAddress);

    // Run flat-field correction Normalization (confirm device access via shutter click)
    printf("Running FFS Normalization\n");
    res = LEP_RunSysFFCNormalization(&_port);
    printf("Result: %d\n", res);

    // Get serial number
    LEP_UINT64 serial_number;
    printf("Getting serial number...\n");
    res = LEP_GetSysFlirSerialNumber(&_port, &serial_number);
    printf("Result: %d\n", res);
    printf("Serial: %llu\n", serial_number);
    printf("String: %08llx\n", serial_number);

    // Flir Camera Part Number
    LEP_CHAR8 part_number[32];
    printf("Getting part number...\n");
    res = LEP_GetOemFlirPartNumber(&_port, part_number);
    printf("Part number: %s\n", part_number);



    // Get Lepton region of interest
    LEP_SYS_VIDEO_ROI_T sceneRoi;
    LEP_GetSysSceneRoi(&_port, &sceneRoi);
    printf("Result: %d\n", res);
    printf("Rows: %d - %d \t Columns: %d - %d \n", sceneRoi.startRow, sceneRoi.endRow, sceneRoi.startCol, sceneRoi.endCol);

    // Attempt to set the values of the region of interest...
    printf("Attempting to set the ROI...\n");
    sceneRoi.startRow = 0;
    sceneRoi.startCol = 0;
    sceneRoi.endRow = 159;
    sceneRoi.endCol = 119;
    LEP_SetSysSceneRoi(&_port, sceneRoi);
    printf("Result: %d\n", res);

    // After setting, does it change?
    LEP_GetSysSceneRoi(&_port, &sceneRoi);
    printf("Result: %d\n", res);
    printf("Rows: %d - %d \t Columns: %d - %d \n", sceneRoi.startRow, sceneRoi.endRow, sceneRoi.startCol, sceneRoi.endCol);
    return 0;
}
