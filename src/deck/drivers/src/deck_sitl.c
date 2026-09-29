#include <stdint.h>
#include "param.h"
#include "sensors_sitl.h"

static uint8_t bcFlow = 0;
static uint8_t bcFlow2 = 1;
static uint8_t bcLighthouse4 = 0;
static uint8_t bcLoco = 0;
static uint8_t bcDWM1000 = 0;
static uint8_t bcZRanger = 0;
static uint8_t bcZRanger2 = 0;
static uint8_t bcLedRing = 0;
static uint8_t bcMultiranger = 1;
static uint8_t bcColorLedBot = 1;
static uint8_t bcColorLedTop = 1;
static uint8_t bcAI = 0;

// The defaults above are kept until the simulator reports its deck stack
// (the Gazebo plugin does, MuJoCo does not).
void deckSitlSetPresent(uint8_t decks)
{
  bcFlow2 = (decks & SITL_DECK_FLOW2) ? 1 : 0;
  bcMultiranger = (decks & SITL_DECK_MULTIRANGER) ? 1 : 0;
  bcAI = (decks & SITL_DECK_AI) ? 1 : 0;
}

PARAM_GROUP_START(deck)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcFlow, &bcFlow)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcFlow2, &bcFlow2)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcLighthouse4, &bcLighthouse4)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcLoco, &bcLoco)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcDWM1000, &bcDWM1000)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcZRanger, &bcZRanger)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcZRanger2, &bcZRanger2)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcLedRing, &bcLedRing)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcMultiranger, &bcMultiranger)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcColorLedBot, &bcColorLedBot)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcColorLedTop, &bcColorLedTop)
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, bcAI, &bcAI)
PARAM_GROUP_STOP(deck)
