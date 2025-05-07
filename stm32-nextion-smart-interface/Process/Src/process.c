#include "process.h"
#include "staticprocess.h"


static uint8_t  password = 0;
static uint8_t  eeprom_read_array[50];
static char     str[35];
static uint8_t  alarm_hour, Alarm_minute, alarm_on_off = 0, alarm_operation = 0;
static uint8_t  status_blue = 0, status_red = 0, status_green = 0;
static uint32_t last_tick = 0;

static nextion_page_state_t   nextion_page_state;
static EE24_HandleTypeDef     ee24;
static NEXTION_PackageTypeDef nextionTouchEvent;
static packet_data            packetData;
static packet_steps_t         packetsteps;

static en_setalarm_state      step_alarm;
static en_settime_state       step_time;
static en_settouch_state      step_touch;



static void nextionPage1LightsSatus (void);
static void nextionSetAlarm(void);
static void nextionSetChangePassword(void);
static void nextionSetTime(void);
static void nextionSetPassword(void);
static void nextionSetSleep(void);
static void nextionSetTemp(void);
static void nextionAlarmOperation(void);
static void nextionRedLightsStatus(void);
static void nextionBlueLightsStatus(void);
static void nextionGreenLightsStatus(void);
static void nextionAlarmSendString(void);



void process_INIT(void)
{


  nextion_page_state  = NEXTION_PAGE0;
  packetsteps         = PACKAGE_İS_VALİD;
  step_touch          = SETTOUCH_STATE_IDLE;

    serial_message("OK%s\n","EY");

  if (EE24_Init(&ee24, get_pointer_hi2c2(), EE24_ADDRESS_DEFAULT, MCU_EEPROM_WC__3V3_GPIO_Port , MCU_EEPROM_WC__3V3_Pin))
  {
      EE24_Read(&ee24, 0, eeprom_read_array, 8, 1000);
      password = eeprom_read_array[0];
  }
  PCF85_Init(get_pointer_hi2c2());
  PCF85_SetDate(0,eeprom_read_array[1],eeprom_read_array[2],eeprom_read_array[3]+1970);
  PCF85_SetTime(eeprom_read_array[4],eeprom_read_array[5],eeprom_read_array[6]);
  

}



