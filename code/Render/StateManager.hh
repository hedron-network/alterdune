#ifndef StateManager_h
#define StateManager_h
#include <stack>
#include <memory>
#include "Views.hh"
namespace Render {
    class StateManager {
    private:
        std::stack<std::unique_ptr<State>> states;

    public:
        void pushState(std::unique_ptr<State> state);

        void popState();

        State* getCurrentState();
    };
}
#endif