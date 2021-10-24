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

class hero
{
    protected:
        int x, y;
        int health;
        float damage;
        float speed;
        float fire_rate;
        //float shot_speed; (?)
        float range;
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
        sf::Texture background;
        switch (room_doors)
        {
        case 0b0001:    //L
            background.loadFromFile("grafiki/background_0001o.png",sf::IntRect(0,0,700,400));
            break;                              
        case 0b0010:    //P
            background.loadFromFile("grafiki/background_0010o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0011:    //LP
            background.loadFromFile("grafiki/background_0011o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0100:    //D
            background.loadFromFile("grafiki/background_0001o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0101:    //LD
            background.loadFromFile("grafiki/background_0101o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0110:    //PD
            background.loadFromFile("grafiki/background_0110o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b0111:    //PLD
            background.loadFromFile("grafiki/background_0111o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1000:    //G
            background.loadFromFile("grafiki/background_1000o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1001:    //GL
            background.loadFromFile("grafiki/background_1001o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1010:    //GP
            background.loadFromFile("grafiki/background_1010o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1011:    //GPL
            background.loadFromFile("grafiki/background_1011o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1100:    //GD
            background.loadFromFile("grafiki/background_1100o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1101:    //GDL
            background.loadFromFile("grafiki/background_1101o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1110:    //GDP
            background.loadFromFile("grafiki/background_1110o.png", sf::IntRect(0, 0, 700, 400));
            break;
        case 0b1111:    //GDLP - wszystkie 4 drzwi
            if (!background.loadFromFile("grafiki/background_1111o.png"))
                return EXIT_FAILURE;
            break;
        }
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
    level->init_grid();
    level->max_level_counter(1);
    level->visit(5, 5);
    level->generate_layout();
    //level->pick_room_layout(0b1111);
    sf::Texture background;
    if (!background.loadFromFile("background_1111o.jpg"))
        return EXIT_FAILURE;
    level->wypisz();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}