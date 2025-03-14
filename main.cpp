#include <SFML/Graphics.hpp>

using namespace sf;
const int M = 20;
const int N = 20;

int field[N][M] = { 0 };

int figures[7][4] = 
{
	1, 3, 5, 7,
	2, 4, 5, 7,
	3, 5, 4, 6,
	3, 5, 4, 7,
	2, 3, 5, 7,
	3, 5, 7, 6,
	2, 3, 4, 5,
};

struct Point
{
	int x,y;

} a[4],b[4];


int main()
{
	RenderWindow window(VideoMode(580,640), "Tryhard Tetris",sf::Style::Titlebar | sf::Style::Close);
	
	Texture tetramino_texture;
	tetramino_texture.loadFromFile("textures/tetramino.png");

	Sprite tetramino(tetramino_texture);
	tetramino.setScale(0.2f, 0.2f);
	tetramino.setTextureRect(IntRect(0, 0, 161, 161));

	int dx = 0; // left/right rotating
	
	bool rotate = 0; //  spining tetramino

	float timer = 0, delay = 0.4f; // fall

	Clock fallingInterval;

	

	// fall

	
	while (window.isOpen())
	{	
		
		float time = fallingInterval.getElapsedTime().asSeconds();
		fallingInterval.restart();
		timer += time;
		Event event;

		while(window.pollEvent(event))
		{
			//close 
			if (event.type == Event::Closed) window.close();
 
			// spining with left/right rotation
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space) rotate = true;
				else if (event.key.code == Keyboard::Left) dx = -1;
				else if (event.key.code == Keyboard::Right) dx = 1;
			}
		}
		for (int i = 0; i < 4; i++) a[i].x +=dx;

			//spining
		if (rotate)
		{
			Point p = a[1];
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
				
		}

		int n = 3;
		if (a[0].x == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] %2;
				a[i].y = figures[n][i] /2;
			}
		}		

		dx=0;
		rotate = 0;			
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) a[i].y += 1;
			timer = 0;
		}
		// out
		window.clear(Color(23, 22,34));

		for (int i = 0; i < 4; i++)
		{	
			tetramino.setPosition(a[i].x * 32, a[i].y * 32);
			window.draw(tetramino);

		}
		

	
		window.display();
	}
	return 0;
}