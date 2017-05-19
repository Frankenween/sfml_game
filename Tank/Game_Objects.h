#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Alg.h"


class GameObject {
	/*
	Главный(родительский) класс для всех объектов игры
	*/
public:
	float xpos = 0;
	float ypos = 0;
	int xsize = 0;
	int ysize = 0;
	sf::Sprite this_sprite;
	virtual void draw(sf::RenderTarget &window) { window.draw(this_sprite); };
};



class Block : public GameObject {
public:
	Block(float x, float y, std::string fname) {
		if (!blTextr.loadFromFile(fname)) {
			printf("Can't load texture");
			system("pause");
			return;
		}
		this_sprite.setPosition(x, y);
		this_sprite.setTexture(blTextr);
		xpos = x;
		ypos = y;
		health = 100; // By default
		xsize = blTextr.getSize().x;
		ysize = blTextr.getSize().y;
	}


	void got_damage(float damage) {
		if (can_destroy == true)
			health -= damage;
	}

	void set_texture_from_file(std::string fname) {
		blTextr.loadFromFile(fname);
		this_sprite.setTexture(blTextr);
	}

	void draw(sf::RenderTarget &window) {
		window.draw(this_sprite);
	}

private:
	int health;
	bool can_destroy = true;
	bool drawable = true;
	sf::Texture blTextr;
};