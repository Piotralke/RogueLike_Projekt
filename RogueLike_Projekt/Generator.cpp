#include "Generator.h"

/** \brief Konstruktor dla generatora mapy
 *
 */

generate_map::generate_map()
{
    background_t.loadFromFile("grafiki/background.png", sf::IntRect(0, 0, 700, 400));
    background_s.setTexture(background_t);
    minimap_room.setSize({ 8.0f,8.0f });
    minimap_rt.loadFromFile("grafiki/minimap_room.png");
    minimap_room.setTexture(&minimap_rt);
    hero_minimap.loadFromFile("grafiki/hero_minimap.png");
    hero_m.setTexture(&hero_minimap);
    hero_m.setSize({ 6.0f,4.0f });
}

/** \brief Funkcja zwracaj¹ca wylosowan¹ œcie¿kê do uk³adu dla danego pokoju
 *
 * @param i Parametr i pokoju
 * @param j Parametr j pokoju
 * @return path zwracana wylosowana œcie¿ka
 */

std::string generate_map::random_layout(int i, int j)
{
    std::string path;
    std::string liczba;
    path = "layouts/";
    switch (check_doors(i, j)) {
    case 0b0001:
        path += "0001/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b0010:
        path += "0010/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b0011:
        path += "0011/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b0100:
        path += "0100/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b0101:
        path += "0101/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b0110:
        path += "0110/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b0111:
        path += "0111/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1000:
        path += "1000/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1001:
        path += "1001/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1010:
        path += "1010/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1011:
        path += "1011/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1100:
        path += "1100/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1101:
        path += "1101/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1110:
        path += "1110/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    case 0b1111:
        path += "1111/";
        liczba = std::to_string(std::rand() % 9);
        path += liczba;
        path += ".txt";
        break;
    }
    return path;
}

/** \brief Funkcja wype³niaj¹ca zerami nasz¹ strukturê poziomu
 *
 */

void generate_map::init_grid()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j].exist = 0;
            grid[i][j].type = 0;
            grid[i][j].visited = false;
        }
    grid[5][5].visited = true;
           
}

/** \brief Funkcja ustalaj¹ca maskymaln¹ i minimaln¹ iloœæ pokojów na danym poziomie
 *
 * @param level Numer poziomu na którym siê aktualnie znajdujemy
 */

void generate_map::max_level_counter(int level)
{
    min_rooms = 20 + level * 1;
    max_rooms = min_rooms + 6;
}

/** \brief Funkcja zliczaj¹ca iloœæ s¹siadów danego pokoju
 *
 * @param i Parametr i pokoju
 * @param j Parametr j pokoju
 * @return grid[i - 1][j].exist + grid[i][j - 1].exist + grid[i + 1][j].exist + grid[i][j + 1].exist zwraca iloœæ s¹siadów danego pokoju
 */

int generate_map::neighbour_count(int i, int j)
{
    return grid[i - 1][j].exist + grid[i][j - 1].exist + grid[i + 1][j].exist + grid[i][j + 1].exist;
}

/** \brief Funkcja tworz¹ca pokój
 *
 * @param i Parametr i pokoju
 * @param j Parametr j pokoju
 * @return false je¿eli nie stworzy³ pokój
 * @return true je¿eli stworzy³ pokój
 */

bool generate_map::visit(int i, int j)
{

    if (grid[i][j].exist)
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
    RoomQueue.push({ i,j });
    grid[i][j].exist = 1;
    grid[i][j].type = 1;
    rooms_counter++;

    return true;
}

/** \brief Funkcja wypisuj¹ca mape poziomu w konsoli
 *
 */

void generate_map::wypiszkons()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << grid[i][j].type;
        }
        std::cout << std::endl;
    }
}

/** \brief Funkcja wypisuj¹ca mape poziomu w HUDzie gry
* 
 * @param window WskaŸnik na okno, w którym ma wypisaæ statystyki
 * @param player WskaŸnik na postaæ g³ówn¹
 */

void generate_map::wypisz(sf::RenderWindow& window, hero& player)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j].exist == 1 && grid[i][j].visited)
            {
               
                minimap_room.setPosition({ 706.0f + j * 8,6.0f + i * 8 });
                window.draw(minimap_room);
            }
        }
    }
    hero_m.setPosition({ 707.0f + player.y * 8, 8.0f + player.x * 8 });
    window.draw(hero_m);
}

