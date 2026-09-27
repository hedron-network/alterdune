#ifndef BestiaryView_h
#define BestiaryView_h

#include <SFML/Graphics.hpp>
#include <sstream>
#include "../GameLogic/Bestiary.hh"
#include "renderTypes.hh"
#include "Views.hh"
#include "Assets.hh"

namespace Render {

    class BestiaryView : public State {
    private:
        const GameLogic::Bestiary& bestiary;

        // Scrolling
        int scrollOffset = 0;          // first visible entry index
        static constexpr int VISIBLE_ROWS = 6;

        // Layout constants
        static constexpr float PADDING      = 40.f;
        static constexpr float INNER_PAD    = 18.f;   // left indent inside the pill
        static constexpr float TITLE_Y      = 28.f;
        static constexpr float LIST_START_Y = 110.f;
        static constexpr float ROW_HEIGHT = 126.f; // taller to fit description
        static constexpr float DIVIDER_H    = 1.f;

        // Colours (UNDERTALE-ish dark palette)
        const sf::Color BG_DARK      { 10,  10,  18, 255};
        const sf::Color BG_ROW_EVEN  { 18,  18,  30, 255};
        const sf::Color BG_ROW_ODD   { 24,  24,  40, 255};
        const sf::Color ACCENT_KILL  {220,  60,  60, 255};   // red   – killed
        const sf::Color ACCENT_SPARE {100, 210, 140, 255};   // green – spared
        const sf::Color ACCENT_BOSS  {230, 170,  40, 255};   // gold  – boss
        const sf::Color ACCENT_MINI  {150, 100, 220, 255};   // purple– miniboss
        const sf::Color TEXT_MAIN    {230, 230, 230, 255};
        const sf::Color TEXT_DIM     {120, 120, 140, 255};
        const sf::Color DIVIDER_COL  { 40,  40,  60, 255};
        const sf::Color SCROLL_BAR   { 60,  60,  90, 255};

        Signal signal = Signal::None;

        // helpers
        sf::Color rowColour(int i)     const { return (i % 2 == 0) ? BG_ROW_EVEN : BG_ROW_ODD; }
        sf::Color categoryColour(Entities::EnemyType t) const;
        std::string categoryLabel(Entities::EnemyType t) const;

        void drawTitle(sf::RenderWindow& window)                           const;
        void drawEmpty(sf::RenderWindow& window)                           const;
        void drawEntry(sf::RenderWindow& window,
                       const GameLogic::BestiaryEntry& e,
                       int slot)                                           const;
        void drawScrollBar(sf::RenderWindow& window)                       const;
        void drawFooter(sf::RenderWindow& window)                          const;
        std::string wrapText(const std::string& text, const sf::Font& font, unsigned int charSize, float maxWidth) const;

    public:
        explicit BestiaryView(const GameLogic::Bestiary& bestiary);

        void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt)                                         override;
        void draw(sf::RenderWindow& window)                           override;
        Signal getSignal()                                            override;
        void   setSignal(Signal s)                                    override;
    };

} // namespace Render
#endif
