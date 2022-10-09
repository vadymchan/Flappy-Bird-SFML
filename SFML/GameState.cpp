#include <sstream>
#include "GameOverState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"


#include<iostream>

namespace Vadym
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init() // нажали на кнопку запуска - мы внутри
	{
		if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))//???
		{
			std::cout << "Error loading Hit Sound Effect" << std::endl;
		}

		if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
		{
			std::cout << "Error loading Point Sound Effect" << std::endl;
		}

		if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
		{
			std::cout << "Error loading Wing Sound Effect" << std::endl;
		}

		_hitSound.setBuffer(_hitSoundBuffer);
		_pointSound.setBuffer(_pointSoundBuffer);
		_wingSound.setBuffer(_wingSoundBuffer);

		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		_data->assets.LoadTexture("Land", LAND_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);


		pipe = new Pipe(_data);//???(их вроде еще и удалить нужно)
		land = new Land(_data); //вроде как конструктор
		bird = new Bird(_data);
		flash = new Flash(_data);
		hud = new HUD(_data);

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_score = 0;
		hud->UpdateScore(_score);//так потому что мы можем легко контролить начальное значение счета

		_gameState = GameStates::eReady; //??? вроде пока не нажмешь на кнопку оно не заработает
		

		
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window)) //??
			{
				if (GameStates::eGameOver != _gameState) {
					_gameState = GameStates::ePlaying;
					bird->Tap();
					_wingSound.play();
				}
			}
			

		}
	}

	void GameState::Update(float dt)
	{
		if (GameStates::eGameOver != _gameState) //пока не проиграли он движется
		{
			bird->Animate(dt);
			land->MoveLand(dt);
		}
		if (GameStates::ePlaying == _gameState)
		{
			pipe->MovePipes(dt);
			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->RandomisePipeOffset();
				pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();

				clock.restart();
			}
			bird->Update(dt);


//Collision check

			std::vector <sf::Sprite> landSprites = land->GetSprites();//???

			for (int i = 0; i < landSprites.size(); i++)// collision detection
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(),0.7f, landSprites.at(i),1.0f))
				{
					_gameState = GameStates::eGameOver;; //??? зОчем цикл(проверяем каждый кусок земли на столкновение)

					clock.restart();

					_hitSound.play();
				}
			}

			std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();

			for (unsigned int i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f , pipeSprites.at(i), 1.0f))
				{
					_gameState = GameStates::eGameOver;

					clock.restart();

					_hitSound.play();
				}
			}

			std::vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites(); //???почему тут ссылка (чтобы потом было легче удалить вектор)

			for (int i = 0; i < scoringSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f))
				{
					_score++;

					hud->UpdateScore(_score);

					scoringSprites.erase(scoringSprites.begin() + i);

					_pointSound.play();
				}
			}



		}

		if (GameStates::eGameOver == _gameState)
		{
			flash->Show( dt);

			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				_data->machine.AddState(StateRef(new GameOverState(_data,_score) ), true); //???
			}
		}


	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);
		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();

		flash->Draw();

		hud->Draw();

		_data->window.display();
	}
}