#include "channel.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tstraus;

TEST(ChannelTests, Ordering)
{
    channel<string> c;

    thread t1([&]()
    {
        c << "asdf"; // send to channel

        // Not normal to read and write from the same thread
        // so we'll sleep so we don't read our own message
        this_thread::sleep_for(chrono::milliseconds(1));

        string o;
        c >> o; // receive from channel

        EXPECT_EQ("fdsa", o);
    });

    thread t2([&]()
    {
        string o;
        c >> o;

        c << "fdsa";

        EXPECT_EQ("asdf", o);
    });

    t1.join();
    t2.join();
}