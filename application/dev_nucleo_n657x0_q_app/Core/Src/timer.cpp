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

#include "timer.hpp"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(timer, LOG_LEVEL_INF);

bool TIMER::init()
{
	// register all timer slots
	for (uint8_t i = 0; i < MAX_TIMER_SLOTS; i++) {
		k_timer_init(&this->timer_slots[i], TIMER::dispatch_expiry_callback,
			     TIMER::dispatch_stop_callback);
	}
	return true;
}

bool TIMER::timer_register(timer_callback_t expiry_callback, timer_callback_t stop_callback)
{
	// find a null slot in the timer_slots array and register the callback
	// allow stop callback to be null, but expiry callback must not be null
	for (int i = 0; i < MAX_TIMER_SLOTS; i++) {
		if (this->timer_expiry_callbacks[i] == nullptr) {
			this->timer_expiry_callbacks[i] = expiry_callback;
			this->timer_stop_callbacks[i] = stop_callback;
			return true;
		}
	}

	return false;
}

bool TIMER::timer_unregister(timer_callback_t expiry_callback, timer_callback_t stop_callback)
{
	(void)expiry_callback;
	(void)stop_callback;

	for (int i = 0; i < MAX_TIMER_SLOTS; i++) {
		// allow stop callback to be null, but expiry callback must not be null
		if (this->timer_expiry_callbacks[i] == expiry_callback) {
			this->timer_expiry_callbacks[i] = nullptr;
			this->timer_stop_callbacks[i] = nullptr;
			return true;
		}
	}

	return false;
}

bool TIMER::timer_start(timer_callback_t expiry_callback, k_timeout_t duration, k_timeout_t period)
{
	int index = this->index_of(expiry_callback);

	if (index < 0) {
		LOG_ERR("Invalid timer_id");
		return false;
	}

	k_timer_start(&this->timer_slots[index], duration, period);

	return true;
}

bool TIMER::timer_stop(timer_callback_t expiry_callback)
{
	int index = this->index_of(expiry_callback);
	if (index < 0) {
		LOG_ERR("Invalid timer_id");
		return false;
	}

	k_timer_stop(&this->timer_slots[index]);

	return true;
}

void TIMER::dispatch_expiry_callback(struct k_timer *timer_id)
{
	TIMER &timer_instance = TIMER::getInstance();
	int index = (int)(timer_id - timer_instance.timer_slots);
	if (index >= 0 && index < MAX_TIMER_SLOTS && timer_instance.timer_expiry_callbacks[index]) {
		timer_instance.timer_expiry_callbacks[index](timer_id);
	}
}

void TIMER::dispatch_stop_callback(struct k_timer *timer_id)
{
	TIMER &timer_instance = TIMER::getInstance();
	int index = (int)(timer_id - timer_instance.timer_slots);
	if (index >= 0 && index < MAX_TIMER_SLOTS && timer_instance.timer_stop_callbacks[index]) {
		timer_instance.timer_stop_callbacks[index](timer_id);
	}
}

int TIMER::index_of(timer_callback_t cb) const
{
	for (int i = 0; i < MAX_TIMER_SLOTS; i++) {
		if (this->timer_expiry_callbacks[i] == cb) {
			return i;
		}
	}
	return -1;
}
