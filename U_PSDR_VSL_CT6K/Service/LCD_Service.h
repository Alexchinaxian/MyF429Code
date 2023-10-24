/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : LCD_Service.h 
用途 : LCD显示服务层头文件
***********************************************************************************************************************/
#ifndef _LCD_SERVICE_H_
#define _LCD_SERVICE_H_

#include "HeadFile.h"
#include "SR_VirtualDevice.h"

#pragma pack(1)

#define DISPLAY_CACHE_SIZE                                      (128)               //设置显示缓存区大小
#define DISPLAY_MENU_COUNT                                      (4)                 //菜单界面输入项数量
#define DISPLAY_DETAILEDINFO_COUNT                              (8)                 //详细数据界面输入项数量
#define DISPLAY_RunningStatus_ITEM_COUNT                        (1)                 //状态机显示页面数量
#define DISPLAY_Machine_ITEM_COUNT                              (3)                 //整机数据界面显示数量
#define DISPLAY_GridInfo_ITEM_COUNT                             (3)                 //电网数据界面显示数量
#define DISPLAY_PVInfo_ITEM_COUNT                               (2)                 //光伏数据界面显示数量
#define DISPLAY_BatteryInfo_ITEM_COUNT                          (2)                 //电池数据界面显示数量
#define DISPLAY_PowerLoadInfo_ITEM_COUNT                        (2)                 //负载数据界面显示数量
#define DISPLAY_GenInfo_ITEM_COUNT                              (2)                 //发电机数据界面显示数量
#define DISPLAY_PowerLoad_ITEM_COUNT                            (2)                 //负载数据界面显示数量
#define DISPLAY_Generato_ITEM_COUNT                             (1)                 //发电机数据界面显示数量
#define DISPLAY_Factory_ITEM_COUNT                              (2)                 //出厂数据界面显示数量
#define DISPLAY_SYS_SETTING_ITEM_COUNT                          (6)                 //系统设置界面显示数量
#define DISPLAY_DETALOG_COUNT                                   (3)                 //历史记录界面显示数量
#define DISPLAY_SET_ITEM_COUNT                                  (6)                 //设置界面输入相数量
#define DISPLAY_SET_SYSTEM_ITEM_COUNT                           (9)                //系统设置界面输入相数量
//#define DISPLAY_SET_SYSTEM_LANGUAGE_ITEM_COUNT                (9)                //语言设置界面输入相数量
#define DISPLAY_SET_SYSTEM_LANGUAGE_ITEM_COUNT                  (2)                 //语言设置界面输入相数量
#define DISPLAY_SET_SYSTEM_PV_ITEM_COUNT                        (3)                 //光伏设置界面输入相数量
#define DISPLAY_SET_SYSTEM_PVCONTROLEAY_ITEM_COUNT              (2)                 //光伏控制设置界面输入相数量
#define DISPLAY_SET_SYSTEM_TIME_ITEM_COUNT                      (15)                //时间设置界面输入相数量
#define DISPLAY_SET_GRID_REACTIVEPOWERCONTROLWAY_COUNT          (2)                 //无功控制方式界面输入相数量
#define DISPLAY_SET_GRID_REACTIVEPOWER_COUNT                    (5)                 //无功功率界面输入相数量
#define DISPLAY_SET_GRID_POWERFACTOR_COUNT                      (6)                 //功率因数界面输入相数量
#define DISPLAY_SET_SYSTEM_PASSWORD_COUNT                       (18)                //密码设置界面输入相数量
#define DISPLAY_SET_SYSTEM_SERIAL_ITEM_COUNT                    (5)                 //串口设置界面输入相数量
#define DISPLAY_SET_SYSTEM_SERIAL_ADDRESS_ITEM_COUNT            (3)                 //串口地址设置界面输入相数量
#define DISPLAY_SET_SYSTEM_SERIAL_BAUD_ITEM_COUNT               (3)                 //串口波特率设置界面输入相数量
#define DISPLAY_SET_SYSTEM_RESET_ITEM_COUNT                     (2)                 //通信复位设置界面输入相数量
#define DISPLAY_SET_SYSTEM_ENABLE_ITEM_COUNT                    (2)                 //使能界面输入相数量
#define DISPLAY_SET_SYSTEM_PROTECT_ITEM_COUNT                   (16)                //保护界面输入相数量
#define DISPLAY_SET_SYSTEM_ENABLE_CLASS_COUNT                   (23)                //使能类别输入相数量
#define DISPLAY_SET_SYSTEM_STRATEGY_CLASS_COUNT                 (6)                 //系统策略输入相数量
#define DISPLAY_SET_SYSTEM_STRATEGY_TPFV_PERIOD_COUNT           (3)                 //系统策略TPFV时间段输入相数量
#define DISPLAY_SET_SYSTEM_STRATEGY_TPFV_CLASS_COUNT            (4)                 //系统策略TPFV类别数量
#define DISPLAY_SET_SYSTEM_STRATEGY_TPFV_NUMBER_COUNT           (8)                 //系统策略TPFV输入数字数量
#define DISPLAY_SET_SYSTEM_STRATEGY_BACKUP_RATEPOWER_COUNT      (5)                 //备电策略输入相数量
#define DISPLAY_SET_SYSTEM_STRATEGY_GEN_SOC_COUNT               (6)                 //发电机策略输入相数量
#define DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_CLASS_COUNT         (2)                 //定时充放电策略类别数量
#define DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_PERIOD_COUNT        (4)                 //定时充放电策略类别数量
#define DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_INPUT_COUNT         (19)                //定时充放电策略数字输入数量
#define DISPLAY_SET_SYSTEM_CT_ITEM_COUNT                        (9)                 //CT设置界面输入相数量
#define DISPLAY_SET_BMS_ITEM_COUNT                              (2)                 //BMS设置输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT                              (2)                 //BMS类型设置输入相数量
#define DISPLAY_SET_BMS_MANUFACTURER_COUNT                      (2)                 //BMS厂商设置输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LI_ION_PARASET               (4)                 //LI BMS类型设置输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LI_COM_WAY                   (2)                 //LI BMS类型设置COM输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LI_SOC_COUNT                 (6)                 //LI BMS类型设置SOC输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LI_CURRENT_COUNT             (10)                 //LI BMS类型设置CURRENT输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LI_OVERPROTECT_COUNT         (6)                 //LI BMS类型设置OVERPROTECT输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LEAD                         (5)                 //LEAD BMS类型设置输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LEAD_ACID_PARASET            (3)                 //LI BMS类型设置输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LEAD_CAPANDCUR_COUNT         (13)                 //LEAD BMS类型设置CAPANDCUR输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LEAD_SOC_COUNT               (6)                 //LEAD BMS类型设置SOC输入相数量
#define DISPLAY_SET_BMS_TYPE_COUNT_LEAD_VOLTPOINT_COUNT         (12)                //LEAD BMS类型设置VOLTPOINT输入相数量
#define DISPLAY_SET_GEN_ITEM_COUNT                              (5)                 //发电机设置输入相数量
#define DISPLAY_SET_GEN_USAGE_COUNT                             (3)                 //干接点作用输入相数量
#define DISPLAY_SET_GEN_DRYLRY_COUNT                            (2)                 //干接点输入相数量
#define DISPLAY_SET_GEN_POWERPARA_COUNT                         (8)                 //发电机功率参数字符跳动
#define DISPLAY_SET_GEN_INTELLOAD_COUNT                         (6)                 //智能负载参数字符跳动
#define DISPLAY_SET_GRID_ITEM_COUNT                             (7)               //电网设置输入相数量
#define DISPLAY_SET_GRIDPOWER_ITEM_COUNT						(2)               //功率设置输入项数量
#define DISPLAY_SET_GRID_SR_ITEM_COUNT                          (5)                 //电网安规设置输入相数量
#define DISPLAY_SET_GRID_PRICE_ITEM_COUNT                       (4)                 //电网电价设置输入相数量
#define DISPLAY_SET_GRID_PRICE_INPUT_COUNT                      (4)                 //电网电价设置输入相数量
#define DISPLAY_SET_TPFV_PRICE_PERIOD_ITEM_COUNT                (4)                 //TPFV时间段设置界面设置相数量
#define DISPLAY_SET_TPFV_TIME_ITEM_COUNT                        (12)                //TPFV时间设置界面输入相数量
#define DISPLAY_LOGIN_PASSWORD_COUNT                            (6)                 //登陆界面输入相数量
#define DISPLAY_STATISTICS_ITEM_COUNT                           (8)                 //统计界面显示页面数量
#define DISPLAY_SYSTEM_ITEM_COUNT                               (4)                 //系统界面显示页面数量
#define DISPLAY_UPGRADE_ITEM_COUNT                              (4)                 //升级界面显示页面数量
#define DISPLAY_REALTIME_ITEM_COUNT                             (9)                 //实时数据界面显示页面数量
#define DISPLAY_DATA_PERPAGE_MAX_ITEM                           (3)                 //故障告警、操作记录显示最大条数
#define DISPLAY_DATA_NAME_CACHE_SIZE                            (16)                //设置显示缓存区大小
#define DISPLAY_TIME_CACHE_SIZE                                 (20)                //时间显示缓存区大小
#define DISPLAY_SET_SYSTEM_CONFIRM_ITEM_COUNT                   (3)                 //确认界面类别数量
#define DISPLAY_PRICE_MAX_VLAUEE                                (100.0)             //市电电价最大值
#define AUTOPAGERCONTER                                         (500)               //无按键操作计时
#define KEYACTIONNULLCONTER                                     (30000)             //无按键操作计时
#define DEVICERATEDPOWER                                        (6000)              //设备额定功率
#define DISPLAY_STATISTICS_COUNT                                (4)                 //统计页面输入量
#define DISPLAY_STATISTICS_DAY_COUNT                            (4)                 //当日统计页面输入量
#define DISPLAY_STATISTICS_MONTH_COUNT                          (4)                 //当月统计页面输入量
#define DISPLAY_STATISTICS_YEAR_COUNT                           (4)                 //当年统计页面输入量
#define DISPLAY_STATISTICS_ALL_COUNT                            (4)                 //累计统计页面输入量
#define DISPLAY_Policysettings_ALL_COUNT                        (4)                 //策略设置页面显示量
#define DISPLAY_StrategyStartTime_COUNT                         (7)                 //开始时间页面输入量
#define DISPLAY_StrategyStartPower_ALL_COUNT                    (6)                 //结束时间结束页面输入量
#define DISPLAY_StrategySOC_ALL_COUNT                           (3)                 //SOC输入量
#define DISPLAY_StrategyPower_ALL_COUNT                         (3)                 //Power输入量
#define DISPLAY_Policysettings_ALL_COUNT                        (4)                 //策略设置页面显示量
#define DISPLAY_StrategyBackupPower_ALL_COUNT                   (6)                 //Power输入量

typedef enum
{
    CONFIRMSOURCE_NONE,                                  //清除故障告警
    CONFIRMSOURCE_CLEARFAULT,                            //清除故障告警    
    CONFIRMSOURCE_CLEARRECORD,                           //清除操作记录
    CONFIRMSOURCE_FACTORY,                               //出厂设置
    CONFIRMSOURCE_BLUETOOTHRESET,                        //蓝牙复位设置
    CONFIRMSOURCE_WIFIRESET,                             //wifi复位设置
}ConfirmSource_TypeDef;

typedef enum
{
    TIP_PASSWORD_SET_SHORT,         //密码设置:请输入6位密码    
    TIP_PASSWORD_SET_ERROR,         //密码设置:旧的密码输入错误
    TIP_PASSWORD_SET_DIFFERENCET,   //密码设置:两次输入的新密码不一致
    TIP_PASSWORD_SET_OVERLAP,       //密码设置:输入的新密码和历史密码重合
    TIP_LOGIN_ERROR,                //密码校验:进入登陆界面，密码校验错误
    TIP_PASSED                      //设置ok
}Tip_TypeDef;


typedef enum
{
    DISPLAY_INIT,          //DISPLAY模块初始化
    DISPLAY_RUNNING,       //DISPLAY模块运行
    DISPLAY_DESTRCUCTION,  //DISPLAY模块析构
    DISPLAY_STATE_NULL 
}DisplayStatus_TypeDef;

//语言类型
typedef enum
{
    WEEK_SUNDAY,   //星期日
    WEEK_MONDAY,   //星期一
    WEEK_TUESDAY,  //星期二 
    WEEK_WEDNESDAY,//星期三 
    WEEK_THURSDAY, //星期四
    WEEK_FRIDAY,   //星期五
    WEEK_SATURDAY, //星期六
    WEEK_NULL
}Week_TypeDef;

//统计时间分类
typedef enum
{
    STATISTICS_TIME_Day,    //日
    STATISTICS_TIME_Month,  //月 
    STATISTICS_TIME_Year,   //年 
    STATISTICS_TIME_Total,  //总计
    STATISTICS_TIME_NULL
}STATISTICS_TIME_TypeDef;

//统计数据类型分类
typedef enum
{
    STATISTICS_TYPE_PV,       //光伏
    STATISTICS_TYPE_Load,     //负载 
    STATISTICS_TYPE_Output,   //输出
    STATISTICS_TYPE_Input,    //输入
    STATISTICS_TYPE_Charge,   //充电 
    STATISTICS_TYPE_Discharge,//放电
    STATISTICS_TYPE_NULL
}STATISTICS_TYPE_TypeDef;


//语言类型
typedef enum
{
    PAGE_ONE = 0,   //第一页
    PAGE_TWO,       //第二页 
    PAGE_THREE,     //第三页 
    PAGE_FOUR,      //第四页
    PAGE_FIVE,      //第五页
    PAGE_SIX,       //第六页
    PAGE_SEVEN,     //第七页
    PAGE_EIGHT,     //第八页
    PAGE_NINE,      //第九页
    PAGE_TEN,       //第十页
    PAGE_ELEVEN,    //第十一页
    PAGE_NULL
}Page_TypeDef;


//语言类型
typedef enum
{
    LANGUAGE_ENGLISH,//英语 
    LANGUAGE_CHINESE,//中文
    LANGUAGE_SPANISH,//西班牙
    LANGUAGE_GERMAN, //德语
    LANGUAGE_FRENCH, //法语
    LANGUAGE_POLISH, //波兰
    LANGUAGE_ITALIAN,//意大利
    LANGUAGE_CZECH,  //捷克
    LANGUAGE_DUTCH,  //荷兰
    LANGUAGE_NULL
}Language_TypeDef;


//语言类型
typedef enum
{
	Power_Backup_Index,			//备电时间设置
	Power_ON_GRID_Index,		//并网功率设置
}PowerType_TypeDef;


//波特率类型
typedef enum
{
    BAUD_9600,   //9600
    BAUD_19200,  //19200 
    BAUD_38400,  //38400
    BAUD_NULL
}Baud_TypeDef;

//使能类型
typedef enum
{
    ENABLE_NO,    //禁止 
    ENABLE_YES,   //使能
    ENABLE_NULL
}ENABLE_TypeDef;

//电池设置类别
typedef enum
{
    BMS_CLASS_BMS,          //电池使能
    //BMS_CLASS_WAKEUP,       //电池唤醒
    //BMS_CLASS_MANUFACTURER, //电池厂商
    BMS_CLASS_TYPE,         //电池类型
    BMS_CLASS_NULL
}BMS_CLASS_TypeDef;

//使能类型
typedef enum
{
    ENABLE_CLASS_CURVE_SCAN,            //IV曲线扫描使能
    ENABLE_CLASS_BATTERY_ENABLE,        //电池使能
    ENABLE_CLASS_BATTERY_WAKEUP,        //电池唤醒使能
    ENABLE_CLASS_SELL,                  //卖电使能
    ENABLE_CLASS_ANTIREFLUX,            //防逆流使能  
    ENABLE_CLASS_GEN,                   //发电机使能    
    ENABLE_CLASS_ISLAND,                //孤岛保护使能
    ENABLE_CLASS_GROUND,                //接地保护使能
    ENABLE_CLASS_LEAKAGE,               //漏电保护使能
    ENABLE_CLASS_ARC,                   //拉弧保护使能
//    ENABLE_CLASS_OVERHEAT,              //过热保护使能
    ENABLE_CLASS_LVRT,                  //低电压穿越保护使能
    ENABLE_CLASS_HVRT,                  //高电压穿越保护使能
    ENABLE_CLASS_LIGHT,                 //防雷保护使能
    ENABLE_CLASS_GEN_PROTECT,           //放电机保护使能
    ENABLE_CLASS_INSULATION_IMPEDANCE,  //绝缘阻抗使能
    ENABLE_CLASS_LFRT,                  //低频率穿越保护使能
    ENABLE_CLASS_HFRT,                  //高频率穿越保护使能
    ENABLE_CLASS_P_V,                   //P(V)保护使能
    ENABLE_CLASS_P_F,                   //P(F)保护使能
    ENABLE_CLASS_Q_V,                   //P(V)保护使能
    ENABLE_CLASS_Q_P,                   //P(P)保护使能
    ENABLE_CLASS_CPF,                   //CPF保护使能
    ENABLE_CLASS_CQ,                    //CQ保护使能
    ENABLE_CLASS_LOWPOWER,              // 低功耗保护使能
    ENABLE_CLASS_NULL
}ENABLE_CLASS_TypeDef;

typedef struct {
    uint8_t   u8StartPos;
    uint8_t   u8EndPos;
}Display_Flicker_Pos;

//设置界面每项设置索引
typedef enum
{
    SET_SYSTEM_Index,  //系统设置索引
    SET_PV_Index,      //光伏设置索引
    SET_BATTERY_Index, //电池设置索引
    SET_GRID_Index,    //电网设置索引
    SET_GEN_Index,     //发电机设置索引
//    SET_UPGRADE_Index  //升级设置索引
}SETAction_TypeDef;


//详细信息索引
typedef enum
{
    DETAILEDINFO_RunningStatus_Index,          //状态机显示索引
    DETAILEDINFO_Machin_Index,          //整机数据显示索引
    DETAILEDINFO_Grid_Index,            //电网数据显示索引
    DETAILEDINFO_Photovoltaic_Index,    //光伏数据显示索引
    DETAILEDINFO_Battery_Index,         //电池数据显示索引
    DETAILEDINFO_PowerLoad_Index,       //负载显示索引
    DETAILEDINFO_Generator_Index,       //发电机数据显示索引
    DETAILEDINFO_Factory_Index,        //出厂数据显示索引
}DETAILEDINFOTypeDef;

//历史记录页面每项设置索引
typedef enum
{
    LOG_REALTIMEFault_Index,         //实时故障显示索引
    LOG_LOGFault_Index,             //历史故障显示索引
    LOG_OPERATIONRECORD_Index       //操作记录显示索引
}LOGTypeDef;

//统计菜单索引
typedef enum
{
    Statistics_Day_Index,           //当日统计索引
    Statistics_Month_Index,         //当月统计索引
    Statistics_Year_Index,          //当年统计索引
    Statistics_All_Index,           //所有历史统计索引
}StatisticsTypeDef;

// 策略设置索引
typedef enum
{
    SET_PeakLoadShifting_Index,     //削峰填谷索引
    SET_SpontaneousSelfUse_Index,   //自发自用索引
    SET_Backup_Index,               //备电索引
    SET_TimingChargingDischarging_Index,            //定时充放电设置索引
}PolicySettings_TypeDef;


//削峰填谷设置索引
typedef enum
{
    STRATEGY_TPFV_PEAK_PERIOD_ONE,              //峰段时间1
    STRATEGY_TPFV_PEAK_PERIOD_TWO,              //峰段时间2
    STRATEGY_TPFV_PEAK_PERIOD_THREE,            //峰段时间3
    STRATEGY_TPFV_VALLEY_PERIOD_ONE,            //谷段时间1
    STRATEGY_TPFV_VALLEY_PERIOD_TWO,            //谷段时间2
    STRATEGY_TPFV_VALLEY_PERIOD_THREE,          //谷段时间3
} PeaksValleys_TypeDef;

