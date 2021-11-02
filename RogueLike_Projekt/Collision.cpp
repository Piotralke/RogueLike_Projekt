#include "Collision.h"
#include <iostream>
bool Collision::check_Collision(sf::RectangleShape& ob1, sf::RectangleShape& ob2)
{
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
			sf::Vector2f line_ob1s = poly1->getOrigin();
			sf::Vector2f line_ob1e = poly1->getPoint(i);

		//	sf::Vector2f displacement = { 0.0f, 0.0f };

			for (int j = 0; j < poly2->getPointCount(); j++)
			{
				sf::Vector2f line_ob2s = poly2->getPoint(j);
				sf::Vector2f line_ob2e = poly2->getPoint((j + 1) % poly2->getPointCount());

				float h = (line_ob2e.x - line_ob2s.x) * (line_ob1s.y - line_ob1e.y) - (line_ob1s.x - line_ob1e.x) * (line_ob2e.y - line_ob2s.y);
				float t1 = ((line_ob2s.y - line_ob2e.y) * (line_ob1s.x - line_ob2s.x) + (line_ob2e.x - line_ob2s.x) * (line_ob1s.y - line_ob2s.y)) / h;
				float t2 = ((line_ob1s.y - line_ob1e.y) * (line_ob1s.x - line_ob2s.x) + (line_ob1e.x - line_ob1s.x) * (line_ob1s.y - line_ob2s.y)) / h;

				std::cout << "h:" << h << std::endl;
				std::cout << "t1:" << t1 << std::endl;
				std::cout << "t2:" << t2 << std::endl;


				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
				{
					//displacement.x += (1.0f - t1) * (line_ob1e.x - line_ob1s.x);
					//displacement.y += (1.0f - t1) * (line_ob1e.y - line_ob1s.y);
					return true;
				}
			}
	//		ob1.setOrigin({ (ob1.getOrigin().x + (displacement.x * (shape == 0 ? -1 : +1))), (ob1.getOrigin().y + (displacement.y * (shape == 0 ? -1 : +1))) });
		}
	}
	return false;
}