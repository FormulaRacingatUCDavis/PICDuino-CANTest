/**
 * PICduino CAN Receive Testing
 */

#include "mcc_generated_files/mcc.h"
#include <stdio.h>

typedef enum {
    BSPD_FLAGS = 0x0c1,
    DRIVER_SWITCHES = 0x0d0,
    TORQUE_REQUEST_COMMAND = 0x766,
    BMS_STATUS_MSG = 0x380,
    PEI_CURRENT = 0x387,
    BMS_VOLTAGES = 0x388,
    BMS_TEMPERATURES = 0x389,
    MC_ESTOP = 0x366,
    MC_DEBUG = 0x466,
    MC_PDO_SEND = 0x566,
    MC_PDO_ACK = 0x666
} CAN_ID;

// print name of CAN message
void print_can_name(CAN_ID id);

/*
                         Main application
 */

void main(void)
{
    
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    uCAN_MSG msg;
    uCAN_MSG tx_msg;
    tx_msg.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
    tx_msg.frame.id = MC_PDO_ACK;
    tx_msg.frame.dlc = 0x08;
    tx_msg.frame.data0 = 0;
    
//    uCAN_MSG tx_msg2;
//    tx_msg2.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
//    tx_msg2.frame.id = MC_ESTOP;
//    tx_msg2.frame.dlc = 0x08;
//    tx_msg2.frame.data0 = 0;
    
    while (1)
    {
        if (CAN_receive(&msg)) {
            printf("CAN Message received: ");
            print_can_name(msg.frame.id);
            printf("\n");
            printf("ID: 0x%lx\n", msg.frame.id);
            for(uint8_t i = 0; i < msg.frame.dlc; i++){
                printf("data%d: %d\n", i, msg.array[i+6]);
            }
            printf("\n");
        } else {
            printf("No Message received:\n");
        }
        __delay_ms(100);
    }
}

// print name of CAN message
void print_can_name(CAN_ID msg_id) {
    switch(msg_id) {
            break;
        case BSPD_FLAGS:
            printf("BSPD_FLAGS");
            break;
        case DRIVER_SWITCHES:
            printf("DRIVER_SWITCHES");
            break;
        case TORQUE_REQUEST_COMMAND:
            printf("TORQUE_REQUEST_COMMAND");
            break;
        case BMS_STATUS_MSG:
            printf("BMS_STATUS_MSG");
            break;
        case PEI_CURRENT:
            printf("PEI_CURRENT");
            break;
        case BMS_VOLTAGES:
            printf("BMS_VOLTAGES");
            break;
        case BMS_TEMPERATURES:
            printf("BMS_TEMPERATURES");
            break;
        case MC_ESTOP:
            printf("MC_ESTOP");
            break;
        case MC_DEBUG:
            printf("MC_DEBUG");
            break;
        case MC_PDO_SEND:
            printf("MC_PDO_SEND");
            break;
        case MC_PDO_ACK:
            printf("MC_PDO_ACK");
            break;
    }
}

/**
 End of File
*/