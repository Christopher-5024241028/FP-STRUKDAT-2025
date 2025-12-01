#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float MIN_RADIUS = 5.0f;
const float MAX_RADIUS = 20.0f;
const float MAX_INITIAL_VELOCITY = 100.0f;
const int INITIAL_PARTICLE_COUNT = 10;

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

void handleParticleCollision(Particle& p1, Particle& p2) {
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

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "C++ Particle Collision (5 Colors)");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    sf::Clock clock;

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
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    particles.push_back(createNewParticle((float)event.mouseButton.x, (float)event.mouseButton.y));
                }
            }
        }

        for (auto& p : particles) {
            p.update(deltaTime);
            handleBoundaryCollision(p);
        }
        
        for (size_t i = 0; i < particles.size(); ++i) {
            for (size_t j = i + 1; j < particles.size(); ++j) {
                handleParticleCollision(particles[i], particles[j]);
            }
        }

        window.clear(sf::Color::Black);

        for (const auto& p : particles) {
            sf::CircleShape shape(p.radius);
            shape.setFillColor(p.color);
            shape.setOrigin(p.radius, p.radius); 
            shape.setPosition(p.position);
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}