// 定时充放电策略设置索引
typedef enum
{
    STRATEGY_TIMERSTRATEGY_CHARGE_ONE,          //充电时间段1
    STRATEGY_TIMERSTRATEGY_CHARGE_TWO,          //充电时间段2
    STRATEGY_TIMERSTRATEGY_CHARGE_THREE,        //充电时间段3
    STRATEGY_TIMERSTRATEGY_DISCHARGE_ONE,          //放电时间段1
    STRATEGY_TIMERSTRATEGY_DISCHARGE_TWO,          //放电时间段2
    STRATEGY_TIMERSTRATEGY_DISCHARGE_THREE,        //放电时间段3
} STRATEGY_TIMERSTRATEGY_DISCHARGE_TypeDef;


//设置界面每项设置索引
typedef enum
{
    SET_GRID_Antireflux_Index,      //防逆流使能界面索引
    SET_GRID_Gridconnection_Index,  //并网标准
    SET_GRID_ReactPowerWay_Index,   //无功控制方式设置索引    
    SEY_GRID_PowerSettings,         //功率设置
    SET_GRID_PF_Index,              //功率因数设置索引
    SET_GRID_Meter_Index,           //电表设置设置索引    
    SET_GRID_SamplingSelection_Index,//采样选择设置索引
    SET_GRID_PriceSetting_Index,    //电价设置索引
}GridAction_TypeDef;

//设置界面每项设置索引
typedef enum
{
    SET_GRID_Powersetting_ReactivePower,      	//无功功率
    SET_GRID_Powersetting_ActivePower,			//有功功率
}GridPowerSetting_TypeDef;

//设置界面每项设置索引
typedef enum
{
    SET_PV_CONTROLWAY_Index,	// 光伏控制索引
    SET_PV_CURVESCAN_Index,		// 光伏曲线扫描索引
    SET_PV_VOC_Index			// 光伏开路电压设置
}PVAction_TypeDef;

//串口设置界面每项设置索引
typedef enum
{
    SERIAL_ADDRESSS_Index,  //串口设置地址设置索引
    SERIAL_BAUD_Index       //串口设置波特率设置索引
}Serial_TypeDef;

typedef enum
{
    RESET_BLT_Index,  //通信复位设置蓝牙复位设置索引
    RESET_WIFI_Index  //通信复位设置WIFI复位设置索引
}RESET_TypeDef;


//设置界面每项设置索引
typedef enum
{
    SET_SYSTEM_LANGUAGE_Index,      //系统设置语言设置索引
    SET_SYSTEM_TIME_Index,          //系统设置时间设置索引
    SET_SYSTEM_PASSWORD_Index,      //系统设置密码设置索引
    SET_SYSTEM_CLEARFAULT_Index,    //系统设置清除故障告警设置索引
    SET_SYSTEM_CLEARRECORD_Index,   //系统设置清除操作记录设置索引
    //SYSTEM_SERIAL_Index,        //系统设置串口设置索引
    SET_SYSTEM_FACTORY_Index,       //系统设置出厂设置索引
    SET_SYSTEM_RESET_Index,         //系统设置通信复位索引
    SET_SYSTEM_REMOTECONTROL_Index, //系统设置远程控制索引 
    SET_SYSTEM_STRATEGY_Index,      //系统设置策略设置索引     
//    SET_SYSTEM_CT_Index,            //系统设置CT设置索引 
    SET_SYSTEM_DETECTION_Index,     //系统设置绝缘阻抗检测设置索引
    SET_SYSTEM_PROTECT_Index,       //系统设置保护设置索引
}SYSTEMSETAction_TypeDef;

//使能类型
typedef enum
{    
    SET_PROTECT_ISLAND_Index,                //孤岛保护使能设置索引
    SET_PROTECT_GROUND_Index,                //接地保护使能设置索引
    SET_PROTECT_DETECTION_Index,             // 绝缘阻抗保护
 //   SET_PROTECT_LEAKAGE_Index,               //漏电保护使能设置索引
 //   SET_PROTECT_ARC_Index,                   //拉弧保护使能设置索引
//    SET_PROTECT_OVERHEAT_Index,              //过热保护使能设置索引
 //   SET_PROTECT_LVRT_Index,                  //低电压穿越保护使能设置索引
 //   SET_PROTECT_HVRT_Index,                  //高电压穿越保护使能设置索引
 //   SET_PROTECT_LIGHT_Index,                 //防雷保护使能设置索引
 //   SET_PROTECT_GEN_Index,                   //发电机使能设置索引
 //   SET_PROTECT_LFRT_Index,                  //低频率穿越保护使能设置索引
 //   SET_PROTECT_HFRT_Index,                  //高频率穿越保护使能设置索引
 //   SET_PROTECT_P_V_Index,                   //P(V)保护使能设置索引
 //   SET_PROTECT_P_F_Index,                   //P(F)保护使能设置索引
 //   SET_PROTECT_Q_V_Index,                   //P(V)保护使能设置索引
 //   SET_PROTECT_Q_P_Index,                   //P(P)保护使能设置索引
 //   SET_PROTECT_CPF_Index,                   //CPF保护使能设置索引
 //   SET_PROTECT_CQ_Index,                    //CQ保护使能设置索引
 //   SET_PROTECT_NULL
}PROTECTSETAction_TypeDef;

//按键操作类型
typedef enum
{
    KEYACTION_NULL,
    KEYACTION_ENTERUP,  //Enter + Up同时键按下
    KEYACTION_ENTERDOWN,//Enter + Down键按下
    KEYACTION_ENTERESC, //Enter + ESC键按下
    KEYACTION_ENTER,    //Enter键按下
    KEYACTION_UPDOWN,   //Up + Down键按下
    KEYACTION_UPESC,    //Up + Esc键按下
    KEYACTION_UP,       //Up键按下
    KEYACTION_DOWNESC,  //Down + Esc键按下
    KEYACTION_DOWN,     //Down键按下
    KEYACTION_ESC       //Esc键按下
}KeyAction_TypeDef;


//按键状态
typedef enum
{
    KEYSTATUS_PRESSED = 1,//按键按下
    KEYSTATUS_REKEASE = 0 //按键释放
}KEYStatus_TypeDef;

//按键状态
typedef enum
{
    PV_WAY_ALONE,//独立
    PV_WAY_PARAL //并联
}PVWay_TypeDef;


//工作状态
typedef enum
{
    WORKSTATE_NULL,
    WORKSTATE_INIT,         //初始化
    WORKSTATE_FIT,          //上电参数匹配
    WORKSTATE_MONITOR,      //监听态
    WORKSTATE_STANDBY,      //待机
    WORKSTATE_TEST,         //测试模式
    WORKSTATE_PRESOFTSTART, //母线软起判断
    WORKSTATE_SOFTSTART,    //母线软起
    WORKSTATE_SOFTSTARTWAIT,//母线软起等待
    WORKSTATE_RELAYCLOSED,  //继电器闭合
    WORKSTATE_RUN,          //运行
    WORKSTATE_FAULT,        //故障
    WORKSTATE_UPGRADE       //在线升级
}WorkState_TypeDef;

//电池类型
typedef enum
{
    BMS_TYPE_LFP,    //磷酸铁锂电池
    BMS_TYPE_PB_AC,  //铅酸电池
    //BMS_TYPE_Ni_MH,  //镍氢电池
    //BMS_TYPE_MA_LI,  //锰酸锂电池
    //BMS_TYPE_LCO,    //钴酸锂电池
    //BMS_TYPE_NMP,    //三元材料电池
    //BMS_TYPE_LI_PO,  //聚合物锂离子电池
    //BMS_TYPE_LTO,    //钛酸锂电池
    //BMS_TYPE_NULL    //
}BMS_TypeDef;

//电池厂商
typedef enum
{
    BMS_MANU_CVTE,     //视源
    //BMS_MANU_LG,       //LG
    BMS_MANU_Pylon,    //派能
    BMS_MANU_NULL      //
}BMS_Manu_TypeDef;

//电池厂商
typedef enum
{
//    BMS_TYPE_NONE,
    BMS_TYPE_LI_ION,     //锂电
    BMS_TYPE_LEAD_ACID   //铅酸
}BMS_TYPE_TypeDef;


//LI.ION电池设置
#if 0
typedef enum
{
//    BMS_TYPE_NONE,
    BMS_TYPE_LI_ION_MANFACT,     //LI电池厂商 
    BMS_TYPE_LI_ION_PARASET      //LI电池参数设置
}BMS_TYPE_LI_ION_TypeDef;
#endif

//LI.ION参数设置
typedef enum
{   
    BMS_LI_ION_PARASET_MANUFACT,         //充电截止SOC
    BMS_LI_ION_PARASET_COM_WAY,         //通信方式
    BMS_LI_ION_PARASET_ENDOF_SOC,       //放电截止SOC
    BMS_LI_ION_PARASET_CURRENT,         //充电电流
    BMS_LI_ION_PARASET_END              //无
}BMS_LI_ION_PARASET_TypeDef;

//LiIon电池通信方式
typedef enum
{
    BMS_LI_ION_CAN,     //CAN通信
    BMS_LI_ION_485     //485通信
}BMS_COMWAY_TypeDef;

//LEAD.ACID参数设置
typedef enum
{   
    BMS_LEAD_ACID_PARASET_CAPACITY_CURRENT, //电池容量
    BMS_LEAD_ACID_PARASET_ENDOF_SOC,       //充电截止SOC
    BMS_LEAD_ACID_PARASET_VOLTPOINT,       //关机点设置
    BMS_LEAD_ACID_PARASET_END              //无
}BMS_LEAD_ACID_PARASET_TypeDef;

//策略类型
typedef enum
{
    STRATEGY_NULL,      //
    STRATEGY_SELF,      //自发自用模式
    STRATEGY_TPFV,      //削峰填谷模式
    STRATEGY_REGULAR,   //定时充放电模式    
    STRATEGY_BACKUP,    //备电模式
    STRATEGY_GEN,       //发电机模式
    STRATEGY_OLD        //老化模式
}STRATEGY_TypeDef;

//策略类型
typedef enum
{
    UPGRADE_EMS,         //BMS升级
    UPGRADE_DSP,         //DSP升级
    UPGRADE_BACKUP_MCU,  //备份MCU升级
    UPGRADE_BMS,         //BMS升级
    UPGRADE_NULL         //
}Upgrade_TypeDef;


//策略类型
typedef enum
{
    SERIAL_USE_PCS,      //用于PCS通信
    SERIAL_USE_Meter,    //用于电表通信
    SERIAL_USE_NULL      //
}SERIALUSE_TypeDef;
typedef enum
{
    REACTPOWER_CONTROL_REACTPOWER, //无功控制
    REACTPOWER_CONTROL_PF,         //PF控制
    REACTPOWER_CONTROL_NULL        //
}REACTPOWER_CONTROL_TypeDef;

//TPFV类型
typedef enum
{
    TPFV_TIP,      //用于PCS通信
    TPFV_PEAK,     //用于电表通信
    TPFV_FLAT,     //用于电表通信
    TPFV_VALLEY,  //用于电表通信
    TPFV_NULL  //
}TPFV_TypeDef;

//TPFV类型
typedef enum
{
    REGULAR_CHARGE,      //定时充电标志
    REGULAR_DISCHARGE,   //定时放电标志
    REGULAR_NULL  //
}REGULAR_TypeDef;


//系统设置
typedef enum
{
    SYS_SET_LANGUAGE_INDEX,       // 语言设置
    SYS_SET_TIME_INDEX,           // 时间设置
    SYS_SET_PASSWORD_INDEX,       // 密码修改
    SYS_SET_ClearFault_INDEX,     // 清除记录
    SYS_SET_ClearRecord_INDEX,    // 清除故障
    SYS_SET_FACTORY_INDEX,        // 出厂设置
    SYS_SET_REMOTECONTROL_INDEX,  // 远程控制
    SYS_SET_PROTECT_INDEX,        // 保护使能
    SYS_SET_LOW_POWER             // 低功耗使能
}Sys_Factory_TypeDef;

typedef enum
{
    PRICE_TPFV_PERIOD_PRICE,  //电价    
    PRICE_TPFV_PERIOD_ONE,    //时间段1
    PRICE_TPFV_PERIOD_TWO,    //时间段2
    PRICE_TPFV_PERIOD_THREE,  //时间段3
    PRICE_TPFV_PERIOD_NULL    //无
}TPFV_Price_TypeDef;

typedef enum
{   
    STRATEGY_TPFV_PERIOD_ONE,    //时间段1
    STRATEGY_TPFV_PERIOD_TWO,    //时间段2
    STRATEGY_TPFV_PERIOD_THREE,  //时间段3
    STRATEGY_TPFV_PERIOD_END   //无
}TPFV_Strategy_TypeDef;

typedef enum
{   
    STRATEGY_REGULAR_PERIOD_ONE,   //时间段1
    STRATEGY_REGULAR_PERIOD_TWO,   //时间段2
    STRATEGY_REGULAR_PERIOD_THREE, //时间段3
    STRATEGY_REGULAR_PERIOD_FOUR,  //时间段4
    STRATEGY_REGULAR_PERIOD_END    //无
}REGULAR_Strategy_TypeDef;


//工作状态
typedef enum
{
    FAULTTATE_NULL,
    FAULTSTATE_NORMAL,//正常
    FAULTSTATE_FAULT, //故障
    FAULTSTATE_ALARM  //告警
}FaultState_TypeDef;

// 菜单页设置索引
typedef enum
{
    MENU_DETAILEDINFO_Index,        //详细数据菜单索引   
    MENU_LOG_Index,                 //历史记录索引
    MENU_SETTING_Index,             //设置索引
    MENU_STATISTICS_Index,          //统计数据索引
}MENUTypeDef;

// 设置菜单页面索引
typedef enum
{
    SET_PolicySettings_Index,       //策略设置索引
    SET_GridSettings_Index,         //电网设置索引
    SET_BatterySetting_Index,       //电池设置索引
    SET_PVSetting_Index,            //光伏设置索引
    SET_GenSetting_Index,           //发电机设置索引
    SET_SYSSettings_Index,      //出厂设置索引
}SettingLis_TypeDef;

// 削峰填谷 
typedef enum
{
    PeakloadShifting_StartTime,     // 开始时间
    PeakloadShifting_EndTime,       // 结束时间
    PeakloadShifting_EndSOC,        // 停止SOC
    PeakloadShifting_EndPower,       // 限制功率
}PeakloadShifting_TypeDef;

// 定时充放电
typedef enum
{
    RegularTiming_StartTime,     // 开始时间
    RegularTiming_EndTime,       // 结束时间
}RegularTiming_TypeDef;

//LCD屏串口通讯参数设置结构体
typedef struct {
    uint8_t  u8Address;   //BMS通讯地址(默认 100) 
    uint16_t u16BaudRate; //电池类型(默认0) 0:9600 1:19200 2:38400 
}Display_SET_USART_Paras;

//LCD屏Can通讯参数设置结构体
typedef struct {
    uint8_t u8Address; //BMS通讯地址(默认 100) 
    uint8_t u8BaudRate;//电池类型(默认0) 0:100 1:125 2:250 
}Display_SET_CAN_Paras;

//LCD屏PV参数设置结构体
typedef struct {
    uint8_t u8PVControlWay; //光伏控制方式(默认 0) 0独立 1 并联
    uint8_t u8IVCurveScan;  //IV曲线扫描(默认0) 0:禁止 1:扫描
}Display_SET_PV;

//LCD屏电池BMS参数设置结构体
typedef struct {
    uint8_t  u8Address;                 //BMS通讯地址(默认 100) 
    uint8_t  u8BaudRate;                //电池类型(默认0) 0:2400 1:4800 2:9600 3:19200 4:38400 
    uint16_t u16MaxChargeCurrent;       //最大充电电流 
    uint16_t u16MaxDisChargeCurrent;    //最大放电电流 
    uint16_t u16HighVoltageProtectPoint;//电池高压保护点 
    uint16_t u16LowVoltageProtectPoint; //电池低压保护点 
    uint8_t  u8ChargeFlag;              //是否允许充电 0:禁止 1:使能 
    uint16_t u16ChargeCVVoltage;        //充电CV电压 
    uint16_t u16ChargeFVVoltage;        //充电FV电压 
}Display_SET_BMS_Paras;

//LCD屏LI.ION电池BMS参数设置结构体
typedef struct {
    uint8_t  u8ComWayFlag;              //通信方式 0:CAN 1:485通信 
    uint8_t  u8EndOfCharSOC;            //充电截止SOC
    uint8_t  u8EndOfDisCharSOC;         //放电截止SOC
    uint16_t u16MaxCharCurrent;            //充电电流
    uint16_t u16MaxDisCharCurrent;      //最大放电电流
}Display_SET_BMS_LiIon_Paras;


//LCD屏LEAD.ACID电池BMS参数设置结构体
typedef struct {
    uint16_t u16BatteryCapacity;        //电池过压保护点设置 
    uint8_t  u8EndOfCharSOC;            //充电截止SOC
    uint8_t  u8EndOfDisCharSOC;         //放电截止SOC
    uint16_t u16MaxCharCurrent;            //充电电流
    uint16_t u16MaxDisCharCurrent;      //最大放电电流
    uint16_t u16LowVoltShutPoint;       //低压关机电压点 
    uint16_t u16FloatVoltPoint;         //浮动电压点
    uint16_t u16ConstVoltCharPoint;     //恒压充电电压点
}Display_SET_BMS_LeadAcid_Paras;

//LCD屏电池BMS参数设置结构体
typedef struct {
    uint8_t u8EnableFlag;                  //BMS使能标志(默认 0) 0禁止 1 使能
    uint8_t u8Type;                        //电池类型(默认0) 0:磷酸铁锂 1:铅酸电池
    uint8_t u8WakeupFlag;                  //电池唤醒标志(默认0) 0禁止 1使能
    uint8_t u8ProtocolType;                //电池协议类型:0:无电池 1:CVTE 2:LG 3:CATL 4:派能 5:Alpha 6:ESS 7:通用  8:FRONUS 9:Talegent 10:Tower 11:pylon
    Display_SET_BMS_LiIon_Paras stHMISetBMSLiIonParas;
    Display_SET_BMS_LeadAcid_Paras stHMISetBMSLeadAcidParas; 
    Display_SET_BMS_Paras stHMISetBMSParas;//电池具体参数
}Display_SET_BMS;

//LCD屏时间划分参数设置结构体
typedef struct {
    uint8_t u8StartHour; //起始小时
    uint8_t u8StartMin;  //起始分钟
    uint8_t u8StartSec;  //起始秒
    uint8_t u8EndHour;   //结束小时
    uint8_t u8EndMin;    //结束分钟
    uint8_t u8EndSec;    //结束秒
}Display_SET_Grid_TimeDivisionElecPrice_Period;

//LCD屏电价参数设置结构体
typedef struct {
    uint16_t u8ElecPrice; //电价
    Display_SET_Grid_TimeDivisionElecPrice_Period  stPeriod1;//时间段1
    Display_SET_Grid_TimeDivisionElecPrice_Period  stPeriod2;//时间段2
    Display_SET_Grid_TimeDivisionElecPrice_Period  stPeriod3;//时间段3
}Display_SET_Grid_TimeDivisionElecPrice_TPFVPeriod;

//LCD屏尖峰平谷参数设置结构体
typedef struct {
    Display_SET_Grid_TimeDivisionElecPrice_TPFVPeriod   stTipPeriod;
    Display_SET_Grid_TimeDivisionElecPrice_TPFVPeriod   stPeakPeriod;
    Display_SET_Grid_TimeDivisionElecPrice_TPFVPeriod   stFlatPeriod;
    Display_SET_Grid_TimeDivisionElecPrice_TPFVPeriod   stValleyPeriod;
}Display_SET_Grid_TimeDivisionElecPrice;

