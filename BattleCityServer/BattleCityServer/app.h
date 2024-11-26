#pragma once

#include <iostream>;

namespace application {
    class App {
    private:
        //TODO: add GUI

    public:
        // Constructor
        App() = default;
        //TODO: add constructor and logic for the more complex constructor

        void Run() {
            //gives the flow
            std::cout << "Application is running." << '\n';
        }

        void Close() {
            //shuts down everything, deallocates memory ...
            std::cout << "Application is closing." << '\n';
        }

        void CreateAccount() {
            //TODO: add conditions and logic to add in db
            std::cout << "Creating a new account..." << '\n';
        }

        void Login() {
            //TODO: add logic and conditions to verify in db
            std::cout << "Logging in..." << '\n';
        }
    };
}