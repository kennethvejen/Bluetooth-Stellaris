#include "inc/lm3s9b92.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

//*****************************************************************************
//
// Function prototypes.
//
//*****************************************************************************
void SetupHardware(void);
void ADCIntial(void);

//*****************************************************************************
//
// Global Variables, Arrays and Pointers.
//
//*****************************************************************************
/************ UART ************/
char 			Rx_String0;
char 			Rx_String1;
char			Rx_Buffer1[5];
char 			Tx_String0[1000];
char 			Tx_String1[1000];
unsigned int 	Tx_ptr0;
unsigned int 	Tx_ptr1;
char			*Pr_ptr0;
char			*Pr_ptr1;

/************ ADC ************/
unsigned long ADCBuffer[1];

/************ Flags ************/
unsigned char flag1 = 0,
			  flag2 = 0;

//*****************************************************************************
//
// Our running system tick counters.
//
//*****************************************************************************
unsigned long SysTickCount;
unsigned long ADCTickCount;

//*****************************************************************************
//
// The number of SysTick ticks per second. 100 ticks = 1sec.
//
//*****************************************************************************
#define TICKS_PER_SECOND 100

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

//*****************************************************************************
//
// ADC Interrupt Handler.
//
//*****************************************************************************
/*void
ADCIntHandler(void)
{
}*/

//*****************************************************************************
//
// Initializing some ADC setup.
//
//*****************************************************************************
void
ADCInitial(void)
{
    // Voltage reference - Internal (3.0V).
    ADCReferenceSet(ADC0_BASE, ADC_REF_INT);

    SysCtlADCSpeedSet(SYSCTL_ADCSPEED_125KSPS);

	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0); // Sequence 0 - Processor triggered - Capture up to eight samples (channels).
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END); // Step 0 Channel 0.

	ADCSequenceEnable(ADC0_BASE, 3); // Enable Sequence 0.
    ADCIntEnable(ADC0_BASE, 3);	// Enable Interrupt Sequence 0.
    IntEnable(INT_ADC0); // Enable interrupt.
    ADCIntClear(ADC0_BASE, 3); // Clear interrupt flag.
}

//*****************************************************************************
//
// The UART0 interrupt handler - prototype defined in startup_ccs.
//
//*****************************************************************************
void
UART0IntHandler(void)
{
    // Clear the asserted interrupts.
    UARTIntClear(UART0_BASE, UART_INT_RX);

    // Gets value from UART0.
    Rx_String0 = UARTCharGet(UART0_BASE);
    UARTCharPut(UART1_BASE, Rx_String0);
}

//*****************************************************************************
//
// The UART1 interrupt handler - prototype defined in startup_ccs.
//
//*****************************************************************************
void
UART1IntHandler(void)
{
    // Clear the asserted interrupts.
    UARTIntClear(UART1_BASE, UART_INT_RX);

    // Gets value from UART1.
    Rx_String1 = UARTCharGet(UART1_BASE);
    UARTCharPut(UART0_BASE, Rx_String1);
}

//*****************************************************************************
//
// This is the interrupt handler regarding certain delays in the program.
// prototype defined in startup_ccs.
//
//*****************************************************************************
void
SysTickIntHandler(void)
{
    // Update our tick counter.
    SysTickCount++;
    ADCTickCount++;

    // Delay for flag3.
    if ( ADCTickCount >= 100 )
    {
    	flag2 = 1;
    }
}

//*****************************************************************************
//
// Hardware setup.
//
//*****************************************************************************
void
SetupHardware(void)
{
    // Set the clocking to run directly from the crystal.
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    // Enable the peripherals used by this example.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    // Enable processor interrupts.
    IntMasterEnable();

    // Configure SysTick for a 100Hz interrupt.
    ROM_SysTickPeriodSet(ROM_SysCtlClockGet() / TICKS_PER_SECOND);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();

	// Configure Ethernet LED.
    GPIODirModeSet( GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT );
    GPIOPadConfigSet( GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD );
    GPIOPinWrite( GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2 );

    /************ Initialize the ADC ************/
    // Set the ADC pins for analog input mode.
    ROM_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_7);

    /************ Initialize the UART0 ************/
    // Set GPIO A0 and A1 as UART0 pins.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configure the UART0 for 115200, 8-N-1 operation.
    UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 57600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    // Enable the UART0 interrupt.
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    // Disables FIFO UART0.
    UARTFIFODisable(UART0_BASE);

    /************ Initialize the UART1 ************/
    // Set GPIO D1 and D2 as UART1 pins.
    GPIOPinConfigure(GPIO_PD2_U1RX);
    GPIOPinConfigure(GPIO_PD1_U1TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_1 | GPIO_PIN_2);

    // Set GPIO D0 and F1 as UART1 handshake pins.
    GPIOPinConfigure(GPIO_PD0_U1CTS);
    GPIOPinConfigure(GPIO_PF1_U1RTS);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeUART(GPIO_PORTF_BASE, GPIO_PIN_1);

    // Configure the UART1 for 115200, 8-N-1 operation.
    UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 57600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    // Enable the UART1 interrupt.
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

    // Disables FIFO UART1.
    UARTFIFODisable(UART1_BASE);
}

