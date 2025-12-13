#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream> 
#include <iomanip>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float MIN_RADIUS = 5.0f;
const float MAX_RADIUS = 20.0f;
const float MAX_INITIAL_VELOCITY = 100.0f;
const int INITIAL_PARTICLE_COUNT = 700;

const int QT_CAPACITY = 4;

enum CollisionMode { BRUTE_FORCE, QUADTREE_MODE };

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    float mass;
    sf::Color color;

    void calculateMass() {
        mass = radius * radius * 0.01f;
    }

    void update(float deltaTime) {
        position += velocity * deltaTime;
    }
};
// --- STRUKTUR QUADTREE ---
struct Quadtree {
    sf::FloatRect boundary;
    int capacity;
    std::vector<Particle*> particles;
    bool divided = false;

    Quadtree* northwest = nullptr;
    Quadtree* northeast = nullptr;
    Quadtree* southwest = nullptr;
    Quadtree* southeast = nullptr;

    Quadtree(const sf::FloatRect& bounds, int cap) : boundary(bounds), capacity(cap) {}

    ~Quadtree() {
        delete northwest;
        delete northeast;
        delete southwest;
        delete southeast;
    }

    void subdivide() {
        float x = boundary.left;
        float y = boundary.top;
        float w = boundary.width / 2.0f;
        float h = boundary.height / 2.0f;

        northwest = new Quadtree(sf::FloatRect(x, y, w, h), capacity);
        northeast = new Quadtree(sf::FloatRect(x + w, y, w, h), capacity);
        southwest = new Quadtree(sf::FloatRect(x, y + h, w, h), capacity);
        southeast = new Quadtree(sf::FloatRect(x + w, y + h, w, h), capacity);
        
        divided = true;
    }

    bool insert(Particle* p) {
        if (!boundary.contains(p->position)) {
            return false;
        }

        if (particles.size() < capacity) {
            particles.push_back(p);
            return true;
        }

        if (!divided) {
            subdivide();
        }

        if (northwest->insert(p)) return true;
        if (northeast->insert(p)) return true;
        if (southwest->insert(p)) return true;
        if (southeast->insert(p)) return true;

        return false;
    }

    void query(std::vector<Particle*>& found, const sf::FloatRect& range) {
        if (!boundary.intersects(range)) {
            return;
        }

        for (Particle* p : particles) {
            if (p->position.x >= range.left && p->position.x <= (range.left + range.width) &&
                p->position.y >= range.top && p->position.y <= (range.top + range.height)) {
                found.push_back(p);
            }
        }

        if (divided) {
            northwest->query(found, range);
            northeast->query(found, range);
            southwest->query(found, range);
            southeast->query(found, range);
        }
    }
};

sf::Color getRandomColor() {
    int choice = rand() % 5;
    switch (choice) {
        case 0: return sf::Color::Red;
        case 1: return sf::Color::Blue;
        case 2: return sf::Color::Green;
        case 3: return sf::Color(255, 192, 203);
        case 4: return sf::Color(128, 0, 128);
        default: return sf::Color::White;
    }
}

float getRandomRadius() {
    float diff = MAX_RADIUS - MIN_RADIUS;
    return MIN_RADIUS + (float)rand() / (RAND_MAX / diff);
}

sf::Vector2f getRandomVelocity() {
    float vx = (float)(rand() % (int)(2 * MAX_INITIAL_VELOCITY) - MAX_INITIAL_VELOCITY);
    float vy = (float)(rand() % (int)(2 * MAX_INITIAL_VELOCITY) - MAX_INITIAL_VELOCITY);
    return sf::Vector2f(vx, vy);
}

Particle createNewParticle(float x, float y) {
    Particle p;
    p.position = sf::Vector2f(x, y);
    p.radius = getRandomRadius();
    p.calculateMass();
    p.color = getRandomColor();
    p.velocity = getRandomVelocity(); 
    return p;
}

void handleCollision(Particle& p1, Particle& p2) {
    sf::Vector2f normal = p1.position - p2.position;
    float distSq = normal.x * normal.x + normal.y * normal.y;
    float dist = std::sqrt(distSq);
    float minSeparation = p1.radius + p2.radius;

    if (dist < minSeparation) {
        float overlap = minSeparation - dist;
        sf::Vector2f unitNormal = normal / dist;

        p1.position += unitNormal * (overlap * (p2.mass / (p1.mass + p2.mass)));
        p2.position -= unitNormal * (overlap * (p1.mass / (p1.mass + p2.mass)));

        sf::Vector2f relativeVelocity = p1.velocity - p2.velocity;
        float velAlongNormal = relativeVelocity.x * unitNormal.x + relativeVelocity.y * unitNormal.y;

        if (velAlongNormal > 0) return;

        float e = 1.0f;
        float j = (-(1.0f + e) * velAlongNormal) / (1.0f / p1.mass + 1.0f / p2.mass);
        
        sf::Vector2f impulse = j * unitNormal;
        p1.velocity += impulse / p1.mass;
        p2.velocity -= impulse / p2.mass;
    }
}

