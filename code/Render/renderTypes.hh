// RenderTypes.hh  (new file — no includes needed)
#ifndef RenderTypes_h
#define RenderTypes_h

namespace Render {
    enum Signal {
        MAINMENU, COMBATMENU, ITEMMENU, ACTMENU,
        BESTIARYMENU, COMBATSTEP, POP,POPANDFIGHT, None
    };
    enum MenuType {
        MAIN_MENU, COMBAT_MENU, ITEM_MENU
    };
}
#endif