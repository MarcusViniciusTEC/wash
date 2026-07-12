

#include "app.h"
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include <stdint.h>
#include <stdbool.h>

void wash_init(void);
void wash_update(void);



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
    uint16_t           time;
}ramp_r3_cfg_t;

typedef struct 
{
    wash_types_t  wash_type;
    uint16_t           time;
}wash_agitsoak_cfg_t;


const wash_agitsoak_cfg_t agitsoak_cfg_data[][3][10]=
{   
{
    {         
            {WASH_SOAK, 1000},
            {WASH_AGIT, 500},
            {WASH_SOAK, 1000},
            {WASH_AGIT, 1500},
            {WASH_END,  200}
        } ,  
        {         
            {WASH_SOAK, 1000},
            {WASH_AGIT, 500},
            {WASH_SOAK, 1000},
            {WASH_AGIT, 1500},
            {WASH_END,  200}
        }  , 
        {         
            {WASH_SOAK, 1000},
            {WASH_AGIT, 500},
            {WASH_SOAK, 1000},
            {WASH_AGIT, 1500},
            {WASH_END,  200}
        }  
    }
    ,
    {
        {         
            {WASH_SOAK, 1000},
            {WASH_AGIT, 500},
            {WASH_SOAK, 1000},
            {WASH_AGIT, 1500},
            {WASH_END,  200}
        } ,  
        {         
            {WASH_SOAK, 1000},
            {WASH_AGIT, 500},
            {WASH_SOAK, 1000},
            {WASH_AGIT, 1500},
            {WASH_END,  200}
        },
        {         
            {WASH_SOAK, 1000},
            {WASH_AGIT, 500},
            {WASH_SOAK, 1000},
            {WASH_AGIT, 1500},
            {WASH_END,  200}
        }    
    }
};

