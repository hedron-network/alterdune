#include "StatsView.hh"
#include <string>
#include <sstream>
#include <iomanip>

namespace Render {

// ── constructor ──────────────────────────────────────────────────────────────

StatsView::StatsView(Entities::Player& player,GameLogic::PlayerStats& stats, const sf::RenderWindow& window)
    : player(player), stats(stats)
{
    auto ws = window.getSize();

    panelW = 360.f;
    panelH = 420.f;
    panelX = (ws.x - panelW) / 2.f;
    panelY = (ws.y - panelH) / 2.f;
}

// ── event / update ───────────────────────────────────────────────────────────

void StatsView::handleEvent(sf::Event& event, sf::RenderWindow& /*window*/) {
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        if (kp->code == sf::Keyboard::Key::Escape ||
            kp->code == sf::Keyboard::Key::Enter  ||
            kp->code == sf::Keyboard::Key::Tab)
        {
            signal = Signal::POP;
        }
    }
    if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mb->button == sf::Mouse::Button::Left) {
            // Click anywhere outside the panel to close
            sf::Vector2f mp(static_cast<float>(mb->position.x),
                            static_cast<float>(mb->position.y));
            sf::FloatRect panel(sf::Vector2f(panelX, panelY),
                                sf::Vector2f(panelW, panelH));
            if (!panel.contains(mp))
                signal = Signal::POP;
        }
    }
}

void StatsView::update(float /*dt*/) {}

Signal StatsView::getSignal()            { return signal; }
void   StatsView::setSignal(Signal s)    { signal = s; }

// ── drawing ──────────────────────────────────────────────────────────────────

void StatsView::draw(sf::RenderWindow& window) {
    drawPanel(window);
}

void StatsView::drawPanel(sf::RenderWindow& window) {
    auto& font = Assets::GetFont();
    const float pad    = 20.f;
    const float lineH  = 32.f;

    // ── Dark background card ─────────────────────────────────────────────────
    sf::RectangleShape bg(sf::Vector2f(panelW, panelH));
    bg.setPosition(sf::Vector2f(panelX, panelY));
    bg.setFillColor(sf::Color(15, 15, 20, 235));
    bg.setOutlineColor(sf::Color::White);
    bg.setOutlineThickness(2.f);
    window.draw(bg);

    // ── Title: player name ───────────────────────────────────────────────────
    sf::Text title(font, player.GetName(), 22);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    {
        sf::FloatRect b = title.getLocalBounds();
        title.setPosition(sf::Vector2f(panelX + (panelW - b.size.x) / 2.f,
                                       panelY + pad));
    }
    window.draw(title);

    // Separator line under title
    sf::RectangleShape sep(sf::Vector2f(panelW - 2 * pad, 1.f));
    sep.setPosition(sf::Vector2f(panelX + pad, panelY + pad + 30.f));
    sep.setFillColor(sf::Color(255, 255, 255, 80));
    window.draw(sep);

    float statsStartY = panelY + pad  + 60.f;
    float col1X = panelX + pad;

    // ATK
    drawStatRow(window, "ATK",
                std::to_string(player.Attack()),
                col1X, statsStartY);
    drawStatRow(window, "HP",
                std::to_string(player.GetHp()),
                col1X, statsStartY+ 1 * lineH);
    drawStatRow(window, "HP max",
                std::to_string(player.GetHpMax()),
                col1X, statsStartY + 2 * lineH);

    // Victories / kills / spares
    drawStatRow(window, "Victories",
                std::to_string(stats.numberOfVictories),
                col1X, statsStartY + 3 * lineH);

    drawStatRow(window, "Kills",
                std::to_string(stats.numberOfKills),
                col1X, statsStartY + 4 * lineH);

    drawStatRow(window, "Spared",
                std::to_string(stats.numberOfSpares),
                col1X, statsStartY + 5 * lineH);

    drawItems(window, panelX, statsStartY + 6 * lineH + 8.f, panelW);

    sf::Text hint(font, "[Enter / Esc] Close", 12);
    hint.setFillColor(sf::Color(255, 255, 255, 100));
    {
        sf::FloatRect b = hint.getLocalBounds();
        hint.setPosition(sf::Vector2f(panelX + (panelW - b.size.x) / 2.f,
                                      panelY + panelH - 20.f));
    }
    window.draw(hint);
    
}

void StatsView::drawStatRow(sf::RenderWindow& window,
                             const std::string& label,
                             const std::string& value,
                             float x, float y)
{
    auto& font = Assets::GetFont();
    const float colW = (panelW - 40.f) / 2.f; // half of inner width

    sf::Text lText(font, label, 15);
    lText.setFillColor(sf::Color(180, 180, 180));
    lText.setPosition(sf::Vector2f(x, y));
    window.draw(lText);

    sf::Text vText(font, value, 15);
    vText.setFillColor(sf::Color::White);
    vText.setStyle(sf::Text::Bold);
    {
        sf::FloatRect b = vText.getLocalBounds();
        vText.setPosition(sf::Vector2f(x + colW - b.size.x, y));
    }
    window.draw(vText);
}

void StatsView::drawItems(sf::RenderWindow& window,float px, float iy, float pw)
{
    auto& font  = Assets::GetFont();
    const float pad = 20.f;

    sf::Text header(font, "Items", 14);
    header.setFillColor(sf::Color(200, 200, 200));
    header.setPosition(sf::Vector2f(px + pad, iy));
    window.draw(header);

    auto& items = player.GetItems();
    if (items.empty()) {
        sf::Text none(font, "none", 13);
        none.setFillColor(sf::Color(120, 120, 120));
        none.setPosition(sf::Vector2f(px + pad, iy + 20.f));
        window.draw(none);
        return;
    }

    float itemY = iy + 22.f;
    for (auto& item : items) {
        std::string txt = item.GetName() + "  x" + std::to_string(item.GetQuantity());
        sf::Text t(font, txt, 13);
        t.setFillColor(sf::Color(220, 220, 220));
        t.setPosition(sf::Vector2f(px + pad + 8.f, itemY));
        window.draw(t);
        itemY += 20.f;
    }
}

}