void Process_Nextion(void)
{
  if(NEXTION_DMA_FLAG == DMA_FLAG_ENABLE)
  {
     NEXTION_DMA_FLAG = DMA_FLAG_DISABLE;
     memcpy(&nextionTouchEvent, rxbuffer_uart1, sizeof(nextionTouchEvent));
  }

  nextionAlarmOperation();

  switch (nextion_page_state)
  {
    case NEXTION_PAGE0:
      if(nextionTouchEvent.componendId == _Nextion_componentId2)
      {
        NEXTION_SendCode("print n0.val");
        last_tick = HAL_GetTick();
        step_touch = SETTOUCH_STATE_PASSWORD;
      }
    break;
  
  
    case NEXTION_PAGE1:
      switch (nextionTouchEvent.componendId)
      {
        case _Nextion_componentId5:
          NEXTION_SendPage("2");
          nextion_page_state = NEXTION_PAGE2;
        break;
        
        case _Nextion_componentId6:
          NEXTION_SendPage("3");
          nextion_page_state = NEXTION_PAGE3;
        break;
    
        case _Nextion_componentId7:
          NEXTION_SendPage("4");
          nextion_page_state = NEXTION_PAGE4;
        break;
    
        case _Nextion_componentIdA:
          nextionBlueLightsStatus();
        break;
    
        case _Nextion_componentId8:
          nextionRedLightsStatus();
        break;
    
        case _Nextion_componentId4:
          nextionGreenLightsStatus();
        break;
    
        case _Nextion_componentIdC:
          NEXTION_SendCode("print n1.val");
          step_touch = SETTOUCH_STATE_TEMP;
          NEXTION_DMA_FLAG = DMA_FLAG_DISABLE;
          last_tick = HAL_GetTick();
          
        break;
    
        case _Nextion_componentIdE:
        last_tick = HAL_GetTick();
        NEXTION_SendCode("sleep=1");
        step_touch = SETTOUCH_STATE_SLEEP;
        break;
      }
    break;
  
  
    case NEXTION_PAGE2:
      switch (nextionTouchEvent.componendId)
      {
        case _Nextion_componentIdA:
          NEXTION_SendPage("1");
          nextionPage1LightsSatus ();
          nextion_page_state = NEXTION_PAGE1;
        break;
  
        case _Nextion_componentIdC:
          NEXTION_SendPage("3");
          nextion_page_state = NEXTION_PAGE3;
        break;
  
        case _Nextion_componentIdD:
          NEXTION_SendPage("4");
          nextion_page_state = NEXTION_PAGE4;
        break;
  
        case _Nextion_componentId9:
          last_tick = HAL_GetTick();
          step_time = SETTIME_STATE_SEND_HOUR;
          step_touch = SETTOUCH_STATE_TIME;
        break;
      }
    break;
  
  
    case NEXTION_PAGE3:
      switch (nextionTouchEvent.componendId)
      {
        case _Nextion_componentId2:
          NEXTION_DMA_FLAG = DMA_FLAG_DISABLE;
          NEXTION_SendPage("1");
          nextionPage1LightsSatus ();
          nextion_page_state = NEXTION_PAGE1;
        break;
  
        case _Nextion_componentId3:
          NEXTION_SendPage("2");
          nextion_page_state = NEXTION_PAGE2;
        break;
  
        case _Nextion_componentId5:
          NEXTION_SendPage("4");
          nextion_page_state = NEXTION_PAGE4;
        break;
  
        case _Nextion_componentIdA:
          last_tick = HAL_GetTick();
          step_alarm = SETALARM_STATE_SEND_HOUR;
          alarm_on_off = 1;
          step_touch = SETTOUCH_STATE_ALARM;
        break;
      }
    break;
  
  
    case NEXTION_PAGE4:
      switch (nextionTouchEvent.componendId)
      {
        case _Nextion_componentId4:
          NEXTION_SendPage("1");
          nextionPage1LightsSatus();
          nextion_page_state = NEXTION_PAGE1;
        break;
  
        case _Nextion_componentId5:
          NEXTION_SendPage("2");
          nextion_page_state = NEXTION_PAGE2;    
        break;
  
        case _Nextion_componentId6:
          NEXTION_SendPage("3");
          nextion_page_state = NEXTION_PAGE3;
        break;
  
        case _Nextion_componentId3:
          NEXTION_SendCode("print n0.val");
          last_tick = HAL_GetTick();
          step_touch = SETTOUCH_STATE_CHANGE_PASSWORD;
        break;
      }
    break;
  }
  nextionTouchEvent.componendId = NEXTION_COPMPONENT_ID_RESET;


  switch (step_touch)
  {
    case SETTOUCH_STATE_IDLE:
    break;

    case SETTOUCH_STATE_PASSWORD:
      nextionSetPassword();
    break;

    case SETTOUCH_STATE_TEMP:
      nextionSetTemp();
    break;

    case SETTOUCH_STATE_SLEEP:
      nextionSetSleep();
    break;

    case SETTOUCH_STATE_TIME:
      nextionSetTime();
    break;

    case SETTOUCH_STATE_ALARM:
      nextionSetAlarm();
    break;

    case SETTOUCH_STATE_CHANGE_PASSWORD:
      nextionSetChangePassword();
    break;
  }

  if(alarm_on_off == 1 && nextion_page_state == NEXTION_PAGE3)
  {
    nextionAlarmSendString();
  }

}

static void nextionAlarmSendString(void)
{
  sprintf(str, "alarm set successfully %02d:%02d", alarm_hour, Alarm_minute);
  NEXTION_SendString("t2", str);
}


