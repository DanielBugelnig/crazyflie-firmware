/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie simulation firmware
 *
 * sim_clock.h - FreeRTOS tick driven by the simulation clock (SITL only)
 *
 * The SITL FreeRTOS port (sitl_make/freertos/port.c) counts ticks on the wall clock until the
 * simulator reports its time, then advances the tick only as far as the simulation time has, so
 * the firmware keeps pace with a simulation running slower (or faster) than real time.
 */
#pragma once

#include <stdint.h>

/**
 * Simulation time of the newest IMU sample [us], from any thread. Must not be called from a
 * FreeRTOS task that waits for a tick to read the next sample (see socketlink.c).
 */
void vPortSetSimTimeUs(uint64_t timeUs);
