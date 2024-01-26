#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

/*
 * Rules:
 *  - You cannot modify this class (except for debugging)
 *  - You cannot read the value of 'secret' (except for debugging)
 *  - You cannot read the memory content related to this class (except for debugging)
 */

class Verifier {
    size_t length;
    size_t slowness;
    std::string full_secret = "td3jfzEsJJfXUkzcQZAdUgSHSfDtmL2Q";
    std::string secret;

    void slow() {
        volatile unsigned int x = 0;
        for (size_t i=0; i<slowness; i++) {
            x = x + 1zu;
        }
    }

    bool slow_compare(const char* s, const char* t) {
        while (*s++ == *t++) {
            slow();
            if (*s == '\0') {
                return true;
            }
        }
        return false;
    }

public:
    Verifier(size_t _length, size_t _slowness) :
        length{_length}, slowness{_slowness} {
        secret = full_secret.substr(0, length);
    }

    [[gnu::noinline]]
    bool verify(std::string guess) {
        return slow_compare(secret.c_str(), guess.c_str());
    }
};


int main(void) {
    std::string guess = "test";

    size_t length = 16zu;

    Verifier verifier(length, 10'000zu);

    std::cout << verifier.verify(guess) << std::endl;

    /*
     * Steps:
     *   - Iterate through all possible first character values, calling the
              'verify' oracle for each of them
     *   - Store the character value that caused the longest computation time
     *   - Repeat for the next byte...
     *   - Guess the full secret!
     */


    return 0;
}
