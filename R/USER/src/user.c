#include "user.h"

uint8_t Radio_Rxbuff[255] = {0};
uint16_t Radio_RxLength = 0;
uint8_t Cmd_Buff[255] = {0};
uint8_t Cmd_A1[7] = {0x14,0x02,0x35,0x69,0x41,0x0a,0x01};
uint8_t Cmd_B1[7] = {0x14,0x02,0x35,0x69,0x41,0x0b,0x11};
uint8_t Cmd_B3[7] = {0x14,0x02,0x35,0x69,0x41,0x0b,0x12};
uint8_t Cmd_B2[7] = {0x14,0x02,0x35,0x69,0x41,0x0b,0x13};
uint8_t Compare_Cmd(uint8_t *recv_cmd_buf, uint8_t recv_buf_num)
{
    uint8_t cmd_Num = 0;
    uint8_t index = 0;

    switch (recv_cmd_buf[6])
    {
    case 0x11:
        for ( ; index < recv_buf_num; index++)
        {
            if (recv_cmd_buf[index] == Cmd_B1[index])
            {

            }
            else
            {
                cmd_Num = 0;
                continue;
            }
        }
        cmd_Num = 1;
        break;

    case 0x12:
        for ( ; index < recv_buf_num; index++)
        {
            if (recv_cmd_buf[index] == Cmd_B2[index])
            {

            }
            else
            {
                cmd_Num = 0;
                continue;
            }
        }
        cmd_Num = 2;
        break;

    case 0x13:
        for ( ; index < recv_buf_num; index++)
        {
            if (recv_cmd_buf[index] == Cmd_B3[index])
            {

            }
            else
            {
                cmd_Num = 0;
                continue;
            }
        }
        cmd_Num = 3;
        break;

    default :
        ;
        break;
    }
    return cmd_Num;
}


void Task_Send(radio_handle_t Radio_handle)
{
    radio_buf_send(Radio_handle, Cmd_A1, 7);
    radio_mode_set(Radio_handle, RX_MODE);//进入接收模式
}
/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Task_Recv
  * @brief  
  * @param   Radio_handle: [输入/出] 
  * @retval
  * @author  潘苏皖
  * @Data    2021-03-11
  * 1. ...
  * <modify staff>: 
  * <data>        :
  * <description> :lora
  * 2. ...
 **/
/* -------------------------------- end -------------------------------- */
uint8_t Task_Recv(radio_handle_t Radio_handle)
{
    uint8_t index = 0;
    uint8_t Recv_Cmd_Num = 0;

    if ( radio_buf_recv(Radio_handle, Radio_Rxbuff, &Radio_RxLength) == RADIO_RET_OK)
    {
        for ( ; index < Radio_RxLength; index++)
        {
            Cmd_Buff[index] = Radio_Rxbuff[index];
        }

        Recv_Cmd_Num = Compare_Cmd(Cmd_Buff, Radio_RxLength);//判断接收到的哪种指令

        switch (Recv_Cmd_Num)//做出相应的指令程序
        {
        case 1 :
            HAL_GPIO_WritePin(RELAY0_GPIO_Port, RELAY0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(RELAY0_GPIO_Port, RELAY1_Pin, GPIO_PIN_RESET);
            radio_mode_set(Radio_handle, RX_MODE);//进入接收模式
            break;
        case 2 :
           HAL_GPIO_WritePin(RELAY0_GPIO_Port, RELAY0_Pin, GPIO_PIN_RESET);
           HAL_GPIO_WritePin(RELAY0_GPIO_Port, RELAY1_Pin, GPIO_PIN_SET);
           radio_mode_set(Radio_handle, RX_MODE);//进入接收模式
           break;

        case 3 :
           HAL_GPIO_WritePin(RELAY0_GPIO_Port, RELAY0_Pin, GPIO_PIN_RESET);
           HAL_GPIO_WritePin(RELAY0_GPIO_Port, RELAY1_Pin, GPIO_PIN_RESET);
           radio_mode_set(Radio_handle, RX_MODE);//进入接收模式
           break;

        default :
            ;
           break;
        }
    }
  return Recv_Cmd_Num;
}

