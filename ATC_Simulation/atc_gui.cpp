#include "aircraft.h"
#include "commercial.h"
#include "military.h"
#include "cargo.h"
#include "helicopter.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

// --- Window & radar constants ---
const int W = 900, H = 600;
const float RX = 290, RY = 300, RR = 250;  // radar center + radius
const float PANEL = 610;                     // left edge of info panel

// --- Position of each aircraft blip on the radar ---
struct Blip {
    float angle;   // angle in radians around the radar center
    float dist;    // 0.0 = center, 1.0 = edge
    float speed;   // how fast the blip orbits (radians per tick)
};

sf::Color statusColor(AircraftStatus s) {
    if (s == GROUNDED)  return sf::Color(100, 100, 100);
    if (s == TAKEOFF)   return sf::Color(255, 200,   0);
    if (s == AIRBORNE)  return sf::Color( 50, 220, 100);
    if (s == LANDING)   return sf::Color(  0, 190, 255);
    return                     sf::Color(255,  55,  55); // EMERGENCY
}

void moveBlip(Blip& b, Aircraft* ac) {
    switch (ac->getStatus()) {
        case GROUNDED:  b.dist -= 0.03f;  if (b.dist < 0)    b.dist = 0;    break;
        case TAKEOFF:   b.dist += 0.02f;  if (b.dist > 0.85f) b.dist = 0.85f; b.angle += b.speed; break;
        case AIRBORNE:  b.dist  = 0.75f;  b.angle += b.speed; break;
        case LANDING:   b.dist -= 0.015f; if (b.dist < 0.05f) b.dist = 0.05f; b.angle += b.speed * 0.3f; break;
        case EMERGENCY: b.dist -= 0.02f;  if (b.dist < 0.05f) b.dist = 0.05f; break;
    }
}