//*****************************************************************************
//
// Main.
//
//*****************************************************************************
int
main(void)
{
	SetupHardware();
	ADCInitial();

    while(1)
    {
    	// Gets data from ADC.
    	ADCProcessorTrigger(ADC0_BASE, 3);
    	while(!ADCIntStatus(ADC0_BASE, 3, false))
    	{
    	}
    	ADCIntClear(ADC0_BASE, 3);
    	ADCSequenceDataGet(ADC0_BASE, 3, ADCBuffer);

    	// When UART1 is not busy and buffer is not empty, send data through UART1.
    	if(UARTBusy(UART1_BASE) == false && Tx_String1[Tx_ptr1]!=0)
    	{
    		UARTCharPut(UART1_BASE, Tx_String1[Tx_ptr1]);
    		Tx_ptr1++;
    	}

    	// 1sec passed and flag2 is 0, send command through UART1.
    	if( flag1 == 0 )
    	{
    		Pr_ptr1 = &Tx_String1[0];

    		// For further information about the commands, please see iWRAP4 User Guide.
    		// Commands sent through string (Pr_ptr1).
    		Pr_ptr1 += sprintf(Pr_ptr1, "SET BT NAME Glova\r\n"); // Names WT-12 module: Glova.
    		Pr_ptr1 += sprintf(Pr_ptr1, "SET CONTROL BAUD 57600,8n1\r\n"); // Set up connection settings.
    		Pr_ptr1 += sprintf(Pr_ptr1, "SET PROFILE SPP ON\r\n"); // Set profile to Serial Port Profile.
    		Pr_ptr1 += sprintf(Pr_ptr1, "SET CONTROL CONFIG 0000 0000 1100\r\n"); // Enables Paircount - see page 129 (iWRAP4 User Guide)
    		Pr_ptr1 += sprintf(Pr_ptr1, "SET BT PAIRCOUNT 1\r\n"); // Set paircount to store only 1 BT address.
    		// Pr_ptr1 += sprintf(Pr_ptr1, "SET CONTROL AUTOCALL 1101 2000 RFCOMM\r\n"); // Enable autocall with SPP (1101) and 2s (2000ms) delay.
    		Pr_ptr1 += sprintf(Pr_ptr1, "SET BT AUTH * 0000\r\n"); // Set password to "0000"
    		Pr_ptr1 += sprintf(Pr_ptr1, "SET BT BDADDR 00:07:80:4B:37:FB\r\n"); // Used to set a unique BT address, for the Android application.
    		Pr_ptr1 += sprintf(Pr_ptr1, "RESET\r\n\0"); // Reset WT-12 module, to enable given settings above.

    		flag1 = 1;
    		Tx_ptr1 = 0;
    	}

    	// Transmitting ADC value through BlueTooth
    	if( SysTickCount >= 300 && flag2 == 1 )
    	{
    		flag2 = 0;
    		Pr_ptr1 = &Tx_String1[0];

    		// Commands sent through string (Pr_ptr1).
			Pr_ptr1 += sprintf(Pr_ptr1, "ADC Value: %d\r\n\0", ADCBuffer[0]);
			// Pr_ptr1 += sprintf(Pr_ptr1, "SET\r\n\0"); // If necessary - to see the settings for WT-12.

			Tx_ptr1 = 0;
	    	ADCTickCount = 0;
    	}

    	// When '1' is received on UART1 RX, turn LED on.
    	if( Rx_String1 == '1' )
    	{
    		GPIOPinWrite( GPIO_PORTF_BASE, GPIO_PIN_2, 0 );
    	}

    	// When '0' is received on UART1 RX, turn LED off.
    	if( Rx_String1 == '0' )
		{
			GPIOPinWrite( GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2 );
		}
    }
}
