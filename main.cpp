#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 20;

int field[M][N] = { 0 };




int figures[7][4] = 
{
	1, 3, 5, 7, // I
	2, 4, 5, 7, // S
	3, 5, 4, 6, // Z
	3, 5, 4, 7, // T
	2, 3, 5, 7, // L
	3, 5, 7, 6, // J
	2, 3, 4, 5, // O
};

struct Point
{
	int x,y;

} a[4],b[4], colorPoints;


bool check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M ) return 0;
		else if(field[a[i].y][a[i].x]) return 0;		
	}
	return 1;
}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(640,640), "Tryhard Tetris",sf::Style::Titlebar | sf::Style::Close);
	
	Texture tetramino_texture;
	tetramino_texture.loadFromFile("textures/tetramino.png");

	Sprite tetramino(tetramino_texture);
	tetramino.setTextureRect(IntRect(0, 0, 32, 32));


	tetramino.setScale(0.2f, 0.2f);

	int tetraminoColor = 1 + rand() % 3;

	int n= rand() % 7; // tetramino type

	int dx = 0; // left/right rotating
	
	bool rotate = 0; //  spining tetramino

	float timer = 0, delay = 0.3; // fall

	bool beginGame = true;

	Clock clock;

	
	while (window.isOpen())
	{	
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
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
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.08;

		///// rotation x /////
		for (int i = 0; i < 4; i++){ b[i] = a[i]; a[i].x +=dx;	}

		if(!check()) for (int i = 0; i < 4; i++) {a[i] = b[i];} // out of boards


		///// spining /////
		if (rotate && n != 6)
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
		if(!check()) for (int i = 0; i < 4; i++) {a[i] = b[i];} // out of boards


		///// rotation y /////
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) {b[i] = a[i]; a[i].y+=1;}
			
			if(!check())
			{


				for (int i = 0; i < 4; i++)field[b[i].y][b[i].x] = tetraminoColor;
				tetraminoColor =  1 + rand() % 3;
				n = rand() % 7; 
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
		
			}
			timer = 0;
		}


		
		if (beginGame)
		{
			beginGame = false;
			n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}
		dx=0; rotate = 0; delay = 0.3;

		

		for (int i = 0; i < M; i++)
		{
			int filledRowCounter = 0;
			for (int j = 0; j < N; j++) {if(field[i][j] != 0) filledRowCounter++;}				
			
			if(filledRowCounter == M)
			{
				int currentRow = i;
				for (int j = 0; j < N; j++) field[i][j] = 0;
			
				for (int j = i-1; j > 0; j--)
				{
					for (int k = 0; k < M; k++) field[currentRow][k]= field[j][k];
					currentRow--;
				}
				
				
			}
			
		}
		
		
		
		// out
		window.clear(Color(23, 22,34));
		for (int i = 0; i < M; i++)
		{
			
			for (int j = 0; j < N; j++)
			{
				if(field[i][j] == 0) continue;
				tetramino.setTextureRect(IntRect(161* field[i][j], 0, 161, 161));
				tetramino.setPosition(j * 32, i * 32);
				window.draw(tetramino);
			}
			
		}
		
		
				
		
		
		for (int i = 0; i < 4; i++)
		{	
			tetramino.setTextureRect(IntRect(161* tetraminoColor, 0, 161, 161));
			tetramino.setPosition(a[i].x * 32, a[i].y * 32);
			window.draw(tetramino);

		}
		
	
		window.display();
	}
	return 0;
}