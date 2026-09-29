/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie simulation firmware
 *
 * Copyright (C) 2018 Bitcraze AB
 * Copyright (C) 2018  Eric Goubault, Sylvie Putot, Franck Djeumou
 *             Cosynux , LIX , France
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __SENSORS_SIM_H__
#define __SENSORS_SIM_H__

#include "sensors.h"

void sensorsSimInit(void);
bool sensorsSimTest(void);
bool sensorsSimAreCalibrated(void);
bool sensorsSimManufacturingTest(void);
void sensorsSimAcquire(sensorData_t *sensors);
void sensorsSimWaitDataReady(void);
bool sensorsSimReadGyro(Axis3f *gyro);
bool sensorsSimReadAcc(Axis3f *acc);
bool sensorsSimReadMag(Axis3f *mag);
bool sensorsSimReadBaro(baro_t *baro);
void sensorsSimSetAccMode(accModes accMode);

// Deck presence reported by the simulator (implemented in deck_sitl.c)
#define SITL_DECK_FLOW2        (1 << 0)
#define SITL_DECK_MULTIRANGER  (1 << 1)
#define SITL_DECK_AI           (1 << 2)
void deckSitlSetPresent(uint8_t decks);

// Raw PMW3901 motion burst from the simulator (implemented in flowdeck_sitl.c)
void flowdeckSitlProcess(const uint8_t *data);

#endif // __SENSORS_SIM_H__