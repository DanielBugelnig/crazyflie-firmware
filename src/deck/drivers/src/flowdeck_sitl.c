/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie simulation firmware
 *
 * SITL counterpart of flowdeck_v1v2.c. The simulator sends what the PMW3901
 * reports every ~10 ms (motion burst); this file applies the same processing
 * as the real deck driver before the measurement goes to the estimator, and
 * registers the same motion.* parameters and logs.
 */

#include <stdlib.h>
#include <string.h>

#include "sensors_sitl.h"
#include "estimator.h"
#include "log.h"
#include "param.h"

#define OULIER_LIMIT 100

typedef struct {
  uint8_t motion;
  int16_t deltaX;
  int16_t deltaY;
  uint8_t squal;
  uint16_t shutter;
} motionSim_t;

static motionSim_t currentMotion;
static uint8_t outlierCount = 0;
static float stdFlow = 2.0f;

static bool useFlowDisabled = false;
static bool useAdaptiveStd = false;
static float flowStdFixed = 2.0f;

void flowdeckSitlProcess(const uint8_t *data)
{
  // Packet: [deltaX i16][deltaY i16][squal u8][shutter u16][motion u8][dt f32], little endian
  float dt;
  memcpy(&currentMotion.deltaX, &data[0], sizeof(int16_t));
  memcpy(&currentMotion.deltaY, &data[2], sizeof(int16_t));
  currentMotion.squal = data[4];
  memcpy(&currentMotion.shutter, &data[5], sizeof(uint16_t));
  currentMotion.motion = data[7];
  memcpy(&dt, &data[8], sizeof(float));

  // Flip motion information to comply with sensor mounting
  int16_t accpx = -currentMotion.deltaY;
  int16_t accpy = -currentMotion.deltaX;

  // Outlier removal
  if (abs(accpx) < OULIER_LIMIT && abs(accpy) < OULIER_LIMIT) {
    if (useAdaptiveStd) {
      // Fitted by Bitcraze from flights over low and high texture
      float shutter_f = (float)currentMotion.shutter;
      stdFlow = 0.0007984f * shutter_f + 0.4335f;
      if (stdFlow < 0.1f) stdFlow = 0.1f;
    } else {
      stdFlow = flowStdFixed;
    }

    flowMeasurement_t flowData;
    flowData.stdDevX = stdFlow;
    flowData.stdDevY = stdFlow;
    // Time since the previous read, also for reads without motion
    flowData.dt = dt;
    flowData.dpixelx = (float)accpx;
    flowData.dpixely = (float)accpy;

    // Push measurements into the estimator if flow is not disabled
    // and the PMW flow sensor indicates motion detection
    if (!useFlowDisabled && currentMotion.motion == 0xB0) {
      estimatorEnqueueFlow(&flowData);
    }
  } else {
    outlierCount++;
  }
}

LOG_GROUP_START(motion)
LOG_ADD(LOG_UINT8, motion, &currentMotion.motion)
LOG_ADD(LOG_INT16, deltaX, &currentMotion.deltaX)
LOG_ADD(LOG_INT16, deltaY, &currentMotion.deltaY)
LOG_ADD(LOG_UINT16, shutter, &currentMotion.shutter)
LOG_ADD(LOG_UINT8, outlierCount, &outlierCount)
LOG_ADD(LOG_UINT8, squal, &currentMotion.squal)
LOG_ADD(LOG_FLOAT, std, &stdFlow)
LOG_GROUP_STOP(motion)

PARAM_GROUP_START(motion)
/**
 * @brief Disable flow measurements in the estimator
 */
PARAM_ADD(PARAM_UINT8, disable, &useFlowDisabled)
/**
 * @brief Noise level from the shutter time instead of flowStdFixed
 */
PARAM_ADD(PARAM_UINT8, adaptive, &useAdaptiveStd)
/**
 * @brief Standard deviation of the flow measurements [pixels]
 */
PARAM_ADD_CORE(PARAM_FLOAT, flowStdFixed, &flowStdFixed)
PARAM_GROUP_STOP(motion)
