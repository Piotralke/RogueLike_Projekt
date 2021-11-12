#include "Room.h"

int room::check_doors(int i, int j)
{
    int room_doors = 0b0000;
    if (grid[i][j - 1] == 1)
        room_doors ^= 0b0001;   //lewe drzwi
    if (grid[i][j + 1] == 1)
        room_doors ^= 0b0010;    //prawe drzwi
    if (grid[i + 1][j] == 1)
        room_doors ^= 0b0100;   //dolne drzwi
    if (grid[i - 1][j] == 1)
        room_doors ^= 0b1000;   //gorne drzwi
    return room_doors;

}
void room::Draw(sf::RenderWindow& window, sf::RectangleShape& door)
{
    window.draw(door);
}
void room::pick_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, int i, int j)
{
    doors_t.loadFromFile("grafiki/doors_o.png");
    sf::RectangleShape doors;
    doors.setSize({ 32, 32 });
    doors.setOrigin(doors.getSize() / 2.0f);
    int room_doors = check_doors(i, j);
    if (room_doors & 0b0001)
    {
        doors.setPosition(16, 200);
        doors.setTexture(&doors_t);
        doors.setRotation(-90.0f);
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors))
        {
            player.y--;
            player.body.setPosition({ 655, player.body.getPosition().y });
        }

    }
    if (room_doors & 0b0010)
    {
        doors.setPosition(684, 200);
        doors.setTexture(&doors_t);
        doors.setRotation(90.0f);
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors))
        {
            player.y++;
            player.body.setPosition({ 45, player.body.getPosition().y });
        }
    }
    if (room_doors & 0b0100)
    {
        doors.setPosition(350, 384);
        doors.setTexture(&doors_t);
        doors.setRotation(180.0f);
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors))
        {
            player.x++;
            player.body.setPosition({ player.body.getPosition().x, 45 });
        }
    }
    if (room_doors & 0b1000)
    {
        doors.setPosition(350, 16);
        doors.setTexture(&doors_t);
        doors.setRotation(0.0f);
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors))
        {
            player.x--;
            player.body.setPosition({ player.body.getPosition().x, 355 });
        }
    }
}