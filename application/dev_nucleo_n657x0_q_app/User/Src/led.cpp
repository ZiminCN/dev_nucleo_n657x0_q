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

void LED::heartbeat_on()
{
	gpio_pin_configure_dt(&this->gpio_instance.getGreenLED(), GPIO_OUTPUT_ACTIVE);
}

void LED::heartbeat_off()
{
	gpio_pin_configure_dt(&this->gpio_instance.getGreenLED(), GPIO_OUTPUT_INACTIVE);
}

void LED::heartbeat_pengpong(struct k_timer *timer_id)
{
	(void)timer_id;
	LED &led_instance = LED::getInstance();

	led_instance.heartbeat_status.count_100ms += 1;
	if (led_instance.heartbeat_status.count_100ms >= 10) {
		led_instance.heartbeat_status.count_100ms = 0;
	}

	if ((led_instance.heartbeat_status.count_100ms == 1) ||
	    (led_instance.heartbeat_status.count_100ms == 3)) {
		led_instance.heartbeat_on();
	} else {
		led_instance.heartbeat_off();
	}
}

void LED::enable_heartbeat()
{
	this->timer_instance.timer_register(this->heartbeat_pengpong, nullptr);
	this->timer_instance.timer_start(this->heartbeat_pengpong, K_MSEC(10), K_MSEC(100));
}