//LCD屏电网参数设置结构体
typedef struct {
    uint8_t u8SellElectricityFlag;                                 //电网买电标注(默认 0) 0禁止 1 卖电
    uint8_t u8MterEnableFlag;                                      //电表使能标志(默认 0) 0禁止 1 使能
    uint8_t u8PreventReverseFlowControlFlag;                       //防逆流控制标志(默认 0) 0禁止 1 使能
    uint8_t u8SafetyRegulationType;                                //安规类别(默认0) 0:欧盟 1:英国 2:南非 3:澳大利亚
    int8_t u8ReactPowerControlWay;                                 //无功控制方式：0：无功控制 1：PF控制
    int16_t s16ReactPower;                                         //无功功率
    int16_t s16PF;                                                 //功率因数
    Display_SET_Grid_TimeDivisionElecPrice stTimeDivisionElecPrice;//分时电价参数
    Display_SET_USART_Paras stMeterParars;                         //电表参数    
    int16_t LOW_POWER;                                             //低功耗使能(默认 0) 0禁止 1 使能
}Display_SET_Grid;

//发电机设置类别
typedef enum
{
    GEN_CLASS_USE,              //干接点作用选择
    GEN_CLASS_DRYRLY_FLAG,      //干接点选择
    GEN_CLASS_ENABLE,           //发电机使能
    GEN_CLASS_POWER_PARA,       //发电机功率参数
    GEN_CLASS_INTELLOAD_PARA,   //智能负载参数
    GEN_CLASS_NULL
}GEN_CLASS_TypeDef;

//发电机用途
typedef enum
{
    GEN_USE_NULL,     //空
    GEN_USE_Gen,      //发电机
    GEN_USE_IntelLoad,//智能负载
}GEN_USE_TypeDef;

//发电机用途
typedef enum
{
    GEN_DRYRLY_One,      //干接点1
    GEN_DRYRLY_Two,      //干接点2
}GEN_DryRly_TypeDef;

//LCD屏发电机参数设置结构体
typedef struct {
    uint8_t u8CutDrySOC;    //智能负载切断继电器SOC
    uint8_t u8OnDrySOC;     //智能负载并入继电器SOC
}Display_SET_IntelLoad;

//LCD屏发电机参数设置结构体
typedef struct {
    uint8_t u8EnableFlag;     //发电机使能标志(默认 0) 0禁止 1 使能
    uint16_t u16RatedPower;   //发电机额定功率
    uint16_t u16MaxPower;     //发电机最大功率
}Display_SET_GenPara;

//LCD屏发电机参数设置结构体
typedef struct {
    uint8_t u8DryNode;                  //干节点选择(默认 0) 0 DRY-RLY1 1 使能 DRY-RLY1 1
    uint8_t u8DryNodeUse;               //干节点作用(默认 0) 1发电机 2智能负载
    Display_SET_IntelLoad  stIntelLoad; //智能负载参数
    Display_SET_GenPara    stGenPara;   //发电机功率参数
}Display_SET_Gen;

//LCD屏升级参数设置结构体
typedef struct {
    uint8_t u8UpgradeType; //版本升级种类(默认 0) 0 EMS 1 DSP 2 BMS 3 备份MCU
}Display_SET_Upgrade;

//LCD屏修改时间参数设置结构体
typedef struct {
    uint16_t u16Year; //年
    uint8_t  u8Month; //月
    uint8_t  u8Day;   //日
    uint8_t  u8Hour;  //时
    uint8_t  u8Min;   //分
    uint8_t  u8Sec;   //秒
    uint16_t u16mSec; //毫秒
}Display_SET_System_TimeSync;

//LCD屏修改密码参数设置结构体
typedef struct {
    uint8_t u8ArrayOldPassword[6];      //原始密码
    uint8_t u8ArrayNewPasswordFrist[6]; //第一次输入密码
    uint8_t u8ArrayNewPasswordSecond[6];//第二次输入密码
}Display_SET_System_PasswordModify;

//LCD屏保护参数设置结构体
typedef struct {
    uint8_t u8IslandProtection;             //孤岛保护
    uint8_t u8GroundProtection;             //接地保护
    uint8_t u8LeakageProtection;            //漏电保护
    uint8_t u8ArcPullingProtection;         //拉弧保护
    uint8_t u8OverheatProtection;           //过热保护
    uint8_t u8LowVoltageCrossProtection;    //低电压穿越保护
    uint8_t u8HighVoltageCrossProtection;   //高电压穿越保护
    uint8_t u8LightProtection;              //防雷保护
    uint8_t u8GeneratorProtection;          //发电机保护
    uint8_t u8InsulationImpedanceProtection;//绝缘阻抗保护
    uint8_t u8LowFrequencyCrossProtection;  //低频率穿越保护
    uint8_t u8HighFrequencyCrossProtection; //高频率穿越保护   
    uint8_t u8P_V_Protection;               //P(V)保护
    uint8_t u8P_F_Protection;               //P(F)保护
    uint8_t u8Q_V_Protection;               //Q(V)保护
    uint8_t u8Q_P_Protection;               //Q(F)保护
    uint8_t u8CPF_Protection;               //CPF保护
    uint8_t u8CQ_Protection;                //CQ保护
    uint8_t u8LOWPOER;                      //低功耗使能
}Display_SET_System_ProtectEnable;

//LCD屏策略时间段设置结构体
typedef struct {
    uint8_t u8StopSOC;                                      //停止SOC
    int16_t s16Power;                                       //充放电功率
    Display_SET_Grid_TimeDivisionElecPrice_Period  stPeriod;//时间段起止时间
}Display_SET_System_Strategy_PeriodParas;

//LCD屏削峰填谷策略设置结构体
typedef struct {
    Display_SET_System_Strategy_PeriodParas stPeriod1;
    Display_SET_System_Strategy_PeriodParas stPeriod2;
    Display_SET_System_Strategy_PeriodParas stPeriod3;
}Display_SET_System_Strategy_TPFV_Period;

//LCD屏定时充放电策略设置结构体
typedef struct {
    Display_SET_System_Strategy_PeriodParas stPeriod1;
    Display_SET_System_Strategy_PeriodParas stPeriod2;
    Display_SET_System_Strategy_PeriodParas stPeriod3;
    Display_SET_System_Strategy_PeriodParas stPeriod4;
}Display_SET_System_Strategy_TIMER_Period;

//LCD屏削峰填谷策略设置结构体
typedef struct {
    uint8_t u8TPFVStatus;
    Display_SET_System_Strategy_TPFV_Period  stTipPeriod;
    Display_SET_System_Strategy_TPFV_Period  stPeakPeriod;
    Display_SET_System_Strategy_TPFV_Period  stFlatPeriod;
    Display_SET_System_Strategy_TPFV_Period  stValleyPeriod;
}Display_SET_System_Strategy_TPFV;

//LCD屏定时充放电策略设置结构体
typedef struct {
    Display_SET_System_Strategy_TIMER_Period  stChargePeriod;
    Display_SET_System_Strategy_TIMER_Period  stDisChargePeriod;
}Display_SET_System_Strategy_Timer;

//LCD屏备电策略设置结构体
typedef struct {
    int16_t s16RatedPower;//额定功率
}Display_SET_System_Strategy_Backup;

//LCD屏发电机策略设置结构体
typedef struct {
    uint8_t u8ForbidSOC;//禁止充电SOC
    uint8_t u8SupplySOC;//补电SOC
}Display_SET_System_Strategy_Gen;

//LCD屏自发自用策略设置结构体
typedef struct {
//
}Display_SET_System_Strategy_Selfcontained;

//LCD屏CT变比设置结构体
typedef struct {
    uint16_t u16CTCurrent;    //电流变比
    uint16_t u16CTVoltage;    //电压变比
    uint8_t  u8CTEnableFlag;  //CT使能标志(默认 0) 0禁止 1 使能
}Display_SET_System_CTRadio;


//LCD屏策略设置结构体
typedef struct {
    uint8_t u8StrategyType;                                           //策略类别(默认0) 0:无策略 1:削峰填谷 2:定时充放电 3:自发自用 4:备电 5：发电机
    Display_SET_System_Strategy_TPFV    stTPFVStrategy;               //削峰填谷策略参数
    Display_SET_System_Strategy_Timer   stTimerStrategy;              //定时充放电策略参数
    Display_SET_System_Strategy_Backup stBackupStrategy;              //备电策略参数
    Display_SET_System_Strategy_Gen    stGenStrategy;                 //发电机策略参数
    Display_SET_System_Strategy_Selfcontained stSelfcontainedStrategy;//自发自用策略参数
}Display_SET_System_Strategy;


//LCD屏设置结构体
typedef struct {
    Language_TypeDef u8LanguageType;                    //语言种类默认 1) 0 中文 1 英文 2 西班牙语 3 德语 4 法语 5 波兰语 6 意大利语 7 捷克语 8 荷兰语
    uint8_t u8ClearFaultFlag;                           //清除故障
    uint8_t u8OperationRecordFlag;                      //清除操作记录
    uint8_t u8FactoryFlag;                              //出厂设置使能
    uint8_t u8WifiResetFlag;                            //Wifi 复位
    uint8_t u8BLTResetFlag;                             //蓝牙复位
    uint8_t u8RemoteControl;                            //远程控制方式(默认 0) 0 本地 1远程
    Display_SET_System_CTRadio         stCTRadio;       //CT变比
    uint8_t u8InsulationImpedanceDetectionFlag;         //绝缘阻抗检测(默认 0) 0 禁止 1 使能
    Display_SET_USART_Paras stDspUsartParas;           
    Display_SET_System_TimeSync        stTimeSync;      //时间设置
    Display_SET_System_PasswordModify  stPasswordModify;//密码修改
    Display_SET_System_ProtectEnable   stProtectEnable; //保护使能
    Display_SET_System_Strategy        stStrategy;      //策略参数
    Display_SET_PV                     stPV;            //PV参数
    Display_SET_BMS                    stBMS;           //电池参数
    Display_SET_Grid                   stGrid;          //电网参数
    Display_SET_Gen                    stGen;           //发电机参数
}Display_SET;

//LCD屏系统数据显示结构体
typedef struct {
    Language_TypeDef u8LanguageType;        //语言种类默认 1) 0 中文 1 英文 2 西班牙语 3 德语 4 法语 5 波兰语 6 意大利语 7 捷克语 8 荷兰语
    uint8_t u8SafetyRegulationType;         //安规类别(默认0) 0:欧盟 1:英国 2:南非 3:澳大利亚
    uint8_t u8PVControlWay;                 //光伏控制方式(默认 0) 0独立 1 并联
    uint8_t u8StrategyType;                 //策略类别(默认0) 0:无策略 1:削峰填谷 2:定时充放电 3:自发自用 4:备点 5：发电机
    uint8_t u8PreventReverseFlowControlFlag;//防逆流控制标志(默认 0) 0禁止 1使能
    uint8_t u8BatteryManufacturer;          //电池厂商:0:无电池 1:CVTE 2:LG 3:CATL 4:派能 5:Alpha 6:ESS 7:通用  8:FRONUS 9:Talegent 10:Tower 11:pylon
    int16_t s16SystemTemperature;           //系统温度
    uchar stringEMSVersion[20];             //EMS版本号
    uchar stringDSPVersion[20];             //DSP版本号
    uchar stringBackUpVersion[20];          //BackUp版本号
}Display_DATA_System;

//LCD屏电网数据显示结构体
typedef struct {
    uint16_t u16GridVoltage;                  //电网电压
    int16_t  sGridcurrent;                    //电网电流
    uint16_t u16GridFrequency;                //电网频率
    int32_t  sGridActivePower;                //有功功率
    int32_t  sGridReactivePower;              //无功功率
    uint8_t  u8GridStatus;                    //电网状态
}Display_DATA_Grid;

//LCD屏光伏数据显示结构体
typedef struct {
    uint16_t u16PVVoltage;                  //光伏电压
     int16_t sPVCurrent;                    //光伏电流
     int16_t sPVPower;                      //光伏功率
     uint8_t u8PVStatus;                    //PV状态
}Display_DATA_PVPara;

//LCD屏光伏数据显示结构体
typedef struct {
    Display_DATA_PVPara stPV1;              //光伏1数据
    Display_DATA_PVPara stPV2;              //光伏2数据
}Display_DATA_PV;

//LCD屏电池BMS数据显示结构体
typedef struct {
    uint16_t u16BMSVoltage;                 //电池电压
    int16_t sBMSCurrent;                    //电池电流
    int16_t sChargePower;                   //电池充电功率
    int16_t sDisChargePower;                //电池放电功率
    uint8_t u8SOC;                          //电池SOC
    uint8_t u8SOH;                          //电池SOH 
    uint8_t u8BMSType;                      //电池类型
    int16_t u16BMSCapacity;                 //电池容量
    uint16_t u16OverValtagevalue;           //电池过压值
    uint16_t u16UnderValtagevalue;          //电池欠压值
    uint8_t u8DOD;                          //电池放电深度
    uint16_t u16MaxChargeVoltage;           //电池最大充电电压
    int16_t sMaxChargeCurrent;              //电池最大充电电流
    uint16_t u16MaxDisChargeVoltage;        //电池最大放电电压
    int16_t sMaxDisChargeCurrent;           //电池最大放电电流   
    uint8_t u8BMSStatus;                    //电池状态
}Display_DATA_BMS;

//LCD屏负载数据显示结构体
typedef struct {
    uint16_t u16LoadVoltage;                //负载电压
     int16_t sLoadcurrent;                  //负载电流
     int16_t sLoadPower;                    //负载功率
}Display_DATA_LOAD;

//LCD屏负载数据显示结构体
typedef struct {
    uint16_t u16GenVoltage;                //发电机电压
    int16_t sGencurrent;                   //发电机电流
    int16_t sGenPower;                     //发电机功率
    uint16_t u16GenFrequency;              //发电机频率    
    uint8_t u8GenStatus;                   //发电机状态
}Display_DATA_Gen;

//LCD屏统计数据显示结构体
typedef struct {
    uint32_t stPVPowerGeneration;              //光伏发电量
    uint32_t stLoadPowerGeneration;            //负载用电量
    uint32_t stOutputPowerGeneration;          //输出发电量
    uint32_t stInputPowerGeneration;           //输入发电量
    uint32_t stChagePowerGeneration;           //充电发电量
    uint32_t stDisChagePowerGeneration;        //放电发电量
}Display_DATA_STATISTICALPara;

//LCD屏统计数据显示结构体
typedef struct {
    Display_DATA_STATISTICALPara stDayStatisticaldata;   //当日统计数据
    Display_DATA_STATISTICALPara stMonthStatisticaldata; //当月统计数据
    Display_DATA_STATISTICALPara stYearStatisticaldata;  //当年统计数据
    Display_DATA_STATISTICALPara stTotalStatisticaldata; //累积统计数据
}Display_DATA_STATISTICAL;

//LCD屏数据显示结构体
typedef struct {
    Display_DATA_System      stSystemData;   //系统数据
    Display_DATA_Grid        stGridData;     //电网数据
    Display_DATA_PV          stPV;           //光伏数据  
    Display_DATA_BMS         stBMS;          //电池数据
    Display_DATA_LOAD        stLoad;         //负载数据
    Display_DATA_STATISTICAL stStatistical;  //统计数据
    Display_DATA_Gen         stGenData;          //发电机数据
}Display_DATA;

//LCD屏主界面结构体
typedef struct {
    uint8_t  u8WorkSate;                     //工作模式
    uint8_t  u8FaultStatus;                  //故障状态    
    float32_t f32ChagePowerGeneration;       //当日充电发电量
    float32_t f32DisChagePowerGeneration;    //当日放电发电量
}Display_HOME;

//LCD屏显示结构体
typedef struct {
    Display_DATA stDisplayData; //系统数据
    Display_SET  stDisplaySet;  //设置参数
    Display_HOME stDisplayHome; //主界面
}DisplaySystem;

//人机交互_按键检测_按键状态结构体
typedef struct {    
    union
    {
        uint16_t u16KeyStatus;
        struct
        {
            uint16_t bKEYDetectionUp:1;          //Up按键状态
            uint16_t bKEYDetectionDown:1;        //Down按键状态
            uint16_t bKEYDetectionEsc:1;         //Esc按键状态
            uint16_t bKEYDetectionEnter:1;       //Enter按键状态
            uint16_t bKEYDetectionReserve1:1;    //Esc按键状态
            uint16_t bKEYDetectionReserve2:1;    //预留
            uint16_t bKEYDetectionReserve3:1;    //预留
            uint16_t bKEYDetectionReserve4:1;    //Enter按键状态     
            uint16_t bKEYDetectionReserve:8;    //预留
        }BitKeyStatus;
    };
}Drive_KEYDetection_Status;

typedef struct
{
    uint16_t bKEYDetectionNull:1;          //无按键操作
    uint16_t bKEYDetectionEnter:1;         //Enter按键状态
    uint16_t bKEYDetectionUp:1;            //Up按键状态
    uint16_t bKEYDetectionDown:1;          //Down按键状态
    uint16_t bKEYDetectionEsc:1;           //Esc按键状态
    uint16_t u16KEYDetectionReserve:11;    //预留
}Display_KEYDetection_Status;

//按键动作滤波
typedef struct
{
    uint16_t u16EnterKeyCnt;         //Enter按键计数
    uint16_t u16UpKeyCnt;            //Up按键计数
    uint16_t u16DownKeyCnt;          //Down按键计数
    uint16_t u16EscKeyCnt;           //Esc按键计数
}Display_KeyDetectionFilter_t;

