
#include "HUD.hpp"

#include<string>

namespace Vadym
{
	HUD::HUD(GameDataRef data) : _data(data) //из-за этого была ошибка
	{
		_scoreText.setFont(_data->assets.GetFont("Flappy Font"));

		_scoreText.setString("0");

		_scoreText.setCharacterSize(128); //можно было и в DEFINITIONS объявить

		_scoreText.setFillColor(sf::Color::White);

		_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2,
			_scoreText.getGlobalBounds().height / 2); //когда увеличивается счет чтобы выглядело нормально
		_scoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y / 5);
	}

	void HUD::Draw()
	{
		_data->window.draw(_scoreText);
	}

	void HUD::UpdateScore(int score)
	{
		_scoreText.setString(std::to_string(score));
	}

}