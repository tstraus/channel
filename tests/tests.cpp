#include "channel.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tstraus;

TEST(ChannelTests, SingleThread)
{
    channel<string> c;

    c << "asdf"; // send to channel

    string o;
    c >> o; // receive from channel

    EXPECT_EQ("asdf", o);
}

TEST(ChannelTests, FromThread)
{
    channel<string> c;

    thread t([&]()
    {
        c << "asdf";
    });

    string o;
    c >> o;

    t.join();

    EXPECT_EQ("asdf", o);
}

TEST(ChannelTests, ToThread)
{
    channel<string> c;

    c << "asdf";

    thread t([&]()
    {
        string o;
        c >> o;

        EXPECT_EQ("asdf", o);
    });

    t.join();
}

TEST(ChannelTests, Ordering)
{
    channel<string> c;

    thread t1([&]()
    {
        c << "asdf";

        // Not normal to read and write from the same thread
        // so we'll sleep so we don't read our own message
        this_thread::sleep_for(chrono::milliseconds(1));

        string o;
        c >> o;

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