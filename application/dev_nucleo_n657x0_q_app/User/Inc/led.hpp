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
	void test_toggle_low();
	void test_toggle_high();

      private:
	LED() = default;
	~LED() = default;
	GPIO &gpio_instance = GPIO::getInstance();

      private:
};

#endif /* __LED_HPP__ */
