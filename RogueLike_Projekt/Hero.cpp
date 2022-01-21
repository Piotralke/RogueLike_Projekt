#include "Hero.h"
#include <iostream>

/** \brief  Konstruktor dla postaci
 *
 * Konstruktor zapisuje parametry podane jako parametry do danego obiektu
 * @param texture Wskaźnik na teksture dla postaci
 * @param imageCount Kontener przechowujący informacje o ilości teskstur zawartych w pliku graficznym animacji postaci (dla bohatera 4,2 - 4oznacza 4 różne tekstury dla animacji, a 2 ilość różnych aninmacji)
 * @param switchTime Czas po jakim ma się zmienić tekstura(wykorzystywana w animacji)
 * @param speed Parametr określający prędkość postaci
 * @param fire_rate Parametr określający szybkostrzelność postaci
 * @param shot_speed Parametr określający prędkość pocisku wystrzelonego przez daną postać
 * @param health Parametr określający podstawową ilość życia postaci
 * @param damage Parametr określający obrażenia jakie zadaje postać
 * @param size Rozmiar pojedynczej tekstury postaci
 * @param position Pozycja na której postać ma zostać postawiona
 * @param flying Parametr określający czy postać może przechodzić przez przeszkody
 * @param arrow Wskaźnik na teksture dla naboju postaci
 * @param wings_t Wskaźnik na teksture skrzydeł
 */

hero::hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
    float damage, sf::Vector2f size, sf::Vector2f position, bool flying, sf::Texture* arrow, sf::Texture* wings_t) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    this->fire_rate = fire_rate;
    this->shot_speed = shot_speed;
    this->health = health;
    this->maxHealth = health;
    this->damage = damage;
    row = 0;
    faceRight = true;
    this->flying = flying;
    this->arrow = arrow;
    body.setSize(size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
    wings.setSize({ 36.0f,20.0f });
    wings.setOrigin(wings.getSize() / 2.0f);
    wings.setTexture(wings_t);
}

/** \brief  Funkcja wypisująca statystyki
 *
 * Funkcja wypisująca statystyki w określonym miejscu na HUDzie gry, używana tylko dla postaci głównej
 * @param window Wskaźnik na okno, w którym ma wypisać statystyki
 * @param font Wskaźnik na czcionkę używaną w programie
 */

void hero::DrawStats(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text health_text;
    std::string health_string;
    sf::RectangleShape health_bar;
    health_bar.setFillColor(sf::Color::Red);
    health_bar.setSize({(health/maxHealth*53),8});
    health_bar.setPosition({731.0f,104.0f});
    health_text.setFont(font);
    health_text.setCharacterSize(8);
    health_text.setFillColor(sf::Color::White);
    health_string = std::to_string(maxHealth);
    health_string.erase(health_string.size() - 4, 4);
    health_text.setString(health_string);
    health_text.setPosition({ 735.0f,103.0f });

    sf::Text damage_text;
    std::string damage_string;
    damage_text.setFont(font);
    damage_text.setCharacterSize(8);
    damage_text.setFillColor(sf::Color::White);
    damage_string = std::to_string(damage);
    damage_string.erase(damage_string.size() - 4, 4);
    damage_text.setString(damage_string);
    damage_text.setPosition({ 740.0f,120.0f });

    sf::Text shot_speed_text;
    std::string shot_speed_string;
    shot_speed_text.setFont(font);
    shot_speed_text.setCharacterSize(8);
    shot_speed_text.setFillColor(sf::Color::White);
    shot_speed_string = std::to_string(shot_speed);
    shot_speed_string.erase(shot_speed_string.size() - 4, 4);
    shot_speed_text.setString(shot_speed_string);
    shot_speed_text.setPosition({ 740.0f,140.0f });

    sf::Text fire_rate_text;
    std::string fire_rate_string;
    fire_rate_text.setFont(font);
    fire_rate_text.setCharacterSize(8);
    fire_rate_text.setFillColor(sf::Color::White);
    fire_rate_string = std::to_string(fire_rate);
    fire_rate_string.erase(fire_rate_string.size() - 4, 4);
    fire_rate_text.setString(fire_rate_string);
    fire_rate_text.setPosition({ 740.0f,158.0f });

    sf::Text speed_text;
    std::string speed_string;
    speed_text.setFont(font);
    speed_text.setCharacterSize(8);
    speed_text.setFillColor(sf::Color::White);
    speed_string = std::to_string(speed);
    speed_string.erase(speed_string.size() - 4, 4);
    speed_text.setString(speed_string);
    speed_text.setPosition({ 740.0f,176.0f });

    sf::Text coin_text;
    std::string coin_string;
    coin_text.setFont(font);
    coin_text.setCharacterSize(8);
    coin_text.setFillColor(sf::Color::White);
    coin_string = std::to_string(money);
    coin_text.setString(coin_string);
    coin_text.setPosition({ 740.0f,196.0f });

    window.draw(health_bar);
    window.draw(health_text);
    window.draw(damage_text);
    window.draw(shot_speed_text);
    window.draw(fire_rate_text);
    window.draw(speed_text);
    window.draw(coin_text);
    
}

