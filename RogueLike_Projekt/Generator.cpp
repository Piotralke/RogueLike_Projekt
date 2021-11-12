#include "Generator.h"

generate_map::generate_map()
{
    background_t.loadFromFile("grafiki/background.png", sf::IntRect(0, 0, 700, 400));
    background_s.setTexture(background_t);
}
void generate_map::init_grid()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            grid[i][j] = 0;
}
void generate_map::max_level_counter(int level)
{
    min_rooms = 20 + level * 1;
    max_rooms = min_rooms + 6;
}
int generate_map::neighbour_count(int i, int j)
{
    return grid[i - 1][j] + grid[i][j - 1] + grid[i + 1][j] + grid[i][j + 1];
}
bool generate_map::visit(int i, int j)
{

    if (grid[i][j])
        return false;

    int neigbours = neighbour_count(i, j);

    if (neigbours > 1)
        return false;

    if (rooms_counter >= max_rooms)
        return false;

    int random = std::rand() % 2;
    if (i != 5 && j == 5 || i == 5 && j != 5)
    {
        if (random > 0 && i != 5 || random > 0 && j != 5)
            return false;
    }

    RoomQueue_i.push(i);
    RoomQueue_j.push(j);
    grid[i][j] = 1;
    rooms_counter++;

    return true;
}
void generate_map::wypisz()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            std::cout << grid[i][j] << " ";
        std::cout << std::endl;
    }

}
bool generate_map::generate_layout()
{
    int i, j;
    while (rooms_counter < max_rooms && !(rooms_counter > min_rooms))
    {
        if (RoomQueue_i.size() > 0 && RoomQueue_j.size() > 0)
        {
            i = RoomQueue_i.front();
            RoomQueue_i.pop();
            j = RoomQueue_j.front();
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
            if (RoomQueue_i.empty())
            {
                RoomQueue_i.push(i);
                RoomQueue_j.push(j);
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