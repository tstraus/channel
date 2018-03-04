#include "channel.h"
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
	tstraus::channel<string> c;

	thread t1([&]()
	{
		c << "asdf"; // send to channel

		// Not normal to read and write from the same thread
		// so we'll sleep so we don't read our own message
		this_thread::sleep_for(chrono::milliseconds(1));

		string o;
		c >> o; // receive from channel
		cout << o << endl;
	});

	thread t2([&]()
	{
		string o;
		c >> o;
		cout << o << endl;

		c << "fdsa";
	});

	t1.join();
	t2.join();

	return 0;
}
