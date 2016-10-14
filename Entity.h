#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Entity
{
public:
	String name;
	enum { up, down, stay, left, right, move } state;
	float x, y, w, h, dx, dy;

	Entity(String, float, float, float, float,float,float);
	virtual void update(float) = 0;
//	virtual void control();
	virtual void checkCollisionWithMap(float Dx, float Dy) = 0;
	virtual ~Entity();
	FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}

};

class Player : public Entity {
public:
	
	Player(String name, float x, float y, float dx, float dy, const sf::Color  color,int score = 0) : Entity(name, x, y, 0, 0,20,100),score(score) {
		rect = *(new RectangleShape(Vector2f(20,100)));
		rect.setFillColor(color);
	}
	void control() {
		state = stay;
		if (Keyboard::isKeyPressed) {
			if (name == "player2") {
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					state = right;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					state = up;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					state = left;
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					state = down;
				}
			}
			if (name == "player1") {
				if (Keyboard::isKeyPressed(Keyboard::D)) {
					state = right;
				}
				if (Keyboard::isKeyPressed(Keyboard::W)) {
					state = up;
				}
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					state = left;
				}
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					state = down;
				}
			}
		} 
	}
	void checkCollisionWithMap(float Dx, float Dy) {
		if (x > 300 && name == "player2")   			
			if (Dx > 0) { x = 300; dx = 0; }
		if (x < 0 && name == "player2")
			if (Dx < 0) { x = 0; dx = 0; }
		if (x < 320 && name == "player1")
			if (Dx < 0) { x = 320; dx = 0; }
		if (x > 620 && name == "player1")
			if (Dx > 0) { x = 620; dx = 0; }
		if (y < 0)
			if (Dy < 0) { y = 0; dy = 0; }
		if (y > 380)
			if (Dy > 0) {
				y = 380; dy = 0;
			}
	}
	void update(float time) {
		control();
		switch (state) {
		case up: dy = -0.1;  break;
		case down: dy = 0.1;   break;
		case left: dx = -0.1; break;
		case right: dx = 0.1; break;
		case stay: dx = 0; dy = 0; break; 
		}
		y += dy*time;
		checkCollisionWithMap(0,dy);
		x += dx*time;
		checkCollisionWithMap(dx,0);
		rect.setPosition(x, y);
	}
	int score;
	RectangleShape rect;
};

////////////////////////////BALL///////////////////////////////
class Ball : public Entity {
public:
	CircleShape circle;
	Ball(String name, float x, float y, float dx, float dy, const sf::Color  color) : Entity(name, x, y, 0.1f, 0.1f,10,10) {
		circle = *(new CircleShape(5.f));
		circle.setFillColor(color);
		w = h = 10;
		state = move;
	}
	void checkCollisionWithMap(float Dx, float Dy) {
		if (x < 0)
			if (Dx < 0) { x = 0; dx = -dx; state = right; }
		if (x > 630)
			if (Dx > 0) { x = 630; dx = -dx; state = left;
		}
		if (y < 0)
			if (Dy < 0) { y = 0; dy = -dy; state = down; }
		if (y > 470)
			if (Dy > 0) {
				y = 470; dy = -dy; state = up;
			}
	}
	void reflect() {
		dy = -dy;
		dx = -dx;
	}
	void update(float time) {
		y += dy*time;
		checkCollisionWithMap(0, dy);
		x += dx*time;
		checkCollisionWithMap(dx, 0);
		circle.setPosition(x, y);
	}
};