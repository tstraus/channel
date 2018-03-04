#include <queue>
#include <thread>
#include <condition_variable>

namespace tstraus
{
	template <typename T>
	class channel
	{
	public:
		channel() : m_closed(false),
			waitLambda([&]() { return m_closed || !q.empty(); }) {}

		void close()
		{
			std::unique_lock<std::mutex> lock(m);

			m_closed = true;
			cv.notify_all();
		}

		bool closed()
		{
			std::unique_lock<std::mutex> lock(m);

			return m_closed;
		}

		void put(const T& input)
		{
			std::unique_lock<std::mutex> lock(m);

			if (m_closed)
				throw std::logic_error("can't put in a closed channel");

			q.push(input);
			cv.notify_one();
		}

		bool get(T& output, bool wait = false)
		{
			std::unique_lock<std::mutex> lock(m);

			if (wait)
				cv.wait(lock, waitLambda);

			if (q.empty())
				return false;

			output = q.front();
			q.pop();

			return true;
		}

		void operator<<(const T& input)
		{
			put(input);
		}

		T& operator>>(T& output)
		{
			get(output, true);

			return output;
		}

	private:
		std::queue<T> q;
		std::mutex m;
		std::condition_variable cv;
		std::function<bool()> waitLambda;
		bool m_closed;
	};
}