#include "ItemMenuRenderer.hh"
#include <algorithm>
#include <iostream>

namespace Render {

ItemMenuRender::ItemMenuRender(std::vector<Attributes::Item>& items,Entities::Player& player,const sf::RenderWindow& window)
    : items(items), player(player)
{
    Assets::LoadFont();

    auto winSize = window.getSize();

    panelWidth  = 360.f;
    panelHeight = PADDING * 2 + std::max((int)items.size(), 1) * ROW_HEIGHT + ROW_HEIGHT; // +1 row for header
    panelX      = (winSize.x - panelWidth)  / 2.f;
    panelY      = (winSize.y - panelHeight) / 2.f;

    panelRect.setSize({panelWidth, panelHeight});
    panelRect.setPosition({panelX, panelY});
    panelRect.setFillColor(sf::Color(10, 10, 10, 230));
    panelRect.setOutlineColor(sf::Color::White);
    panelRect.setOutlineThickness(3.f);

    selectionHighlight.setSize({panelWidth - PADDING * 2, ROW_HEIGHT - 4.f});
    selectionHighlight.setFillColor(sf::Color(255, 255, 0, 50));
    selectionHighlight.setOutlineColor(sf::Color::Yellow);
    selectionHighlight.setOutlineThickness(2.f);
}

int ItemMenuRender::validSelected() const {
    return std::clamp(selectedIndex, 0, std::max((int)items.size() - 1, 0));
}

void ItemMenuRender::handleKeyPress(sf::Keyboard::Key key) {
    if (items.empty()) {
        if (key == sf::Keyboard::Key::Escape || key == sf::Keyboard::Key::X)
            signal = Signal::POP;
        return;
    }

    if (key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Z) {
        selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
    }
    if (key == sf::Keyboard::Key::Down || key == sf::Keyboard::Key::S) {
        selectedIndex = (selectedIndex + 1) % items.size();
    }
    if (key == sf::Keyboard::Key::Enter) {
        int idx = validSelected();
        if (!items[idx].IsEmpty()) {
            items[idx].UseItem(player);
            // Remove item if depleted
            if (items[idx].IsEmpty()) {
                items.erase(items.begin() + idx);
                selectedIndex = std::min(selectedIndex, (int)items.size() - 1);
            }
            signal = Signal::POPANDFIGHT; // stay in menu after use; change to POP if you want to exit
        }
    }
    if (key == sf::Keyboard::Key::Escape || key == sf::Keyboard::Key::X) {
        signal = Signal::POP;
    }
}

void ItemMenuRender::handleClick(sf::Vector2f mousePos) {
    float headerH = ROW_HEIGHT; // skip header row
    for (int i = 0; i < (int)items.size(); i++) {
        float rowY = panelY + PADDING + headerH + i * ROW_HEIGHT;
        sf::FloatRect rowRect({panelX + PADDING, rowY}, {panelWidth - PADDING * 2, ROW_HEIGHT});
        if (rowRect.contains(mousePos)) {
            if (selectedIndex == i) {
                // Double-click equivalent: second click on already-selected item uses it
                if (!items[i].IsEmpty()) {
                    items[i].UseItem(player);
                    if (items[i].IsEmpty()) {
                        items.erase(items.begin() + i);
                        selectedIndex = std::min(selectedIndex, (int)items.size() - 1);
                    }
                }
            } else {
                selectedIndex = i;
            }
            return;
        }
    }
}

void ItemMenuRender::update(float dt) {}

void ItemMenuRender::draw(sf::RenderWindow& window) {
    drawLifeBar(window);
    const auto& font = Assets::GetFont();

    window.draw(panelRect);

    // --- Header ---
    sf::Text header(font, "ITEMS", (unsigned)FONT_SIZE_LG);
    header.setFillColor(sf::Color::Yellow);
    sf::FloatRect hb = header.getLocalBounds();
    header.setPosition({panelX + (panelWidth - hb.size.x) / 2.f, panelY + PADDING});
    window.draw(header);

    float headerH = ROW_HEIGHT;

    if (items.empty()) {
        sf::Text empty(font, "- No items -", (unsigned)FONT_SIZE_SM);
        empty.setFillColor(sf::Color(180, 180, 180));
        sf::FloatRect eb = empty.getLocalBounds();
        empty.setPosition({panelX + (panelWidth - eb.size.x) / 2.f,
                           panelY + PADDING + headerH + 6.f});
        window.draw(empty);
        return;
    }

    int sel = validSelected();

    for (int i = 0; i < (int)items.size(); i++) {
        float rowY = panelY + PADDING + headerH + i * ROW_HEIGHT;

        // Selection highlight
        if (i == sel) {
            selectionHighlight.setPosition({panelX + PADDING, rowY + 2.f});
            window.draw(selectionHighlight);
        }

        // Bullet / cursor
        sf::Text bullet(font, i == sel ? "> " : "  ", (unsigned)FONT_SIZE_SM);
        bullet.setFillColor(sf::Color::Yellow);
        bullet.setPosition({panelX + PADDING + 4.f, rowY + 6.f});
        window.draw(bullet);

        // Item name
        std::string nameStr = items[i].GetName();
        sf::Text nameText(font, nameStr, (unsigned)FONT_SIZE_SM);
        nameText.setFillColor(items[i].IsEmpty() ? sf::Color(100,100,100) : sf::Color::White);
        nameText.setPosition({panelX + PADDING + 28.f, rowY + 6.f});
        window.draw(nameText);

        // Quantity (right-aligned)
        std::string qtyStr = "x" + std::to_string(items[i].GetQuantity());
        sf::Text qtyText(font, qtyStr, (unsigned)FONT_SIZE_SM);
        qtyText.setFillColor(sf::Color(200, 200, 200));
        sf::FloatRect qb = qtyText.getLocalBounds();
        qtyText.setPosition({panelX + panelWidth - PADDING - qb.size.x - 8.f, rowY + 6.f});
        window.draw(qtyText);
    }

    // Footer hint
    sf::Text hint(font, "[Enter] Use   [Esc] Back", (unsigned)13);
    hint.setFillColor(sf::Color(140, 140, 140));
    sf::FloatRect fb = hint.getLocalBounds();
    hint.setPosition({panelX + (panelWidth - fb.size.x) / 2.f,
                      panelY + panelHeight - 22.f});
    window.draw(hint);
}

Render::Signal ItemMenuRender::getSignal() { return signal; }
void ItemMenuRender::setSignal(Signal s) { signal = s; }

void ItemMenuRender::drawLifeBar(sf::RenderWindow& window) {
        const float endY =window.getSize().y -40;
        const float barWidth  = 100;
        const float barHeight = 10.f;
        const float barY      = endY + 18.f;
        const float barX      = window.getSize().x/2-50;
        float maxHp    = static_cast<float>(100);
        float currentHp = static_cast<float>(player.GetHp());
        float ratio    = std::clamp(currentHp / maxHp, 0.f, 1.f);

        // Background (empty bar)
        sf::RectangleShape bgBar(sf::Vector2f(barWidth, barHeight));
        bgBar.setPosition(sf::Vector2f(barX, barY));
        bgBar.setFillColor(sf::Color::Red);

        // Foreground (filled portion)
        sf::RectangleShape fgBar(sf::Vector2f(barWidth * ratio, barHeight));
        fgBar.setPosition(sf::Vector2f(barX, barY));
        fgBar.setFillColor(sf::Color::Yellow);

        window.draw(bgBar);
        window.draw(fgBar);
    }
}