static void nextionAlarmOperation(void)
{
      if(alarm_on_off == 1 && get_st_time().minute == Alarm_minute && get_st_time().hour == alarm_hour)
    {
      NEXTION_SendPage("6");
      alarm_on_off = 0;
      alarm_operation = 1;
    }else if(alarm_operation == 1)
    {
      HAL_GPIO_WritePin(MCU_BUZZER__3V3_GPIO_Port,MCU_BUZZER__3V3_Pin,1);
     
      if(nextionTouchEvent.pageNumber == 0x06)
      {
        HAL_GPIO_WritePin(MCU_BUZZER__3V3_GPIO_Port,MCU_BUZZER__3V3_Pin, GPIO_PIN_RESET);
        Alarm_minute = 50;
        alarm_hour = 50;
        alarm_operation = 0;

        switch (nextion_page_state)
        {
          case NEXTION_PAGE1:
            NEXTION_SendPage("1");
          break;
          case NEXTION_PAGE2:
            NEXTION_SendPage("2");
          break;
          case NEXTION_PAGE3:
            NEXTION_SendPage("3");
          break;
          case NEXTION_PAGE4:
            NEXTION_SendPage("4");
          break;
          case NEXTION_PAGE0:
          break;
        }
        nextionTouchEvent.componendId = 0;
      }
    }
}

static void nextionSetTemp(void)
{
  if(delay_tick_1ms_no_rst(&last_tick, 75))
  {
    sprintf(str, "%d", rxbuffer_uart1[0]);
    eeprom_read_array[7] = rxbuffer_uart1[0];
    NEXTION_SendValue("n1",str);
    EE24_Write(&ee24,7,rxbuffer_uart1,1,1000);
    step_touch = SETTOUCH_STATE_IDLE;
  }
}


static void nextionSetSleep(void)
{
  if(!delay_tick_1ms_no_rst(&last_tick,500))
  {
    nextionTouchEvent.TouchEvent = 0x00;
  }
  if(delay_tick_1ms_no_rst(&last_tick, 1400))
  {
    if (nextionTouchEvent.TouchEvent == 0x68)
    {
      NEXTION_SendCode("sleep=0");
      step_touch = SETTOUCH_STATE_IDLE;
    }
  }
}


static void nextionSetPassword(void)
{
  if(delay_tick_1ms(&last_tick, 50))
  {
    serial_message("sifre: %d",password);
    if(rxbuffer_uart1[0] == password)
    {
      NEXTION_SendPage("1");
      nextion_page_state = NEXTION_PAGE1; 
      nextionPage1LightsSatus();
    }
    step_touch = SETTOUCH_STATE_IDLE;
  }
}


static void nextionSetTime(void)
{
  uint8_t indata[1];
  switch (step_time)
  {
    case SETTIME_STATE_SEND_HOUR:
      NEXTION_SendCode("print n0.val");
      last_tick = HAL_GetTick();
      step_time = SETTIME_STATE_OPERATION_HOUR;
    break;

    case SETTIME_STATE_OPERATION_HOUR:
      if(delay_tick_1ms_no_rst(&last_tick,50))
      {
        indata[0] = rxbuffer_uart1[0];
        PCF85_SetHour(indata[0]);
        //EE24_Write(&ee24,4,indata,1,1000);
        step_time = SETTIME_STATE_SEND_MINUTE;
      }
    break;

    case SETTIME_STATE_SEND_MINUTE:
      NEXTION_SendCode("print n1.val");
      last_tick = HAL_GetTick();
      step_time = SETTIME_STATE_OPERATION_MINUTE;
    break;

    case SETTIME_STATE_OPERATION_MINUTE:
      if(delay_tick_1ms_no_rst(&last_tick, 50))
      {

        indata[0] = rxbuffer_uart1[0];
        PCF85_SetMinute(indata[0]);
        //EE24_Write(&ee24,5,indata,1,1000);
        step_time = SETTIME_STATE_SEND_SECOND;
      }
    break;

    case SETTIME_STATE_SEND_SECOND:
      NEXTION_SendCode("print n2.val");
      last_tick = HAL_GetTick();
      step_time = SETTIME_STATE_OPERATION_SECOND;
    break;

    case SETTIME_STATE_OPERATION_SECOND:
      if(delay_tick_1ms_no_rst(&last_tick,50))
      {
        indata[0] = rxbuffer_uart1[0];
        PCF85_SetSecond(indata[0]);
        step_time = SETTIME_STATE_SEND_DAY;
      }    
    break;

    case SETTIME_STATE_SEND_DAY:
      NEXTION_SendCode("print n3.val");
      last_tick = HAL_GetTick();
      step_time = SETTIME_STATE_OPERATION_DAY;
    break;

    case SETTIME_STATE_OPERATION_DAY:
      if(delay_tick_1ms_no_rst(&last_tick,50))
      {
        indata[0] = rxbuffer_uart1[0];
        PCF85_Setday(indata[0]);
        step_time = SETTIME_STATE_SEND_MONTH;
      }
    break;

    case SETTIME_STATE_SEND_MONTH:
      NEXTION_SendCode("print n4.val");
      last_tick = HAL_GetTick();
      step_time = SETTIME_STATE_OPERATION_MONTH;
    break;

    case SETTIME_STATE_OPERATION_MONTH:
      if(delay_tick_1ms_no_rst(&last_tick,50))
      {
        indata[0] = rxbuffer_uart1[0];
        PCF85_Setmonth(indata[0]);
        step_time = SETTIME_STATE_SEND_YEAR;
      }
    break;
    
    case SETTIME_STATE_SEND_YEAR:
      NEXTION_SendCode("print n5.val");
      last_tick = HAL_GetTick();
      step_time = SETTIME_STATE_OPERATION_YEAR;
    break;

    case SETTIME_STATE_OPERATION_YEAR:
      if(delay_tick_1ms_no_rst(&last_tick,50))
      {
        indata[0] = rxbuffer_uart1[0];
        PCF85_Setyear(indata[0]-178);
        NEXTION_SendString("t0", "update successfully");
        step_touch = SETTOUCH_STATE_IDLE;
      }
    break;    
  }
}    