//界面操作类型
typedef enum
{
    DISPLAY_NULL,
    DISPLAY_HOME,                                               //主界面
    DISPLAY_LOGIN,                                              //登陆设置界面
    DISPLAY_MENU,                                               //菜单页面
    DISPLAY_DETAILEDINFO,                                       //详细数据页面  
    DISPLAY_LOG,                                                //历史数据界面
    DISPLAY_SET,                                                //设置界面
    DISPLAY_RunningStatus,                                      //状态机显示
    DISPLAY_MachinStatus,                                       //整机数据
    DISPLAY_GridInfo,                                           //电网数据
    DISPLAY_Photovoltaic,                                       //光伏数据显示
    DISPLAY_Battery,                                            //电池数据显示
    DISPLAY_PowerLoad,                                          //负载数据显示
    DISPLAY_Generator,                                          //发电机数据显示
    DISPLAY_Factory,                                            //出厂数据显示 
    DISPLAY_STATISTICS,                                         //统计数据界面
    DISPLAY_STATISTICS_DAY,                                     //当日统计界面
    DISPLAY_STATISTICS_MONTH,                                   //当月统计界面
    DISPLAY_STATISTICS_YEAR,                                    //当年统计界面
    DISPLAY_STATISTICS_ALL,                                     //累计统计界面
    DISPLAY_SET_PV,                                             //光伏设置界面
    DISPLAY_SET_PV_CONTROLWAY,                                  //光伏控制设置界面
    DISPLAY_SET_PV_SCAN,                                        //光伏曲线扫描界面
    DISPLAY_SET_PV_VOC,                                         //光伏开路电压设置界面
    DISPLAY_SET_BATTERY,                                        //电池设置界面
    DISPLAY_SET_BATTERY_ENABLE,                                 //电池使能设置界面
    DISPLAY_SET_BATTERY_WAKEUP,                                 //电池唤醒使能设置界面
    //DISPLAY_SET_BATTERY_MANUFACTURER,                         //电池厂商设置界面
    DISPLAY_SET_BATTERY_TYPE,                                   //电池类型设置界面
    DISPLAY_SET_BATTERY_TYPE_LI_ION,                            //Li.Ion电池设置界面
    DISPLAY_SET_BATTERY_TYPE_LI_ION_MANUFACTURER,               //Li.Ion厂商设置界面
    DISPLAY_SET_BATTERY_TYPE_LI_ION_COMWAY,                     //Li.Ion通信方式设置界面
    DISPLAY_SET_BATTERY_TYPE_LI_ION_ENDOF_SOC,                  //Li.Ion截止SOC设置
    DISPLAY_SET_BATTERY_TYPE_LI_ION_CURRENT,                    //Li.Ion最大电流设置
    DISPLAY_SET_BATTERY_TYPE_LEAD_ACID,                         //Lead.Acid电池设置界面
    DISPLAY_SET_BATTERY_TYPE_LEAD_ACID_CAPANDCUR,               //Lead.Acid容量和电流设置界面
    DISPLAY_SET_BATTERY_TYPE_LEAD_ACID_ENDOF_SOC,               //Lead.Acid截止SOC设置
    DISPLAY_SET_BATTERY_TYPE_LEAD_ACID_VOLTPOINT,               //Lead.Acid电压点设置
    DISPLAY_SET_GRID,                                           //电网设置界面
    DISPLAY_SET_GRID_SELLENABLE,                                //卖电使能界面
    DISPLAY_SET_GRID_ANTIREFLUX,                              //防逆流使能界面
    DISPLAY_SET_GRID_METER,                                     //电表设置界面
    DISPLAY_SET_GRID_METER_ADDRESS,                             //电表地址设置界面
    DISPLAY_SET_GRID_METER_BAUD,                                //电表波特率设置界面
    //DISPLAY_SET_GRID_SR,                                        //安规设置界面   
    DISPLAY_SET_GRID_SR,                                        //并网设置设置界面
    DISPLAY_SET_GRID_TIMEDIVEPRICE,                             //分时电价设置界面
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_TIP,                    //尖时电价设置界面
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_ONE,         //尖时尖段时间段1设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_TWO,         //尖时尖段时间段2设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_THREE,       //尖时尖段时间段3设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK,                   //峰时电价设置界面
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_ONE,        //峰时尖段时间段1设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_TWO,        //峰时尖段时间段2设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_THREE,      //峰时尖段时间段3设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT,                   //平时电价设置界面
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_ONE,        //平时尖段时间段1设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_TWO,        //平时尖段时间段2设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_THREE,      //平时尖段时间段3设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY,                 //谷时电价设置界面
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_ONE,      //平时尖段时间段1设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_TWO,      //平时尖段时间段2设置
    DISPLAY_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_THREE,    //平时尖段时间段3设置
    DISPLAY_SET_GRID_REACTIVEPOWERCONTROLWAY,                   //无功功率控制方式设置
    DISPLAY_SET_GRID_POWERSETTING,                             //功率设置
    DISPLAY_SET_GRID_REACTIVEPOWER,                             //无功功率设置
    DISPLAY_SET_GRID_POWERFACTOR,                               //功率因数设置
    DISPLAY_SET_GEN,                                            //发电机设置界面
    DISPLAY_SET_GEN_USE,                                        //电接点用途界面
    DISPLAY_SET_GEN_DRYRLY,                                     //干接点选择界面
    DISPLAY_SET_GEN_ENABLE,                                     //发电机使能界面
    DISPLAY_SET_GEN_POWERPARA,                                  //发电机功率参数界面
    DISPLAY_SET_GEN_INTELLOADPARA,                              //智能负载参数界面
    DISPLAY_SET_SYSTEM,                                         //系统设置界面
    DISPLAY_SET_SYSTEM_LANGUAGE,                                //语言设置
    DISPLAY_SET_SYSTEM_TIME,                                    //时间设置
    DISPLAY_SET_SYSTEM_PASSWORD,                                //密码设置
    DISPLAY_SET_SYSTEM_CLEARFAULT,                              //清除故障告警
    DISPLAY_SET_SYSTEM_CLEARRECORD,                             //清除操作记录
    DISPLAY_SET_SYSTEM_SERIAL,                                  //串口设置
    DISPLAY_SET_SYSTEM_SERIAL_ADDRESS,                          //串口地址设置
    DISPLAY_SET_SYSTEM_SERIAL_BAUD,                             //串口波特率设置
    DISPLAY_SET_SYSTEM_FACTORY,                                 //出厂设置
    DISPLAY_SET_SYSTEM_RESET,                                   //通信复位
    DISPLAY_SET_SYSTEM_REMOTECONTROL,                           //远程控制
    DISPLAY_SET_SYSTEM_STRATEGY,                                //策略设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV,                           //削峰填谷策略设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_TIP,                       //削峰填谷策略尖段设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_TIP_PERIOD_ONE,            //削峰填谷策略尖段时间段1设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_TIP_PERIOD_TWO,            //削峰填谷策略尖段时间段2设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_TIP_PERIOD_THREE,          //削峰填谷策略尖段时间段3设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_PEAK,                      //削峰填谷策略峰段设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_PEAK_PERIOD_ONE,           //削峰填谷策略峰段时间段1设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_PEAK_PERIOD_TWO,           //削峰填谷策略峰段时间段2设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_PEAK_PERIOD_THREE,         //削峰填谷策略峰段时间段3设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_FLAT,                      //削峰填谷策略峰段设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_FLAT_PERIOD_ONE,           //削峰填谷策略峰段时间段1设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_FLAT_PERIOD_TWO,           //削峰填谷策略峰段时间段2设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_FLAT_PERIOD_THREE,         //削峰填谷策略峰段时间段3设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_VALLEY,                    //削峰填谷策略谷段设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_VALLEY_PERIOD_ONE,         //削峰填谷策略尖段时间段1设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_VALLEY_PERIOD_TWO,         //削峰填谷策略尖段时间段2设置
    DISPLAY_SET_SYSTEM_STRATEGY_TPFV_VALLEY_PERIOD_THREE,       //削峰填谷策略尖段时间段3设置
    DISPLAY_SET_SYSTEM_STRATEGY_SELFUSE,                        //自发自用策略设置
    DISPLAY_SET_SYSTEM_STRATEGY_BACKUP,                         //备电策略设置
    DISPLAY_SET_SYSTEM_STRATEGY_GEN,                            //发电机策略设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR,                        //定时充放电策略设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_CHARGE,                 //定时充放电策略充电设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_CHARGE_PERIOD_ONE,      //定时充放电策略充电时间段1设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_CHARGE_PERIOD_TWO,      //定时充放电策略充电时间段2设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_CHARGE_PERIOD_THREE,    //定时充放电策略充电时间段3设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_CHARGE_PERIOD_FOUR,     //定时充放电策略充电时间段4设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_DISCHARGE,              //定时充放电策略放电设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_DISCHARGE_PERIOD_ONE,   //定时充放电策略放电时间段1设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_DISCHARGE_PERIOD_TWO,   //定时充放电策略放电时间段2设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_DISCHARGE_PERIOD_THREE, //定时充放电策略放电时间段3设置
    DISPLAY_SET_SYSTEM_STRATEGY_REGULAR_DISCHARGE_PERIOD_FOUR,  //定时充放电策略放电时间段4设置
//    DISPLAY_SET_SYSTEM_CT,                                      //CT设置
    DISPLAY_SET_SYSTEM_DETECTION,                               //绝缘阻抗检测
    DISPLAY_SET_SYSTEM_PROTECT,                                 //保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_ISLAND,                          //孤岛保护使能设置 
    DISPLAY_SET_SYSTEM_PROTECT_GROUND,                          //接地保护使能设置 
    DISPLAY_SET_SYSTEM_PROTECT_LEAKAGE,                         //漏电保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_ARC,                             //拉弧保护使能设置
//    DISPLAY_SET_SYSTEM_PROTECT_OVERHEAT,                        //过热保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_LVRT,                            //低电压穿越保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_HVRT,                            //高电压穿越保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_LIGHT,                           //防雷保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_GEN,                             //发电机保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_LFRT,                            //低频率穿越保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_HFRT,                            //高频率穿越保护使能设置   
    DISPLAY_SET_SYSTEM_PROTECT_P_V,                             //P(V)保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_P_F,                             //P(F)保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_Q_V,                             //Q(V)保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_Q_P,                             //Q(P)保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_CPF,                             //CPF保护使能设置
    DISPLAY_SET_SYSTEM_PROTECT_CQ,                              //CQ保护使能设置
//    DISPLAY_SET_UPGRADE,                                        //升级
//    DISPLAY_SET_UPGRADE_EMS,                                    //EMS升级
//    DISPLAY_SET_UPGRADE_DSP,                                    //DSP升级
//    DISPLAY_SET_UPGRADE_BMS,                                    //BMS升级
//    DISPLAY_SET_UPGRADE_BACKUP,                                 //备份MCU    
    DISPLAY_DATA_DISPLAYSTACISTICS,                             //统计显示
    DISPLAY_DATA_DISPLAYREALFAULTRECORD,                        //实时故障记录显示
    DISPLAY_DATA_DISPLAYHISTORYFAULTRECORD,                     //历史故障记录显示
    DISPLAY_DATA_DISPLAYOPERATIONRECORD,                        //操作记录显示
    DISPLAY_DATA_DISPLAYSYSTEMDATA,                             //系统数据显示
    DISPLAY_DATA_DISPLAYREALTIMEDATA,                           //实时数据显示
    DISPLAY_PROMPT,                                             //提示界面
    DISPLAY_CONFIRM,                                             //确认界面
    DISPAY_SET_SYSTEM_LOWPOWER ,                                 // 低功耗使能                
}DisplayAction_TypeDef;

//界面操作类型
typedef enum
{
    OPERATE_NULL,
    OPERATE_TEST_fourteen  = 14,                      //test故障14
    OPERATE_TEST_fifteen,                             //test故障15
    OPERATE_TEST_sixteen,                             //test故障16
    OPERATE_TEST_seventeen,                           //test故障17
    OPERATE_PROMPT                                    //提示界面
}Operate_TypeDef;

typedef struct
{
    Tip_TypeDef eTipType;                      //提示类型
    DisplayAction_TypeDef eOccurTipAction;     //出现提示界面
    ConfirmSource_TypeDef eConfirmSource;      //出现确认消息源
    //DisplayAction_TypeDef eOccurPreTipAction;//出现提示界面上一菜单
    //uint8_t eOccurPreIndex;                  //出现提示界面上一菜单进入出现提示界面索引
    uint8_t u8PromptTime;                      //提示停留时间
}Display_Tip_Status;

typedef struct
{
    DisplayAction_TypeDef eCurrentDisplayMenuType; //当前菜单
    //bool_t bReverse;                             //逆向标志
    Display_Tip_Status stTip;                      //异常提示信息状态
}Display_CurrentMenu_Status;

typedef struct
{
    DisplayAction_TypeDef eLastDisplayMenuType;    //当前菜单
    //bool_t bReverse;                             //逆向标志
    Display_Tip_Status stTip;                      //异常提示信息状态
}Display_LastMenu_Status;

typedef struct
{
    uint16_t u16MainDspVerV;                       //主DSP版本号V
    uint16_t u16MainDspVerB;                       //主DSP版本号B
    uint16_t u16MainDspVerD;                       //主DSP版本号D
    uint16_t u16BackMcuVerV;                       //副DSP版本号V
    uint16_t u16BackMcuVerB;                       //副DSP版本号B
    uint16_t u16BackMcuVerD;                       //副DSP版本号D
}Display_DSP_MCU_Version;

//显示处理总入口函数,给main模块lcd总接口函数
extern void Display_Handler(void);
//初始化变量函数
extern void Display_Service_InitVar(void);

//Display总初始化函数
void DisplayInit(void);
//Display总运行函数
void DisplayRunning(void);
//AteDisplay总运行函数
void AteDisplayRunning(void);
//Display析构函数
void DisplayDestruction(void);
//英文字符闪烁点阵初始化
void ArrayFixFlickerStartPosAndEndPosInit_English(void);
//中文文字符闪烁点阵初始化
void ArrayFixFlickerStartPosAndEndPosInit_Chinese(void);
void SystemLanguageInit(void);
//安规初始化发送函数
void SafetyRegulationInit(uint8_t u8SRType);
//根据按键检测结果得到人机交互处理码
KeyAction_TypeDef getDisplayHandleCodeByKeyDetection(const Display_KEYDetection_Status keyDetectStatus);

//获取主界面实时数据
void getDisplayHomeData(void);

//根据上一次界面操作类型和本次操作类型判断本次HOME界面数据更新
void updateDisplayHomeData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文HOME界面
void updateDisplayHomeData_English(void);
//西班牙HOME界面
void updateDisplayHomeData_Spanish(void);
//德语HOME界面
void updateDisplayHomeData_German(void);
//法语HOME界面
void updateDisplayHomeData_French(void);
//波兰HOME界面
void updateDisplayHomeData_Polish(void);
//意大利HOME界面
void updateDisplayHomeData_Italian(void);
//捷克HOME界面
void updateDisplayHomeData_Czech(void);
//荷兰HOME界面
void updateDisplayHomeData_Dutch(void);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换
void updateDisplayLoginData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文LOGIN界面
void updateDisplayLoginData_English(char* sLoginPassword);
//西班牙LOGIN界面
void updateDisplayLoginData_Spanish(char* sLoginPassword);
//德语LOGIN界面
void updateDisplayLoginData_German(char* sLoginPassword);
//法语LOGIN界面
void updateDisplayLoginData_French(char* sLoginPassword);
//波兰LOGIN界面
void updateDisplayLoginData_Polish(char* sLoginPassword);
//意大利LOGIN界面
void updateDisplayLoginData_Italian(char* sLoginPassword);
//捷克LOGIN界面
void updateDisplayLoginData_Czech(char* sLoginPassword);
//荷兰LOGIN界面
void updateDisplayLoginData_Dutch(char* sLoginPassword);


//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换 菜单页
void updateDisplayMenuSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 菜单页英文
void updateDisplayMenuSetData_English(uint8_t u8SetIndex);
// 菜单页 西班牙
void updateDisplayMenuSetData_Spanish(uint8_t u8SetIndex);
// 菜单页 德语
void updateDisplayMenuSetData_German(uint8_t u8SetIndex);
// 菜单页 法语
void updateDisplayMenuSetData_French(uint8_t u8SetIndex);
// 菜单页 波兰
void updateDisplayMenuSetData_Polish(uint8_t u8SetIndex);
// 菜单页 意大利
void updateDisplayMenuSetData_Italian(uint8_t u8SetIndex);
// 菜单页 捷克
void updateDisplayMenuSetData_Czech(uint8_t u8SetIndex);
// 菜单页 荷兰
void updateDisplayMenuSetData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换 详细数据
void updateDisplayDETAILEDINFOIndexSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文LOGIN界面
void updateDisplayDetailedInfoData_English(uint8_t u8SetIndex);
//西班牙LOGIN界面
void updateDisplayDetailedInfoData_Spanish(uint8_t u8SetIndex);
//德语LOGIN界面
void updateDisplayDetailedInfoData_German(uint8_t u8SetIndex);
//法语LOGIN界面
void updateDisplayDetailedInfoData_French(uint8_t u8SetIndex);
//波兰LOGIN界面
void updateDisplayDetailedInfoData_Polish(uint8_t u8SetIndex);
//意大利LOGIN界面
void updateDisplayDetailedInfoData_Italian(uint8_t u8SetIndex);
//捷克LOGIN界面
void updateDisplayDetailedInfoData_Czech(uint8_t u8SetIndex);
//荷兰LOGIN界面
void updateDisplayDetailedInfoData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换 运行状态
void updateDisplayRunningStatus(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);  
//英文LOGIN界面
void updateDisplayRunningStatus_English(uint8_t u8SetIndex);
//西班牙LOGIN界面
void updateDisplayRunningStatus_Spanish(uint8_t u8SetIndex);
//德语LOGIN界面
void updateDisplayRunningStatus_German(uint8_t u8SetIndex);
//法语LOGIN界面
void updateDisplayRunningStatus_French(uint8_t u8SetIndex);
//波兰LOGIN界面
void updateDisplayRunningStatus_Polish(uint8_t u8SetIndex);
//意大利LOGIN界面
void updateDisplayRunningStatus_Italian(uint8_t u8SetIndex);
//捷克LOGIN界面
void updateDisplayRunningStatus_Czech(uint8_t u8SetIndex);
//荷兰LOGIN界面
void updateDisplayRunningStatus_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换 (整机数据)
void updateDisplayMachinData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:整机数据显示 英文界面
void updateDisplayMachin_English(uint8_t u8SetIndex);
// 功能:整机数据显示 中文界面
void updateDisplayMachin_Chinese(uint8_t u8SetIndex);
//功能:整机数据显示 西班牙语界面
void updateDisplayMachin_Spanish(uint8_t u8SetIndex);
//功能:整机数据显示 德语界面
void updateDisplayMachin_German(uint8_t u8SetIndex);
 //功能:整机数据显示 法语界面
void updateDisplayMachin_French(uint8_t u8SetIndex);
// 功能:整机数据显示 波兰语界面
void updateDisplayMachin_Polish(uint8_t u8SetIndex);
// 功能:整机数据显示 意大利语界面
void updateDisplayMachin_Italian(uint8_t u8SetIndex);
// 功能:整机数据显示 捷克语界面
void updateDisplayMachin_Czech(uint8_t u8SetIndex);
// 功能:整机数据显示 荷兰语界面
void updateDisplayMachin_Dutch(uint8_t u8SetIndex);


//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （电网数据）
void updateDisplayGridData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:电网数据显示 英文界面
void updateDisplayGridData_English(uint8_t u8SetIndex);
// 功能:电网数据显示 中文界面
void updateDisplayGridData_Chinese(uint8_t u8SetIndex);
//功能:电网数据显示 西班牙语界面
void updateDisplayGridData_Spanish(uint8_t u8SetIndex);
//功能:电网数据显示 德语界面
void updateDisplayGridData_German(uint8_t u8SetIndex);
 //功能:电网数据显示 法语界面
void updateDisplayGridData_French(uint8_t u8SetIndex); 
// 功能:电网数据显示 波兰语界面
void updateDisplayGridData_Polish(uint8_t u8SetIndex);
// 功能:电网数据显示 意大利语界面
void updateDisplayGridData_Italian(uint8_t u8SetIndex);
// 功能:电网数据显示 捷克语界面
void updateDisplayGridData_Czech(uint8_t u8SetIndex);
// 功能:电网数据显示 意大利语界面
void updateDisplayGridData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （光伏数据）
void updateDisplayPVData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:光伏数据显示 英文界面
void updateDisplayPVData_English(uint8_t u8SetIndex);
// 功能:光伏数据显示 中文界面
void updateDisplayPVData_Chinese(uint8_t u8SetIndex);
//功能:光伏数据显示 西班牙语界面
void updateDisplayPVData_Spanish(uint8_t u8SetIndex);
//功能:光伏数据显示 德语界面
void updateDisplayPVData_German(uint8_t u8SetIndex);
 //功能:光伏数据显示 法语界面
void updateDisplayPVData_French(uint8_t u8SetIndex);
// 功能:光伏数据显示 波兰语界面
void updateDisplayPVData_Polish(uint8_t u8SetIndex);
// 功能:光伏数据显示 意大利语界面
void updateDisplayPVData_Italian(uint8_t u8SetIndex);
// 功能:光伏数据显示 捷克语界面
void updateDisplayPVData_Czech(uint8_t u8SetIndex);
// 功能:光伏数据显示 荷兰语界面
void updateDisplayPVData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （电池数据）
void updateDisplayBatteryData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:电池数据显示 英文界面
void updateDisplayBatteryData_English(uint8_t u8SetIndex);
// 功能:电池数据显示 中文界面
void updateDisplayBatteryData_Chinese(uint8_t u8SetIndex);
//功能:电池数据显示 西班牙语界面
void updateDisplayBatteryData_Spanish(uint8_t u8SetIndex);
//功能:电池数据显示 德语界面
void updateDisplayBatteryData_German(uint8_t u8SetIndex);
 //功能:电池数据显示 法语界面
