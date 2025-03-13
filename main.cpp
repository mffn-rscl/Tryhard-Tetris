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
	RenderWindow window(VideoMode(580,640), "Adrew Shotgun",sf::Style::Titlebar | sf::Style::Close);
	
	Texture tetramino_texture;
	tetramino_texture.loadFromFile("textures/tetramino.png");

	while (window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		window.clear(Color(23, 22,34));
		
		Sprite tetramino(tetramino_texture);
		tetramino.setScale(0.2f, 0.2f);
	
		int n = 3;
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;

		/*
			a[0]: (1, 1)
			a[1]: (1, 2)
			a[2]: (0, 2)
			a[3]: (1, 3)
		*/
		}
		
		for (int i = 0; i < 4; i++)
		{	
			tetramino.setTextureRect(IntRect(0, 0, 161, 161));
			tetramino.setPosition(a[i].x * 32, a[i].y * 32);

			/*
				a[0]: (32, 32)
				a[1]: (64, 64)
				a[2]: (0, 64)
				a[3]: (32, 96)
			
			*/

			window.draw(tetramino);


		}
		
		window.display();
	}
	return 0;
}