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

#include "app_version.h"

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>

#include "main.hpp"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
	LOG_INF("Application version: %s", APP_VERSION_STRING);
	// Core Class
	static GPIO &gpio_instance = GPIO::getInstance();

	// User Class
	static LED &led_instance = LED::getInstance();

	gpio_instance.init();

	while (1) {
		led_instance.test_toggle_low();
		k_sleep(K_MSEC(500));
		led_instance.test_toggle_high();
		k_sleep(K_MSEC(500));
	}
}