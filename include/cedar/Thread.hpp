//
// Created by Marcel Schauer on 26.01.20.
//

#ifndef CEDAR_XTHREAD_H
#define CEDAR_XTHREAD_H

#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <atomic>
#include "Logger.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Enum defining the execution order of the task queue of a thread.
	 */
	enum QueueExecutionOrder
	{
		/**
		 * The thread will not accept tasks from other threads.
		 */
		QUEUE_DISABLED,
		/**
		 * The task queue is processed before the onTick() method will be called.
		 */
		QUEUE_BEFORE_TICK,
		/**
		 * The task queue is processed after the onTick() method was called.
		 */
		QUEUE_AFTER_TICK,
		/**
		 * The thread will only process the task queue and sleep until new tasks are added
		 */
		QUEUE_ONLY
	};

	/**
	 * Class representing a thread.
	 *
	 * This class adds the functionality of letting threads execute certain tasks in a fixed interval and allows for other
	 * threads to add tasks that will be executed by this thread.
	 */
	class Thread
	{
	private:
		/**
		 * A List of all Threads.
		 */
		static std::vector<Thread *> *THREADS;
		/**
		 * Mutex for {@link #THREADS}.
		 */
		static std::mutex *THREAD_MUTEX;
	protected:
		/**
		 * The name of the Thread.
		 */
		std::string m_name;
		/**
		 * The ticks per second this Thread tries to achieve.
		 */
		double m_tps;
		/**
		 * The task queue execution order if this Thread.
		 */
		QueueExecutionOrder m_queueExecutionOrder;
		/**
		 * The task threshold of the Thread.
		 *
		 * <p>If when processing the task queue the size of the queue exceeds the threshold a warning will be logged.</p>
		 */
		unsigned int m_taskThreshold;
		/**
		 * The sleep duration of the Thread in microseconds.
		 */
		std::chrono::duration<long, std::micro> m_sleepTime;
		/**
		 * A list of XThreads this thread is waiting for before starting.
		 */
		std::vector<Thread *> m_waitingQueue;
		/**
		 * Mutex for {@link #m_waitingQueue}.
		 */
		std::mutex m_waitingQueueMutex;
		/**
		 * This task queue is the one being processed by the Thread.
		 */
		std::queue<std::function<void()>> *m_frontTaskQueue;
		/**
		 * This task queue is the one where tasks are added.
		 */
		std::queue<std::function<void()>> *m_backTaskQueue;
		/**
		 * Mutex for the {@link #m_backTaskQueue back task queue}.
		 */
		std::mutex m_taskQueueMutex;
		/**
		 * The number of ticks the Thread already executed.
		 */
		unsigned long m_tickCount;
		/**
		 * The number of seconds the last tick took to execute.
		 */
		double m_frameTime;
		/**
		 * The <code>std::thread</code> this Thread is running in.
		 */
		std::thread *m_thread;
		/**
		 * A pointer to the logger of the thread.
		 */
		Logger *m_logger;
		/**
		 * Whether the Thread was started or not.
		 *
		 * <p>Note: This does not necessarily mean the Thread is running. It might be waiting for other XThreads to start first.</p>
		 */
		std::atomic_bool m_started{};
		/**
		 * Whether the Thread is running or not.
		 */
		std::atomic_bool m_running{};
		/**
		 * Whether the Thread is currently trying to stop or not.
		 *
		 * <p>Note: This does not mean the thread has stopped already, it is just trying to.</p>
		 */
		std::atomic_bool m_stopping{};

		/**
		 * Method which is called by the {@link start()} method, but from the newly created thread.
		 *
		 * <p>This method checks if the {@link #m_waitingQueue} is empty and sleeps if it isn't.</p>
		 */
		void preStart();

		/**
		 * Method which is called when the thread is about to start.
		 */
		virtual void onStart() = 0;

		/**
		 * Runs the main loop of the thread.
		 */
		void run();

		/**
		 * Method which is called every tick of the thread.
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick.
		 */
		virtual void onTick(unsigned long currentTime, unsigned long tickCount) = 0;

		/**
		 * Copies swaps the {@link #m_frontTaskQueue} and the {@link m_backTaskQueue} and then processes all added tasks.
		 */
		void executeTasks();

		/**
		 * Method which is called when the thread is about to stop.
		 */
		virtual void onStop() = 0;

	public:
		/**
		 * Creates a new Thread.
		 *
		 * @param threadName              The name of the Thread.
		 * @param ticksPerSecond          The number of ticks the Thread should execute per second.
		 *                                <p>If this is 0 the Thread will not sleep and tick as fast as possible.</p>
		 * @param taskQueueExecutionOrder The queue execution order of the Thread.
		 * @param taskThreshold           The task threshold of the Thread.
		 *                                <p>If when processing the task queue the size of the queue exceeds the threshold a warning will be logged.</p>
		 */
		Thread(const std::string &threadName, double ticksPerSecond, QueueExecutionOrder taskQueueExecutionOrder,
			   unsigned int taskThreshold);

		/**
		 * Destroys the Thread.
		 */
		virtual ~Thread();

		/**
		 * Removes the given Thread from the waiting queue of this Thread.
		 *
		 * @param thread The Thread that will be removed from {@link #m_waitingQueue waiting queue}.
		 */
		void removeFromWaitingQueue(const Thread *thread);

		/**
		 * Starts the Thread.
		 *
		 * @param waitForSize The number of XThreads in the <code>waitFor</code> array.
		 * @param waitFor     A list of XThreads that have to start before this Thread will start.
		 *                    <p>If this is a <code>nullptr</code> or the listed threads have already been started this Thread will start immediately.</p>
		 * @return the <code>std::thread</code> this Thread runs in.
		 */
		std::thread *start(unsigned int waitForSize = 0, Thread **waitFor = nullptr);

		/**
		 * Stops the Thread.
		 *
		 * <p>This will take effect when the next tick is about to be executed.</p>
		 */
		void stop();

		/**
		 * Adds the given task to the task queue of the Thread.
		 *
		 * @param task The task that will be added.
		 */
		void addTask(const std::function<void()> &task);

		/**
		 * Checks whether the Thread has started or not.
		 *
		 * @return <code>true</code> if the Thread started already.
		 */
		[[nodiscard]] bool hasStarted() const;

		/**
		 * Checks whether the Thread is running or not.
		 *
		 * @return <code>true</code> if the Thread is running.
		 */
		[[nodiscard]] bool isRunning() const;

		/**
		 * Checks whether the Thread is stopping or not.
		 *
		 * @return <code>true</code> if the Thread is stopping.
		 */
		[[nodiscard]] bool isStopping() const;

		/**
		 * Gets the name of the Thread.
		 *
		 * @return the name of the Thread.
		 */
		[[nodiscard]] const char *getName() const;

		/**
		 * Gets the logger of the Thread.
		 *
		 * @return the {@link Logger} of the Thread.
		 */
		[[nodiscard]] const Logger *getLogger() const;

		/**
		 * Gets the ticks per second this Thread tries to achieve.
		 *
		 * @return The ticks per second this Thread tries to achieve.
		 */
		[[nodiscard]] double getTPS() const;

		/**
		 * Gets the frame time of the last tick of the Thread.
		 *
		 * @return the frame time of the last tick of the Thread.
		 */
		[[nodiscard]] double getLastFrameTime() const;
	};

}

#endif //CEDAR_XTHREAD_H
