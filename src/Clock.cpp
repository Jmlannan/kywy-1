// SPDX-FileCopyrightText: 2023 KOINSLOT, Inc.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "kywy/Clock.hpp"
#include "kywy/Events.hpp"

#include "freertos/projdefs.h"

namespace Kywy {

int Clock::getTickDuration() { return pdTICKS_TO_MS(tickDuration); }

void Clock::setTickDuration(int milliseconds) {
  tickDuration = pdMS_TO_TICKS(milliseconds);

  if (timer) {
    xTimerChangePeriod(timer, tickDuration, 0);
  }
}

void clockTickCallback(TimerHandle_t timer) {
  Clock clock = *static_cast<Clock *>(pvTimerGetTimerID(timer));
  ::Actor::Message message(Events::TICK);
  clock.publish(&message);
};

void Clock::initialize() {
  timer = xTimerCreate(getName(),        // timer name
                       tickDuration,     // timer period in FreeRTOS ticks
                       pdTRUE,           // auto reload
                       (void *)this,     // use timer ID to store a reference to the Clock object
                       clockTickCallback // timer callback
  );

  xTimerStart(timer, 0);
}

void Clock::handle(::Actor::Message *message) {
  switch (message->signal) {
  case Events::SET_TICK_DURATION: {
    setTickDuration(*(int *)message->data);
    break;
  }
  default: {
    break;
  }
  }
};

} // namespace Kywy