const ramp_r3_cfg_t ramp_r3_cfg_data[][15] =
{
    {
    {WASH_RAMP,         1},
    {WASH_RAMP_IDLE,    1},
        {WASH_RAMP,         10000},
        {WASH_RAMP_IDLE,    25000},
        {WASH_RAMP,         10000},
        {WASH_RAMP_IDLE,    25000},
        {WASH_RAMP,         10000},
        {WASH_RAMP_IDLE,    25000},
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
        {WASH_RAMP_IDLE,    25000},
        {WASH_RAMP_END,     0}

    }
    ,
    {

        {WASH_RAMP_IDLE,    25000},
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

typedef struct 
{
   uint8_t program;
   uint8_t level;
   uint8_t wash_type;
   uint8_t perfil;
}hmi_data_t;

typedef struct 
{
    
    void (*init)(void);
    void (*pupdate)(void);
    void (*set_hmi_data)(const hmi_data_t *data);
    void (*deinit)(void);

}wash_task_data_t;

void rinse_init(void);
void rinse_update(void);
void rinse_hmi(const hmi_data_t *data);
void rinse_deinit(void);

void agitsoak_init(void);
void agitsoak_update(void);
void agitsoak_hmi(const hmi_data_t *data);
void agitsoak_deinit(void);



const wash_task_data_t wash_task_data [] =
{
    {
        rinse_init,
        rinse_update,
        rinse_hmi,
        rinse_deinit
    },
    {

        agitsoak_init,
        agitsoak_update,
        agitsoak_hmi,
        agitsoak_deinit
    }
};


const hmi_data_t hmi_data[] =
{
    {
        0u,
        0u,
        0u,
        0u
    }
};


void wash_init(void)
{
    agitsoak_init();
}

typedef enum
{
    WASH_TASK_INIT = 0U,
    WASH_TASK_HMI,
    WaSH_TASK_UPDATE,
    WASH_TASK_DEINIT
}wash_task_types_t;

uint8_t i = 0;

wash_task_types_t state  = WASH_TASK_INIT;

void wash_update(void)
{

    switch (state)
    {
        case WASH_TASK_INIT:
            wash_task_data[i].init();
            state = WASH_TASK_HMI;
        break;
        case WASH_TASK_HMI:
            wash_task_data[i].set_hmi_data(hmi_data);
            state = WaSH_TASK_UPDATE;
        break;
        case WaSH_TASK_UPDATE:
            
            wash_task_data[i].pupdate();
        break;
        case WASH_TASK_DEINIT:
            wash_task_data[i].deinit();
        break;
        default:
        break;
    } 
}


/*====================================================================================================================================================*/
/*====================================================================================================================================================*/
/*====================================================================================================================================================*/
void rinse_process(bool valve_type);
void rinse_process_rampRx(void);
void rinse_process_rampEx(void);

typedef enum
{
    RINSE_IDLE = 0U,
    RINSE_START,
    RINSE_MONO ,
    RINSE_DOUBLE,
    RINSE_END,
}rinse_types__t_;


typedef enum
{
    RINSE_PROC_REUSE_WATTER ,
    RINSE_PROC_DRAIN,
    RINSE_PROC_RAMP_Rx,
    RINSE_PROC_RAMP_Ex,
    RINSE_PROC_WATTER_FILL,
    RINSE_PROC_AGIT_2MIN,
    RINSE_PROC_AGITSOAK
    
}rinse_states_types_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/


uint8_t               ramp_type = 0; /*fazer uma função que analiza o nivel setado e define */
rinse_states_types_t rinse_states = RINSE_PROC_REUSE_WATTER ;

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void rinse_init(void)
{


}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void rinse_update(void)
{
    switch (2)
    {
        case RINSE_IDLE: 
        break;
        case RINSE_START:
        break;
        case RINSE_MONO: 
            rinse_process(0);
        break;
        case RINSE_DOUBLE:
            rinse_process(1);
        break;
        case RINSE_END:
        break;
        default:
        break;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void rinse_hmi(const hmi_data_t *data)
{

}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void rinse_deinit(void)
{


}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void rinse_process(bool valve_type)
{

    const wash_rinse_cfg_t *rinse_data;
    rinse_data = &wash_rinse_cfg_data[0];

    uint32_t now = HAL_GetTick();

    switch (rinse_states)
    {
        case RINSE_PROC_REUSE_WATTER:
            rinse_states = RINSE_PROC_DRAIN;
        break;
        case RINSE_PROC_DRAIN:
            rinse_states = RINSE_PROC_RAMP_Rx;
        break;
        case RINSE_PROC_RAMP_Rx:
            switch (rinse_data->rampR3[ramp_type][index].wash_type)
            {
                case WASH_RAMP:
                    if( now  - last_time >= rinse_data->rampR3[ramp_type][index].time)
                    {
                        index++;
                        last_time = now ;
                        MOTOR_CCW_OFF();
                    }
                    else
                    {
                        MOTOR_CCW_ON();
                    }
                break;
                case WASH_RAMP_IDLE:
                    if( now  - last_time >= rinse_data->rampR3[ramp_type][index].time)
                    {
                        index++;
                        last_time = now ;
                    }
                break;
                case WASH_RAMP_END:
                    MOTOR_CCW_OFF();
                    rinse_states = RINSE_PROC_RAMP_Ex;
                break;
                default:
                break;
            }
        break;
        case RINSE_PROC_RAMP_Ex:
            switch (rinse_data->rampER[ramp_type][index].wash_type)
            {
                case WASH_RAMP:
                    if( now  - last_time >= rinse_data->rampER[ramp_type][index].time)
                    {
                        index++;
                        last_time = now ;
                        MOTOR_CCW_OFF();
                    }
                    else
                    {
                        MOTOR_CCW_ON();
                    }
                break;
                case WASH_RAMP_IDLE:
                    if( now  - last_time >= rinse_data->rampER[ramp_type][index].time)
                    {
                        index++;
                        last_time = now ;
                    }
                break;
                case WASH_RAMP_END:
                    MOTOR_CCW_OFF();
                    rinse_states = RINSE_PROC_WATTER_FILL;
                break;
                default:
                break;
            }
        break;
        case RINSE_PROC_WATTER_FILL:
        break;
        case RINSE_PROC_AGIT_2MIN:
        break;
        case RINSE_PROC_AGITSOAK:
        break;
        default:
        break;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

static uint32_t last_time;
static uint8_t index;

void rinse_process_rampRx(void)
{



}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void rinse_process_rampEx(void)
{


}

/*====================================================================================================================================================*/
/*====================================================================================================================================================*/
/*====================================================================================================================================================*/

static void agitsoak_process(void);
static void agitsoak_motor_on();
static void agitsoak_motor_off();

#define DOOR_STATE() (HAL_GPIO_ReadPin(DOOR_GPIO_Port, DOOR_Pin))

typedef enum
{
    MOTOR_OFF = 0U,
    MOTOR_ON,
    MOTOR_IDLE

}agitsoak_motor_state_types_t;

typedef enum
{
    AGIISOAK_IDLE,
    AGITSOAK_INIT,
    AGITSOAK_START,
    AGITSOAK_FILL_WATTER,
    AGITSOAK_SET_ATUADOR,
    AGITSOAK_RUNN,
    AGITSOAK_STOP,
    AGITSOAK_END,
    AGITSOAK_DEINIT
}agitsoak_process_type_t;

typedef struct 
{
    agitsoak_motor_state_types_t motor_state;
    bool door_state;
    wash_types_t state;
    uint32_t last_time;
    uint8_t index;
    uint8_t wash_index;
    agitsoak_process_type_t process_state;
    uint8_t program;
}agitsoak_ctrl_t;


/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

static agitsoak_ctrl_t agitsoak_ctrl = {0};
static hmi_data_t      agit_soak_hmi_data = {0};

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void agitsoak_init(void)
{
    
    agitsoak_ctrl.index         = 0;
    agitsoak_ctrl.wash_index    = 0;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void agitsoak_update(void)
{
    if(DOOR_STATE() == GPIO_PIN_SET)
    {
        agitsoak_ctrl.process_state = AGITSOAK_STOP;
    }

    switch (agitsoak_ctrl.process_state)
    {
        case AGIISOAK_IDLE:
        break;
        case AGITSOAK_INIT:
        break;
        case AGITSOAK_START:
            agitsoak_ctrl.process_state = AGITSOAK_FILL_WATTER;
        break;
        case AGITSOAK_FILL_WATTER:
            agitsoak_ctrl.process_state = AGITSOAK_SET_ATUADOR;
        break;
        case AGITSOAK_SET_ATUADOR:
            agitsoak_ctrl.process_state = AGITSOAK_RUNN;
        break;
        case AGITSOAK_RUNN:
            agitsoak_process();
        break;
        case AGITSOAK_STOP:
            agitsoak_ctrl.last_time = HAL_GetTick();
            MOTOR_CCW_OFF();
            MOTOR_CW_OFF(); 
        if(DOOR_STATE() == !GPIO_PIN_SET)
        {
            agitsoak_ctrl.process_state = AGITSOAK_START;
        }
        break;
        case AGITSOAK_END:
            /*AGITAÇÃO COMPLETA*/
        break;
        case AGITSOAK_DEINIT:

        break;
        default:
        break;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

static void agitsoak_process(void)
{
    const wash_agitsoak_cfg_t *agitsoak_data;
    agitsoak_data = &agitsoak_cfg_data[agitsoak_ctrl.program][agitsoak_ctrl.wash_index][agitsoak_ctrl.index];

    uint32_t now = HAL_GetTick();

    switch (agitsoak_data->wash_type)
    {
        case WASH_AGIT:
        if( now  - agitsoak_ctrl.last_time >= agitsoak_data->time)
        {
                agitsoak_ctrl.index++;
                agitsoak_ctrl.last_time = now ;
                MOTOR_CCW_OFF();
        }
        else
        {
                MOTOR_CCW_ON();
        }
        break;
        case WASH_SOAK:
            MOTOR_CCW_OFF();
            MOTOR_CW_ON();
        if(now  - agitsoak_ctrl.last_time >= agitsoak_data->time)
        {
                agitsoak_ctrl.index++;
                agitsoak_ctrl.last_time = now ;
                MOTOR_CW_OFF();
        }    
        break;
        case WASH_END:
            if(agitsoak_ctrl.wash_index < 2)
            {
                agitsoak_ctrl.wash_index++;
                agitsoak_ctrl.index = 0;
            }
            else
            {
                agitsoak_ctrl.process_state = AGITSOAK_END;
                agitsoak_ctrl.index = 0;
                agitsoak_ctrl.wash_index = 0;
            }
        break;
        default:
        break;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void agitsoak_hmi(const hmi_data_t *data)
{
    agitsoak_ctrl.wash_index    = data->wash_type;
    agitsoak_ctrl.program       = data->program;
    agitsoak_ctrl.process_state = AGITSOAK_START;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void agitsoak_deinit(void)
{
    agitsoak_ctrl.index         = 0;
    agitsoak_ctrl.wash_index    = 0;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/


