// SPDX-FileCopyrightText: 2023 KOINSLOT, Inc.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

// Display definitions
#if !defined(HAL_DISPLAY_PROTOCOL_I2C) && !defined(HAL_DISPLAY_PROTOCOL_SPI)
#define HAL_DISPLAY_PROTOCOL_SPI
#endif

#ifndef HAL_DISPLAY_PROTOCOL_I2C
#define HAL_DISPLAY_PIN_I2C_SDA -1
#define HAL_DISPLAY_PIN_I2C_SCL -1
#define HAL_DISPLAY_I2C_ADDRESS 0x0
#endif

#ifndef HAL_DISPLAY_PROTOCOL_SPI
#define HAL_DIPSLAY_PIN_SPI_CS -1
#define HAL_DIPSLAY_PIN_SPI_RST -1
#define HAL_DIPSLAY_PIN_SPI_DC -1
#define HAL_DIPSLAY_PIN_SPI_SCLK -1
#define HAL_DIPSLAY_PIN_SPI_MOSI -1
#else
#define HAL_DISPLAY_PIN_SPI_CS 17 // Display Chip select
#define HAL_DISPLAY_PIN_SPI_RST 22 // Pull high to activate display, defaults to off.
// #define HAL_DISPLAY_PIN_SPI_DC // This is no longer needed by the sharp memory display
#define HAL_DISPLAY_PIN_SPI_SCLK 18 // Clock signal
#define HAL_DISPLAY_PIN_SPI_MOSI 20 // Master out slave in
#endif


// Button definitions

#ifndef HAL_BUTTON_LEFT_PIN
#define HAL_BUTTON_LEFT_PIN 12
#endif

#ifndef HAL_BUTTON_RIGHT_PIN
#define HAL_BUTTON_RIGHT_PIN 2
#endif

#ifndef HAL_D_PAD_LEFT_PIN
#define HAL_D_PAD_LEFT_PIN 6
#endif

#ifndef HAL_D_PAD_RIGHT_PIN
#define HAL_D_PAD_RIGHT_PIN 7
#endif

#ifndef HAL_D_PAD_UP_PIN
#define HAL_D_PAD_UP_PIN 9
#endif

#ifndef HAL_D_PAD_DOWN_PIN
#define HAL_D_PAD_DOWN_PIN 3
#endif

//Battery definitions

#ifndef HAL_BATTERY_VOLTAGE_PIN 
#define HAL_BATTERY_VOLTAGE_PIN 26
#endif
// Voltage divider to battery, reports battery voltage to ADC pin 26, voltage is divided in half

#ifndef HAL_BATTERY_CHARGE_PIN
#define HAL_BATTERY_CHARGE_PIN 10
#endif
// Pin is pulled low when battery is charging

#ifndef HAL_BATTERY_STANDBY_PIN
#define HAL_BATTERY_STANDBY_PIN 11
#endif
// Pin is pulled low when battery is fully charged and plugged in

// Expansion pin definitions for back pin headers and stemma qt

#define HAL_EXP_SPI_CS1           15  // Expansion SPI Chip Select 1 (GPIO15), goes to pin headder on back
#define HAL_EXP_SPI_CS2           14  // Expansion SPI Chip Select 2 (GPIO14), goes to pin headder on back
#define HAL_SPI_MOSI              20  // SPI Master out, slave in
#define HAL_SPI_MISO              19  // SPI Master in, slave out
#define HAL_SPI_CLK               18  // SPI Clock

#define HAL_I2C_SDA               4   // Expansion I2C SDA (GPIO4)
#define HAL_I2C_SCL               5   // Expansion I2C SCL (GPIO5)
