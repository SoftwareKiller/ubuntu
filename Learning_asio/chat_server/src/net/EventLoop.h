#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>


#include "../base/Timestamp.h"

namespace net {
	class EventLoop {
	public:
		typedef std::function<void()> Functor;

		EventLoop();
		~EventLoop();

		void loop();

		void quit();

	private:

		bool                       looping_;
		bool                       quit_;
	};
}
