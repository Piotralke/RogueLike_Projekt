#include "Room.h"

void room::init_Texture() {
    wizardTexture.loadFromFile("grafiki/wizard_animation.png");
    ghostTexture.loadFromFile("grafiki/ghost_animation.png");
    rockTexture.loadFromFile("grafiki/rock.png");
    bonesTexture.loadFromFile("grafiki/bone_pile.png");
}

int room::check_doors(int i, int j)
{
    int room_doors = 0b0000;
    if (grid[i][j - 1].exist == 1)
        room_doors ^= 0b0001;   //lewe drzwi
    if (grid[i][j + 1].exist == 1)
        room_doors ^= 0b0010;    //prawe drzwi
    if (grid[i + 1][j].exist == 1)
        room_doors ^= 0b0100;   //dolne drzwi
    if (grid[i - 1][j].exist == 1)
        room_doors ^= 0b1000;   //gorne drzwi
    return room_doors;

}
void room::Draw(sf::RenderWindow& window, sf::RectangleShape& door)
{
    window.draw(door);
}

void room::read_from_file(hero& player, std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC)
{
    std::ifstream read(grid[player.x][player.y].sciezka);
    
    if (read.is_open())
    {
        
        char znak;
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                read >> znak;
                if (znak == '0')        //0-9 MONSTER
                {
                    if (!grid[player.x][player.y].visited)
                    {
                        monster wizard(&wizardTexture, sf::Vector2u(4, 1), 0.1f, 0.0f, 1.5f, 150.0f, 30.0f, 10.0f, { 16.0f,20.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true);
                        monsterVEC.push_back(wizard);
                    }
                    
                }
                else if (znak == '1')
                {
                    if (!grid[player.x][player.y].visited)
                    {
                        monster ghost(&ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, false);
                        monsterVEC.push_back(ghost);
                    }
                   
                }
                else if (znak == '2')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == '3')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == '4')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == '5')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == '6')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == '7')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == '8')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == '9')
                {
                    if (!grid[player.x][player.y].visited)
                    {

                    }
                }
                else if (znak == 'a')
                {
                    Object rock(&rockTexture, { 50.0f + 30 * j,50.0f + 30 * i }, {30.0f,30.0f});
                    objectVEC.push_back(rock);
                }
                else if (znak == 'b')
                {
                    Object bones(&bonesTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 30.0f,30.0f });
                    objectVEC.push_back(bones);
                }
                else if (znak == 'c')
                {

                }
                else if (znak == 'd')
                {

                }
                else if (znak == 'e')
                {

                }
                else if (znak == 'A')
                {

                }
                else if (znak == 'B')
                {

                }
                else if (znak == 'C')
                {

                }
                else if (znak == 'D')
                {

                }
                else if (znak == 'E')
                {

                }
            }
        }
    }
}

void room::pick_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, std::vector<Bullet>& heroB, std::vector<Bullet>& monsterB, std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC)
{
    if (!monsterVEC.empty())
    {
        doors_t.loadFromFile("grafiki/doors_c.png");
        doors_bs_t.loadFromFile("grafiki/doors_boss_c.png");
        doors_sh_t.loadFromFile("grafiki/doors_shop_c.png");
        doors_it_t.loadFromFile("grafiki/doors_item_c.png");
    }
    else
    {
        doors_t.loadFromFile("grafiki/doors_o.png");
        doors_bs_t.loadFromFile("grafiki/doors_boss_o.png");
        doors_sh_t.loadFromFile("grafiki/doors_shop_o.png");
        doors_it_t.loadFromFile("grafiki/doors_item_o.png");
    }

    sf::RectangleShape doors;
    doors.setSize({ 32, 32 });
    doors.setOrigin(doors.getSize() / 2.0f);
    int room_doors = check_doors(player.x, player.y);
    //losowanie layaout, o ile nie odwiedzony pokoj
    if (room_doors & 0b0001)
    {
        doors.setPosition(19, 200);
        doors.setRotation(-90.0f);
        if (grid[player.x][player.y - 1].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x][player.y - 1].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x][player.y - 1].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors) && monsterVEC.empty())
        {
            player.y--;
            player.body.setPosition({ 655, player.body.getPosition().y });
            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            read_from_file(player,monsterVEC,objectVEC);
            grid[player.x][player.y].visited = true;
        }

    }
    if (room_doors & 0b0010)
    {
        doors.setPosition(681, 200);
        doors.setRotation(90.0f);
        if (grid[player.x][player.y + 1].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x][player.y + 1].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x][player.y + 1].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors)&&monsterVEC.empty())
        {

            player.y++;
            player.body.setPosition({ 45, player.body.getPosition().y });
            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            read_from_file(player, monsterVEC, objectVEC);
            grid[player.x][player.y].visited = true;
        }
    }
    if (room_doors & 0b0100)
    {
        doors.setPosition(350, 381);
        doors.setRotation(180.0f);
        if (grid[player.x+1][player.y].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x+1][player.y].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x+1][player.y].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors) && monsterVEC.empty())
        {

            player.x++;
            player.body.setPosition({ player.body.getPosition().x, 45 });
            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            read_from_file(player, monsterVEC, objectVEC);
            grid[player.x][player.y].visited = true;
        }
    }
    if (room_doors & 0b1000)
    {
        doors.setPosition(350, 19);
        doors.setRotation(0.0f);
        if (grid[player.x - 1][player.y].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x - 1][player.y].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x - 1][player.y].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors) && monsterVEC.empty())
        {

            player.x--;
            player.body.setPosition({ player.body.getPosition().x, 355 });
            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            read_from_file(player, monsterVEC, objectVEC);
            grid[player.x][player.y].visited = true;
        }
    }
}