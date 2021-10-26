#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <iostream>

#define SIZE 11

class object
{
    private:
        int x, y;
        int obj_type;
        // tekstura(?)
};

class Animation {
    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;
        float totalTime;
        float switchTime;
    public:
        sf::IntRect uvRect;
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
        {
            this->imageCount = imageCount;
            this->switchTime = switchTime;
            totalTime = 0.0f;
            currentImage.x = 0;

            uvRect.width = texture->getSize().x / float(imageCount.x);
            uvRect.height = texture->getSize().y / float(imageCount.y);
        }
        void Update(int row, float deltaTime, bool faceRight)
        {
            currentImage.y = row;
            totalTime += deltaTime;

            if (totalTime >= switchTime)
            {
                totalTime -= switchTime;
                currentImage.x++;
                if (currentImage.x >= imageCount.x)
                {
                    currentImage.x = 0;
                }
            }
            
            uvRect.top = currentImage.y * uvRect.height;

            if (faceRight)
            {
                uvRect.left = currentImage.x * uvRect.width;
                uvRect.width = abs(uvRect.width);
            }
            else
            {
                uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
                uvRect.width = -abs(uvRect.width);
            }
                
        }

};
class hero
{
    protected:
        sf::Vector2f pos;
        sf::Vector2f vel = {0.0f,0.0f};
        sf::Texture texture;
        sf::Sprite sprite;
        float speed = 20.0f;
        float health;
        float damage;
        sf::RectangleShape body;
        Animation animation;
        bool faceRight;
        unsigned int row;
        float fire_rate;
        //float shot_speed; (?)
        float range;
    public:
        hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
            animation(texture,imageCount,switchTime)
        {
            this->speed = speed;
            row = 0;
            faceRight = true;

            body.setSize(sf::Vector2f(16.0f, 28.0f));
            body.setPosition(100.0f, 100.0f);
            body.setTexture(texture);
        }
        void Draw(sf::RenderWindow& window)
        {
            window.draw(body);
        }
        void Update(float deltaTime)
        {
            sf::Vector2f movement(0.0f, 0.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                movement.y -= speed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                movement.y += speed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                movement.x -= speed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                movement.x += speed * deltaTime;
            }

            if (movement.x == 0.0f)
            {
                row = 0;
            }
            else
            {
                row = 1;
                if (movement.x > 0.0f)
                    faceRight = true;
                else
                    faceRight = false;
            }
            if (movement.y != 0.0f)
                row = 1;

            animation.Update(row, deltaTime, faceRight);
            body.setTextureRect(animation.uvRect);
            body.move(movement);


        }
        void shot(float vec_x, float vec_y) //albo jakis jeden argument, jasli strzelanie byloby tylko pod katem prostym
        {
            // strzelenie w kierunku w ktorym patrzymy od pozycji gracza
        }
        void move(int x_dir, int y_dir)
        {
            //modyfikacja pozycji gracza w zaleznosci od kierunku poruszania sie
        }
};

class monster : public hero
{
    int type;
};

class room 
{
    protected:
        
