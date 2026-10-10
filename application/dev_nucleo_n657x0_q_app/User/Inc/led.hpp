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

#pragma once
#ifndef __LED_HPP__
#define __LED_HPP__

#include "gpio.hpp"
#include "timer.hpp"

class LED
{
      public:
	LED(const LED &) = delete;
	LED &operator=(const LED &) = delete;
	static LED &getInstance()
	{
		static LED instance;
		return instance;
	}

      public:
	bool init();
	void enable_heartbeat();

      private:
	LED() = default;
	~LED() = default;
	void heartbeat_on();
	void heartbeat_off();
	static void heartbeat_pengpong(struct k_timer *timer_id);

      private:
	GPIO &gpio_instance = GPIO::getInstance();
	TIMER &timer_instance = TIMER::getInstance();

      private:
	struct heartbeat_status_t {
#define HEARTBEAT_INTERVAL_100ms 10
		int count_100ms;
	};
	struct heartbeat_status_t heartbeat_status = {0};
};

#endif /* __LED_HPP__ */