/** \brief G³ówna funkcja generuj¹ca rozk³ad pokojów w poziomu
* 
 * Funkcja, która wywo³uje wszystkie wczeœniej zdefiniowane funkcje z tej klasy do wygenerowania nowego rozk³adu poziomu
 */

void generate_map::generate_layout()
{
    sf::Vector2i i;
    while (rooms_counter < max_rooms && !(rooms_counter > min_rooms))
    {
        if (RoomQueue.size()>0)
        {
            i = RoomQueue.front();
            RoomQueue.pop();
            bool created = false;
            if (i.x > 0)
                created = created | visit(i.x - 1, i.y);
            if (i.x < SIZE)
                created = created | visit(i.x + 1, i.y);
            if (i.y > 0)
                created = created | visit(i.x, i.y - 1);
            if (i.y < SIZE)
                created = created | visit(i.x, i.y + 1);
            if (RoomQueue.empty())
            {
                RoomQueue.push(i);
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j].exist == 1 && neighbour_count(i, j) == 1)
                DeadEnd.push_back({ i,j });
        }
    }
   // wypiszkons();
   // std::cout << rooms_counter << std::endl;
   // std::cout << DeadEnd.size() << std::endl;
     
         sf::Vector2i max = DeadEnd.at(0);
         float max_distance=0;
         int max_pos = 0;
         for (int i = 0; i < DeadEnd.size(); i++)
         {
             float distance = sqrt((pow(5-DeadEnd.at(i).x, 2) + pow(5-DeadEnd.at(i).y,2)));
             if (distance > max_distance)
             {
                 max_pos = i;
                 max = DeadEnd.at(i);
                 std::swap(distance, max_distance);
             }
         }
         grid[max.x][max.y].type = 2;              // boss room
         DeadEnd.erase(DeadEnd.begin()+max_pos);
         bool okay = true;
         do
         {
             int random = std::rand() % DeadEnd.size();
             if (DeadEnd.at(random).x != 5 && DeadEnd.at(random).y != 5)
             {
                 grid[DeadEnd.at(random).x][DeadEnd.at(random).y].type = 3; //sklep
                 DeadEnd.erase(DeadEnd.begin() + random);
                 okay = false;
             }
         } while (okay);
         okay = true;
                                            
         do
         {
             int random = std::rand() % DeadEnd.size();
             if (DeadEnd.at(random).x != 5 && DeadEnd.at(random).y != 5)
             {
                 grid[DeadEnd.at(random).x][DeadEnd.at(random).y].type = 4; //pokoj z przedmiotem
                 DeadEnd.erase(DeadEnd.begin() + random);
                 okay = false;
             }
         } while (okay);

         
         for (int i = 0; i < SIZE; i++)
         {
             for (int j = 0; j < SIZE; j++)
             {
                 if (grid[i][j].exist)
                 {
                     if (i == 5 && j == 5)
                     {
                         grid[i][j].sciezka = "layouts/spawn.txt";
                     }
                     else if (grid[i][j].type==2)
                     {
                         std::string liczba;
                         grid[i][j].sciezka = "layouts/boss/";
                         liczba = std::to_string(std::rand() % 2 +1);  //5 albo 10 po 1 albo 2 na kazdego bossa
                         grid[i][j].sciezka += liczba;
                         grid[i][j].sciezka += ".txt";
                     }
                     else if (grid[i][j].type == 3)
                     {
                         std::string liczba;
                         grid[i][j].sciezka = "layouts/shop/";
                       //  liczba = std::to_string(std::rand() % 9);  //mozliwe ze bedzie jeden layout
                         liczba = std::to_string(1);
                         grid[i][j].sciezka += liczba;              //albo kilka ale z 2-3 max
                         grid[i][j].sciezka += ".txt";              //to samo do item roomu
                     }
                     else if (grid[i][j].type == 4)
                     {
                         std::string liczba;
                         grid[i][j].sciezka = "layouts/item/";
                         liczba = std::to_string(1);
                      //   liczba = std::to_string(std::rand() % 9);
                         grid[i][j].sciezka += liczba;
                         grid[i][j].sciezka += ".txt";
                     }
                     else
                     {
                         grid[i][j].sciezka = random_layout(i, j);
                        // std::cout << grid[i][j].sciezka << std::endl;
                     } 
                 }  
             }
         }
         DeadEnd.clear();
         DeadEnd = std::vector<sf::Vector2i>();
         std::queue <sf::Vector2i> RoomQueueTmp;
         RoomQueue = RoomQueueTmp;
         rooms_counter = 0;    
}