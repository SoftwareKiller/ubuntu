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
	}
}

void EventLoop::quit() {
	quit_ = true;
}
