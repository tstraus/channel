#include "channel.h"
#include "lest.hpp"

using namespace std;
using namespace tstraus;

const lest::test t[] =
{
    CASE("Single Thread" "[tstraus::Channel]")
    {
        Channel<string> channel;

        channel << "asdf"; // send to channel

        string o;
        channel >> o; // receive from channel

        EXPECT(o == "asdf");
    },

    CASE("From Thread" "[tstraus::Channel]")
    {
        Channel<string> channel;

        thread t([&]()
        {
            channel << "asdf";
        });

        string o;
        channel >> o;

        t.join();

        EXPECT(o == "asdf");
    },

    CASE("To Thread" "[tstraus::Channel]")
    {
        Channel<string> channel;

        channel << "asdf";

        thread t([&]()
        {
            string o;
            channel >> o;

            EXPECT(o == "asdf");
        });

        t.join();
    },

    CASE("Ordering" "[tstraus::Channel]")
    {
        Channel<string> channel;

        thread t1([&]()
        {
            channel << "asdf";

            // Not normal to read and write from the same thread
            // so we'll sleep so we don't read our own message
            this_thread::sleep_for(chrono::milliseconds(1));

            string o;
            channel >> o;

            EXPECT(o == "fdsa");
        });

        thread t2([&]()
        {
            string o;
            channel >> o;

            channel << "fdsa";

            EXPECT(o == "asdf");
        });

        t1.join();
        t2.join();
    }
};

// run with '-p' to see each test
int main(int argc, char** argv)
{
    return lest::run(t, argc, argv);
}
