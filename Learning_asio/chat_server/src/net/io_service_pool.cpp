#include "io_service_pool.h"
#include "../base/AsyncLogging.h"

IOContextPool::IOContextPool(uint16_t pool_size = std::thread::hardware_concurrency())
	:pool_size_(pool_size)
	, next_io_context_(0) {
	if (pool_size == 0) {
		LOG_ERROR("io_service_pool size is 0");
	}

	for (uint16_t i = 0; i < pool_size; ++i) {
		auto io_service = std::make_shared<asio::io_context>();
		auto work = std::make_shared<asio::io_context::work>(*io_service);
		io_contexts_.emplace_back(io_service);
		works_.emplace_back(work);
	}
}

void IOContextPool::Run() {
	for (uint16_t i = 0; i < pool_size_; ++i) {
		auto ioc = io_contexts_[i];
		auto thr = std::make_shared<std::thread>([this, ioc]() { ioc->run(); });
		threads_.emplace_back(thr);
	}
}

void IOContextPool::Join() {
	for (uint16_t i = 0; i < pool_size_; ++i) {
		threads_[i]->join();
	}
}

void IOContextPool::Stop() {
	for (uint16_t i = 0; i < pool_size_; ++i) {
		io_contexts_[i]->stop();
	}
}

asio::io_context& IOContextPool::get_io_context() {
	std::lock_guard<std::mutex> lock(this->mutex_);

	asio::io_context& io_context = *io_contexts_[next_io_context_];

	++next_io_context_;
	if (next_io_context_ == pool_size_) {
		next_io_context_ = 0;
	}

	return io_context;
}
