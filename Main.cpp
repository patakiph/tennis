#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <sstream>

using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Tennis");
	Player p1("player1", 500, 200, 0, 0, sf::Color::Red);
	Player p2("player2", 200, 200, 0, 0, sf::Color::Blue);
	Ball b("ball", 320, 200, 0.2, 0.2, sf::Color::Green);
	Clock clock;
	Font font;
	font.loadFromFile("ARCADECLASSIC.ttf");
	Text text1("Score    ",font,20), text2("Score    ", font, 20), text("  WON!", font, 20);
	text1.setPosition(0, 3);
	text2.setPosition(520, 3);
	text.setPosition(300, 210);
	while (window.isOpen())
	{
		sf::Event event;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 900;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		if (b.getRect().intersects(p1.getRect())){ 
			b.reflect();
	//		b.x = p1.x - p1.w;
		}
		if (b.getRect().intersects(p2.getRect())) {
			b.reflect();
	//		b.x = p2.x + p2.w;
		}
		p1.update(time);
		window.draw(p1.rect);
		p2.update(time);
		window.draw(p2.rect);
		
		if (b.x <= 0)
			p2.score++;
		if (b.x >= 630)
			p1.score++;
		std::ostringstream playerScoreString1, playerScoreString2;    // объ€вили переменную
		playerScoreString1 << p1.score;
		playerScoreString2 << p2.score;
		text1.setString("score  " + playerScoreString1.str());
		window.draw(text1);
		text2.setString("score  " + playerScoreString2.str());
		window.draw(text2);
		if (p1.score >= 10) {
			text.setString("BLUE WON!");
			window.draw(text);
		}
		if (p2.score >= 10) {
			text.setString("RED WON!");
			window.draw(text);
		}
		b.update(time);
		
		window.draw(b.circle);
		window.display();
	}

	return 0;
}