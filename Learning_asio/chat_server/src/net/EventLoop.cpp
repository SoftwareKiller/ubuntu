#include "EventLoop.h"

using namespace net;

EventLoop::EventLoop()
	:looping_(false)
	, quit_(false)
{
}

EventLoop::~EventLoop()
{
}

void EventLoop::loop() {
	while (!quit_)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
}

void EventLoop::quit() {
	quit_ = true;
}
