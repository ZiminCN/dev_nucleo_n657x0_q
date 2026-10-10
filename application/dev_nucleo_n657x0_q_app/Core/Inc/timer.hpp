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
#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <zephyr/kernel.h>

static constexpr int MAX_TIMER_SLOTS = CONFIG_TIMER_SLOTS_COUNT;

class TIMER
{
      public:
	typedef void (*timer_callback_t)(struct k_timer *timer_id);

      public:
	TIMER(const TIMER &) = delete;
	TIMER &operator=(const TIMER &) = delete;
	static TIMER &getInstance()
	{
		static TIMER instance;
		return instance;
	}

      public:
	bool init();
	bool timer_register(timer_callback_t expiry_callback, timer_callback_t stop_callback);
	bool timer_unregister(timer_callback_t expiry_callback, timer_callback_t stop_callback);
	bool timer_start(timer_callback_t expiry_callback, k_timeout_t duration,
			 k_timeout_t period);
	bool timer_stop(timer_callback_t expiry_callback);

      public:
      private:
	TIMER() = default;
	~TIMER() = default;
	static void dispatch_expiry_callback(struct k_timer *timer_id);
	static void dispatch_stop_callback(struct k_timer *timer_id);
	int index_of(timer_callback_t cb) const;

      private:
	struct k_timer timer_slots[MAX_TIMER_SLOTS] = {}; // timer slots array
	timer_callback_t timer_expiry_callbacks[MAX_TIMER_SLOTS] =
		{};						     // timer expiry callbacks array
	timer_callback_t timer_stop_callbacks[MAX_TIMER_SLOTS] = {}; // timer stop callbacks array

      private:
};

#endif /* __TIMER_HPP__ */