//#include<SFML/Graphics.hpp>
#include<iostream>
#include"Game.hpp"
#include "DEFINITIONS.hpp"
//using namespace sf;
//
//#define	SCREEN_WIDTH 1024
//#define	SCREEN_HEIGHT 1024
//
//int main()
//{
//	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
//
//	while (window.isOpen())
//	{
//		Event event;
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//				case Event::Closed:
//					window.close();
//					break;
//			}
//		}
//		//window.clear();
//		window.display();
//
//	}
//}

int main()
{
	Vadym::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
	return EXIT_SUCCESS;
}