        int grid[SIZE][SIZE];
        int room_type;

public:
    sf::Texture background_t;
    sf::Sprite background_s;
    int check_doors(int i, int j)
    {
        int room_doors = 0b0000;
        if (grid[i - 1][j])     
            room_doors += 0b0001;   //lewe drzwi
        if (grid[i + 1][j])    
            room_doors += 0b0010;    //prawe drzwi
        if (grid[i][j + 1])     
            room_doors += 0b0100;   //dolne drzwi
        if (grid[i][j - 1])      
            room_doors += 0b1000;   //gorne drzwi
        return room_doors;

    }
    bool pick_room_layout(int room_doors)
    {
        switch (room_doors)
        {
        case 0b0001:    //L
            background_t.loadFromFile("grafiki/background_0001o.png",sf::IntRect(0,0,700,400));
            break;                              
        case 0b0010:    //P
            background_t.loadFromFile("grafiki/background_0010o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0011:    //LP
            background_t.loadFromFile("grafiki/background_0011o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0100:    //D
            background_t.loadFromFile("grafiki/background_0001o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0101:    //LD
            background_t.loadFromFile("grafiki/background_0101o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0110:    //PD
            background_t.loadFromFile("grafiki/background_0110o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0111:    //PLD
            background_t.loadFromFile("grafiki/background_0111o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1000:    //G
            background_t.loadFromFile("grafiki/background_1000o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1001:    //GL
            background_t.loadFromFile("grafiki/background_1001o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1010:    //GP
            background_t.loadFromFile("grafiki/background_1010o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1011:    //GPL
            background_t.loadFromFile("grafiki/background_1011o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1100:    //GD
            background_t.loadFromFile("grafiki/background_1100o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1101:    //GDL
            background_t.loadFromFile("grafiki/background_1101o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1110:    //GDP
            background_t.loadFromFile("grafiki/background_1110o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1111:    //GDLP - wszystkie 4 drzwi
            if (!background_t.loadFromFile("grafiki/background_1111o.png", sf::IntRect(0, 0, 700, 400)))
                return EXIT_FAILURE;
            break;
        }
        background_s.setTexture(background_t);
    }
};

class generate_map : public room
{
    protected:
        
        int rooms_counter=0;
        int max_rooms;
        int min_rooms;
        std::queue <int> RoomQueue_i;
        std::queue <int> RoomQueue_j;
        std::stack <int> DeadEnd_i;
        std::stack <int> DeadEnd_j;
        bool placedSpecial = false;

    public:
        void init_grid()
        {
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    grid[i][j] = 0;
        }
        void max_level_counter(int level)
        {
            min_rooms = 20 + level * 1;
            max_rooms = min_rooms + 6;
        }
        int neighbour_count(int i, int j)
        {
            return grid[i - 1][j] + grid[i][j - 1] + grid[i + 1][j] + grid[i][j + 1];
        }
        bool visit(int i, int j)
        {
            
            if (grid[i][j])
                return false;

            int neigbours = neighbour_count(i, j);

            if (neigbours > 1)
                return false;

            if (rooms_counter >= max_rooms)
                return false;

            if (rand() % 101 > 80 && i != 5 || rand() % 101 > 80 && j != 5)
                return false;

            RoomQueue_i.push(i);
            RoomQueue_j.push(j);
            grid[i][j] = 1;
            rooms_counter++;

            return true;
        }
        void wypisz()
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                    std::cout << grid[i][j] << " ";
                std::cout << std::endl;
            }
            
        }
        bool generate_layout()
        {
            while (rooms_counter < max_rooms || rooms_counter >min_rooms)
            {
                if (RoomQueue_i.size() > 0 && RoomQueue_j.size() > 0)
                {
                    int i = RoomQueue_i.front();
                    RoomQueue_i.pop();
                    int j = RoomQueue_j.front();
                    RoomQueue_j.pop();
                    bool created = false;
                    if (i > 0)
                        created = created | visit(i - 1, j);
                    if (i < SIZE)
                        created = created | visit(i + 1, j);
                    if (j > 0)
                        created = created | visit(i, j - 1);
                    if (j < SIZE)
                        created = created | visit(i, j + 1);
                    if (!created)
                    {
                        DeadEnd_i.push(i);
                        DeadEnd_j.push(j);
                    }
                }
                else if (!placedSpecial)
                {
                    if (rooms_counter >= min_rooms && DeadEnd_i.size() > 2)
                    {
                        placedSpecial = true;
                        room* Boss_room = new room;
                    Boss_room:grid[DeadEnd_i.top()][DeadEnd_j.top()];
                        grid[DeadEnd_i.top()][DeadEnd_j.top()] = 2;
                        DeadEnd_i.pop();
                        DeadEnd_j.pop();

                        room* Shop = new room;
                    Shop:grid[DeadEnd_i.top()][DeadEnd_j.top()];
                        grid[DeadEnd_i.top()][DeadEnd_j.top()] = 3;
                        DeadEnd_i.pop();
                        DeadEnd_j.pop();

                        room* Item_Room = new room;
                    Item_Room:grid[DeadEnd_i.top()][DeadEnd_j.top()];
                        grid[DeadEnd_i.top()][DeadEnd_j.top()] = 4;
                        DeadEnd_i.pop();
                        DeadEnd_j.pop();

                        return true;
                    }
                }
            }
            
        }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "RogueLike!");
    generate_map* level = new generate_map;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("grafiki/hero_animation.png");
    hero player(&playerTexture, sf::Vector2u(4, 2), 0.1f, 100.0f);
    level->init_grid();
    level->max_level_counter(1);
    level->visit(5, 5);
    level->generate_layout();
    level->pick_room_layout(0b1111);
    level->wypisz();

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        { 
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(deltaTime);

        window.clear();
        window.draw(level->background_s);
        player.Draw(window);
        window.display();
    }

    return 0;
}
