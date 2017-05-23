#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Alg.h"
#include "Game_Objects.h"

#define and &&
#define or ||


using namespace sf;


class Tank_Animation {
public:
	int frames;
	int time_for_loop;
	int current_frame_number = 0;
	int time = 0;
	int tilesize_x;
	int tilesize_y;
	Clock timer;
	Texture tileset_texture; // В этой текстуре содержится весь тайлсет
	Image img;

	void init(std::string tileset_name, int fr) {
		if (!img.loadFromFile(tileset_name)){
			printf("Can't load texture");
			system("pause");
			return;
		}
		img.createMaskFromColor(Color::White);
		tileset_texture.loadFromImage(img);
		 // Загружаем изображение из файла
		tilesize_x = tileset_texture.getSize().x / fr;
		tilesize_y = tileset_texture.getSize().y;
		frames = fr;
		time_for_loop = 1000 / frames;
	}

	void set_current_frame(Sprite &target) {
		/*
		
		*/
		time += timer.getElapsedTime().asMilliseconds();
		timer.restart();
		if (time > 1000) {
			time = 0;
		}
		current_frame_number = time / time_for_loop;
		// Первый и второй параметры - координатыб 3 и 4 ширина и высота
		target.setTextureRect(IntRect(current_frame_number*tilesize_x, 0,
			tilesize_x, tilesize_y));

	}

	void set_texture(Sprite &target) {
		target.setTexture(tileset_texture);
	}
};


class Tank:public GameObject{
public:
	float health;
	Tank_Animation animation;
	float dx = 0;
	float dy = 0;
	Tank(float x, float y, std::string fname, float tank_health):GameObject () {
		animation.init(fname, 2);
		this_sprite.setPosition(x, y);
		xpos = x;
		ypos = y;
		health = tank_health;
		animation.set_texture(this_sprite);
		xsize = animation.tilesize_x;
		ysize = animation.tilesize_y;
	}

	void draw(RenderTarget &window);

	bool intersects_with(GameObject &second);

	IntRect get_rect();

	void move(float x_offset, float y_offset);

	void update(std::vector<GameObject*> &game_objects);
	
	void degen();
	
	void regen();
};

bool Tank::intersects_with(GameObject &second) {
	if ((alg::max<float>(xpos, second.xpos) < alg::min<float>(xpos + xsize, second.xpos + second.xsize)) == true and
		(alg::max<float>(ypos, second.ypos) < alg::min<float>(ypos + ysize, second.ypos + second.ysize)) == true ) {
		return true;
	}
	else
		return false;
}

IntRect Tank::get_rect() {
	return this_sprite.getTextureRect();
}

void Tank::move(float x_offset, float y_offset) {
	if (available == true){
		dx += x_offset;
		dy += y_offset;
	}
}

void Tank::draw(RenderTarget &window) {
	{
		/*
		Передаю функции set_current_animation спрайт такна с текстурой в виде всего тайлсета
		и на выходе получаю спрайт с нужным кадром
		*/
		if (available == true){
			animation.set_current_frame(this_sprite);
			window.draw(this_sprite);
		}
	}
}

void Tank::update(std::vector<GameObject*> &game_objects) {
	if (available == true){
		this_sprite.move(dx, 0);
		xpos += dx;
		for (auto &gm : game_objects) {
			if (intersects_with(*gm) == true and gm->available == true) {
				printf("Called intersect with X\n");
				this_sprite.move(-dx, 0);
				xpos -= dx;
				break;
			}
		}
		this_sprite.move(0, dy);
		ypos += dy;
		for (auto &gm : game_objects) {
			if (intersects_with(*gm) == true and gm->available == true) {
				printf("Called intersect with Y\n");
				this_sprite.move(0, -dy);
				ypos -= dy;
				break;
			}
		}
		dx = 0;
		dy = 0;
	}
}


void Tank::degen() {
	available = false;
}


void Tank::regen() {
	available = true;
}