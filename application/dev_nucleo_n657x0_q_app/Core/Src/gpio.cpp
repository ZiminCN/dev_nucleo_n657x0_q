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

#include "gpio.hpp"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(gpio, LOG_LEVEL_INF);
static const struct gpio_dt_spec green_led_spec = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec blue_led_spec = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
static const struct gpio_dt_spec red_led_spec = GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);

bool GPIO::init()
{
	if (!gpio_is_ready_dt(&green_led_spec)) {
		LOG_ERR("green_led GPIO device is not ready");
		return false;
	}

	if (!gpio_is_ready_dt(&blue_led_spec)) {
		LOG_ERR("blue_led GPIO device is not ready");
		return false;
	}

	if (!gpio_is_ready_dt(&red_led_spec)) {
		LOG_ERR("red_led GPIO device is not ready");
		return false;
	}

	LOG_INF("ALL GPIO device is ready");
	return true;
}

const struct gpio_dt_spec &GPIO::getGreenLED() const
{
	return green_led_spec;
}

const struct gpio_dt_spec &GPIO::getBlueLED() const
{
	return blue_led_spec;
}

const struct gpio_dt_spec &GPIO::getRedLED() const
{
	return red_led_spec;
}
