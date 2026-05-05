#include "BestiaryView.hh"
#include <algorithm>

namespace Render {

// ──────────────────────────────────────────────
//  Helpers
// ──────────────────────────────────────────────

sf::Color BestiaryView::categoryColour(Entities::EnemyType t) const {
    switch (t) {
        case Entities::EnemyType::BOSS:     return ACCENT_BOSS;
        case Entities::EnemyType::MINIBOSS: return ACCENT_MINI;
        default:                            return TEXT_DIM;
    }
}

std::string BestiaryView::categoryLabel(Entities::EnemyType t) const {
    switch (t) {
        case Entities::EnemyType::BOSS:     return "BOSS";
        case Entities::EnemyType::MINIBOSS: return "MINI-BOSS";
        default:                            return "NORMAL";
    }
}

// ──────────────────────────────────────────────
//  Constructor
// ──────────────────────────────────────────────

BestiaryView::BestiaryView(const GameLogic::Bestiary& bestiary)
    : bestiary(bestiary) {}

// ──────────────────────────────────────────────
//  State interface
// ──────────────────────────────────────────────

Signal BestiaryView::getSignal()          { return signal; }
void   BestiaryView::setSignal(Signal s)  { signal = s; }
void   BestiaryView::update(float /*dt*/) {}

void BestiaryView::handleEvent(sf::Event& event, sf::RenderWindow& /*window*/) {
    const auto& entries = bestiary.GetEntries();
    const int maxScroll = std::max(0, (int)entries.size() - VISIBLE_ROWS);

    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        switch (kp->code) {
            case sf::Keyboard::Key::Escape:
            case sf::Keyboard::Key::Backspace:
                signal = Signal::POP;
                break;
            case sf::Keyboard::Key::Up:
            case sf::Keyboard::Key::Z:
                scrollOffset = std::max(0, scrollOffset - 1);
                break;
            case sf::Keyboard::Key::Down:
            case sf::Keyboard::Key::S:
                scrollOffset = std::min(maxScroll, scrollOffset + 1);
                break;
            default: break;
        }
    }
    // Mouse wheel
    if (const auto* mw = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (mw->delta < 0)
            scrollOffset = std::min(maxScroll, scrollOffset + 1);
        else
            scrollOffset = std::max(0, scrollOffset - 1);
    }
}

// ──────────────────────────────────────────────
//  Drawing helpers
// ──────────────────────────────────────────────

void BestiaryView::drawTitle(sf::RenderWindow& window) const {
    const float W = static_cast<float>(window.getSize().x);

    // ── full-width header band ──
    sf::RectangleShape band({W, 80.f});
    band.setFillColor(sf::Color{20, 20, 36, 255});
    band.setPosition({0.f, 0.f});
    window.draw(band);

    // ── thin accent line under the band ──
    sf::RectangleShape line({W, 2.f});
    line.setFillColor(TEXT_DIM);
    line.setPosition({0.f, 80.f});
    window.draw(line);

    // ── title text ──
    sf::Text title(Assets::GetFont(), "BESTIARY", 36);
    title.setFillColor(TEXT_MAIN);
    title.setStyle(sf::Text::Bold);
    sf::FloatRect b = title.getLocalBounds();
    title.setPosition({(W - b.size.x) / 2.f, TITLE_Y});
    window.draw(title);

    // ── entry count badge ──
    const auto& entries = bestiary.GetEntries();
    sf::Text count(Assets::GetFont(),
                   std::to_string(entries.size()) + " encountered",
                   16);
    count.setFillColor(TEXT_DIM);
    sf::FloatRect cb = count.getLocalBounds();
    count.setPosition({(W - cb.size.x) / 2.f, TITLE_Y + 40.f});
    window.draw(count);
}

void BestiaryView::drawEmpty(sf::RenderWindow& window) const {
    const float W = static_cast<float>(window.getSize().x);
    const float H = static_cast<float>(window.getSize().y);
    sf::Text msg(Assets::GetFont(), "No enemies defeated yet.", 22);
    msg.setFillColor(TEXT_DIM);
    sf::FloatRect b = msg.getLocalBounds();
    msg.setPosition({(W - b.size.x) / 2.f, (H - b.size.y) / 2.f});
    window.draw(msg);
}