int main() {
    srand((unsigned)time(nullptr));

    sf::RenderWindow win(sf::VideoMode(W, H), "ATC Radar Tower");
    win.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf");

    // --- Create aircraft ---
    std::vector<Aircraft*> planes;
    planes.push_back(new AirbusA350        ("A350",    TAKEOFF));
    planes.push_back(new Dreamliner787     ("B787",    TAKEOFF));
    planes.push_back(new F22Raptor         ("F-22",    GROUNDED));
    planes.push_back(new EurofighterTyphoon("Typhoon", AIRBORNE));
    planes.push_back(new SuperGalaxyC5M    ("C-5M",    GROUNDED));
    planes.push_back(new Freighter747      ("747-F",   EMERGENCY));
    planes.push_back(new Apache            ("Apache",  TAKEOFF));
    planes.push_back(new KingStallion      ("CH-53K",  LANDING));

    // --- Init radar blips ---
    std::vector<Blip> blips(planes.size());
    for (int i = 0; i < (int)planes.size(); i++) {
        blips[i].angle = (float)i / planes.size() * 6.28f;
        blips[i].speed = 0.02f + (rand() % 10) * 0.005f;
        AircraftStatus s = planes[i]->getStatus();
        blips[i].dist = (s == AIRBORNE) ? 0.75f : (s == GROUNDED) ? 0.0f : 0.35f;
    }

    int  selected = -1;
    bool paused   = false;
    int  tick     = 0;
    sf::Clock tickClock, flashClock, sweepClock;

    while (win.isOpen()) {

        // --- Events ---
        sf::Event ev;
        while (win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) win.close();

            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
                paused = !paused;

            if (ev.type == sf::Event::MouseButtonPressed) {
                float mx = (float)ev.mouseButton.x;
                float my = (float)ev.mouseButton.y;

                // Click on radar to select a blip
                if (mx < PANEL) {
                    selected = -1;
                    for (int i = 0; i < (int)planes.size(); i++) {
                        float bx = RX + cosf(blips[i].angle) * blips[i].dist * RR;
                        float by = RY + sinf(blips[i].angle) * blips[i].dist * RR;
                        if ((mx-bx)*(mx-bx) + (my-by)*(my-by) < 144) { selected = i; break; }
                    }
                }

                // Click on list row to select
                if (mx > PANEL) {
                    int idx = (int)((my - 60) / 55);
                    if (idx >= 0 && idx < (int)planes.size()) selected = idx;
                }

                // Click status buttons (bottom of panel)
                if (selected >= 0 && my > H - 55) {
                    AircraftStatus map[] = { TAKEOFF, LANDING, GROUNDED, EMERGENCY };
                    for (int b = 0; b < 4; b++) {
                        float bx = PANEL + 8 + b * 73;
                        if (mx >= bx && mx < bx + 68) planes[selected]->setStatus(map[b]);
                    }
                }
            }
        }

        // --- Simulation tick every 0.9 s ---
        if (!paused && tickClock.getElapsedTime().asSeconds() > 0.9f) {
            tickClock.restart();
            tick++;
            for (int i = 0; i < (int)planes.size(); i++) {
                planes[i]->update();
                moveBlip(blips[i], planes[i]);
            }
        }

        float sweep = fmodf(sweepClock.getElapsedTime().asSeconds() * 0.8f, 6.28f);
        bool  flash = (int)(flashClock.getElapsedTime().asMilliseconds() / 380) % 2;

        // ======== DRAW ========
        win.clear(sf::Color(8, 12, 18));

        // Radar background + rings
        sf::CircleShape radarBg(RR);
        radarBg.setOrigin(RR, RR);
        radarBg.setPosition(RX, RY);
        radarBg.setFillColor(sf::Color(10, 24, 14));
        radarBg.setOutlineColor(sf::Color(0, 60, 28));
        radarBg.setOutlineThickness(2);
        win.draw(radarBg);

        for (int r = 1; r <= 4; r++) {
            float rr = RR * r / 4.f;
            sf::CircleShape ring(rr);
            ring.setOrigin(rr, rr);
            ring.setPosition(RX, RY);
            ring.setFillColor(sf::Color::Transparent);
            ring.setOutlineColor(sf::Color(0, 40, 18));
            ring.setOutlineThickness(1);
            win.draw(ring);
        }

        // Sweep line
        sf::VertexArray sl(sf::Lines, 2);
        sl[0].position = sf::Vector2f(RX, RY);                                      sl[0].color = sf::Color(0, 200, 90, 180);
        sl[1].position = sf::Vector2f(RX + cosf(sweep)*RR, RY + sinf(sweep)*RR);    sl[1].color = sf::Color::Transparent;
        win.draw(sl);

        // Aircraft blips
        for (int i = 0; i < (int)planes.size(); i++) {
            float bx = RX + cosf(blips[i].angle) * blips[i].dist * RR;
            float by = RY + sinf(blips[i].angle) * blips[i].dist * RR;
            sf::Color col = statusColor(planes[i]->getStatus());
            if (planes[i]->getStatus() == EMERGENCY && flash) col = sf::Color::White;

            if (i == selected) {
                sf::CircleShape ring(13); ring.setOrigin(13, 13); ring.setPosition(bx, by);
                ring.setFillColor(sf::Color::Transparent);
                ring.setOutlineColor(sf::Color(255, 255, 255, 140));
                ring.setOutlineThickness(1.5f);
                win.draw(ring);
            }

            sf::CircleShape dot(7); dot.setOrigin(7, 7); dot.setPosition(bx, by);
            dot.setFillColor(col);
            win.draw(dot);

            sf::Text label(planes[i]->getCallSign(), font, 10);
            label.setFillColor(sf::Color(150, 200, 150));
            label.setPosition(bx + 10, by - 8);
            win.draw(label);
        }

        // Panel divider
        sf::RectangleShape div(sf::Vector2f(2, H));
        div.setPosition(PANEL, 0);
        div.setFillColor(sf::Color(0, 55, 25));
        win.draw(div);

        // Panel header
        sf::Text title("FLIGHT LIST", font, 13);
        title.setFillColor(sf::Color(0, 185, 85));
        title.setPosition(PANEL + 8, 8);
        win.draw(title);

        sf::Text tickTxt("TICK: " + std::to_string(tick) + (paused ? "  [PAUSED]" : ""), font, 11);
        tickTxt.setFillColor(paused ? sf::Color(255, 200, 0) : sf::Color(50, 90, 50));
        tickTxt.setPosition(PANEL + 8, 28);
        win.draw(tickTxt);

        sf::Text hint("SPACE = pause | click to select", font, 9);
        hint.setFillColor(sf::Color(35, 60, 35));
        hint.setPosition(PANEL + 8, 46);
        win.draw(hint);

        // Aircraft list rows
        for (int i = 0; i < (int)planes.size(); i++) {
            float ry = 60.f + i * 55.f;
            sf::Color col = statusColor(planes[i]->getStatus());
            bool em = planes[i]->getStatus() == EMERGENCY;

            if (i == selected) {
                sf::RectangleShape hi(sf::Vector2f(W - PANEL - 4, 53));
                hi.setPosition(PANEL + 2, ry);
                hi.setFillColor(sf::Color(18, 35, 22));
                win.draw(hi);
            }

            sf::Text model(planes[i]->getModel(), font, 12);
            model.setFillColor(sf::Color(195, 220, 195));
            model.setPosition(PANEL + 10, ry + 2);
            win.draw(model);

            std::string info = planes[i]->statusToString()
                + "  " + std::to_string(planes[i]->getAltitude()) + "ft"
                + "  " + std::to_string((int)planes[i]->getSpeed()) + "mph";
            sf::Text infoTxt(info, font, 10);
            infoTxt.setFillColor((em && flash) ? sf::Color::White : col);
            infoTxt.setPosition(PANEL + 10, ry + 19);
            win.draw(infoTxt);
        }

        // Status buttons (shown when something is selected)
        if (selected >= 0) {
            const char* labels[] = { "TAKEOFF", "LAND", "GROUND", "EMRGNCY" };
            AircraftStatus map[] = { TAKEOFF, LANDING, GROUNDED, EMERGENCY };
            for (int b = 0; b < 4; b++) {
                float bx = PANEL + 8 + b * 73;
                sf::Color bc = statusColor(map[b]);
                bool current = planes[selected]->getStatus() == map[b];

                sf::RectangleShape btn(sf::Vector2f(68, 28));
                btn.setPosition(bx, H - 50);
                btn.setFillColor(current ? sf::Color(bc.r/5, bc.g/5, bc.b/5) : sf::Color(12, 18, 24));
                btn.setOutlineColor(bc);
                btn.setOutlineThickness(1.5f);
                win.draw(btn);

                sf::Text btnTxt(labels[b], font, 11);
                btnTxt.setFillColor(bc);
                btnTxt.setPosition(bx + 4, H - 44);
                win.draw(btnTxt);
            }
        }

        win.display();
    }

    for (auto p : planes) delete p;
    return 0;
}
