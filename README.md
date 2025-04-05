# Reaction Time Game on STM32F1

## Overview

This repository contains firmware for a reaction time measurement game based on the STM32F1 microcontroller. The project is designed to test and improve human reflexes by measuring the delay between a visual cue (LED) and a button press. The code is written in C++, uses FreeRTOS for precise timing and task scheduling, and avoids using the STM32 HAL, relying instead on lightweight custom drivers.
## Key Features

  LED-based visual stimulus: The game starts with a visual cue (LED on), signaling the user to respond.

  Button press reaction measurement: Measures time between LED activation and user's button press with millisecond accuracy.

  FreeRTOS integration: Uses FreeRTOS tasks and timing for clean code structure and accurate timing.

  TFT LCD display support: Displays the results on a TFT LCD screen (e.g., 320x240).

  Custom peripheral drivers: All drivers are implemented without using STM32 HAL, for improved performance and understanding.

## Dependencies

    Standard C++ Libraries: For core functionalities.

    Custom Peripheral Drivers (no HAL): Based on lightweight drivers from @ucgosupl & @FreddieChopin & me.

    FreeRTOS: Used for multitasking and precise timing.

## Hardware

    MCU: STM32F103C8T6 ("hy-ministm32v")

    LCD: HAOYU 320x240 LCD TFT.

    Power Supply: USB or external regulated 3.3V / 5V source.

## How It Works

    User starts the game by pressing touch screen

    After a random delay,

    The user must press the button as fast as possible.

    The time between green screen on and button press is measured and shown

Contribution

Contributions are welcome! Please follow the standard GitHub pull request process for bug reports, improvements, or feature additions.
License

This project is released under the MIT License.
Author

Developed by cf-embedded.pl
