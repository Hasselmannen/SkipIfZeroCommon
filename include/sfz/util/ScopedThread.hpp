#pragma once
#ifndef SFZ_UTIL_SCOPED_THREAD_HPP
#define SFZ_UTIL_SCOPED_THREAD_HPP

#include <thread>
#include <stdexcept>

namespace sfz {

	/**
	 * @brief A simple wrapper class for std::thread that joins the thread in the destructor.
	 * 
	 * @author Peter Hillerström <peter@hstroem.se>
	 * @date 2014-06-28
	 */
	class ScopedThread {
	public:

		/**
		 * @brief Constructs a ScopedThread given an std::thread that is joinable.
		 * The specified std::thread is moved into this ScopedThread which then assumes ownership of the thread.
		 * @throws std::invalid_argument if specified thread is not joinable
		 * @param t the std::thread to transfer to this ScopedThread
		 */
		explicit ScopedThread(std::thread t);

		// No default constructor.
		ScopedThread() = delete;

		// No copy constructor.
		ScopedThread(const ScopedThread&) = delete;
		
		virtual ~ScopedThread();

		/**
		 * @brief Returns the id of this thread.
		 * Returns the id given by the internal std::thread.
		 * @return id of this thread
		 */
		std::thread::id getID() const;

		// No assignment.
		ScopedThread& operator= (const ScopedThread&) = delete;
		
	private:
		std::thread thread;
	};
}
#endif