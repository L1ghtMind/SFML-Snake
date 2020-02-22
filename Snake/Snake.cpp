#include <SFML/Graphics.hpp>
#include <time.h>
#include "structures.h"
using namespace	sf;

int N = 32, M = 32;
int size = 16;
int width = N * size;
int height = M * size;
int direction, body = 4;
int gameOver = 0;

void Game()
{
	for (int i = body; i > 0; --i)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	if (direction == 0) snake[0].y += 1;
	if (direction == 1) snake[0].x -= 1;
	if (direction == 2) snake[0].x += 1;
	if (direction == 3) snake[0].y -= 1;
	if ((snake[0].x == fruit.x) && snake[0].y == fruit.y)
	{
		body++;
		fruit.x = rand() % N;
		fruit.y = rand() % M;
	}
	if (snake[0].x > N) snake[0].x = 0;
	if (snake[0].x < 0) snake[0].x = N;
	if (snake[0].y > M) snake[0].y = 0;
	if (snake[0].y < 0) snake[0].y = M;
	for (int i = 1; i < body; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			gameOver = 1;
		}
	};
}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(width, height), "Snake");
	Texture t1, t2, t3;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Clock clock;
	float timer = 0, delay = 0.1;
	fruit.x = 10;
	fruit.y = 10;
	
	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;
		
		if(timer>delay)
		{
			timer = 0;
			Game();
		}
		//------DRAWING----//
		window.clear();
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i * size, j * size);
				window.draw(sprite1);
			}
		}
		for(int i = 0; i<body; i++)
		{
			sprite2.setPosition(snake[i].x * size, snake[i].y * size);
			window.draw(sprite2);
		}
		sprite3.setPosition(fruit.x * size, fruit.y * size);
		window.draw(sprite3);
		if(gameOver==1)
		{
			window.close();
		}
		window.display();
	}
	return 0;
}

