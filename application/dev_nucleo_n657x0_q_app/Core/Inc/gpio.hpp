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
#ifndef __GPIO_HPP__
#define __GPIO_HPP__
#include <zephyr/drivers/gpio.h>

class GPIO
{
      public:
	GPIO(const GPIO &) = delete;
	GPIO &operator=(const GPIO &) = delete;
	static GPIO &getInstance()
	{
		static GPIO instance;
		return instance;
	}

      public:
	bool init();
	const struct gpio_dt_spec &getGreenLED() const;
	const struct gpio_dt_spec &getBlueLED() const;
	const struct gpio_dt_spec &getRedLED() const;

      private:
	GPIO() = default;
	~GPIO() = default;

      private:
};

#endif /* __GPIO_HPP__ */
