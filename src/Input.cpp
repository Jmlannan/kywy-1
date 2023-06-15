// SPDX-FileCopyrightText: 2023 KOINSLOT, Inc.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "kywy/Input.hpp"
#include "kywy/Events.hpp"

#include "sdkconfig.h"

#ifndef CONFIG_IDF_TARGET_LINUX
#include "driver/gpio.h"
#include "soc/gpio_reg.h"
#endif

namespace Kywy {

void getInputsCallback(TimerHandle_t timer) {
  Input input = *static_cast<Input *>(pvTimerGetTimerID(timer));
  ::Actor::Message message(Events::GET_INPUTS);
  input.dispatch(&message);
}

int Input::getPollingPeriod() { return pdTICKS_TO_MS(pollingPeriod); }

void Input::setPollingPeriod(int milliseconds) {
  pollingPeriod = pdMS_TO_TICKS(milliseconds);

  if (timer) {
    xTimerChangePeriod(timer, pollingPeriod, 0);
  }
}

void Input::initialize() {
#ifndef CONFIG_IDF_TARGET_LINUX
  uint64_t pinMask = 0;

#if HAL_BUTTON_LEFT_PIN >= 0
  pinMask |= 1ull << HAL_BUTTON_LEFT_PIN;
#endif

#if HAL_BUTTON_RIGHT_PIN >= 0
  pinMask |= 1ull << HAL_BUTTON_RIGHT_PIN;
#endif

#if HAL_D_PAD_LEFT_PIN >= 0
  pinMask |= 1ull << HAL_D_PAD_LEFT_PIN;
#endif

#if HAL_D_PAD_RIGHT_PIN >= 0
  pinMask |= 1ull << HAL_D_PAD_RIGHT_PIN;
#endif

#if HAL_D_PAD_UP_PIN >= 0
  pinMask |= 1ull << HAL_D_PAD_UP_PIN;
#endif

#if HAL_D_PAD_DOWN_PIN >= 0
  pinMask |= 1ull << HAL_D_PAD_DOWN_PIN;
#endif

  gpio_config_t config;
  config.pin_bit_mask = pinMask;
  config.mode = GPIO_MODE_INPUT;
  config.pull_up_en = GPIO_PULLUP_ENABLE;
  config.pull_down_en = GPIO_PULLDOWN_DISABLE;
  config.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&config);
#endif

  timer = xTimerCreate(getName(),        // timer name
                       pollingPeriod,    // timer period in FreeRTOS ticks
                       pdTRUE,           // auto reload
                       (void *)this,     // use timer ID to store a reference to the Input object
                       getInputsCallback // timer callback
  );

  xTimerStart(timer, 0);
}

void Input::handle(::Actor::Message *message) {
  switch (message->signal) {
  case Events::SET_INPUT_POLLING_PERIOD: {
    setPollingPeriod(*(int *)message->data);
    break;
  }
#ifndef CONFIG_IDF_TARGET_LINUX
  case Events::GET_INPUTS: {
    uint32_t pinLevels = REG_READ(GPIO_IN_REG);

#if HAL_BUTTON_LEFT_PIN >= 0
    bool currentButtonLeftPressed = !((pinLevels & 1ull << HAL_BUTTON_LEFT_PIN) >> HAL_BUTTON_LEFT_PIN);
    if (currentButtonLeftPressed != buttonLeftPressed) {
      buttonLeftPressed = currentButtonLeftPressed;
      ::Actor::Message message(buttonLeftPressed ? Events::BUTTON_LEFT_PRESSED : Events::BUTTON_LEFT_RELEASED);
      publish(&message);
    }
#endif

#if HAL_BUTTON_RIGHT_PIN >= 0
    bool currentButtonRightPressed = !((pinLevels & 1ull << HAL_BUTTON_RIGHT_PIN) >> HAL_BUTTON_RIGHT_PIN);
    if (currentButtonRightPressed != buttonRightPressed) {
      buttonRightPressed = currentButtonRightPressed;
      ::Actor::Message message(buttonRightPressed ? Events::BUTTON_RIGHT_PRESSED : Events::BUTTON_RIGHT_RELEASED);
      publish(&message);
    }
#endif

#if HAL_D_PAD_LEFT_PIN >= 0
    bool currentDPadLeftPressed = !((pinLevels & 1ull << HAL_D_PAD_LEFT_PIN) >> HAL_D_PAD_LEFT_PIN);
    if (currentDPadLeftPressed != dPadLeftPressed) {
      dPadLeftPressed = currentDPadLeftPressed;
      ::Actor::Message message(dPadLeftPressed ? Events::D_PAD_LEFT_PRESSED : Events::D_PAD_LEFT_RELEASED);
      publish(&message);
    }
#endif

#if HAL_D_PAD_RIGHT_PIN >= 0
    bool currentDPadRightPressed = !((pinLevels & 1ull << HAL_D_PAD_RIGHT_PIN) >> HAL_D_PAD_RIGHT_PIN);
    if (currentDPadRightPressed != dPadRightPressed) {
      dPadRightPressed = currentDPadRightPressed;
      ::Actor::Message message(dPadRightPressed ? Events::D_PAD_RIGHT_PRESSED : Events::D_PAD_RIGHT_RELEASED);
      publish(&message);
    }
#endif

#if HAL_D_PAD_UP_PIN >= 0
    bool currentDPadUpPressed = !((pinLevels & 1ull << HAL_D_PAD_UP_PIN) >> HAL_D_PAD_UP_PIN);
    if (currentDPadUpPressed != dPadUpPressed) {
      dPadUpPressed = currentDPadUpPressed;
      ::Actor::Message message(dPadUpPressed ? Events::D_PAD_UP_PRESSED : Events::D_PAD_UP_RELEASED);
      publish(&message);
    }
#endif

#if HAL_D_PAD_DOWN_PIN >= 0
    bool currentDPadDownPressed = !((pinLevels & 1ull << HAL_D_PAD_DOWN_PIN) >> HAL_D_PAD_DOWN_PIN);
    if (currentDPadDownPressed != dPadDownPressed) {
      dPadDownPressed = currentDPadDownPressed;
      ::Actor::Message message(dPadDownPressed ? Events::D_PAD_DOWN_PRESSED : Events::D_PAD_DOWN_RELEASED);
      publish(&message);
    }
#endif

    break;
  }
#endif
  default: {
    break;
  }
  }
};

} // namespace Kywy