void handleBoundaryCollision(Particle& p) {
    if (p.position.x - p.radius < 0) {
        p.position.x = p.radius;
        p.velocity.x = -p.velocity.x;
    } else if (p.position.x + p.radius > WINDOW_WIDTH) {
        p.position.x = WINDOW_WIDTH - p.radius;
        p.velocity.x = -p.velocity.x;
    }

    if (p.position.y - p.radius < 0) {
        p.position.y = p.radius;
        p.velocity.y = -p.velocity.y;
    } else if (p.position.y + p.radius > WINDOW_HEIGHT) {
        p.position.y = WINDOW_HEIGHT - p.radius;
        p.velocity.y = -p.velocity.y;
    }
}


// --- 1. MODE BRUTE FORCE (O(N^2)) ---
void processBruteForce(std::vector<Particle>& particles) {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            handleCollision(particles[i], particles[j]);
        }
    }
}

// --- 2. MODE QUADTREE ---
void processQuadtree(std::vector<Particle>& particles) {
    Quadtree qt(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), QT_CAPACITY);
    
    std::vector<Particle*> p_pointers;
    for (auto& p : particles) {
        p_pointers.push_back(&p);
    }

    for (Particle* p : p_pointers) {
        qt.insert(p);
    }

    for (size_t i = 0; i < particles.size(); ++i) {
        Particle& p1 = particles[i];
        
        float searchSize = MAX_RADIUS * 2.5f; 
        sf::FloatRect range(p1.position.x - searchSize, 
                            p1.position.y - searchSize, 
                            searchSize * 2, 
                            searchSize * 2);

        std::vector<Particle*> neighbors;
        qt.query(neighbors, range);

        for (Particle* p_neighbor : neighbors) {
            Particle& p2 = *p_neighbor;
            
            if (&p1 == &p2) continue;
            
            handleCollision(p1, p2);
        }
    }
}

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Collision Mode Switcher");

    std::vector<Particle> particles;
    sf::Clock clock;
    sf::Clock fpsClock;
    int frameCount = 0;

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) { 
        std::cerr << "Peringatan: Gagal memuat font sistem. Teks FPS/Mode mungkin tidak terlihat." << std::endl;
        
    }
    
    // Text Mode
    sf::Text modeText;
    modeText.setFont(font);
    modeText.setCharacterSize(18);
    modeText.setFillColor(sf::Color::White);
    modeText.setPosition(10, 10);

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(18);
    fpsText.setFillColor(sf::Color::Yellow);
    fpsText.setPosition(10, 30);

    CollisionMode currentMode = BRUTE_FORCE;

    for (int i = 0; i < INITIAL_PARTICLE_COUNT; ++i) {
        float randX = (float)(rand() % (WINDOW_WIDTH - (int)MAX_RADIUS * 2) + MAX_RADIUS);
        float randY = (float)(rand() % (WINDOW_HEIGHT - (int)MAX_RADIUS * 2) + MAX_RADIUS);
        particles.push_back(createNewParticle(randX, randY));
    }

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Switch Mode saat tombol TAB ditekan
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab) {
                if (currentMode == BRUTE_FORCE) {
                    currentMode = QUADTREE_MODE;
                } else {
                    currentMode = BRUTE_FORCE;
                }
            }
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                particles.push_back(createNewParticle((float)event.mouseButton.x, (float)event.mouseButton.y));
            }
        }
        
        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            float fps = frameCount / fpsClock.getElapsedTime().asSeconds();
            std::stringstream ss;
            ss << "FPS: " << std::fixed << std::setprecision(0) << fps; 
            fpsText.setString(ss.str());
            
            frameCount = 0;
            fpsClock.restart();
        }

        for (auto& p : particles) {
            p.update(deltaTime);
            handleBoundaryCollision(p);
        }
        
        if (currentMode == BRUTE_FORCE) {
            processBruteForce(particles);
            modeText.setString("Mode: BRUTE FORCE | Partikel: " + std::to_string(particles.size()));
        } else {
            processQuadtree(particles);
            modeText.setString("Mode: QUADTREE | Partikel: " + std::to_string(particles.size()));
        }

        window.clear(sf::Color::Black);

        for (const auto& p : particles) {
            sf::CircleShape shape(p.radius);
            shape.setFillColor(p.color);
            shape.setOrigin(p.radius, p.radius); 
            shape.setPosition(p.position);
            window.draw(shape);
        }
        window.draw(modeText);
        window.draw(fpsText); 
        
        window.display();
    }

    return 0;
}