static void nextionSetAlarm(void)
{
  switch (step_alarm)
  {
  case   SETALARM_STATE_SEND_HOUR:
    NEXTION_SendCode("print n2.val");
    step_alarm = SETALARM_STATE_OPERATION_HOUR;
  break;

  case SETALARM_STATE_OPERATION_HOUR:
    if(delay_tick_1ms_no_rst(&last_tick,75))
    {
      uint8_t indata;
      indata = rxbuffer_uart1[0];
      alarm_hour = indata;
      step_alarm = SETALARM_STATE_SEND_MINUTE;
    }
  break;

  case SETALARM_STATE_SEND_MINUTE:
    NEXTION_SendCode("print n1.val");
    step_alarm = SETALARM_STATE_OPERATION_MINUTE;
  break;

  case SETALARM_STATE_OPERATION_MINUTE:
    if(delay_tick_1ms_no_rst(&last_tick, 200))
    {
      uint8_t indata;
      indata = rxbuffer_uart1[0];
      Alarm_minute = indata;
      step_alarm = SETALARM_STATE_SEND_ALARMTIME;
    }
  break;

  case SETALARM_STATE_SEND_ALARMTIME:
    sprintf(str, "alarm set successfully %02d:%02d", alarm_hour, Alarm_minute);
    NEXTION_SendString("t2", str);
    step_touch = SETTOUCH_STATE_IDLE;
  break;
  }
}


static void nextionSetChangePassword(void)
{
      if(delay_tick_1ms_no_rst(&last_tick, 75))
    {
      EE24_Write(&ee24,0,rxbuffer_uart1,1,1000);
      password = rxbuffer_uart1[0];
      rxbuffer_uart1[0] = -1;
      NEXTION_SendPage("0");
      NEXTION_SendValue("n0","0");
      nextion_page_state = Nextion_Page0;
      NEXTION_DMA_FLAG = DMA_FLAG_DISABLE;
      step_touch = SETTOUCH_STATE_IDLE;
    }
}


static void nextionPage1LightsSatus (void)
{
  sprintf(str, "%d", eeprom_read_array[7]);
  NEXTION_SendValue("n1",str);
  if(status_blue == 1)
  {
    NEXTION_SendCode("b6.pco=8507");
  }else
  {
    NEXTION_SendCode("b6.pco=65535");
  }
  if(status_red == 1)
  {
    NEXTION_SendCode("b5.pco=61440");
  }else
  {
    NEXTION_SendCode("b5.pco=65535");
  }
  if(status_green == 1)
  {
    NEXTION_SendCode("b0.pco=18248");
  }else
  {
    NEXTION_SendCode("b0.pco=65535");
  }
}


