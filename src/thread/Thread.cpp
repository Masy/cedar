//
// Created by masy on 26.01.20.
//

#include "cedar/Thread.hpp"
#include "cedar/LoggerFactory.hpp"

using namespace cedar;

const std::chrono::duration<long, std::micro> MAX_OVERHEAD = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(2000));
const std::chrono::duration<long, std::micro> MIN_OVERHEAD = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(-2000));

std::vector<Thread *> *Thread::THREADS = new std::vector<Thread *>();
std::mutex *Thread::THREAD_MUTEX = new std::mutex();

Thread::Thread(const std::string &threadName, const double ticksPerSecond, const QueueExecutionOrder taskQueueExecutionOrder,
			   const unsigned int taskThreshold)
{
	this->m_name = threadName;
	this->m_tps = ticksPerSecond;
	this->m_queueExecutionOrder = taskQueueExecutionOrder;
	this->m_taskThreshold = taskThreshold;
	this->m_sleepTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds((long) (1000000 / ticksPerSecond)));
	this->m_running = false;
	this->m_started = false;
	this->m_stopping = false;
	this->m_tickCount = 0;
	this->m_frameTime = 0.0;
	this->m_thread = nullptr;
	this->m_frontTaskQueue = new std::queue<std::function<void()>>;
	this->m_backTaskQueue = new std::queue<std::function<void()>>;
	this->m_waitingQueue = std::vector<Thread *>();
	this->m_logger = LoggerFactory::getLogger(threadName);

	// Add this Thread to the list of all XThreads.
	THREAD_MUTEX->lock();
	THREADS->push_back(this);
	THREAD_MUTEX->unlock();
}

Thread::~Thread()
{
	delete this->m_frontTaskQueue;
	delete this->m_backTaskQueue;
	delete this->m_logger;
	delete this->m_thread;
}

void Thread::run()
{
	this->m_running = true;

	std::chrono::duration<long, std::micro> overhead = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(0));
	std::chrono::duration<long, std::micro> duration = std::chrono::microseconds(0);
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTick = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTick = currentTick - this->m_sleepTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> sleepUntil;

	if (this->m_queueExecutionOrder == QUEUE_ONLY)
	{
		while (this->m_running)
		{
			this->m_taskQueueMutex.lock();
			bool hasTasks = this->m_backTaskQueue->empty();
			this->m_taskQueueMutex.unlock();

			// Check if the Thread has any tasks in the task queue. If not, sleep for the duration specified in <code>sleepTime</code>
			while (this->m_running && !hasTasks)
			{
				std::this_thread::sleep_for(this->m_sleepTime);

				this->m_taskQueueMutex.lock();
				hasTasks = this->m_backTaskQueue->empty();
				this->m_taskQueueMutex.unlock();
			}

			this->executeTasks();
		}
	}
	else
	{
		while (this->m_running)
		{
			currentTick = std::chrono::high_resolution_clock::now();

			duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTick - lastTick);
			this->m_frameTime = duration.count() / 1000000.0;

			// Calculate the overhead of the last ticks and add it to the current overhead
			// The overhead is subtracted from the allowed sleep time to make up for ticks that needed more time than allowed by the sleep time
			overhead += duration - this->m_sleepTime;

			// Clamp the overhead so ticks are "skipped" if one tick took extremely long
			if (overhead < MIN_OVERHEAD)
				overhead = MIN_OVERHEAD;
			else if (overhead > MAX_OVERHEAD)
				overhead = MAX_OVERHEAD;

			// Calculate the timestamp to which the thread should sleep after the task queue and tick was processed
			sleepUntil = currentTick + this->m_sleepTime - overhead;
			// Set the last tick to the current tick. This is done now as (hopefully) the currentTick variable is still in the cpu cache
			lastTick = currentTick;

			if (this->m_queueExecutionOrder == QUEUE_BEFORE_TICK)
				this->executeTasks();

			this->onTick(currentTick.time_since_epoch().count(), this->m_tickCount++);

			if (this->m_queueExecutionOrder == QUEUE_AFTER_TICK)
				this->executeTasks();

			std::this_thread::sleep_until(sleepUntil);
		}
	}

	this->m_started = false;
}

void Thread::executeTasks()
{
	this->m_taskQueueMutex.lock();
	// Check if the threshold was exceeded and print warning if so.
	if (this->m_backTaskQueue->size() > this->m_taskThreshold)
		this->m_logger->warn("Task queue has more tasks than threshold! %d/%d", this->m_backTaskQueue->size(), this->m_taskThreshold);

	// Swap front and back queue so new tasks can already be added while the queue is being processed.
	// That way other threads don't freeze when trying to add a task while the task queue is processed.
	std::queue<std::function<void()>> *tmp = this->m_frontTaskQueue;
	this->m_frontTaskQueue = this->m_backTaskQueue;
	this->m_backTaskQueue = tmp;

	this->m_taskQueueMutex.unlock();

	// Process task queue.
	while (!this->m_frontTaskQueue->empty())
	{
		this->m_frontTaskQueue->front()();
		this->m_frontTaskQueue->pop();
	}
}

std::thread *Thread::start(const unsigned int waitForSize, Thread **waitFor)
{
	// Only add threads that aren't already running to the waiting queue to avoid deadlocks.
	for (unsigned int n = 0; n < waitForSize; n++)
	{
		if (!waitFor[n]->m_running)
			this->m_waitingQueue.push_back(waitFor[n]);
	}

	this->m_started = true;
	this->m_thread = new std::thread(&Thread::preStart, this);
	return this->m_thread;
}

void Thread::stop()
{
	this->m_stopping = true;
	this->m_running = false;
}

void Thread::preStart()
{
	this->m_waitingQueueMutex.lock();
	bool isEmpty = this->m_waitingQueue.empty();
	this->m_waitingQueueMutex.unlock();
	while (!isEmpty)
	{
		std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(1)));

		this->m_waitingQueueMutex.lock();
		isEmpty = this->m_waitingQueue.empty();
		this->m_waitingQueueMutex.unlock();
	}

	this->onStart();

	// Remove this thread from the waiting queues of all other threads.
	THREAD_MUTEX->lock();
	for (Thread *thread: *THREADS)
	{
		thread->removeFromWaitingQueue(this);
	}
	THREAD_MUTEX->unlock();

	this->run();

	this->onStop();
}

void Thread::removeFromWaitingQueue(const Thread *thread)
{
	this->m_waitingQueueMutex.lock();
	auto iterator = this->m_waitingQueue.begin();
	while (iterator != this->m_waitingQueue.end())
	{
		if (*iterator == thread)
		{
			this->m_waitingQueue.erase(iterator);
			break;
		}
		iterator++;
	}
	this->m_waitingQueueMutex.unlock();
}

void Thread::addTask(const std::function<void()> &task)
{
	if (this->m_running)
	{
		if (this->m_queueExecutionOrder != QUEUE_DISABLED)
		{
			this->m_taskQueueMutex.lock();
			this->m_backTaskQueue->push(task);
			this->m_taskQueueMutex.unlock();
		}
		else
		{
			this->m_logger->warn("Received a task but the task queue is disabled!");
		}
	}
}

bool Thread::hasStarted() const
{
	return this->m_started;
}

bool Thread::isRunning() const
{
	return this->m_running;
}

bool Thread::isStopping() const
{
	return this->m_stopping;
}

const char *Thread::getName() const
{
	return this->m_name.c_str();
}

const Logger *Thread::getLogger() const
{
	return this->m_logger;
}

double Thread::getTPS() const
{
	return this->m_tps;
}

double Thread::getLastFrameTime() const
{
	return this->m_frameTime;
}