

#include "app.h"
#include "main.h"
#include "stm32l4xx_hal_gpio.h"
#include <stdint.h>

void wash_init(void);
void wash_update(void);

void rinse_init(void);
void rinse_update(void);
void agitsoak_init(void);
void agitsoak_update(void);


#define    MOTOR_CCW_ON()   HAL_GPIO_WritePin(MOTOR_CCW_GPIO_Port, MOTOR_CCW_Pin, GPIO_PIN_SET)
#define    MOTOR_CCW_OFF()  HAL_GPIO_WritePin(MOTOR_CCW_GPIO_Port, MOTOR_CCW_Pin, GPIO_PIN_RESET)

#define    MOTOR_CW_ON()   HAL_GPIO_WritePin(MOTOR_CW_GPIO_Port, MOTOR_CW_Pin, GPIO_PIN_SET)
#define    MOTOR_CW_OFF()  HAL_GPIO_WritePin(MOTOR_CW_GPIO_Port, MOTOR_CW_Pin, GPIO_PIN_RESET)


typedef enum
{
    WASH_AGIT = 0U,
    WASH_SOAK,
    WASH_END

}wash_types_t;

typedef enum
{
    WASH_RAMP = 0U,
    WASH_RAMP_IDLE,
    WASH_RAMP_END
}wash_ramp_types_t;

typedef struct 
{
    wash_ramp_types_t wash_type;
    uint8_t           time;
}ramp_r3_cfg_t;

typedef struct 
{
    wash_types_t  wash_type;
    uint8_t           time;
}wash_agitsoak_cfg_t;


const wash_agitsoak_cfg_t agitsoak_cfg_data[][10]=
{   
{         
        {WASH_SOAK, 2},
        {WASH_AGIT, 1},
        {WASH_SOAK, 2},
        {WASH_AGIT, 1},
        {WASH_END,  2}
    } ,  
    {         
        {WASH_SOAK, 2},
        {WASH_AGIT, 1},
        {WASH_SOAK, 2},
        {WASH_AGIT, 1},
        {WASH_END,  2}
    }   

};

const ramp_r3_cfg_t ramp_r3_cfg_data[][15] =
{
    {
    {WASH_RAMP,         1},
    {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP_END,     0}

    }
    ,
    {
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         1},
        {WASH_RAMP_IDLE,    1},
        {WASH_RAMP_END,     0}
    }
};
const ramp_r3_cfg_t ramp_ER_cfg_data[][2] =
{
    {
        {WASH_RAMP_IDLE,    10},
        {WASH_RAMP_END,     0}

    }
    ,
    {

        {WASH_RAMP_IDLE,    10},
        {WASH_RAMP_END,      0}
    }
};

typedef struct app
{   
    const ramp_r3_cfg_t (*rampR3)[15];
    const ramp_r3_cfg_t (*rampER)[2];

    const wash_agitsoak_cfg_t    agitsoak[6];

    
}wash_rinse_cfg_t;

const wash_rinse_cfg_t wash_rinse_cfg_data[]=
{
    {
        ramp_r3_cfg_data,
        ramp_ER_cfg_data,

        {
            {WASH_AGIT, 1},
            {WASH_SOAK, 2},
            {WASH_AGIT, 1},
            {WASH_SOAK, 2},
            {WASH_AGIT, 1},
            {WASH_END,  2}
        }
    }
};

/*====================================================================================================================================================*/
/*====================================================================================================================================================*/
/*====================================================================================================================================================*/

void wash_init(void)
{

}


void wash_update(void)
{


}

/*====================================================================================================================================================*/
/*====================================================================================================================================================*/
/*====================================================================================================================================================*/

void rinse_init(void)
{


}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void rinse_update(void)
{
    const wash_agitsoak_cfg_t *rinse_data;
    rinse_data = &wash_rinse_cfg_data;

}

/*====================================================================================================================================================*/
/*====================================================================================================================================================*/
/*====================================================================================================================================================*/

void agitsoak_init(void)
{


}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void agitsoak_update(void)
{
    const wash_agitsoak_cfg_t *agitsoak_data;
    agitsoak_data = &wash_rinse_cfg_data;

    switch (expression)
    {
    case WASH_AGIT:
        /* code */
        break;
    case WASH_SOAK:
        /* code */
        break;
    case WASH_END:
        break;
        
    
    default:
        break;
    }


}