static void nextionBlueLightsStatus(void)
{
    if(status_blue==0)
  {
    status_blue=!status_blue;
    HAL_GPIO_WritePin(RED_LED_GPIO_Port,BLUE_LED_Pin, status_blue);
    NEXTION_SendCode("b6.pco=8507");
  }else
  {
    status_blue=!status_blue;
    HAL_GPIO_WritePin(RED_LED_GPIO_Port,BLUE_LED_Pin, status_blue);
    NEXTION_SendCode("b6.pco=65535");
  }
}


static void nextionRedLightsStatus(void)
{
    if(status_red==0)
  {
    status_red=!status_red;
    HAL_GPIO_WritePin(RED_LED_GPIO_Port,RED_LED_Pin, status_red);
    NEXTION_SendCode("b5.pco=61440");
  }else{
    status_red=!status_red;
    HAL_GPIO_WritePin(RED_LED_GPIO_Port,RED_LED_Pin, status_red);
    NEXTION_SendCode("b5.pco=65535");
  }
}


static void nextionGreenLightsStatus(void)
{
        if(status_green==0)
      {
        status_green=!status_green;
        HAL_GPIO_WritePin(RED_LED_GPIO_Port,GREEN_LED_Pin, status_green);
        NEXTION_SendCode("b0.pco=18248");
      }else{
        status_green=!status_green;
        HAL_GPIO_WritePin(RED_LED_GPIO_Port,GREEN_LED_Pin, status_green);
        NEXTION_SendCode("b0.pco=65535");
      }
}


void Prosess_PacketComminication (void)
{
  if(uart_dma_flag)
  {
    switch (packetsteps)
    {
    case PACKAGE_İS_VALİD:
      HAL_Delay(150);  
      if(isPacketValid(MainBuf,120) )
      {
        packetsteps = PACKAGE_ENDING;
        break;
      }
      packetsteps = PACKAGE_START_BYTE;
    break;

    case PACKAGE_START_BYTE:
      {

        packetData = function_ptr[PACKAGE_START_BYTE](MainBuf);
        if(packetData.Start_byte == 0)
        {
          packetsteps = PACKAGE_ENDING;
          break;
        }
        serial_message("start byte: 0x%02X\n", packetData.Start_byte);
        packetsteps = PACKAGE_LENGTH;
      }
      break;

    case PACKAGE_LENGTH:
      {
        packetData = function_ptr[PACKAGE_LENGTH](MainBuf);
        serial_message("lenght: %d \n",packetData.Data_Lengh);
        packetsteps = PACKAGE_PAYLOUD;
      }
      break;
      case PACKAGE_PAYLOUD:
          packetData = function_ptr[PACKAGE_PAYLOUD](MainBuf);
          for(int i=0; i<packetData.Data_Lengh; i++)
          serial_message("payload: 0x%02X \n",packetData.Payload[i]);
          packetsteps = PACKAGE_CRC;
      break;
      
      case PACKAGE_CRC:
      packetData = function_ptr[PACKAGE_CRC](MainBuf);
      for(int i=0; i<3; i++)
      serial_message("CRC: 0x%02X \n",packetData.CRC_byte[i]);
      packetsteps = PACKAGE_STOP_BYTE;
      break;

      case PACKAGE_STOP_BYTE:
      packetData =function_ptr[PACKAGE_STOP_BYTE](MainBuf);
      serial_message("stop byte: 0x%02X", packetData.Stop_byte);
      packetsteps = PACKAGE_ENDING;
      break;

      case PACKAGE_ENDING:
      {
        uart_dma_flag = DMA_FLAG_DISABLE;
        oldPos = newPos = 0; 
        memset((uint8_t*)MainBuf,0,MainBuf_SIZE );
        packetsteps = PACKAGE_İS_VALİD;
      }
      break;
    }

  }
}


nextion_page_state_t get_nextion_page_state(void)
{
  return nextion_page_state;
}




