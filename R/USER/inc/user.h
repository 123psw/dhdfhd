/**
  ************************************* Copyright ******************************   
  *                 (C) Copyright 2021,平湖烟雨,China, CCIT.
  *                            All Rights Reserved
  *                              
  *                     By(常州信息职业技术学院电子工程学院)
  *                     https://github.com/123psw/51lib
  *      
  * FileName   : user.h   
  * Version    : v1.0		
  * Author     : 潘苏皖		
  * Date       : 2021-02-15         
  * Description:    
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 **/
#ifndef __USER_H_
#define __USER_H_

#include "sx127x_lora.h"

uint8_t Compare_Cmd(uint8_t *recv_cmd_buf, uint8_t recv_buf_num);
void Task_Send(radio_handle_t Radio_handle);
uint8_t Task_Recv(radio_handle_t Radio_handle);
#endif


 

