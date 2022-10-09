#include "Collision.hpp"

namespace Vadym
{
	Collision::Collision()
	{

	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		sf::Rect<float> rect1 = sprite1.getGlobalBounds();//???
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		if (rect1.intersects(rect2)) //???
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2)
	{
		sprite1.setScale(scale1, scale1); //??? для точности соударения
		sprite2.setScale(scale2, scale2); //была проблема(было 1-2,1-2 стало 1-1,2-2)

		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		if (rect1.intersects(rect2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}