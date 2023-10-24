
#ifndef __GLOBALCONST_H_
#define __GLOBALCONST_H_


/*------System configuration------*/

#define TIME_INTERVAL                   (0)
#define SINE_POINT_MAX_NUM_50HZ         (384)
#define SINE_POINT_MAX_NUM_60HZ         (320)

/*------Battery voltage------*/
#define BATTERY_VOLTAGE_0V1             (1)
#define BATTERY_VOLTAGE_0V3             (3)

/*------Battery current------*/
#define BATTERY_CURRENT_2A              (200)
#define BATTERY_CURRENT_5A              (500)


/*------Power frequency------*/

#define FREQUENCY_50HZ0                                 (5000)
#define FREQUENCY_60HZ0                                 (6000)

/*------Power phase lock loop------*/

#define PLL_SOGI_GAIN                                   (0)

#define PLL_SOGI_INPUT_UPPER_LIMIT                      (0)
#define PLL_SOGI_INPUT_LOWER_LIMIT                      (0)

#define PLL_POWER_FREQUENCY_FEEDBACK_B0                 (0)
#define PLL_POWER_FREQUENCY_FEEDBACK_B1                 (0)
#define PLL_POWER_FREQUENCY_FEEDBACK_B2                 (0)
#define PLL_POWER_FREQUENCY_FEEDBACK_A1                 (0)
#define PLL_POWER_FREQUENCY_FEEDBACK_A2                 (0)
#define PLL_POWER_FREQUENCY_FEEDBACK_INPUT_UPPER_LIMIT  (0)
#define PLL_POWER_FREQUENCY_FEEDBACK_INPUT_LOWER_LIMIT  (0)


#define PLL_POWER_PHASE_FEEDBACK_B0                     (0)
#define PLL_POWER_PHASE_FEEDBACK_B1                     (0)
#define PLL_POWER_PHASE_FEEDBACK_B2                     (0)
#define PLL_POWER_PHASE_FEEDBACK_A1                     (0)
#define PLL_POWER_PHASE_FEEDBACK_A2                     (0)
#define PLL_POWER_PHASE_FEEDBACK_INPUT_UPPER_LIMIT      (0)
#define PLL_POWER_PHASE_FEEDBACK_INPUT_LOWER_LIMIT      (0)

/*------PFC control loop------*/
#define PFC_OUTER_LOOP_B0                               (0)
#define PFC_OUTER_LOOP_B1                               (0)
#define PFC_OUTER_LOOP_B2                               (0)
#define PFC_OUTER_LOOP_A1                               (0)
#define PFC_OUTER_LOOP_A2                               (0)
#define PFC_OUTER_LOOP_INPUT_UPPER_LIMIT                (0)
#define PFC_OUTER_LOOP_INPUT_LOWER_LIMIT                (0)

#define PFC_POWER_FREQUENCY_NOTCH_B0                    (0)
#define PFC_POWER_FREQUENCY_NOTCH_B1                    (0)
#define PFC_POWER_FREQUENCY_NOTCH_B2                    (0)
#define PFC_POWER_FREQUENCY_NOTCH_A1                    (0)
#define PFC_POWER_FREQUENCY_NOTCH_A2                    (0)
#define PFC_POWER_FREQUENCY_NOTCH_INPUT_UPPER_LIMIT     (0)
#define PFC_POWER_FREQUENCY_NOTCH_INPUT_LOWER_LIMIT     (0)

#define PFC_INNER_LOOP_B0                               (0)
#define PFC_INNER_LOOP_B1                               (0)
#define PFC_INNER_LOOP_B2                               (0)
#define PFC_INNER_LOOP_A1                               (0)
#define PFC_INNER_LOOP_A2                               (0)
#define PFC_INNER_LOOP_INPUT_UPPER_LIMIT                (0)
#define PFC_INNER_LOOP_INPUT_LOWER_LIMIT                (0)

#define PFC_BUS_SOFT_START_STEP                         (0)

/*------INV control loop------*/

/*------LLC control loop------*/
#define LLC_DRIVER_SOFT_START_MAX_STEP                  (14)

/*------Parallel service------*/
#define PARALLEL_SYSTEM_0                               (0)
#define PARALLEL_SYSTEM_1                               (1)
#define PARALLEL_SYSTEM_2                               (2)
#define PARALLEL_SYSTEM_3                               (3)
#define PARALLEL_SYSTEM_4                               (4)
#define PARALLEL_SYSTEM_5                               (5)
#define PARALLEL_SYSTEM_6                               (6)
#define PARALLEL_SYSTEM_7                               (7)
#define PARALLEL_SYSTEM_8                               (8)
#define PARALLEL_MAX_NUM                                (9)

#define PARALLEL_DATA_NEW_ROLE                          (0)
#define PARALLEL_DATA_MASTER_ROLE                       (1)
#define PARALLEL_DATA_SLAVE_ROLE                        (2)
#define PARALLEL_DATA_ROLE_MAX                          (3)

#define PARALLEL_PHASE_NEW_ROLE                         (0)
#define PARALLEL_PHASE_MASTER_ROLE                      (1)
#define PARALLEL_PHASE_SLAVE_ROLE                       (2)
#define PARALLEL_PHASE_ROLE_MAX                         (3)

#define PARALLEL_MODE_SINGLE                            (0)
#define PARALLEL_MODE_PARALLEL                          (1)
#define PARALLEL_MODE_PHASE_A                           (2)
#define PARALLEL_MODE_PHASE_B                           (3)
#define PARALLEL_MODE_PHASE_C                           (4)


#endif
