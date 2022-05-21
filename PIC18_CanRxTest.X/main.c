/**
 * PICduino CAN Receive Testing
 */

#include "mcc_generated_files/mcc.h"
#include <stdio.h>

typedef enum {
    VEHICLE_STATE = 0x0c0,
    SWITCHES = 0x0d0,
    TORQUE_REQUEST_COMMAND = 0x766,
    BMS_STATUS = 0x380,
    BMS_VOLTAGES = 0x388,
    BMS_TEMPERATURES = 0x389
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
    tx_msg.frame.id = SWITCHES;
    tx_msg.frame.dlc = 0x01;
    tx_msg.frame.data0 = 0b10;
    
    uint8_t count = 0;    
    
    while (1)
    {
        if(CAN_receive(&msg)){
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
        
        // transmit
        if (!(count % 100)) {
            if(CAN_transmit(&tx_msg)){
                IO_RA0_Toggle();
                printf("Sending %d on ID: 0x%lx\n", tx_msg.frame.data0, tx_msg.frame.id);
            }
            if (tx_msg.frame.data0 == 0b10) {
                tx_msg.frame.data0 = 0;
            } else {
                tx_msg.frame.data0 = 0b10;
            }
        }
        count++;
        __delay_ms(100);
    }
}

// print name of CAN message
void print_can_name(CAN_ID msg_id) {
    switch(msg_id) {
        case VEHICLE_STATE:
            printf("Vehicle_State");
            break;
        case SWITCHES:
            printf("Driver_Switches");
            break;
        case TORQUE_REQUEST_COMMAND:
            printf("Torque_Request_Command");
            break;
        case BMS_STATUS:
            printf("BMS_Status");
            break;
        case BMS_VOLTAGES:
            printf("BMS_Voltages");
            break;
        case BMS_TEMPERATURES:
            printf("BMS_Temperatures");
            break;
    }
}

/**
 End of File
*/