void updateDisplayBatteryData_French(uint8_t u8SetIndex);
// 功能:电池数据显示 波兰语界面
void updateDisplayBatteryData_Polish(uint8_t u8SetIndex);
// 功能:电池数据显示 意大利语界面
void updateDisplayBatteryData_Italian(uint8_t u8SetIndex);
// 功能:电池数据显示 捷克语界面
void updateDisplayBatteryData_Czech(uint8_t u8SetIndex);
// 功能:电池数据显示 荷兰语界面
void updateDisplayBatteryData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （负载数据）
void updateDisplayPowerLodaData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:负载数据显示 英文界面
void updateDisplayPowerLoadData_English(uint8_t u8SetIndex);
// 功能:负载数据显示 中文界面
void updateDisplayPowerLoadData_Chinese(uint8_t u8SetIndex);
//功能:负载数据显示 西班牙语界面
void updateDisplayPowerLoadData_Spanish(uint8_t u8SetIndex);
//功能：负载数据显示 德语界面
void updateDisplayPowerLoadData_German(uint8_t u8SetIndex);
 //功能:负载数据显示 法语界面
void updateDisplayPowerLoadData_French(uint8_t u8SetIndex);
// 功能:负载数据显示 波兰语界面
void updateDisplayPowerLoadData_Polish(uint8_t u8SetIndex);
// 功能:负载数据显示 意大利语界面
void updateDisplayPowerLoadData_Italian(uint8_t u8SetIndex);
// 功能:负载数据显示 捷克语界面
void updateDisplayPowerLoadData_Czech(uint8_t u8SetIndex);
// 功能:负载数据显示 荷兰语界面
void updateDisplayPowerLoadData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （发电机数据）
void updateDisplayGeneratorData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:发电机数据显示 英文界面
void updateDisplayGeneratorData_English(uint8_t u8SetIndex);
// 功能:发电机数据显示 中文界面
void updateDisplayGeneratorData_Chinese(uint8_t u8SetIndex);
//功能:发电机数据显示 西班牙语界面
void updateDisplayGeneratorData_Spanish(uint8_t u8SetIndex);
//功能：发电机数据显示 德语界面
void updateDisplayGeneratorData_German(uint8_t u8SetIndex);
 //功能:发电机数据显示 法语界面
void updateDisplayGeneratorData_French(uint8_t u8SetIndex);
// 功能:发电机数据显示 波兰语界面
void updateDisplayGeneratorData_Polish(uint8_t u8SetIndex);
// 功能:发电机数据显示 意大利语界面
void updateDisplayGeneratorData_Italian(uint8_t u8SetIndex);
// 功能:发电机数据显示 捷克语界面
void updateDisplayGeneratorData_Czech(uint8_t u8SetIndex);
// 功能:发电机数据显示 荷兰语界面
void updateDisplayGeneratorData_Dutch(uint8_t u8SetIndex);


//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （出厂设置数据）
void updateDisplayFactoryData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:出厂设置数据显示 英文界面
void updateDisplayFactoryData_English(uint8_t u8SetIndex);
// 功能:出厂设置数据显示 中文界面
void updateDisplayFactoryData_Chinese(uint8_t u8SetIndex);
//功能:出厂设置数据显示 西班牙语界面
void updateDisplayFactoryData_Spanish(uint8_t u8SetIndex);
//功能：出厂设置数据显示 德语界面
void updateDisplayFactoryData_German(uint8_t u8SetIndex);
 //功能:出厂设置数据显示 法语界面
void updateDisplayFactoryData_French(uint8_t u8SetIndex);
// 功能:出厂设置数据显示 波兰语界面
void updateDisplayFactoryData_Polish(uint8_t u8SetIndex);
// 功能:出厂设置数据显示 意大利语界面
void updateDisplayFactoryData_Italian(uint8_t u8SetIndex);
// 功能:出厂设置数据显示 捷克语界面
void updateDisplayFactoryData_Czech(uint8_t u8SetIndex);
// 功能:出厂设置数据显示 荷兰语界面
void updateDisplayFactoryData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （历史记录）
void updateDisplayLogData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:历史记录显示 英文界面
void updateDisplayLogData_English(uint8_t u8SetIndex);
// 功能:历史记录显示 中文界面
void updateDisplayLogData_Chinese(uint8_t u8SetIndex);
//功能: 历史记录显示 西班牙语界面
void updateDisplayLogData_Spanish(uint8_t u8SetIndex);
//功能:历史记录显示 德语界面
void updateDisplayLogData_German(uint8_t u8SetIndex);
//功能:历史记录显示 法语界面
void updateDisplayLogData_French(uint8_t u8SetIndex);
// 功能:历史记录显示 波兰语界面
void updateDisplayLogData_Polish(uint8_t u8SetIndex);
// 功能:历史记录显示 意大利语界面
void updateDisplayLogData_Italian(uint8_t u8SetIndex);
// 功能:历史记录显示 捷克语界面
void updateDisplayLogData_Czech(uint8_t u8SetIndex);
// 功能:历史记录显示 荷兰语界面
void updateDisplayLogData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次SET界面切换 (设置菜单页)
void updateDisplaySettingMenuData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//设置菜单页 英文
void updateDisplaySettingMenuData_English(uint8_t u8SetIndex);
//设置菜单页 中文
void updateDisplaySettingMenuData_Chinese(uint8_t u8SetIndex);
//设置菜单页 西班牙SET界面
void updateDisplaySettingMenuData_Spanish(uint8_t u8SetIndex);
//设置菜单页 德语SET界面
void updateDisplaySettingMenuData_German(uint8_t u8SetIndex);
//法语SET界面
void updateDisplaySettingMenuData_French(uint8_t u8SetIndex);
//波兰SET界面
void updateDisplaySettingMenuData_Polish(uint8_t u8SetIndex);
//意大利SET界面
void updateDisplaySettingMenuData_Italian(uint8_t u8SetIndex);
//捷克SET界面
void updateDisplaySettingMenuData_Czech(uint8_t u8SetIndex);
//荷兰SET界面
void updateDisplaySettingMenuData_Dutch(uint8_t u8SetIndex);


