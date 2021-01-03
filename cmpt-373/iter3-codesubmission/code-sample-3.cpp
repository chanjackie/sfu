// ------------------------------------------------------------
//  timercpp.h (Branch: organizing_structs_of_rules)
// ------------------------------------------------------------

#include <iostream>
#include <thread>
#include <chrono>

// Timer third party library: https://github.com/99x/timercpp

class Timer {
    bool clear = false;

    public:
        void setTimeout(auto function, int delay);
        void setInterval(auto function, int interval);
        void stop();

};

void Timer::setTimeout(auto function, int delay) {
    this->clear = false;
    std::thread t([=]() {
        if(this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(this->clear) return;
        function();
    });
    t.detach();
}

void Timer::setInterval(auto function, int interval) {
    this->clear = false;
    std::thread t([=]() {
        while(true) {
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(this->clear) return;
            function();
        }
    });
    t.detach();
}

void Timer::stop() {
    this->clear = true;
}

// ------------------------------------------------------------
// HumanInput.h (Branch: organizing_structs_of_rules)
// ------------------------------------------------------------

#ifndef HUMANINPUT_H
#define HUMANINPUT_H

#include <vector>
#include <string_view>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "timercpp.h"

/***
 *** Need suggestion on how to approach the problem of taking in human input.
 *** This is only a placeholder as it is modeled after the Rock, Paper, Scissor.
 *** We need suggestion on how we could propmt and take input of a specific player,
 *** This currently does not work as it only prompt once on the server.
 ***/

namespace human_input{
    template<class P>
    void input_choice(const P& player, std::string_view prompt, std::unordered_map<std::string, std::string>& choices, std::string& respond, long timeout = -1){
        if (timeout > 0) {
            Timer t = Timer();
            t.setTimeout([&]() {
                auto s = std::format(prompt, player.getName());

                std::cout << s << std::endl;

                for (auto i : choices) {
                    std::cout << i->first << std::endl;
                }

                std::cout << ">";
                std::cin >> respond;
            }, timeout);
        }
    }

    template<class P>
    void input_text(const P& player, std::string_view prompt, std::string& respond, long timeout = -1){
        if (timeout > 0) {
            Timer t = Timer();
            t.setTimeout([&]() {
                auto s = std::format(prompt, player.getName());

                std::cout << s << std::endl;

                std::cout << ">";
                std::cin >> respond;
            }, timeout);
        }
    }

    // TODO: Need to figure out how to prompt the input for each user within this function 
    // then count the vote
    template<class P>
    void input_vote(const P& player, std::string_view prompt, std::unordered_map<std::string, std::string>& choices, std::unordered_map<std::string, int>, long timeout = -1){
        if (timeout > 0) {
            Timer t = Timer();
            t.setTimeout([&]() {
                auto s = std::format(prompt, player.getName());

                std::cout << s << std::endl;

                for (auto i : choices) {
                    std::cout << i->first << std::endl;
                }

                std::string input;
                std::cout << ">";
                std::cin >> input;
            }, timeout);
        }
    }
}
#endif