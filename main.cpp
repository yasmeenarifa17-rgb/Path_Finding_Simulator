#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <cmath>
#include <map>

const int WINDOW_SIZE = 800;
const int GRID_SIZE = 40;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

enum State { EMPTY, WALL, START, END, VISITED, PATH, OPEN };

struct Node {
    int x, y;
    float g, h;
    Node* parent = nullptr;
    float f() const { return g + h; }
};

float heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "AI Pathfinding Visualizer");
    std::vector<std::vector<State>> grid(GRID_SIZE, std::vector<State>(GRID_SIZE, EMPTY));
    
    int startX = 5, startY = 5, endX = 35, endY = 35;
    grid[startX][startY] = START;
    grid[endX][endY] = END;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Interactive Wall Placement
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                int x = pos.x / CELL_SIZE, y = pos.y / CELL_SIZE;
                if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE)
                    if (grid[x][y] == EMPTY) grid[x][y] = WALL;
            }

            // Start Animation on Space
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                auto compare = [](Node* a, Node* b) { return a->f() > b->f(); };
                std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
                
                Node* startNode = new Node{startX, startY, 0, heuristic(startX, startY, endX, endY)};
                openSet.push(startNode);

                while (!openSet.empty()) {
                    Node* current = openSet.top();
                    openSet.pop();

                    if (current->x == endX && current->y == endY) {
                        while (current) {
                            grid[current->x][current->y] = PATH;
                            current = current->parent;
                        }
                        break;
                    }

                    if (grid[current->x][current->y] != START) grid[current->x][current->y] = VISITED;

                    int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
                    for (int i = 0; i < 4; i++) {
                        int nx = current->x + dx[i], ny = current->y + dy[i];
                        if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && (grid[nx][ny] == EMPTY || grid[nx][ny] == END)) {
                            if (grid[nx][ny] == EMPTY) grid[nx][ny] = OPEN;
                            openSet.push(new Node{nx, ny, current->g + 1, heuristic(nx, ny, endX, endY), current});
                        }
                    }

                    // Refresh Window for Animation Effect
                    window.clear();
                    for (int i = 0; i < GRID_SIZE; i++) {
                        for (int j = 0; j < GRID_SIZE; j++) {
                            sf::RectangleShape rect(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                            rect.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                            if (grid[i][j] == WALL) rect.setFillColor(sf::Color::Black);
                            else if (grid[i][j] == START) rect.setFillColor(sf::Color::Green);
                            else if (grid[i][j] == END) rect.setFillColor(sf::Color::Red);
                            else if (grid[i][j] == VISITED) rect.setFillColor(sf::Color(100, 149, 237)); // Cornflower Blue
                            else if (grid[i][j] == OPEN) rect.setFillColor(sf::Color(173, 216, 230));    // Light Blue
                            else if (grid[i][j] == PATH) rect.setFillColor(sf::Color::Yellow);
                            else rect.setFillColor(sf::Color::White);
                            window.draw(rect);
                        }
                    }
                    window.display();
                    sf::sleep(sf::milliseconds(5)); // Controls animation speed
                }
            }
        }
        window.display();
    }
    return 0;
}
