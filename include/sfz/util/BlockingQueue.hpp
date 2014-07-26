#pragma once
#ifndef SFZ_UTIL_BLOCKING_QUEUE_HPP
#define SFZ_UTIL_BLOCKING_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace sfz {

	/**
	 * @brief A thread-safe queue that blocks until an element is available.
	 *
	 * Inspired by a similar class in Anthony William's 'C++ Concurrency in Action'.
	 *
	 * @param T the type to be held by the queue
	 *
	 * @author Peter Hillerström <peter@hstroem.se>
	 * @date 2014-07-26
	 */
	template<typename T>
	class BlockingQueue {
	public:
		
		/**
		 * @brief Constructs an empty BlockingQueue.
		 */
		BlockingQueue();

		// No copy constructor.
		BlockingQueue(const BlockingQueue&) = delete;
		
		virtual ~BlockingQueue();
		
		/**
		 * @brief Pushes an element onto the back of the queue.
		 * This operation is thread-safe and will acquire mutual exclusion before pushing the element onto the queue.
		 * If there are any callers waiting to pop an element they will be notified.
		 * @param element the element to push
		 */
		void push(const T& element);

		/**
		 * @brief Pops an element from the front of the queue.
		 * This operation is thread-safe and will block until an element is available. If no element is pushed this
		 * operation will block forever.
		 * @return an element from the front of the queue
		 */
		T pop();

		/**
		 * @brief Attempts to pop an element from the front of the queue and returns immediately.
		 * This operation is thread-safe and will acquire mutual exclusion and then check if the queue is empty. If it
		 * is empty it will return nullptr (== empty unique_ptr), otherwise it will return the element in the front of
		 * the queue.
		 * @return unique_ptr to an element at the front of the queue
		 */
		std::unique_ptr<T> tryPop();

		/**
		 * @brief Checks if the queue is currently empty.
		 * This state might be changed by another thread at any time and cannot be guaranteed to be the same.
		 * @return whether the queue was empty or not
		 */
		bool empty() const;

		// No assignment.
		BlockingQueue& operator= (const BlockingQueue&) = delete;

	private:
		std::queue<T> queue;
		mutable std::mutex queueMutex;
		std::condition_variable queueCond;
	};
}
#include "BlockingQueue.inl"
#endif