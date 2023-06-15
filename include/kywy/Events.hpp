// SPDX-FileCopyrightText: 2023 KOINSLOT, Inc.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "kywy/HAL.hpp"

namespace Kywy::Events {

typedef enum : int {
  // Clock Events
  TICK,
  SET_TICK_DURATION,

  // Input Events
  GET_INPUTS,
  SET_INPUT_POLLING_PERIOD,

#if HAL_BUTTON_LEFT_PIN >= 0
  BUTTON_LEFT_PRESSED,
  BUTTON_LEFT_RELEASED,
#endif

#if HAL_BUTTON_RIGHT_PIN >= 0
  BUTTON_RIGHT_PRESSED,
  BUTTON_RIGHT_RELEASED,
#endif

#if HAL_D_PAD_LEFT_PIN >= 0
  D_PAD_LEFT_PRESSED,
  D_PAD_LEFT_RELEASED,
#endif

#if HAL_D_PAD_RIGHT_PIN >= 0
  D_PAD_RIGHT_PRESSED,
  D_PAD_RIGHT_RELEASED,
#endif

#if HAL_D_PAD_UP_PIN >= 0
  D_PAD_UP_PRESSED,
  D_PAD_UP_RELEASED,
#endif

#if HAL_D_PAD_DOWN_PIN >= 0
  D_PAD_DOWN_PRESSED,
  D_PAD_DOWN_RELEASED,
#endif

  // User Event Boundary
  USER_EVENTS,

} KywyEvents;

} // namespace Kywy::Events