//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （统计数据）
void updateDisplayStatistics(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:统计数据显示 英文界面
void updateDisplayStatistics_English(uint8_t u8SetIndex);
// 功能:统计数据显示 中文界面
void updateDisplayStatistics_Chinese(uint8_t u8SetIndex);
//功能: 统计数据显示 西班牙语界面
void updateDisplayStatistics_Spanish(uint8_t u8SetIndex);
//功能:统计数据显示 德语界面
void updateDisplayStatistics_German(uint8_t u8SetIndex);
//功能:统计数据显示 法语界面
void updateDisplayStatistics_French(uint8_t u8SetIndex);
// 功能:统计数据显示 波兰语界面
void updateDisplayStatistics_Polish(uint8_t u8SetIndex);
// 功能:统计数据显示 意大利语界面
void updateDisplayStatistics_Italian(uint8_t u8SetIndex);
// 功能:统计数据显示 捷克语界面
void updateDisplayStatistics_Czech(uint8_t u8SetIndex);
// 功能:统计数据显示 荷兰语界面
void updateDisplayStatistics_Dutch(uint8_t u8SetIndex);


//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （当日统计数据）
void updateDisplayStatistics_Day(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:统计数据显示 英文界面
void updateDisplayStatistics_Day_English(uint8_t u8SetIndex);
// 功能:统计数据显示 中文界面
void updateDisplayStatistics_Day_Chinese(uint8_t u8SetIndex);
//功能: 统计数据显示 西班牙语界面
void updateDisplayStatistics_Day_Spanish(uint8_t u8SetIndex);
//功能:统计数据显示 德语界面
void updateDisplayStatistics_Day_German(uint8_t u8SetIndex);
 //功能:统计数据显示 法语界面
void updateDisplayStatistics_Day_French(uint8_t u8SetIndex);
// 功能:统计数据显示 波兰语界面
void updateDisplayStatistics_Day_Polish(uint8_t u8SetIndex);
// 功能:统计数据显示 意大利语界面
void updateDisplayStatistics_Day_Italian(uint8_t u8SetIndex);
// 功能:统计数据显示 捷克语界面
void updateDisplayStatistics_Day_Czech(uint8_t u8SetIndex);
// 功能:统计数据显示 荷兰语界面
void updateDisplayStatistics_Day_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （当月统计数据）
void updateDisplayStatistics_Month(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:统计数据显示 英文界面
void updateDisplayStatistics_Month_English(uint8_t u8SetIndex);
// 功能:统计数据显示 中文界面
void updateDisplayStatistics_Month_Chinese(uint8_t u8SetIndex);
//功能: 统计数据显示 西班牙语界面
void updateDisplayStatistics_Month_Spanish(uint8_t u8SetIndex);
//功能:统计数据显示 德语界面
void updateDisplayStatistics_Month_German(uint8_t u8SetIndex);
 //功能:统计数据显示 法语界面
void updateDisplayStatistics_Month_French(uint8_t u8SetIndex);
// 功能:统计数据显示 波兰语界面
void updateDisplayStatistics_Month_Polish(uint8_t u8SetIndex);
// 功能:统计数据显示 意大利语界面
void updateDisplayStatistics_Month_Italian(uint8_t u8SetIndex);
// 功能:统计数据显示 捷克语界面
void updateDisplayStatistics_Month_Czech(uint8_t u8SetIndex);
// 功能:统计数据显示 荷兰语界面
void updateDisplayStatistics_Month_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （当年统计数据）
void updateDisplayStatistics_Year(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:统计数据显示 英文界面
void updateDisplayStatistics_Year_English(uint8_t u8SetIndex);
// 功能:统计数据显示 中文界面
void updateDisplayStatistics_Year_Chinese(uint8_t u8SetIndex);
//功能: 统计数据显示 西班牙语界面
void updateDisplayStatistics_Year_Spanish(uint8_t u8SetIndex);
//功能:统计数据显示 德语界面
void updateDisplayStatistics_Year_German(uint8_t u8SetIndex);
 //功能:统计数据显示 法语界面
void updateDisplayStatistics_Year_French(uint8_t u8SetIndex);
// 功能:统计数据显示 波兰语界面
void updateDisplayStatistics_Year_Polish(uint8_t u8SetIndex);
// 功能:统计数据显示 意大利语界面
void updateDisplayStatistics_Year_Italian(uint8_t u8SetIndex);
// 功能:统计数据显示 捷克语界面
void updateDisplayStatistics_Year_Czech(uint8_t u8SetIndex);
// 功能:统计数据显示 荷兰语界面
void updateDisplayStatistics_Year_Dutch(uint8_t u8SetIndex);


//根据上一次界面操作类型和本次操作类型判断本次LOGIN界面切换   （累计统计数据）
void updateDisplayStatistics_All(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:统计数据显示 英文界面
void updateDisplayStatistics_All_English(uint8_t u8SetIndex);
// 功能:统计数据显示 中文界面
void updateDisplayStatistics_All_Chinese(uint8_t u8SetIndex);
//功能: 统计数据显示 西班牙语界面
void updateDisplayStatistics_All_Spanish(uint8_t u8SetIndex);
//功能:统计数据显示 德语界面
void updateDisplayStatistics_All_German(uint8_t u8SetIndex);
 //功能:统计数据显示 法语界面
void updateDisplayStatistics_All_French(uint8_t u8SetIndex);
// 功能:统计数据显示 波兰语界面
void updateDisplayStatistics_All_Polish(uint8_t u8SetIndex);
// 功能:统计数据显示 意大利语界面
void updateDisplayStatistics_All_Italian(uint8_t u8SetIndex);
// 功能:统计数据显示 捷克语界面
void updateDisplayStatistics_All_Czech(uint8_t u8SetIndex);
// 功能:统计数据显示 荷兰语界面
void updateDisplayStatistics_All_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次SET界面切换   (策略设置界面)
void updateDisplayPolicySettingsData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//策略设置 英文界面
void updateDisplayPolicySettings_English(uint8_t u8SetIndex);
//策略设置 中文页面
void updateDisplayPolicySettings_Chinese(uint8_t u8SetIndex);
//策略设置 西班牙界面
void updateDisplayPolicySettings_Spanish(uint8_t u8SetIndex);
//策略设置 德语界面
void updateDisplayPolicySettings_German(uint8_t u8SetIndex);
//策略设置 法语界面
void updateDisplayPolicySettings_French(uint8_t u8SetIndex);
//策略设置 波兰界面
void updateDisplayPolicySettings_Polish(uint8_t u8SetIndex);
//策略设置 意大利界面
void updateDisplayPolicySettings_Italian(uint8_t u8SetIndex);
//策略设置 捷克界面
void updateDisplayPolicySettings_Czech(uint8_t u8SetIndex);
//策略设置 荷兰界面
void updateDisplayPolicySettings_Dutch(uint8_t u8SetIndex);


//功能:根据上一次界面操作类型和本次操作类型判断本次 策略设置界面切换
void updateDisplayPolicySettingsData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能:策略设置 英文界面
void updateDisplayPolicySettings_English(uint8_t u8SetIndex);
// 功能:策略设置 中文页面
void updateDisplayPolicySettings_Chinese(uint8_t u8SetIndex);
//功能:策略设置 西班牙界面
void updateDisplayPolicySettings_Spanish(uint8_t u8SetIndex);
//功能:策略设置 德语界面
void updateDisplayPolicySettings_German(uint8_t u8SetIndex);
//功能:策略设置 法语界面
void updateDisplayPolicySettings_French(uint8_t u8SetIndex);
//功能:策略设置 波兰界面
void updateDisplayPolicySettings_Polish(uint8_t u8SetIndex);
//功能:策略设置意大利界面
void updateDisplayPolicySettings_Italian(uint8_t u8SetIndex);
//功能:策略设置 捷克界面
void updateDisplayPolicySettings_Czech(uint8_t u8SetIndex);
//功能:策略设置 荷兰界面
void updateDisplayPolicySettings_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次SET界面切换(削峰填谷)
void updateDisplayPeakLoadShiftingSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//削峰填谷 英文SET界面
void updateDisplayPeakLoadShiftingSetData_English(uint8_t u8SetIndex);
// 削峰填谷 中文界面
void updateDisplayPeakLoadShiftingSetData_Chinese(uint8_t u8SetIndex);
//削峰填谷 西班牙SET界面
void updateDisplayPeakLoadShiftingSetData_Spanish(uint8_t u8SetIndex);
//削峰填谷 德语SET界面
void updateDisplayPeakLoadShiftingSetData_German(uint8_t u8SetIndex);
//削峰填谷 法语SET界面
void updateDisplayPeakLoadShiftingSetData_French(uint8_t u8SetIndex);
//削峰填谷 波兰SET界面
void updateDisplayPeakLoadShiftingSetData_Polish(uint8_t u8SetIndex);
//削峰填谷 意大利SET界面
void updateDisplayPeakLoadShiftingSetData_Italian(uint8_t u8SetIndex);
//削峰填谷 捷克SET界面
void updateDisplayPeakLoadShiftingSetData_Czech(uint8_t u8SetIndex);
//削峰填谷 荷兰SET界面
void updateDisplayPeakLoadShiftingSetData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次SET界面切换削峰填谷
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,PeaksValleys_TypeDef enum_tpfv);
// 削峰填谷 中文界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_Chinese(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 英文SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_English(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 西班牙SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_Spanish(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 德语SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_German(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 法语SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_French(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 波兰SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_Polish(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 意大利SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_Italian(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 捷克SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_Czech(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);
//削峰填谷 荷兰SET界面
void updateDisplayPeakLoadShiftingPEAKVALLEYSetData_Dutch(uint8_t u8SetIndex,PeaksValleys_TypeDef enum_tpfv);

 //功能:备电时间
void updateDisplayBackupPowerSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,PowerType_TypeDef nowPowertype);
// 功能:英文 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_English(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);
// 功能:西班牙 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_Spanish(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);
// 功能:德语 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_German(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);
// 功能:法语 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_French(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);
// 功能:波兰语 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_Polish(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);
// 功能:意大利语 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_Italian(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);
// 功能:捷克语 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_Czech(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);
// 功能:荷兰语 系统SELF策略设置界面信息
void updateDisplayBackupPowerSetData_Dutch(uint8_t u8SetIndex,PowerType_TypeDef nowPowertype);

//功能:系统设置界面
void updateDisplaySystemSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文SET界面
void updateDisplaySystemSetData_English(uint8_t u8SetIndex);
//西班牙SET界面
void updateDisplaySystemSetData_Spanish(uint8_t u8SetIndex);
//德语SET界面
void updateDisplaySystemSetData_German(uint8_t u8SetIndex);
//法语SET界面
void updateDisplaySystemSetData_French(uint8_t u8SetIndex);
//波兰SET界面
void updateDisplaySystemSetData_Polish(uint8_t u8SetIndex);
//意大利SET界面
void updateDisplaySystemSetData_Italian(uint8_t u8SetIndex);
//捷克SET界面
void updateDisplaySystemSetData_Czech(uint8_t u8SetIndex);
//荷兰SET界面
void updateDisplaySystemSetData_Dutch(uint8_t u8SetIndex);

// 恢复出厂设置
void updateDisplaySystemFactorySetData(void);

//根据上一次界面操作类型和本次操作类型判断本次SET界面切换
void updateDisplaySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文SET界面
void updateDisplaySetData_English(uint8_t u8SetIndex);
//西班牙SET界面
void updateDisplaySetData_Spanish(uint8_t u8SetIndex);
//德语SET界面
void updateDisplaySetData_German(uint8_t u8SetIndex);
//法语SET界面
void updateDisplaySetData_French(uint8_t u8SetIndex);
//波兰SET界面
void updateDisplaySetData_Polish(uint8_t u8SetIndex);
//意大利SET界面
void updateDisplaySetData_Italian(uint8_t u8SetIndex);
//捷克SET界面
void updateDisplaySetData_Czech(uint8_t u8SetIndex);
//荷兰SET界面
void updateDisplaySetData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次SET界面切换
void updateDisplaySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文SET界面
void updateDisplaySetData_English(uint8_t u8SetIndex);
//西班牙SET界面
void updateDisplaySetData_Spanish(uint8_t u8SetIndex);
//德语SET界面
void updateDisplaySetData_German(uint8_t u8SetIndex);
//法语SET界面
void updateDisplaySetData_French(uint8_t u8SetIndex);
//波兰SET界面
void updateDisplaySetData_Polish(uint8_t u8SetIndex);
//意大利SET界面
void updateDisplaySetData_Italian(uint8_t u8SetIndex);
//捷克SET界面
void updateDisplaySetData_Czech(uint8_t u8SetIndex);
//荷兰SET界面
void updateDisplaySetData_Dutch(uint8_t u8SetIndex);

//根据上一次界面操作类型和本次操作类型判断本次系统 SET界面切换 （出厂设置界面）
void updateDisplayFactorySettingData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文   出厂设置界面
void updateDisplayFactorySettingData_English(uint8_t u8SetIndex);
//西班牙 出厂设置界面
void updateDisplayFactorySettingData_Spanish(uint8_t u8SetIndex);
//德语 出厂设置界面
void updateDisplayFactorySettingData_German(uint8_t u8SetIndex);
//法语 出厂设置界面
void updateDisplayFactorySettingData_French(uint8_t u8SetIndex);
//波兰 出厂设置界面
void updateDisplayFactorySettingData_Polish(uint8_t u8SetIndex);
//意大利 出厂设置界面
void updateDisplayFactorySettingData_Italian(uint8_t u8SetIndex);
//捷克 出厂设置界面
void updateDisplayFactorySettingData_Czech(uint8_t u8SetIndex);
//荷兰 出厂设置界面
void updateDisplayFactorySettingData_Dutch(uint8_t u8SetIndex);


//根据上一次界面操作类型和本次操作类型判断本次Language SET界面切换
void updateDisplaySystemLanguageSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_English(Language_TypeDef u8SetIndex);
//西班牙语LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_Spanish(Language_TypeDef u8SetIndex);
//德语LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_German(Language_TypeDef u8SetIndex);
//法语LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_French(Language_TypeDef u8SetIndex);
//波兰语LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_Polish(Language_TypeDef u8SetIndex);
//意大利语LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_Italian(Language_TypeDef u8SetIndex);
//捷克语LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_Czech(Language_TypeDef u8SetIndex);
//荷兰语LanguageSystemSet界面
void updateDisplaySystemLanguageSetData_Dutch(Language_TypeDef u8SetIndex);

//设置系统Time设置
void updateDisplaySystemTimeSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 设置系统Time界面
void updateDisplaySystemTimeSetData_English(char* sDate,char* sTime,Week_TypeDef eWeek);
//西班牙 设置系统Time界面
void updateDisplaySystemTimeSetData_Spanish(char* sDate,char* sTime,Week_TypeDef eWeek);
//德语 设置系统Time界面
void updateDisplaySystemTimeSetData_German(char* sDate,char* sTime,Week_TypeDef eWeek);
//法语 设置系统Time界面
void updateDisplaySystemTimeSetData_French(char* sDate,char* sTime,Week_TypeDef eWeek);
//波兰语 设置系统Time界面
void updateDisplaySystemTimeSetData_Polish(char* sDate,char* sTime,Week_TypeDef eWeek);
//意大利语 设置系统Time界面
void updateDisplaySystemTimeSetData_Italian(char* sDate,char* sTime,Week_TypeDef eWeek);
//捷克语 设置系统Time界面
void updateDisplaySystemTimeSetData_Czech(char* sDate,char* sTime,Week_TypeDef eWeek);
//荷兰语 设置系统Time界面
void updateDisplaySystemTimeSetData_Dutch(char* sDate,char* sTime,Week_TypeDef eWeek);

//设置系统密码设置
void updateDisplaySystemPasswordSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 设置系统Password界面
void updateDisplaySystemPasswordSetData_English(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//西班牙 设置系统Password界面
void updateDisplaySystemPasswordSetData_Spanish(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//德语 设置系统Password界面
void updateDisplaySystemPasswordSetData_German(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//法语 设置系统Password界面
void updateDisplaySystemPasswordSetData_French(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//波兰语 设置系统Password界面
void updateDisplaySystemPasswordSetData_Polish(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//意大利语 设置系统Password界面
void updateDisplaySystemPasswordSetData_Italian(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//捷克语 设置系统Password界面
void updateDisplaySystemPasswordSetData_Czech(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//荷兰语 设置系统Password界面
void updateDisplaySystemPasswordSetData_Dutch(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);

//英文 登陆密码错误提示界面信息
void updateDisplayTipLoginError_English(void);
//西班牙 登陆密码错误提示界面信息
void updateDisplayTipLoginError_Spanish(void);
//德语 登陆密码错误提示界面信息
void updateDisplayTipLoginError_German(void);
//法语 登陆密码错误提示界面信息
void updateDisplayTipLoginError_French(void);
//波兰语 登陆密码错误提示界面信息
void updateDisplayTipLoginError_Polish(void);
//意大利语 登陆密码错误提示界面信息
void updateDisplayTipLoginError_Italian(void);  
//捷克语 登陆密码错误提示界面信息
void updateDisplayTipLoginError_Czech(void);
//荷兰语 登陆密码错误提示界面信息
void updateDisplayTipLoginError_Dutch(void);

//英文 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_English(void);
//西班牙 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_Spanish(void);
//德语 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_German(void);
//法语 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_French(void);
//波兰语 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_Polish(void);
//意大利语 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_Italian(void);  
//捷克语 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_Czech(void);
//荷兰语 密码修改密码设置位数不够6位提示界面信息
void updateDisplayTipPasswordShort_Dutch(void);

//英文 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_English(void);
//西班牙 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_Spanish(void);
//德语 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_German(void);
//法语 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_French(void);
//波兰语 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_Polish(void);
//意大利语 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_Italian(void);  
//捷克语 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_Czech(void);
//荷兰语 密码修改旧的密码输入错误提示界面信息
void updateDisplayTipOldPasswordError_Dutch(void);

//英文 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_English(void);
//西班牙 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_Spanish(void);
//德语 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_German(void);
//法语 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_French(void);
//波兰语 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_Polish(void);
//意大利语 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_Italian(void);  
//捷克语 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_Czech(void);
//荷兰语 密码修改两次输入的新密码不一致提示界面信息
void updateDisplayTipOldPasswordNotMatch_Dutch(void);

//英文 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_English(void);
//西班牙 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_Spanish(void);
//德语 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_German(void);
//法语 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_French(void);
//波兰语 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_Polish(void);
//意大利语 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_Italian(void);  
//捷克语 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_Czech(void);
//荷兰语 密码修改输入的新密码和历史密码重合提示界面信息
void updateDisplayTipOldPasswordOverlaps_Dutch(void);

//英文 设置通过提示界面信息
void updateDisplayTipSetPassed_English(void);
//西班牙 设置通过提示界面信息
void updateDisplayTipSetPassed_Spanish(void);
//德语 设置通过提示界面信息
void updateDisplayTipSetPassed_German(void);
//法语 设置通过提示界面信息
void updateDisplayTipSetPassed_French(void);
//波兰语 设置通过提示界面信息
void updateDisplayTipSetPassed_Polish(void);
//意大利语 设置通过提示界面信息
void updateDisplayTipSetPassed_Italian(void);  
//捷克语 设置通过提示界面信息
void updateDisplayTipSetPassed_Czech(void);
//荷兰语 设置通过提示界面信息
void updateDisplayTipSetPassed_Dutch(void);

//设置ok 英文界面组装 
void updateDisplaySystemConfirm_English(void);                                           
//设置ok 西班牙界面组装
void updateDisplaySystemConfirm_Spanish(void);                               
//设置ok 德语界面组装 
void updateDisplaySystemConfirm_German(void);                          
//设置ok 法语界面组装
void updateDisplaySystemConfirm_French(void);                                    
//设置ok 波兰界面组装
void updateDisplaySystemConfirm_Polish(void);                                 
//设置ok 意大利界面组装
void updateDisplaySystemConfirm_Italian(void);                     
//设置ok 捷克界面组装
void updateDisplaySystemConfirm_Czech(void);       
//设置ok 荷兰界面组装 
void updateDisplaySystemConfirm_Dutch(void);            

//设置系统清除故障告警
void updateDisplaySystemClearFaultData(void);
//设置系统清除操作记录
void updateDisplaySystemClearRecordData(void);
//设置系统串口设置
void updateDisplaySystemSerialSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,SERIALUSE_TypeDef enumSerialUse);
//英文 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_English(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//西班牙 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_Spanish(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//德语 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_German(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//法语 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_French(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//波兰语 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_Polish(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//意大利语 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_Italian(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);  
//捷克语 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_Czech(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//荷兰语 设置系统串口设置界面信息
void updateDisplaySystemSerialSetData_Dutch(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//从Flash读串口信息
void getSysteSerialData(SERIALUSE_TypeDef enumSerialType);
//设置串口信息到Flash
void setSystemSerialData(SERIALUSE_TypeDef enumSerialType, bool_t bEnableFlag);


//设置系统串口波特率设置
void updateDisplaySystemSerialBaudSetData(KeyAction_TypeDef nowDisplayActionType,SERIALUSE_TypeDef enumSerialUse); 
//英文 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_English(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);
//中文 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_Chinese(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);
//西班牙 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_Spanish(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);
//德语 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_German(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);
//法语 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_French(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);
//波兰语 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_Polish(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);
//意大利语 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_Italian(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);  
//捷克语 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_Czech(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);
//荷兰语 设置系统串口波特率设置界面信息
void updateDisplaySystemSerialBaudSetData_Dutch(Baud_TypeDef u8SetIndex,SERIALUSE_TypeDef enumSerialUse);


//设置系统通信复位设置
void updateDisplaySystemCommResetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_English(Baud_TypeDef u8SetIndex);
//西班牙 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_Spanish(Baud_TypeDef u8SetIndex);
//德语 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_German(Baud_TypeDef u8SetIndex);
//法语 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_French(Baud_TypeDef u8SetIndex);
//波兰语 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_Polish(Baud_TypeDef u8SetIndex);
//意大利语 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_Italian(Baud_TypeDef u8SetIndex);  
//捷克语 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_Czech(Baud_TypeDef u8SetIndex);
//荷兰语 设置系统通信复位设置界面信息
void updateDisplaySystemCommResetData_Dutch(Baud_TypeDef u8SetIndex);

//设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_English(ENABLE_TypeDef u8SetIndex);
//西班牙 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_Spanish(ENABLE_TypeDef u8SetIndex);
//德语 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_German(ENABLE_TypeDef u8SetIndex);
//法语 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_French(ENABLE_TypeDef u8SetIndex);
//波兰语 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_Polish(ENABLE_TypeDef u8SetIndex);
//意大利语 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_Italian(ENABLE_TypeDef u8SetIndex);  
//捷克语 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_Czech(ENABLE_TypeDef u8SetIndex);
//荷兰语 设置系统通信复位设置界面信息
void updateDisplaySystemRemoteControlData_Dutch(ENABLE_TypeDef u8SetIndex);

//系统策略设置界面信息
void updateDisplaySystemStrategySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 系统策略设置界面信息
void updateDisplaySystemStrategySetData_English(STRATEGY_TypeDef u8StrategyIndex);
//西班牙 系统策略设置界面信息
void updateDisplaySystemStrategySetData_Spanish(STRATEGY_TypeDef u8StrategyIndex);
//德语 系统策略设置界面信息
void updateDisplaySystemStrategySetData_German(STRATEGY_TypeDef u8StrategyIndex);
//法语 系统策略设置界面信息
void updateDisplaySystemStrategySetData_French(STRATEGY_TypeDef u8StrategyIndex);
//波兰语 系统策略设置界面信息
void updateDisplaySystemStrategySetData_Polish(STRATEGY_TypeDef u8StrategyIndex);
//意大利语 系统策略设置界面信息
void updateDisplaySystemStrategySetData_Italian(STRATEGY_TypeDef u8StrategyIndex);  
//捷克语 系统策略设置界面信息
void updateDisplaySystemStrategySetData_Czech(STRATEGY_TypeDef u8StrategyIndex);
//荷兰语 系统策略设置界面信息
void updateDisplaySystemStrategySetData_Dutch(STRATEGY_TypeDef u8StrategyIndex);

//系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType); 
//英文 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_English(TPFV_TypeDef u8TPFVStrategyIndex);
//西班牙 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_Spanish(TPFV_TypeDef u8TPFVStrategyIndex);
//德语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_German(TPFV_TypeDef u8TPFVStrategyIndex);
//法语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_French(TPFV_TypeDef u8TPFVStrategyIndex);
//波兰语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_Polish(TPFV_TypeDef u8TPFVStrategyIndex);
//意大利语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_Italian(TPFV_TypeDef u8TPFVStrategyIndex);  
//捷克语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_Czech(TPFV_TypeDef u8TPFVStrategyIndex);
//荷兰语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategyAbstractSetData_Dutch(TPFV_TypeDef u8TPFVStrategyIndex);

//系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,TPFV_TypeDef enum_tpfv);
//英文 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_English(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);  
//西班牙 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_Spanish(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);
//德语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_German(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);
//法语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_French(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);
//波兰语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_Polish(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);
//意大利语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_Italian(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);  
//捷克语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_Czech(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);
//荷兰语 系统TPFV策略设置界面信息
void updateDisplaySystemTPFVStrategySetData_Dutch(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);

//系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//英文 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_English(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);  
//西班牙 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_Spanish(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//德语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_German(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//法语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_French(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//波兰语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_Polish(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//意大利语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_Italian(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);  
//捷克语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_Czech(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//荷兰语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemTPFVStrategyPeriodSetData_Dutch(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);

//系统自发自用策略设置界面信息
void updateDisplaySystemSelfStrategySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_English(void);  
//西班牙 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_Spanish(void);
//德语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_German(void);
//法语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_French(void);
//波兰语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_Polish(void);
//意大利语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_Italian(void);  
//捷克语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_Czech(void);
//荷兰语 系统TPFV策略时间段设置界面信息
void updateDisplaySystemSelfStrategySetData_Dutch(void);

//系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_English(char* strPower);  
//西班牙 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_Spanish(char* strPower);
//德语 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_German(char* strPower);
//法语 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_French(char* strPower);
//波兰语 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_Polish(char* strPower);
//意大利语 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_Italian(char* strPower);  
//捷克语 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_Czech(char* strPower);
//荷兰语 系统备电策略设置界面信息
void updateDisplaySystemBackupStrategySetData_Dutch(char* strPower);

//系统发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_English(char* strForbidSOC,char* strSupplySOC);
//西班牙 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_Spanish(char* strForbidSOC,char* strSupplySOC);
//德语 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_German(char* strForbidSOC,char* strSupplySOC);
//法语 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_French(char* strForbidSOC,char* strSupplySOC);
//波兰语 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_Polish(char* strForbidSOC,char* strSupplySOC);
//意大利语 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_Italian(char* strForbidSOC,char* strSupplySOC);  
//捷克语 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_Czech(char* strForbidSOC,char* strSupplySOC);
//荷兰语 发电机策略设置界面信息
void updateDisplaySystemGenStrategySetData_Dutch(char* strForbidSOC,char* strSupplySOC);

//系统定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_English(REGULAR_TypeDef u8RegularStrategyIndex);
//西班牙 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_Spanish(REGULAR_TypeDef u8RegularStrategyIndex);
//德语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_German(REGULAR_TypeDef u8RegularStrategyIndex);
//法语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_French(REGULAR_TypeDef u8RegularStrategyIndex);
//波兰语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_Polish(REGULAR_TypeDef u8RegularStrategyIndex);
//意大利语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_Italian(REGULAR_TypeDef u8RegularStrategyIndex);  
//捷克语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_Czech(REGULAR_TypeDef u8RegularStrategyIndex);
//荷兰语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategyAbstractSetData_Dutch(REGULAR_TypeDef u8RegularStrategyIndex);

//系统定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,REGULAR_TypeDef enum_RegularClass); 
//英文 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_English(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//西班牙 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_Spanish(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//德语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_German(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//法语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_French(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//波兰语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_Polish(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//意大利语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_Italian(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);  
//捷克语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_Czech(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//荷兰语 定时充放电策略设置界面信息
void updateDisplaySystemRegularStrategySetData_Dutch(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);

//定时充放电策略时间段设置
void updateDisplaySystemRegularStrategyPeriodSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//英文 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_English(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//西班牙 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_Spanish(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//德语 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_German(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//法语 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_French(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//波兰语 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_Polish(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//意大利语 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_Italian(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);  
//捷克语 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_Czech(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//荷兰语 定时充放电策略时间段设置界面信息
void updateDisplaySystemRegularStrategyPeriodSetData_Dutch(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);


//设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_English(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//中文 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_Chinese(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//西班牙 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_Spanish(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//德语 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_German(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//法语 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_French(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//波兰语 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_Polish(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//意大利语 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_Italian(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);  
//捷克语 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_Czech(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//荷兰语 设置系统CT变比设置界面信息
void updateDisplaySystemCTRatioData_Dutch(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT); 
//从Flash读串口信息
void getSysteCTRatioData(void);
//设置串口信息到Flash
void setSystemCTRatioData(bool_t bEnableFlag);



//设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType); 
//英文 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_English(ENABLE_TypeDef u8SetIndex);
//西班牙 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_Spanish(ENABLE_TypeDef u8SetIndex);
//德语 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_German(ENABLE_TypeDef u8SetIndex);
//法语 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_French(ENABLE_TypeDef u8SetIndex);
//波兰语 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_Polish(ENABLE_TypeDef u8SetIndex);
//意大利语 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_Italian(ENABLE_TypeDef u8SetIndex);  
//捷克语 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_Czech(ENABLE_TypeDef u8SetIndex);
//荷兰语 设置系统绝缘检测设置界面信息
void updateDisplaySystemInsulationDetetionData_Dutch(ENABLE_TypeDef u8SetIndex); 

//设置保护使能设置界面信息
void updateDisplayProtectSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType); 
//英文 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_English(PROTECTSETAction_TypeDef u8SetIndex);  
//西班牙 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_Spanish(PROTECTSETAction_TypeDef u8SetIndex);
//德语 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_German(PROTECTSETAction_TypeDef u8SetIndex);
//法语 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_French(PROTECTSETAction_TypeDef u8SetIndex);
//波兰语 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_Polish(PROTECTSETAction_TypeDef u8SetIndex);
//意大利语 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_Italian(PROTECTSETAction_TypeDef u8SetIndex);  
//捷克语 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_Czech(PROTECTSETAction_TypeDef u8SetIndex);
//荷兰语 设置系统保护使能设置界面信息
void updateDisplayProtectSetData_Dutch(PROTECTSETAction_TypeDef u8SetIndex);

//
void updateDisplayProtectItemSetData(DisplayAction_TypeDef dispalyAction,KeyAction_TypeDef nowDisplayActionType,ENABLE_CLASS_TypeDef enableClass);
//
void updateDisplayProtectItemNameSetData(ENABLE_TypeDef sU8ProtectSelected,ENABLE_CLASS_TypeDef enableClass);
//
void updateDisplayProtectItemSetData_English(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//
//
void updateDisplayProtectItemSetData_Spanish(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//
void updateDisplayProtectItemSetData_German(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//
void updateDisplayProtectItemSetData_French(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//
void updateDisplayProtectItemSetData_Polish(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//
void updateDisplayProtectItemSetData_Italian(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//
void updateDisplayProtectItemSetData_Czech(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//
void updateDisplayProtectItemSetData_Dutch(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);


//根据上一次界面操作类型和本次操作类型判断本次实时统计数据更新
void updateDisplayStatisticsData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 实时统计数据界面
void updateDisplayStatisticsData_English(uint8_t sU8StatisticsCounter);
//西班牙语 实时统计数据界面
void updateDisplayStatisticsData_Spanish(uint8_t sU8StatisticsCounter);
//德语 实时统计数据界面
void updateDisplayStatisticsData_German(uint8_t sU8StatisticsCounter);
//法语 实时统计数据界面
void updateDisplayStatisticsData_French(uint8_t sU8StatisticsCounter);
//波兰语 实时统计数据界面
void updateDisplayStatisticsData_Polish(uint8_t sU8StatisticsCounter);
//意大利语 实时统计数据界面
void updateDisplayStatisticsData_Italian(uint8_t sU8StatisticsCounter);
//捷克语 实时统计数据界面
void updateDisplayStatisticsData_Czech(uint8_t sU8StatisticsCounter);
//荷兰语 实时统计数据界面
void updateDisplayStatisticsData_Dutch(uint8_t sU8StatisticsCounter);

//根据上一次界面操作类型和本次操作类型判断本次系统数据更新
void updateDisplaySystemData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 系统数据界面
void updateDisplaySystemData_English(uint8_t sU8SystemCounter);
//西班牙语 系统数据界面
void updateDisplaySystemData_Spanish(uint8_t sU8SystemCounter);
//德语 系统数据界面
void updateDisplaySystemData_German(uint8_t sU8SystemCounter);
//法语 系统数据界面
void updateDisplaySystemData_French(uint8_t sU8SystemCounter);
//波兰语 系统数据界面
void updateDisplaySystemData_Polish(uint8_t sU8SystemCounter);
//意大利语 系统数据界面
void updateDisplaySystemData_Italian(uint8_t sU8SystemCounter);
//捷克语 系统数据界面
void updateDisplaySystemData_Czech(uint8_t sU8SystemCounter);
//荷兰语 系统数据界面
void updateDisplaySystemData_Dutch(uint8_t sU8SystemCounter);

//根据上一次界面操作类型和本次操作类型判断本次实时数据更新
void updateDisplayRealtimeData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 实时数据界面
void updateDisplayRealtimeData_English(uint8_t sU8RealtimeCounter);
//西班牙语 实时数据界面
void updateDisplayRealtimeData_Spanish(uint8_t sU8RealtimeCounter);
//德语 实时数据界面
void updateDisplayRealtimeData_German(uint8_t sU8RealtimeCounter);
//法语 实时数据界面
void updateDisplayRealtimeData_French(uint8_t sU8RealtimeCounter);
//波兰语 实时数据界面
void updateDisplayRealtimeData_Polish(uint8_t sU8RealtimeCounter);
//意大利语 实时数据界面
void updateDisplayRealtimeData_Italian(uint8_t sU8RealtimeCounter);
//捷克语 实时数据界面
void updateDisplayRealtimeData_Czech(uint8_t sU8RealtimeCounter);
//荷兰语 实时数据界面
void updateDisplayRealtimeData_Dutch(uint8_t sU8RealtimeCounter);


//根据上一次界面操作类型和本次操作类型判断本次实时故障告警数据更新
void updateDisplayRealFaultData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 实时故障告警界面
void updateDisplayRealFaultData_English(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//西班牙语 实时故障告警界面
void updateDisplayRealFaultData_Spanish(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//德语 实时故障告警界面
void updateDisplayRealFaultData_German(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//法语 实时故障告警界面
void updateDisplayRealFaultData_French(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//波兰语 实时故障告警界面
void updateDisplayRealFaultData_Polish(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//意大利语 实时故障告警界面
void updateDisplayRealFaultData_Italian(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//捷克语 实时故障告警界面
void updateDisplayRealFaultData_Czech(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//荷兰语 实时故障告警界面
void updateDisplayRealFaultData_Dutch(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//根据上一次界面操作类型和本次操作类型判断本次历史故障告警数据更新
void updateDisplayHistoryFaultData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 历史故障告警界面
void updateDisplayHistoryFaultData_English(uint8_t u8CurrentPage);
//西班牙语 历史故障告警界面
void updateDisplayHistoryFaultData_Spanish(uint8_t u8CurrentPage);
//德语 历史故障告警界面
void updateDisplayHistoryFaultData_German(uint8_t u8CurrentPage);
//法语 历史故障告警界面
void updateDisplayHistoryFaultData_French(uint8_t u8CurrentPage);
//波兰语 历史故障告警界面
void updateDisplayHistoryFaultData_Polish(uint8_t u8CurrentPage);
//意大利语 历史故障告警界面
void updateDisplayHistoryFaultData_Italian(uint8_t u8CurrentPage);
//捷克语 历史故障告警界面
void updateDisplayHistoryFaultData_Czech(uint8_t u8CurrentPage);
//荷兰语 历史故障告警界面
void updateDisplayHistoryFaultData_Dutch(uint8_t u8CurrentPage);

//根据上一次界面操作类型和本次操作类型判断操作记录数据更新
void updateDisplayOperationRecordData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);   
//英文 操作记录界面
void updateDisplayOperationRecordData_English(uint8_t u8CurrentPage);
//西班牙语 操作记录界面
void updateDisplayOperationRecordData_Spanish(uint8_t u8CurrentPage);
//德语 操作记录界面
void updateDisplayOperationRecordData_German(uint8_t u8CurrentPage);
//法语 操作记录界面
void updateDisplayOperationRecordData_French(uint8_t u8CurrentPage);
//波兰语 操作记录界面
void updateDisplayOperationRecordData_Polish(uint8_t u8CurrentPage);
//意大利语 操作记录界面
void updateDisplayOperationRecordData_Italian(uint8_t u8CurrentPage);
//捷克语 操作记录界面
void updateDisplayOperationRecordData_Czech(uint8_t u8CurrentPage);
//荷兰语 操作记录界面
void updateDisplayOperationRecordData_Dutch(uint8_t u8CurrentPage);

void updateDisplayIslandProtectSetData(KeyAction_TypeDef nowDisplayActionType,ENABLE_CLASS_TypeDef enableClass);

//根据上一次界面操作类型和本次操作类型判断本次光伏 SET界面切换
void updateDisplayPVSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 光伏设置界面
void updateDisplayPVSetData_English(uint8_t u8PVSetIndex);
//西班牙语 光伏设置界面
void updateDisplayPVSetData_Spanish(uint8_t u8PVSetIndex);
//德语 光伏设置界面
void updateDisplayPVSetData_German(uint8_t u8PVSetIndex);
//法语 光伏设置界面
void updateDisplayPVSetData_French(uint8_t u8PVSetIndex);
//波兰语 光伏设置界面
void updateDisplayPVSetData_Polish(uint8_t u8PVSetIndex);
//意大利语 光伏设置界面
void updateDisplayPVSetData_Italian(uint8_t u8PVSetIndex);
//捷克语 光伏设置界面
void updateDisplayPVSetData_Czech(uint8_t u8PVSetIndex);
//荷兰语 光伏设置界面
void updateDisplayPVSetData_Dutch(uint8_t u8PVSetIndex);

//根据上一次界面操作类型和本次操作类型判断本次光伏控制SET界面切换
void updateDisplayPVControlWaySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 光伏控制设置界面
void updateDisplayPVControlWaySetData_English(uint8_t u8PVContWaySetIndex);
//西班牙语 光伏控制设置界面
void updateDisplayPVControlWaySetData_Spanish(uint8_t u8PVContWaySetIndex);
//德语 光伏控制设置界面
void updateDisplayPVControlWaySetData_German(uint8_t u8PVContWaySetIndex);
//法语 光伏控制设置界面
void updateDisplayPVControlWaySetData_French(uint8_t u8PVContWaySetIndex);
//波兰语 光伏控制设置界面
void updateDisplayPVControlWaySetData_Polish(uint8_t u8PVContWaySetIndex);
//意大利语 光伏控制设置界面
void updateDisplayPVControlWaySetData_Italian(uint8_t u8PVContWaySetIndex);
//捷克语 光伏控制设置界面
void updateDisplayPVControlWaySetData_Czech(uint8_t u8PVContWaySetIndex);
//荷兰语 光伏控制设置界面
void updateDisplayPVControlWaySetData_Dutch(uint8_t u8PVContWaySetIndex);


//根据上一次界面操作类型和本次操作类型判断本次电池设置SET界面切换
void updateDisplayBMSSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 电池设置设置界面
void updateDisplayBMSSetData_English(uint8_t sU8BMSSetCounter);
//西班牙语 电池设置设置界面
void updateDisplayBMSSetData_Spanish(uint8_t sU8BMSSetCounter);
//德语 电池设置设置界面
void updateDisplayBMSSetData_German(uint8_t sU8BMSSetCounter);
//法语 电池设置设置界面
void updateDisplayBMSSetData_French(uint8_t sU8BMSSetCounter);
//波兰语 电池设置设置界面
void updateDisplayBMSSetData_Polish(uint8_t sU8BMSSetCounter);
//意大利语 电池设置设置界面
void updateDisplayBMSSetData_Italian(uint8_t sU8BMSSetCounter);
//捷克语 电池设置设置界面
void updateDisplayBMSSetData_Czech(uint8_t sU8BMSSetCounter);
//荷兰语 电池设置设置界面
void updateDisplayBMSSetData_Dutch(uint8_t sU8BMSSetCounter);

//根据上一次界面操作类型和本次操作类型判断本次电池厂商设置SET界面切换
void updateDisplayBatteryManufacturerSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_English(uint8_t sU8BatteryManufacturerCounter);
//西班牙语 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_Spanish(uint8_t sU8BatteryManufacturerCounter);
//德语 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_German(uint8_t sU8BatteryManufacturerCounter);
//法语 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_French(uint8_t sU8BatteryManufacturerCounter);
//波兰语 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_Polish(uint8_t sU8BatteryManufacturerCounter);
//意大利语 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_Italian(uint8_t sU8BatteryManufacturerCounter);
//捷克语 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_Czech(uint8_t sU8BatteryManufacturerCounter);
//荷兰语 电池厂商设置设置界面
void updateDisplayBatteryManufacturerSetData_Dutch(uint8_t sU8BatteryManufacturerCounter);
    
//根据上一次界面操作类型和本次操作类型判断本次电池厂商设置SET界面切换
void updateDisplayBatteryTypeSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_English(uint8_t sU8BatteryTypeCounter);
//西班牙语 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_Spanish(uint8_t sU8BatteryTypeCounter);
//德语 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_German(uint8_t sU8BatteryTypeCounter);
//法语 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_French(uint8_t sU8BatteryTypeCounter);
//波兰语 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_Polish(uint8_t sU8BatteryTypeCounter);
//意大利语 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_Italian(uint8_t sU8BatteryTypeCounter);
//捷克语 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_Czech(uint8_t sU8BatteryTypeCounter);
//荷兰语 电池厂商设置设置界面
void updateDisplayBatteryTypeSetData_Dutch(uint8_t sU8BatteryTypeCounter);


//根据上一次界面操作类型和本次操作类型判断本次锂电池设置SET界面切换
void updateDisplayBatteryLiIonParaSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_English(uint8_t sU8BatteryLiParaCounter);
//中文 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_Chinese(uint8_t sU8BatteryLiParaCounter);
//西班牙语 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_Spanish(uint8_t sU8BatteryLiParaCounter);
//德语 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_German(uint8_t sU8BatteryLiParaCounter);
//法语 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_French(uint8_t sU8BatteryLiParaCounter);
//波兰语 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_Polish(uint8_t sU8BatteryLiParaCounter);
//意大利语 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_Italian(uint8_t sU8BatteryLiParaCounter);
//捷克语 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_Czech(uint8_t sU8BatteryLiParaCounter);
//荷兰语 锂电池设置设置界面
void updateDisplayBatteryLiIonParaSetData_Dutch(uint8_t sU8BatteryLiParaCounter);



void updateDisplayBatteryLiIonComWaySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//中文 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_English(uint8_t sU8BatteryComWayCounter);
//中文 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_Chinese(uint8_t sU8BatteryComWayCounter);
//西班牙语 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_Spanish(uint8_t sU8BatteryComWayCounter);
//德语 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_German(uint8_t sU8BatteryComWayCounter);
//法语 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_French(uint8_t sU8BatteryComWayCounter);
//波兰语 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_Polish(uint8_t sU8BatteryComWayCounter);
//意大利语 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_Italian(uint8_t sU8BatteryComWayCounter);
//捷克语 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_Czech(uint8_t sU8BatteryComWayCounter);
//荷兰语 锂电池通信方式界面
void updateDisplayBatteryLiIonComWaySetData_Dutch(uint8_t sU8BatteryComWayCounter);


void updateDisplayBatteryLiIonParaSetEndofSOCData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_English(char* strCharSOC,char* strDisCharSOC);
//中文 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_Chinese(char* strCharSOC,char* strDisCharSOC);
//西班牙语 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_Spanish(char* strCharSOC,char* strDisCharSOC);
//德语 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_German(char* strCharSOC,char* strDisCharSOC);
//法语 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_French(char* strCharSOC,char* strDisCharSOC);
//波兰语 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_Polish(char* strCharSOC,char* strDisCharSOC);
//意大利语 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_Italian(char* strCharSOC,char* strDisCharSOC);
//捷克语 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_Czech(char* strCharSOC,char* strDisCharSOC);
//荷兰语 锂电池充放电截止SOC设置设置界面
void updateDisplayBatteryLiIonParaSetEndofSOCData_Dutch(char* strCharSOC,char* strDisCharSOC);


void updateDisplayBatteryLiIonParaSetCurrentData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_English(char* strCharCur,char* strDisCharCur);
//中文 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_Chinese(char* strCharCur,char* strDisCharCur);
//西班牙语 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_Spanish(char* strCharCur,char* strDisCharCur);
//德语 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_German(char* strCharCur,char* strDisCharCur);
//法语 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_French(char* strCharCur,char* strDisCharCur);
//波兰语 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_Polish(char* strCharCur,char* strDisCharCur);
//意大利语 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_Italian(char* strCharCur,char* strDisCharCur);
//捷克语 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_Czech(char* strCharCur,char* strDisCharCur);
//荷兰语 锂电池最大电流设置设置界面
void updateDisplayBatteryLiIonParaSetCurrentData_Dutch(char* strCharCur,char* strDisCharCur);


//void updateDisplayBatteryLiIonParaSetOverProctectData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//void updateDisplayBatteryLiIonParaSetOverProctectData_English(char* strCharCur,char* strDisCharCur);


//根据上一次界面操作类型和本次操作类型判断本次铅酸电池类型设置SET界面切换
void updateDisplayLeadAcidBatteryTypeSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_English(uint8_t sU8BatteryTypeCounter);
//中文 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_Chinese(uint8_t sU8BatteryTypeCounter);
//西班牙语 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_Spanish(uint8_t sU8BatteryTypeCounter);
//德语 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_German(uint8_t sU8BatteryTypeCounter);
//法语 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_French(uint8_t sU8BatteryTypeCounter);
//波兰语 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_Polish(uint8_t sU8BatteryTypeCounter);
//意大利语 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_Italian(uint8_t sU8BatteryTypeCounter);
//捷克语 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_Czech(uint8_t sU8BatteryTypeCounter);
//荷兰语 铅酸电池类型设置设置界面
void updateDisplayLeadAcidBatteryTypeSetData_Dutch(uint8_t sU8BatteryTypeCounter);


//根据上一次界面操作类型和本次操作类型判断本次铅酸电池类型容量和最大电流设置SET界面切换
void updateDisplayLeadAcidBatteryParaSetCapacityData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_English(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//中文 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_Chinese(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//西班牙语 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_Spanish(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//德语 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_German(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//法语 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_French(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//波兰语 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_Polish(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//意大利语 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_Italian(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//捷克语 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_Czech(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);
//荷兰语 铅酸电池类型容量和最大电流设置界面
void updateDisplayLeadAcidBatteryParaSetCapacityData_Dutch(char* strBmsCapacity,char* strMaxCharCur,char* strMaxDisCharCur);


//根据上一次界面操作类型和本次操作类型判断本次铅酸电池截止SOC设置SET界面切换
void updateDisplayBatteryLeadAcidParaSetEndofSOCData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_English(char* strCharSOC,char* strDisCharSOC);
//中文 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_Chinese(char* strCharSOC,char* strDisCharSOC);
//西班牙语 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_Spanish(char* strCharSOC,char* strDisCharSOC);
//德语 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_German(char* strCharSOC,char* strDisCharSOC);
//法语 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_French(char* strCharSOC,char* strDisCharSOC);
//波兰语 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_Polish(char* strCharSOC,char* strDisCharSOC);
//意大利语 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_Italian(char* strCharSOC,char* strDisCharSOC);
//捷克语 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_Czech(char* strCharSOC,char* strDisCharSOC);
//荷兰语 铅酸电池类型截止SOC设置界面
void updateDisplayBatteryLeadAcidParaSetEndofSOCData_Dutch(char* strCharSOC,char* strDisCharSOC);


//根据上一次界面操作类型和本次操作类型判断本次铅酸电池电压点设置SET界面切换
void updateDisplayLeadAcidBatteryParaSetVoltPointData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_English(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//中文 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_Chinese(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//西班牙语 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_Spanish(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//德语 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_German(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//法语 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_French(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//波兰语 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_Polish(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//意大利语 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_Italian(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//捷克语 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_Czech(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);
//荷兰语 铅酸电池类型电压点设置界面
void updateDisplayLeadAcidBatteryParaSetVoltPointData_Dutch(char* strBmsShutPoint, char* strFloatVoltPoint, char* strConstVoltPoint);

//从Flash获取电池类型
uint8_t getBmsBatteryTypeData(void);

//保存电池类型到Flash
void setBmsBatteryTypeData(uint8_t s8BmsType);

//从Flash获取锂电电池参数
Display_SET_BMS_LiIon_Paras * getLiIonParasData(void);
//保存通信方式到Flash
void setLiIonComWayFlagData(uint8_t u8ComWayFlag);
//保存截止SOC到Flash
void setLiIonEndofSOCData(uint8_t u8EndOfCharSOC,uint8_t u8EndOfDisCharSOC);
//保存最大充放电流到Flash
void setLiIonMaxCharCurData(int16 s16MaxCharCur, int16 s16MaxDisCharCur);


//从Flash获取铅酸电池参数
Display_SET_BMS_LeadAcid_Paras * getLeadAcidParasData(void);
//保存容量和最大充放电流到Flash
void setLeadAcidCapacityAndMaxCharCurData(uint16_t u16Capacity, int16 s16MaxCharCur, int16 s16MaxDisCharCur);
//保存截止SOC到Flash
void setLeadAcidEndofSOCData(uint8_t u8EndOfCharSOC,uint8_t u8EndOfDisCharSOC);
//保存电压点到Flash
void setVoltPointData(int16 s16LowVoltPoint,int16 s16FloatVolt,int16 s16ConstVolt);


//根据上一次界面操作类型和本次操作类型判断本次电网 GridSET界面切换
void updateDisplayGridSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 电网设置设置界面
void updateDisplayGridSetData_English(uint8_t sU8GridCounter);
//西班牙语 电网设置设置界面
void updateDisplayGridSetData_Spanish(uint8_t sU8GridCounter);
//德语 电网设置设置界面
void updateDisplayGridSetData_German(uint8_t sU8GridCounter);
//法语 电网设置设置界面
void updateDisplayGridSetData_French(uint8_t sU8GridCounter);
//波兰语 电网设置设置界面
void updateDisplayGridSetData_Polish(uint8_t sU8GridCounter);
//意大利语 电网设置设置界面
void updateDisplayGridSetData_Italian(uint8_t sU8GridCounter);
//捷克语 电网设置设置界面
void updateDisplayGridSetData_Czech(uint8_t sU8GridCounter);
//荷兰语 电网设置设置界面
void updateDisplayGridSetData_Dutch(uint8_t sU8GridCounter);


/***************************************************************************
 功能:根据上一次界面操作类型和本次操作类型判断本次 功率设置界面
****************************************************************************/
void updateDisplayGridPowerSettingsData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
// 功能：功率设置 英文界面
void updateDisplayGridPowerSettingsData_English(uint8_t sU8PowerSetCounter);                    
// 功能：功率设置 中文界面
void updateDisplayGridPowerSettingsData_Chinese(uint8_t sU8PowerSetCounter);
// 功能：功率设置 西班牙界面 
void updateDisplayGridPowerSettingstData_Spanish(uint8_t sU8PowerSetCounter);
// 功能：功率设置 德语界面
void updateDisplayGridPowerSettingsData_German(uint8_t sU8PowerSetCounter);
// 功能：功率设置 法语界面
void updateDisplayGridPowerSettingsData_French(uint8_t sU8PowerSetCounter);                    
// 功能：功率设置 波兰语界面
void updateDisplayGridPowerSettingsData_Polish(uint8_t sU8PowerSetCounter);   
// 功能：功率设置 意大利界面
void updateDisplayGridPowerSettingsData_Italian(uint8_t sU8PowerSetCounter);                   
// 功能：功率设置 捷克语界面
void updateDisplayGridPowerSettingsData_Czech(uint8_t sU8PowerSetCounter);                
// 功能：功率设置 荷兰语界面
void updateDisplayGridPowerSettingsData_Dutch(uint8_t sU8PowerSetCounter);     
// 功能：功率设置 荷兰语界面
void updateDisplayGridPowerSettingsData_English(uint8_t sU8PowerSetCounter);       


//根据上一次界面操作类型和本次操作类型判断本次电网安规 GridSRSET界面切换
void updateDisplayGridSRSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 电网安规设置设置界面
void updateDisplayGridSRSetData_English(uint8_t sU8GridCounter);
//西班牙语 电网安规设置设置界面
void updateDisplayGridSRSetData_Spanish(uint8_t sU8GridCounter);
//德语 电网安规设置设置界面
void updateDisplayGridSRSetData_German(uint8_t sU8GridCounter);
//法语 电网安规设置设置界面
void updateDisplayGridSRSetData_French(uint8_t sU8GridCounter);
//波兰语 电网安规设置设置界面
void updateDisplayGridSRSetData_Polish(uint8_t sU8GridCounter);
//意大利语 电网安规设置设置界面
void updateDisplayGridSRSetData_Italian(uint8_t sU8GridCounter);
//捷克语 电网安规设置设置界面
void updateDisplayGridSRSetData_Czech(uint8_t sU8GridCounter);
//荷兰语 电网安规设置设置界面
void updateDisplayGridSRSetData_Dutch(uint8_t sU8GridCounter);
//获取当前系统的安规标准
SR_TypeDef getSafetyRegulationItem(void);
//设置当前系统的安规标准
void setSafetyRegulationItem(SR_TypeDef srItem);

void updateDisplayGridReactPowerControlWaySetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);  
void updateDisplayGridReactPowerControlWaySetData_English(uint8_t u8Way);
void updateDisplayGridReactPowerControlWaySetData_Spanish(uint8_t u8Way);
void updateDisplayGridReactPowerControlWaySetData_German(uint8_t u8Way);
void updateDisplayGridReactPowerControlWaySetData_French(uint8_t u8Way);
void updateDisplayGridReactPowerControlWaySetData_Polish(uint8_t u8Way);
void updateDisplayGridReactPowerControlWaySetData_Italian(uint8_t u8Way);
void updateDisplayGridReactPowerControlWaySetData_Czech(uint8_t u8Way);
void updateDisplayGridReactPowerControlWaySetData_Dutch(uint8_t u8Way);
REACTPOWER_CONTROL_TypeDef getReactPowerControlWayItem(void);
void setReactPowerControlWayItem(REACTPOWER_CONTROL_TypeDef controlWayItem);
//无功功率设置界面
void updateDisplayGridReactivePowerSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);  
//英文 无功功率设置界面
void updateDisplayGridReactivePowerSetData_English(char *ReactivePowerValue);
//中文 无功功率设置界面
//西班牙语 无功功率设置界面
void updateDisplayGridReactivePowerSetData_Spanish(char *ReactivePowerValue);
//德语 无功功率设置界面
void updateDisplayGridReactivePowerSetData_German(char *ReactivePowerValue);
//法语 无功功率设置界面
void updateDisplayGridReactivePowerSetData_French(char *ReactivePowerValue);
//波兰语 无功功率设置界面
void updateDisplayGridReactivePowerSetData_Polish(char *ReactivePowerValue);
//意大利语 无功功率设置界面
void updateDisplayGridReactivePowerSetData_Italian(char *ReactivePowerValue);
//捷克语 无功功率设置界面
void updateDisplayGridReactivePowerSetData_Czech(char *ReactivePowerValue);
//荷兰语 无功功率设置界面
void updateDisplayGridReactivePowerSetData_Dutch(char *ReactivePowerValue);
int16_t getReactPowerData(void);
void setReactPowerData(int16_t s16ReactPower);

//功率设置界面
void updateDisplayGridPowerFactorSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);  
//英文 功率设置界面
void updateDisplayGridPowerFactorSetData_English(char* strPF);
//中文 功率设置界面
//西班牙语 功率设置界面
void updateDisplayGridPowerFactorSetData_Spanish(char* strPF);
//德语 电网安规设置设置界面
void updateDisplayGridPowerFactorSetData_German(char* strPF);
//法语 功率设置界面
void updateDisplayGridPowerFactorSetData_French(char* strPF);
//波兰语 功率设置界面
void updateDisplayGridPowerFactorSetData_Polish(char* strPF);
//意大利语 功率设置界面
void updateDisplayGridPowerFactorSetData_Italian(char* strPF);
//捷克语 功率设置界面
void updateDisplayGridPowerFactorSetData_Czech(char* strPF);
//荷兰语 功率设置界面
void updateDisplayGridPowerFactorSetData_Dutch(char* strPF);
int16_t getPowerFactorData(void);
//无功功率因数写Flash
void setPowerFactorData(int16_t s16ReactPower);

//根据上一次界面操作类型和本次操作类型判断本次电网电价 GridPriceSET界面切换
void updateDisplayGridPriceSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 电网电价设置设置界面
void updateDisplayGridPriceSetData_English(uint8_t sU8GridCounter);
//中文 电网电价设置设置界面
//西班牙语 电网电价设置设置界面
void updateDisplayGridPriceSetData_Spanish(uint8_t sU8GridCounter);
//德语 电网电价设置设置界面
void updateDisplayGridPriceSetData_German(uint8_t sU8GridCounter);
//法语 电网电价设置设置界面
void updateDisplayGridPriceSetData_French(uint8_t sU8GridCounter);
//波兰语 电网电价设置设置界面
void updateDisplayGridPriceSetData_Polish(uint8_t sU8GridCounter);
//意大利语 电网电价设置设置界面
void updateDisplayGridPriceSetData_Italian(uint8_t sU8GridCounter);
//捷克语 电网电价设置设置界面
void updateDisplayGridPriceSetData_Czech(uint8_t sU8GridCounter);
//荷兰语 电网电价设置设置界面
void updateDisplayGridPriceSetData_Dutch(uint8_t sU8GridCounter);

//根据上一次界面操作类型和本次操作类型判断本次电网尖峰平谷分时电价 GridTPFVPriceSET界面切换
void updateDisplayGridPriceTPFVSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,TPFV_TypeDef enum_tpfv);
//英文 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_English(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv); 
//中文 尖峰平谷分时电价设置设置界面
//西班牙语 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_Spanish(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//德语 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_German(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//法语 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_French(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//波兰语 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_Polish(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//意大利语 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_Italian(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//捷克语 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_Czech(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//荷兰语 尖峰平谷分时电价设置设置界面
void updateDisplayGridPriceTPFVSetData_Dutch(uint8_t sU8BMSSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);

//根据上一次界面操作类型和本次操作类型判断本次电网尖峰平谷分时电价起始时间设置 GridTPFVPriceSET界面切换
void updateDisplayGridPriceTPFVTimePeriodSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType,TPFV_TypeDef enum_tpfv, TPFV_Price_TypeDef enumTPFVPeriod);
//英文 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_English(char* strStartTime, char* strEndTime, TPFV_TypeDef enum_tpfv,TPFV_Price_TypeDef enumTPFVPeriod); 
//中文 分时电价起始时间设置设置界面
//西班牙语 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_Spanish(char* strStartTime, char* strEndTime, TPFV_Price_TypeDef enumTPFVPeriod);
//德语 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_German(char* strStartTime, char* strEndTime, TPFV_Price_TypeDef enumTPFVPeriod);
//法语 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_French(char* strStartTime, char* strEndTime, TPFV_Price_TypeDef enumTPFVPeriod);
//波兰语 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_Polish(char* strStartTime, char* strEndTime, TPFV_Price_TypeDef enumTPFVPeriod);
//意大利语 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_Italian(char* strStartTime, char* strEndTime, TPFV_Price_TypeDef enumTPFVPeriod);
//捷克语 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_Czech(char* strStartTime, char* strEndTime, TPFV_Price_TypeDef enumTPFVPeriod);
//荷兰语 分时电价起始时间设置设置界面
void updateDisplayGridPriceTPFVTimePeriodSetData_Dutch(char* strStartTime, char* strEndTime, TPFV_Price_TypeDef enumTPFVPeriod);

//根据上一次界面操作类型和本次操作类型判断本次发电机 SET界面切换
void updateDisplayGenSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 发电机设置设置界面
void updateDisplayGenSetData_English(uint8_t sU8GenSetCounter);
//英文 发电机设置设置界面
void updateDisplayGenSetData_Chinese(uint8_t sU8GenSetCounter);
//西班牙语 发电机设置设置界面
void updateDisplayGenSetData_Spanish(uint8_t sU8GenSetCounter);
//德语 发电机设置设置界面
void updateDisplayGenSetData_German(uint8_t sU8GenSetCounter);
//法语 发电机设置设置界面
void updateDisplayGenSetData_French(uint8_t sU8GenSetCounter);
//波兰语 发电机设置设置界面
void updateDisplayGenSetData_Polish(uint8_t sU8GenSetCounter);
//意大利语 发电机设置设置界面
void updateDisplayGenSetData_Italian(uint8_t sU8GenSetCounter);
//捷克语 发电机设置设置界面
void updateDisplayGenSetData_Czech(uint8_t sU8GenSetCounter);
//荷兰语 发电机设置设置界面
void updateDisplayGenSetData_Dutch(uint8_t sU8GenSetCounter);

//根据上一次界面操作类型和本次操作类型判断本次发电机功率参数设置SET界面切换
void updateDisplayGenPowerParaSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_English(char *strRatedPower,char *strMaxPower);
//英文 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_Chinese(char *strRatedPower,char *strMaxPower);
//西班牙语 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_Spanish(char *strRatedPower,char *strMaxPower);
//德语 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_German(char *strRatedPower,char *strMaxPower);
//法语 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_French(char *strRatedPower,char *strMaxPower);
//波兰语 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_Polish(char *strRatedPower,char *strMaxPower);
//意大利语 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_Italian(char *strRatedPower,char *strMaxPower);
//捷克语 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_Czech(char *strRatedPower,char *strMaxPower);
//荷兰语 发电机功率参数设置界面
void updateDisplayGenPowerParaSetData_Dutch(char *strRatedPower,char *strMaxPower);
//从Flash获取发电机参数
Display_SET_GenPara * getGenParaData(void);
//写发电机参数到Flash
void setGenParaData(Display_SET_GenPara stGenPara);

//根据上一次界面操作类型和本次操作类型判断本次发电机用途选择设置SET界面切换
void updateDisplayGenUsageSelectSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 发电机用途选择设置界面
void updateDisplayGenUsageSelectSetData_English(uint8_t sU8GenUsageSCounter);
//英文 发电机用途选择设置界面
void updateDisplayGenUsageSelectSetData_Chinese(uint8_t sU8GenUsageSCounter);
//西班牙语 发电机用途选择设置界面
void updateDisplayGenUsageSelectSetData_Spanish(uint8_t sU8GenUsageSCounter);
//德语 发电机用途选择设置界面
void updateDisplayGennUsageSelectSetData_German(uint8_t sU8GenUsageSCounter);
//法语 发电机用途选择设置界面
void updateDisplayGennUsageSelectSetData_French(uint8_t sU8GenUsageSCounter);
//波兰语 发电机用途选择设置界面
void updateDisplayGennUsageSelectSetData_Polish(uint8_t sU8GenUsageSCounter);
//意大利语 发电机用途选择设置界面
void updateDisplayGenPnUsageSelectSetData_Italian(uint8_t sU8GenUsageSCounter);
//捷克语 发电机用途选择设置界面
void updateDisplayGennUsageSelectSetData_Czech(uint8_t sU8GenUsageSCounter);
//荷兰语 发电机用途选择设置界面
void updateDisplayGenPnUsageSelectSetData_Dutch(uint8_t sU8GenUsageSCounter);
//从Flash获取发电机用途选择参数
uint8_t getDryNodeUseData(void);
//写发电机用途选择参数到Flash
void setDryNodeUseData(uint8_t u8UsageNode);

//根据上一次界面操作类型和本次操作类型判断本次发电机干接点选择设置SET界面切换
void updateDisplayGenDryRlySelectSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_English(uint8_t sU8GenUsageSCounter);
//英文 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_Chinese(uint8_t sU8GenUsageSCounter);
//西班牙语 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_Spanish(uint8_t sU8GenUsageSCounter);
//德语 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_German(uint8_t sU8GenUsageSCounter);
//法语 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_French(uint8_t sU8GenUsageSCounter);
//波兰语 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_Polish(uint8_t sU8GenUsageSCounter);
//意大利语 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_Italian(uint8_t sU8GenUsageSCounter);
//捷克语 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_Czech(uint8_t sU8GenUsageSCounter);
//荷兰语 发电机干接点选择设置界面
void updateDisplayGenDryRlySelectSetData_Dutch(uint8_t sU8GenUsageSCounter);
//从Flash获取发电机干接点选择参数
uint8_t getDryNodeData(void);
//写发电机用途选择参数到Flash
void setDryNodeData(uint8_t u8DryNode);

//根据上一次界面操作类型和本次操作类型判断本次智能负载参数设置SET界面切换
void updateDisplayIntelLoadParaSetData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 智能负载参数设置界面
void updateDisplayIntelLoadSetData_English(char *strCutSOC,char *stOnSOC);
//英文 智能负载参数设置界面
void updateDisplayIntelLoadSetData_Chinese(char *strCutSOC,char *stOnSOC);
//西班牙语 智能负载参数设置界面
void updateDisplayIntelLoadSetData_Spanish(char *strCutSOC,char *stOnSOC);
//德语 智能负载参数设置界面
void updateDisplayIntelLoadSetData_German(char *strCutSOC,char *stOnSOC);
//法语 智能负载参数设置界面
void updateDisplayIntelLoadSetData_French(char *strCutSOC,char *stOnSOC);
//波兰语 智能负载参数设置界面
void updateDisplayIntelLoadSetData_Polish(char *strCutSOC,char *stOnSOC);
//意大利语 智能负载参数设置界面
void updateDisplayIntelLoadSetData_Italian(char *strCutSOC,char *stOnSOC);
//捷克语 智能负载参数设置界面
void updateDisplayIntelLoadSetData_Czech(char *strCutSOC,char *stOnSOC);
//荷兰语 智能负载参数设置界面
void updateDisplayIntelLoadSetData_Dutch(char *strCutSOC,char *stOnSOC);
//从Flash获取智能负载参数
Display_SET_IntelLoad * getIntelLoadParaData(void);
//写智能负载参数到Flash
void setIntelLoadParaData(Display_SET_IntelLoad stIntelLoadPara);

//根据上一次界面操作类型和本次操作类型判断本次升级 界面切换
void updateDisplayUpgradeData(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//英文 升级界面
void updateDisplayUpgradeData_English(Upgrade_TypeDef u8UpgradeIndex); 
//中文 升级界面
//西班牙语 升级界面
void updateDisplayUpgradeData_Spanish(Upgrade_TypeDef u8UpgradeIndex);
//德语 升级界面
void updateDisplayUpgradeData_German(Upgrade_TypeDef u8UpgradeIndex);
//法语 升级界面
void updateDisplayUpgradeData_French(Upgrade_TypeDef u8UpgradeIndex);
//波兰语 升级界面
void updateDisplayUpgradeData_Polish(Upgrade_TypeDef u8UpgradeIndex);
//意大利语 升级界面
void updateDisplayUpgradeData_Italian(Upgrade_TypeDef u8UpgradeIndex);
//捷克语 升级界面
void updateDisplayUpgradeData_Czech(Upgrade_TypeDef u8UpgradeIndex);
//荷兰语 升级界面
void updateDisplayUpgradeData_Dutch(Upgrade_TypeDef u8UpgradeIndex);



//根据故障码获取故障名称
void getFaultNameByFaultCode(char* Fault_Name,uint16_t u16Code);
//根据操作类型码获取操作名称
void getOperateNameByOperateCode(char* Operate_Name,uint8_t u8Code);
//根据操作对象码获取操作对象名称名称
void getOperatObjeNameByOperateObjCode(char* OperateObj_Name,uint8_t u8Code);
//按键检测
Display_KEYDetection_Status getKeyDetectionStatus(void);

//获取当前系统的语言
Language_TypeDef getSystemLanguageItem(void);
//设置当前系统的语言
void setSystemLanguageItem(Language_TypeDef languageItem);
BMS_Manu_TypeDef getBatteryManufacturerItem(void); 
void setBatteryManufacturerItem(BMS_Manu_TypeDef BMSManuItem);
//系统设置时间接口到RTC时钟
void setDisplayTimetoRTCTime(void);
//系统RTC时钟到显示时间
void getRTCTimetoDisplayTime(void);
//系统设置密码接口到Flash存储
void setDisplayPasswordtToFlash(char* sSetPassword);
//系统设置从Flash存储获取密码
void getDisplayPasswordFromFlash(char* sGetPassword);
//密码校验 password verify
Tip_TypeDef DisplaySystemPasswordVerify(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//登陆校验 Login verify
Tip_TypeDef DisplaySystemLoginVerify(char* sPassword);
//异常提示界面
void updateDisplaySystemPrompt(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//确认界面
void updateDisplaySystemConfirm(KeyAction_TypeDef nowActionType,DisplayAction_TypeDef nowDisplayType);
//产生一条操作记录
void generateOperationRecord(uint16_t u16Type);

//获取统计数据接口函数
extern Display_DATA_STATISTICAL* Display_Get_OperateStatistics(void);
//获取电池设置接口
extern Display_SET_BMS* Display_Get_BmsSetPara(void);
//获取分时电价数据接口函数
extern Display_SET_Grid_TimeDivisionElecPrice* Display_Get_ElecPrice(void);
//获取系统策略数据接口函数
extern Display_SET_System_Strategy* Display_Get_SystemStrategy(void);
//获取发电机参数数据接口函数
extern Display_SET_Gen* Display_Get_GenPara(void);

//获取电网参数数据接口函数
extern Display_SET_Grid* Display_Get_GridPara(void);
//获取PV数据参数
Display_SET_PV* Display_Get_PVPara(void);
//获取保护数据参数
Display_SET_System_ProtectEnable *Display_Get_ProtectPara(void);

//获取统计数据接口函数
extern Display_DATA_STATISTICAL* Display_Get_SystemStatistical(void);
//统计数据清零接口函数
extern void Display_Clear_SystemStatistical(void);
//电网数据清零接口函数
extern Display_SET_Grid* Display_Get_Grid(void);

//电网状态标志结构体
typedef struct 
{
    uint16_t bIsSell                :1;             //买电使能标志
    uint16_t bIsHasGen              :1;             //发电机使能标志
    uint16_t bIsHasMeter            :1;             //电表使能标志
    uint16_t bIsHasCT               :1;             //CT使能标志
    uint16_t bIsHasBMS              :1;             //BMS使能标志
    uint16_t bControlWay            :1;             //控制标志
    uint16_t bControlLowPower           :1;             //低功耗使能
    uint16_t bKEYDetectionReserve   :9;            //预留
}Display_EnableDetection_Status;

//获取使能状态信息接口函数
extern void Display_Get_EnableDetection(Display_EnableDetection_Status* pEnableDetection);

//设置控制方式接口函数
extern void Display_Set_ControlWay(uint8_t u8ControlWay);

//功率数据结构体
typedef struct {
    uint16_t u16PVPower;              //光伏功率
    uint16_t u16tLoadPower;           //负载功率
     int16_t s16GridPower;            //电网功率
    uint16_t u16ChargePower;          //电池充电功率
    uint16_t u16tDisChargePower;      //电池放电功率
}Display_Kind_Power;

//获取使能状态信息接口函数
extern void Display_Get_KindPower(Display_Kind_Power* pKindPower);

//获取LCD屏实时刷新数据
extern void GetDisplayRealTimeData(void);

typedef struct {
    uint8_t u8Version_V;              //V版本号
    uint8_t u8Version_B;              //B版本号
    uint8_t u8Version_D;              //D版本号
}Display_Version;
extern void Display_Get_EMSVersion(Display_Version* pVersion);
#pragma pack()
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
