#include <Entity.hh>
#include <string>

using namespace std;

namespace Entities
{
    class Player : public Entity {
    private:
    int numberOfKill;
    int numberOfSpare;
    int numberOfVictory;

    public :
    Player(string name, int hpMax);

};
}
