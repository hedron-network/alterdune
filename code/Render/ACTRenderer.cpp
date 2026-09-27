#include "ACTRenderer.hh"
#include <algorithm>

namespace Render {
ActMenuRender::ActMenuRender(std::vector<Action> actions,
                             Entities::Enemy&     enemy,
                             Entities::Player&    player,
                             const sf::RenderWindow& window)
    : actions(actions), enemy(enemy), player(player)
{
    Assets::LoadFont();

    auto winSize = window.getSize();

    panelWidth  = 360.f;
    panelHeight = PADDING * 2 + std::max((int)actions.size(), 1) * ROW_HEIGHT + ROW_HEIGHT;
    panelX      = (winSize.x - panelWidth)  / 2.f;
    panelY      = (winSize.y - panelHeight) / 2.f;

    panelRect.setSize({panelWidth, panelHeight});
    panelRect.setPosition({panelX, panelY});
    panelRect.setFillColor(sf::Color(10, 10, 10, 230));
    panelRect.setOutlineColor(sf::Color::Cyan);
    panelRect.setOutlineThickness(3.f);

    selectionHighlight.setSize({panelWidth - PADDING * 2, ROW_HEIGHT - 4.f});
    selectionHighlight.setFillColor(sf::Color(0, 255, 255, 40));
    selectionHighlight.setOutlineColor(sf::Color::Cyan);
    selectionHighlight.setOutlineThickness(2.f);

    // Description overlay box (centered, above or below panel)
    float descW = panelWidth + 40.f;
    float descH = 60.f;
    descBox.setSize({descW, descH});
    descBox.setPosition({panelX - 20.f, panelY - descH - 12.f});
    descBox.setFillColor(sf::Color(20, 20, 20, 220));
    descBox.setOutlineColor(sf::Color::Cyan);
    descBox.setOutlineThickness(2.f);
}

int ActMenuRender::validSelected() const {
    return std::clamp(selectedIndex, 0, std::max((int)actions.size() - 1, 0));
}

void ActMenuRender::handleKeyPress(sf::Keyboard::Key key) {
    if (showingDesc) return; // block input while showing description

    if (actions.empty()) {
        if (key == sf::Keyboard::Key::Escape || key == sf::Keyboard::Key::X)
            signal = Signal::POP;
        return;
    }

    if (key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Z)
        selectedIndex = (selectedIndex - 1 + actions.size()) % actions.size();

    if (key == sf::Keyboard::Key::Down || key == sf::Keyboard::Key::S)
        selectedIndex = (selectedIndex + 1) % actions.size();

    if (key == sf::Keyboard::Key::Enter) {
        int idx = validSelected();
        enemy.ACT(actions[idx]);   // apply the action to the enemy
        showingDesc = true;
        descTimer   = 0.f;
    }

    if (key == sf::Keyboard::Key::Escape || key == sf::Keyboard::Key::X)
        signal = Signal::POP;
}

void ActMenuRender::handleClick(sf::Vector2f mousePos) {
    if (showingDesc) return;

    float headerH = ROW_HEIGHT;
    for (int i = 0; i < (int)actions.size(); i++) {
        float rowY = panelY + PADDING + headerH + i * ROW_HEIGHT;
        sf::FloatRect rowRect({panelX + PADDING, rowY}, {panelWidth - PADDING * 2, ROW_HEIGHT});
        if (rowRect.contains(mousePos)) {
            if (selectedIndex == i) {
                enemy.ACT(actions[i]);
                showingDesc = true;
                descTimer   = 0.f;
            } else {
                selectedIndex = i;
            }
            return;
        }
    }
}

void ActMenuRender::update(float dt) {
    if (!showingDesc) return;

    descTimer += dt;
    if (descTimer >= DESC_DURATION) {
        showingDesc = false;
        signal      = Signal::POPANDFIGHT;
    }
}

void ActMenuRender::draw(sf::RenderWindow& window) {
    drawLifeBar(window);
    const auto& font = Assets::GetFont();

    window.draw(panelRect);

    // --- Header ---
    sf::Text header(font, "ACT", (unsigned)FONT_SIZE_LG);
    header.setFillColor(sf::Color::Cyan);
    sf::FloatRect hb = header.getLocalBounds();
    header.setPosition({panelX + (panelWidth - hb.size.x) / 2.f, panelY + PADDING});
    window.draw(header);

    float headerH = ROW_HEIGHT;

    if (actions.empty()) {
        sf::Text empty(font, "- No actions -", (unsigned)FONT_SIZE_SM);
        empty.setFillColor(sf::Color(180, 180, 180));
        sf::FloatRect eb = empty.getLocalBounds();
        empty.setPosition({panelX + (panelWidth - eb.size.x) / 2.f,
                           panelY + PADDING + headerH + 6.f});
        window.draw(empty);
        return;
    }

    int sel = validSelected();

    for (int i = 0; i < (int)actions.size(); i++) {
        float rowY = panelY + PADDING + headerH + i * ROW_HEIGHT;

        if (i == sel) {
            selectionHighlight.setPosition({panelX + PADDING, rowY + 2.f});
            window.draw(selectionHighlight);
        }

        sf::Text bullet(font, i == sel ? "> " : "  ", (unsigned)FONT_SIZE_SM);
        bullet.setFillColor(sf::Color::Cyan);
        bullet.setPosition({panelX + PADDING + 4.f, rowY + 6.f});
        window.draw(bullet);

        sf::Text nameText(font, actions[i].GetName(), (unsigned)FONT_SIZE_SM);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition({panelX + PADDING + 28.f, rowY + 6.f});
        window.draw(nameText);
    }

    // Footer hint
    sf::Text hint(font, "[Enter] Act   [Esc] Back", (unsigned)13);
    hint.setFillColor(sf::Color(140, 140, 140));
    sf::FloatRect fb = hint.getLocalBounds();
    hint.setPosition({panelX + (panelWidth - fb.size.x) / 2.f,
                      panelY + panelHeight - 22.f});
    window.draw(hint);

    // --- Description overlay ---
    if (showingDesc) {
        int idx = validSelected();
        window.draw(descBox);

        // Fade out effect based on remaining time
        float alpha = std::clamp(1.f - (descTimer / DESC_DURATION) * 0.4f, 0.f, 1.f);
        auto a =(255 * alpha);

        sf::Text desc(font, actions[idx].GetDescription(), (unsigned)FONT_SIZE_SM);
        desc.setFillColor(sf::Color(200, 255, 255, a));
        sf::FloatRect db = desc.getLocalBounds();
        float bx = descBox.getPosition().x;
        float by = descBox.getPosition().y;
        float bw = descBox.getSize().x;
        float bh = descBox.getSize().y;
        desc.setPosition({bx + (bw - db.size.x) / 2.f, by + (bh - db.size.y) / 2.f});
        window.draw(desc);

        // Progress bar showing how long the description stays
        float progress = 1.f - (descTimer / DESC_DURATION);
        sf::RectangleShape progBg({panelWidth - PADDING * 2, 4.f});
        progBg.setPosition({panelX + PADDING, panelY + panelHeight - 8.f});
        progBg.setFillColor(sf::Color(60, 60, 60));
        window.draw(progBg);

        sf::RectangleShape progFg({(panelWidth - PADDING * 2) * progress, 4.f});
        progFg.setPosition({panelX + PADDING, panelY + panelHeight - 8.f});
        progFg.setFillColor(sf::Color::Cyan);
        window.draw(progFg);
    }
}

Render::Signal ActMenuRender::getSignal() { return signal; }
void ActMenuRender::setSignal(Signal s) { signal = s; }

void ActMenuRender::drawLifeBar(sf::RenderWindow& window) {
    const float endY      = window.getSize().y - 40;
    const float barWidth  = 100.f;
    const float barHeight = 10.f;
    const float barY      = endY + 18.f;
    const float barX      = window.getSize().x / 2.f - 50.f;
    float ratio = std::clamp(static_cast<float>(player.GetHp()) / 100.f, 0.f, 1.f);

    sf::RectangleShape bgBar(sf::Vector2f(barWidth, barHeight));
    bgBar.setPosition(sf::Vector2f(barX, barY));
    bgBar.setFillColor(sf::Color::Red);

    sf::RectangleShape fgBar(sf::Vector2f(barWidth * ratio, barHeight));
    fgBar.setPosition(sf::Vector2f(barX, barY));
    fgBar.setFillColor(sf::Color::Yellow);

    window.draw(bgBar);
    window.draw(fgBar);
}

} 