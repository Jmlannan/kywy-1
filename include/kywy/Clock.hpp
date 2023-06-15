// SPDX-FileCopyrightText: 2023 KOINSLOT, Inc.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "Actor.hpp"

#include "freertos/timers.h"

namespace Kywy {

// Tick callback that publishes the tick event to subscribers
void clockTickCallback(TimerHandle_t timer);

class Clock : public Actor::Actor {
private:
  // The number of FreeRTOS ticks between a Clock tick
  int tickDuration = pdMS_TO_TICKS(50);

  // Software timer used to trigger ticks
  TimerHandle_t timer;

public:
  const char *getName() { return "clock"; };
  void initialize();
  void handle(::Actor::Message *message);

  // Returns the milliseconds between each Clock tick
  int getTickDuration();

  // Sets the milliseconds between each Clock tick
  void setTickDuration(int milliseconds);
};

} // namespace Kywy