/** \brief  Funkcja wyświetlająca postać
 *
 * Funkcja, która wyświetla na podane okno postać, ułatwia nam wyświetlanie tej postaci
 * @param window Wskaźnik na okno, w którym ma wyświetlić postać
 */

void hero::Draw(sf::RenderWindow& window)
{
    if (flying)
    {
        wings.setPosition(body.getPosition().x, body.getPosition().y-6.0f);
        window.draw(wings);
    }
    window.draw(body);

}

/** \brief  Funkcja od wyświetlania postaci w menu
 *
 * Funkcja ułatwia wyświetlanie postaci animowanych w menu, używana tylko w menu
 * @param window Wskaźnik na okno, w którym ma wyświetlić postać
 * @param deltaTime Zmienna określająca ile czasu minęło pomiędzy klatkami gry (umożliwia ona płynniejsze działanie gry, ponieważ niezależnie od wykorzystanie zasobów komputera gra nie powinna przyspieszać, ani zwalniać)
 */

void hero::DrawMenu(sf::RenderWindow& window, float deltaTime)
{
    if (flying)
        faceRight = false;
    animation.Update(0, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    window.draw(body);
}

/** \brief  Funkcja aktualizująca pozycje postaci
 *
 * Główna funkcja dla naszej postaci, w niej obsługiwane są klawisze odpowiadające za poruszanie się postaci oraz strzelanie
 * @param deltaTime Zmienna określająca ile czasu minęło pomiędzy klatkami gry (umożliwia ona płynniejsze działanie gry, ponieważ niezależnie od wykorzystanie zasobów komputera gra nie powinna przyspieszać, ani zwalniać)
 * @param bulletVec Wskaźnik na vector naboi postaci głównej
 */

void hero::Update(float deltaTime, std::vector<Bullet> &bulletVec)
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, {0.0f, -1.0f}, arrow, 0.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, { 0.0f, 1.0f }, arrow, 180.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, { -1.0f, 0.0f }, arrow, -90.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, { 1.0f, 0.0f }, arrow, 90.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }
        
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

/** \brief  Funkcja zwracająca pozycje postaci
 *
 * @return body.getPosition() Zwraca pozycję postaci
 */

sf::Vector2f hero::GetPosition()
{
    return body.getPosition();
}

/** \brief  Funkcja zwracająca obrażenia postaci
 *
 * @return body.getPosition() Zwraca obrażenia postaci
 */

float hero::getDamage()
{
    return damage;
}

/** \brief  Funkcja zwracająca życie postaci
 *
 * @return body.getPosition() Zwraca życie postaci
 */

float hero::getHealth()
{
    return health;
}

/** \brief  Funkcja zwracająca prędkość postaci
 *
 * @return body.getPosition() Zwraca prędkość postaci
 */

float hero::getSpeed()
{
    return speed;
}

/** \brief  Funkcja zwracająca prędkość naboju postaci
 *
 * @return body.getPosition() Zwraca prędkość naboju postaci
 */

float hero::getShotSpeed()
{
    return shot_speed;
}

/** \brief  Funkcja zwracająca szybkostrzelność postaci
 *
 * @return body.getPosition() Zwraca szybkostrzelność postaci
 */

float hero::getFireDelay()
{
    return fire_rate;
}

/** \brief  Funkcja zwracająca czy postać może latac
 *
 * @return body.getPosition() Zwraca czy postać może latać
 */

bool hero::getFlying()
{
    return flying;
}

/** \brief  Funkcja zwracająca ilość monetek postaci
 *
 * @return body.getPosition() Zwraca ilość monetek postaci
 */

int hero::getMoney()
{
    return money;
}

/** \brief  Funkcja zadająca obrażenia postaci
 *
 * @param damage Parametr o ile ma obniżyc życie postaci
 */

void hero::getHit(float damage)
{
    health -= damage;
}

/** \brief  Funkcja dodająca statystyki
 *
 * Funkcja wywołująca się przy podnoszeniu przedmiotów, która dodaje parametry tych przedmiotów do naszej postaci
 * @param damage Parametr określający ile obrażeñ ma dodać do naszej postaci
 * @param health Parametr określający ile życia ma dodać do naszej postaci
 * @param maxHealth Parametr określający ile maksymalnego życia ma dodać do naszej postaci
 * @param fire_delay Parametr określający ile szybkostrzelności ma dodać do naszej postaci
 * @param shot_speed Parametr określający ile predkości naboju ma dodać do naszej postaci
 * @param speed Parametr określający ile prędkości ma dodać do naszej postaci
 * @param money Parametr określający ile monet ma dodać do naszej postaci
 * @param flying Parametr określający czy ma dodać do postaci przechodzenie przez przeszkody
 */

void hero::setStatistics(float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed, int money, bool flying)
{
    this->damage += damage;
    this->maxHealth += maxHealth;
    this->health += health;
    if (this->health > this->maxHealth)
        this->health = this->maxHealth;
    if (this->fire_rate >= 0.2f)
        this->fire_rate += fire_delay;
    else if (this->fire_rate < 0.2f)
        this->fire_rate = 0.2f;
    this->shot_speed += shot_speed;
    if (this->speed <= 300.0f)
        this->speed += speed;
    else if (this->speed > 300.0f)
        this->speed = 300.0f;
    this->money += money;
    if (this->flying == false)
    {
        this->flying = flying;
    } 
}
