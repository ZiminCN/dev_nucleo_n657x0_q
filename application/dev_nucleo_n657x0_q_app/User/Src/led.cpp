// Copyright (c) 2025 Zimin
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "led.hpp"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(led, LOG_LEVEL_INF);

bool LED::init()
{
	return true;
}

void LED::test_toggle_low()
{
	gpio_pin_configure_dt(&this->gpio_instance.getGreenLED(), GPIO_OUTPUT_LOW);
	gpio_pin_configure_dt(&this->gpio_instance.getRedLED(), GPIO_OUTPUT_LOW);
	gpio_pin_configure_dt(&this->gpio_instance.getBlueLED(), GPIO_OUTPUT_LOW);
}

void LED::test_toggle_high()
{
	gpio_pin_configure_dt(&this->gpio_instance.getGreenLED(), GPIO_OUTPUT_HIGH);
	gpio_pin_configure_dt(&this->gpio_instance.getRedLED(), GPIO_OUTPUT_HIGH);
	gpio_pin_configure_dt(&this->gpio_instance.getBlueLED(), GPIO_OUTPUT_HIGH);
}