void BestiaryView::drawEntry(sf::RenderWindow& window,
                              const GameLogic::BestiaryEntry& e,
                              int slot) const
{
    const float W  = static_cast<float>(window.getSize().x);
    const float y  = LIST_START_Y + slot * ROW_HEIGHT;
    const float xL = PADDING;
    const float xR = W - PADDING;

    // ── row background ──
    // (slot here is the visual slot 0-5, not the entry index)
    // we derive the real index for colour striping below in draw()
    sf::RectangleShape row({xR - xL, ROW_HEIGHT - DIVIDER_H});
    row.setFillColor(rowColour(slot));   // alternating colour
    row.setPosition({xL, y});
    window.draw(row);

    // ── left colour pill (spared / killed) ──
    sf::Color pillCol = e.wasSpared ? ACCENT_SPARE : ACCENT_KILL;
    sf::RectangleShape pill({4.f, ROW_HEIGHT - DIVIDER_H - 12.f});
    pill.setFillColor(pillCol);
    pill.setPosition({xL + 6.f, y + 6.f});
    window.draw(pill);

    const float contentX = xL + INNER_PAD;   // unified left edge for all content

    // ── enemy name ──
    sf::Text name(Assets::GetFont(), e.enemy.GetName(), 22);
    name.setFillColor(TEXT_MAIN);
    name.setStyle(sf::Text::Bold);
    name.setPosition({contentX, y + 10.f});
    window.draw(name);

    // ── result label (right-aligned, same row as name) ──
    std::string resultStr = e.wasSpared ? "SPARED" : "KILLED";
    sf::Color   resultCol = e.wasSpared ? ACCENT_SPARE : ACCENT_KILL;
    sf::Text result(Assets::GetFont(), resultStr, 18);
    result.setFillColor(resultCol);
    result.setStyle(sf::Text::Bold);
    sf::FloatRect rb = result.getLocalBounds();
    result.setPosition({xR - rb.size.x - 4.f, y + 12.f});
    window.draw(result);

    // ── description (second row, wrapped) ──
    const float maxDescWidth = (xR - contentX) - 8.f;  // right margin
    std::string wrapped = wrapText(e.enemy.GetDescription(),Assets::GetFont(), 15, maxDescWidth);
    sf::Text desc(Assets::GetFont(), wrapped, 15);
    desc.setFillColor(TEXT_DIM);
    desc.setPosition({contentX, y + 40.f});
    window.draw(desc);

    // ── third row: category tag then HP with guaranteed gap ──
    const float tagY = y + 70.f;

    // category tag
    std::string catLabel = categoryLabel(e.enemy.GetCategorie());
    sf::Color   catCol   = categoryColour(e.enemy.GetCategorie());
    sf::Text catText(Assets::GetFont(), catLabel, 13);
    catText.setFillColor(catCol);
    sf::FloatRect cb = catText.getLocalBounds();
    sf::RectangleShape catBg({cb.size.x + 12.f, cb.size.y + 6.f});
    catBg.setFillColor(sf::Color{catCol.r, catCol.g, catCol.b, 40});
    catBg.setOutlineColor(catCol);
    catBg.setOutlineThickness(1.f);
    catBg.setPosition({contentX, tagY});
    window.draw(catBg);
    catText.setPosition({contentX + 6.f, tagY + 2.f});
    window.draw(catText);

    // HP — placed after the tag with a fixed gap, never overlapping
    const float hpX = contentX + cb.size.x + 12.f + 16.f;  // tag width + gap
    sf::Text hp(Assets::GetFont(), "HP  " + std::to_string(e.enemy.GetHpMax()), 15);
    hp.setFillColor(TEXT_DIM);
    hp.setPosition({hpX, tagY + 2.f});
    window.draw(hp);

    // ── divider ──
    sf::RectangleShape div({xR - xL, DIVIDER_H});
    div.setFillColor(DIVIDER_COL);
    div.setPosition({xL, y + ROW_HEIGHT - DIVIDER_H});
    window.draw(div);
}

void BestiaryView::drawScrollBar(sf::RenderWindow& window) const {
    const auto& entries = bestiary.GetEntries();
    if ((int)entries.size() <= VISIBLE_ROWS) return;

    const float W         = static_cast<float>(window.getSize().x);
    const float barX      = W - PADDING + 12.f;
    const float totalH    = VISIBLE_ROWS * ROW_HEIGHT;
    const float trackY    = LIST_START_Y;
    const float thumbRatio= (float)VISIBLE_ROWS / (float)entries.size();
    const float thumbH    = totalH * thumbRatio;
    const float maxScroll = (float)(entries.size() - VISIBLE_ROWS);
    const float thumbY    = trackY + (scrollOffset / maxScroll) * (totalH - thumbH);

    // track
    sf::RectangleShape track({4.f, totalH});
    track.setFillColor(sf::Color{40, 40, 60, 255});
    track.setPosition({barX, trackY});
    window.draw(track);

    // thumb
    sf::RectangleShape thumb({4.f, thumbH});
    thumb.setFillColor(TEXT_DIM);
    thumb.setPosition({barX, thumbY});
    window.draw(thumb);
}

void BestiaryView::drawFooter(sf::RenderWindow& window) const {
    const float W = static_cast<float>(window.getSize().x);
    const float H = static_cast<float>(window.getSize().y);

    sf::RectangleShape line({W - 2 * PADDING, 1.f});
    line.setFillColor(DIVIDER_COL);
    line.setPosition({PADDING, H - 36.f});
    window.draw(line);

    sf::Text hint(Assets::GetFont(), "[UP/DOWN]  Scroll      [ESC]  Back", 14);
    hint.setFillColor(TEXT_DIM);
    sf::FloatRect hb = hint.getLocalBounds();
    hint.setPosition({(W - hb.size.x) / 2.f, H - 28.f});
    window.draw(hint);
}

// ──────────────────────────────────────────────
//  Main draw
// ──────────────────────────────────────────────

void BestiaryView::draw(sf::RenderWindow& window) {
    // Background
    window.clear(BG_DARK);

    drawTitle(window);

    const auto& entries = bestiary.GetEntries();
    if (entries.empty()) {
        drawEmpty(window);
    } else {
        const int count = (int)entries.size();
        const int end   = std::min(scrollOffset + VISIBLE_ROWS, count);
        for (int i = scrollOffset; i < end; ++i) {
            drawEntry(window, entries[i], i - scrollOffset);
        }
        drawScrollBar(window);
    }

    drawFooter(window);
}
std::string BestiaryView::wrapText(const std::string& text, const sf::Font& font,unsigned int charSize, float maxWidth) const
{
    std::istringstream words(text);
    std::string word, line, result;
    while (words >> word) {
        std::string test = line.empty() ? word : line + " " + word;
        sf::Text probe(font, test, charSize);
        if (probe.getLocalBounds().size.x > maxWidth && !line.empty()) {
            result += line + "\n";
            line = word;
        } else {
            line = test;
        }
    }
    if (!line.empty()) result += line;
    return result;
}
} // namespace Render
