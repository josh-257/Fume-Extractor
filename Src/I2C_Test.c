/*
 * Application Entry Point
 */
#include "mcu.h"


//Need to add: global system init, clock init
#define MY_ADDR 0x61
#define SLAVE_ADDR 0x68

void delay(void){
    // Course standard software delay for button debouncing
    for(uint32_t i = 0; i < 500000/2; i++);
}

#define MY_ADDR 0x61
#define SLAVE_ADDR 0x68
#define CMD_SEND_LEN 0x51
#define CMD_SEND_MSG 0x52

//flag variable
uint8_t rxComplt = RESET;


/*********************************This is needed for using SWV printf**************************/

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        ITM_SendChar((*ptr++));
    }
    return len;
}
/**********************************************************************************************/
/*
 * pb6 --> SCL
 * pb7 --> SDA
 */

I2C_Handle_t I2C1Handle;

void I2C1_GPIOInits(void){

    GPIO_Handle_t I2CPins;

    I2CPins.pGPIOx = GPIOB;
    I2CPins.GPIO_Config.PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_Config.PinOPType = GPIO_OP_TYPE_OD;
    I2CPins.GPIO_Config.PinPuPdControl = GPIO_PIN_NOPUPD;
    I2CPins.GPIO_Config.AltFunMode = 4;
    I2CPins.GPIO_Config.PinSpeed = GPIO_SPEED_HIGH;

    //scl
    I2CPins.GPIO_Config.PinNumber = 6;
    GPIO_Init(&I2CPins);

    //sda
    I2CPins.GPIO_Config.PinNumber = 7;
    GPIO_Init(&I2CPins);
}

void I2C1_Inits(void){



  I2C1Handle.pI2Cx = I2C1;
  I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
  I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
  I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2_1;
  I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

  I2C_Init(&I2C1Handle);
}

void Button_Init(void){

    GPIO_Handle_t GPIO_btn, GpioLed;

    GPIO_btn.pGPIOx = GPIOA;
    GPIO_btn.GPIO_Config.PinNumber = 0;
    GPIO_btn.GPIO_Config.PinMode = GPIO_MODE_IN;
    GPIO_btn.GPIO_Config.PinSpeed = GPIO_SPEED_HIGH;
    GPIO_btn.GPIO_Config.PinPuPdControl = GPIO_PIN_NOPUPD;

    GPIO_Init(&GPIO_btn);

  GpioLed.pGPIOx = GPIOD;
  GpioLed.GPIO_Config.PinNumber = 12;
  GpioLed.GPIO_Config.PinMode = GPIO_MODE_OUT;
  GpioLed.GPIO_Config.PinSpeed = GPIO_SPEED_HIGH;
  GpioLed.GPIO_Config.PinOPType = GPIO_OP_TYPE_PP;
  GpioLed.GPIO_Config.PinPuPdControl = GPIO_PIN_NOPUPD;


  GPIO_Init(&GpioLed);
}

int main(void){

  uint8_t commandcode, msg_len;
  char buffer[50];

    Test_Init();

    Button_Init();

    I2C1_GPIOInits();

    I2C1_Inits();

    __NVIC_EnableIRQ(I2C1_EV_IRQn);
    __NVIC_EnableIRQ(I2C1_ER_IRQn);

    I2C_PeripheralControl(I2C1Handle.pI2Cx, ENABLE);

    I2C_ToggleAcking(I2C1, I2C_ACK_ENABLE);

      while(1){

        //wait for button press
        while(GPIO_ReadFromInputPin(GPIOA, 0) == 0);

        delay();

        //First get the length of message from arduino
        commandcode = CMD_SEND_LEN;

        while(I2C_MasterSendDataIT(&I2C1Handle, &commandcode, 1, SLAVE_ADDR, I2C_SR_EN) != I2C_READY);

        while(I2C_MasterReceiveDataIT(&I2C1Handle, &msg_len, 1, SLAVE_ADDR, I2C_SR_EN) != I2C_READY);
        //Second receive message from arduino
        commandcode = CMD_SEND_MSG;

        while(I2C_MasterSendDataIT(&I2C1Handle, &commandcode, 1, SLAVE_ADDR, I2C_SR_EN) != I2C_READY);

        while(I2C_MasterReceiveDataIT(&I2C1Handle, buffer, msg_len, SLAVE_ADDR, I2C_SR_DI) != I2C_READY);

        rxComplt = RESET;

        while(rxComplt != SET){

        }

        buffer[msg_len+1] = '\0';
        printf("message: %s\n", buffer);
        printf("printed\n");

        rxComplt = RESET;

      }

}

void I2C1_EV_IRQHandler(void)
{
  I2C_EVIRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler(void){

  I2C_ERIRQHandling(&I2C1Handle);
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv)
{
  if(AppEv == I2C_EV_TX_CMPLT){

    printf("Tx is completed\n");
  }
  else if(AppEv == I2C_EV_RX_CMPLT)
  {
    printf("Rx is completed\n");
    rxComplt = SET;
  }
  else if(AppEv == I2C_ERROR_AF)
  {
    //Slave has failed to send ack byte to master
    printf("Error: Ack failure\n");

    I2C_CloseSendData(pI2CHandle);

    I2C_GenerateStopCondition(I2C1);

    //Hang in infinite loop
    while(1);
  }
  else if(AppEv == I2C_EV_TX_CMPLT){

    printf("Tx is completed\n");
  }

}
