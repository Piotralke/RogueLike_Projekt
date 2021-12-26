#include "Collision.h"
bool Collision::check_Collision(sf::RectangleShape& ob1, sf::RectangleShape& ob2)
{
	//if (ob1.getGlobalBounds().intersects(ob2.getGlobalBounds()))
	//{
	//	ob1.setPosition();
	//}
	sf::RectangleShape* poly1 = &ob1;
	sf::RectangleShape* poly2 = &ob2;
	
	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &ob2;
			poly2 = &ob1;
		}
		for (int i = 0; i < poly1->getPointCount(); i++)
		{
			sf::Vector2f line_ob1s = poly1->getPosition();
			sf::Vector2f line_ob1e;
			switch (i)
			{
			case 0:
				line_ob1e = { poly1->getGlobalBounds().left, poly1->getGlobalBounds().top };
				break;
			case 1:
				line_ob1e = { poly1->getGlobalBounds().left + poly1->getGlobalBounds().width, poly1->getGlobalBounds().top };
				break;
			case 2:
				line_ob1e = { poly1->getGlobalBounds().left + poly1->getGlobalBounds().width, poly1->getGlobalBounds().top + poly1->getGlobalBounds().height };
				break;
			case 3:
				line_ob1e = { poly1->getGlobalBounds().left, poly1->getGlobalBounds().top + poly1->getGlobalBounds().height };
				break;
			}
			
			sf::Vector2f displacement = { 0.0f, 0.0f };

			for (int j = 0; j < poly2->getPointCount(); j++)
			{
				sf::Vector2f line_ob2s;
				sf::Vector2f line_ob2e;
				switch (j)
				{
				case 0:
					line_ob2s = { poly2->getGlobalBounds().left, poly2->getGlobalBounds().top };
					line_ob2e = { poly2->getGlobalBounds().left + poly2->getGlobalBounds().width, poly2->getGlobalBounds().top };
					break;
				case 1:
					line_ob2s = { poly2->getGlobalBounds().left + poly2->getGlobalBounds().width, poly2->getGlobalBounds().top };
					line_ob2e = { poly2->getGlobalBounds().left + poly2->getGlobalBounds().width, poly2->getGlobalBounds().top + poly2->getGlobalBounds().height };
					break;
				case 2:
					line_ob2s = { poly2->getGlobalBounds().left + poly2->getGlobalBounds().width, poly2->getGlobalBounds().top + poly2->getGlobalBounds().height };
					line_ob2e = { poly2->getGlobalBounds().left, poly2->getGlobalBounds().top + poly2->getGlobalBounds().height };
					break;
				case 3:
					line_ob2s = { poly2->getGlobalBounds().left, poly2->getGlobalBounds().top + poly2->getGlobalBounds().height };
					line_ob2e = { poly2->getGlobalBounds().left, poly2->getGlobalBounds().top };
					break;
				}

				float h = (line_ob2e.x - line_ob2s.x) * (line_ob1s.y - line_ob1e.y) - (line_ob1s.x - line_ob1e.x) * (line_ob2e.y - line_ob2s.y);
				float t1 = ((line_ob2s.y - line_ob2e.y) * (line_ob1s.x - line_ob2s.x) + (line_ob2e.x - line_ob2s.x) * (line_ob1s.y - line_ob2s.y)) / h;
				float t2 = ((line_ob1s.y - line_ob1e.y) * (line_ob1s.x - line_ob2s.x) + (line_ob1e.x - line_ob1s.x) * (line_ob1s.y - line_ob2s.y)) / h;


				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
				{
					displacement.x += (1.0f - t1) * (line_ob1e.x - line_ob1s.x);
					displacement.y += (1.0f - t1) * (line_ob1e.y - line_ob1s.y);
					ob1.setPosition({ (ob1.getPosition().x + (displacement.x * (shape == 0 ? -1 : 1))), (ob1.getPosition().y + (displacement.y * (shape == 0 ? -1 : 1))) });
					return true;
				}
			}
			
		}
	}
	return false;
}