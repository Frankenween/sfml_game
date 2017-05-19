#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "Tank.h"
#include "Errorr.h"

#define and &&
#define or ||

#define DEBUGMODE
#define MAPSIZE 20

using namespace sf;


template <typename T>
std::vector<T> make_list(std::string line) {
	std::vector<T> ret;
	std::stringstream iss(line);
	T current;
	while (iss >> current) {
		ret.push_back(current);
	}
	return ret;

}

void generate_map_from_file(std::string mname, std::vector<GameObject*> &obj) {
	ifstream map_(mname);
	if (map_.is_open() == false) {
		printf("cant open file");
		throw "Cant load file";
	}
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			int current;
			map_ >> current;
			if (current == 1) {
				obj.emplace_back(new Block(j * 32, i * 32, "C:/Users/Vova/Documents/Visual Studio 2017/Projects/Tank/Debug/block.png"));
			}
		}
	}
}


int main()
{
	RenderWindow window(VideoMode(32 * 20, 32 * 20), "SFML works!");
	std::vector<GameObject*> game_rects;
	window.setFramerateLimit(60);

	Tank *t1 = new Tank(270, 270, "C:/Users/Vova/Documents/visual studio 2017/Projects/Tank/Debug/tank1.png", 100);
	Tank *t2 = new Tank(50, 35, "C:/Users/Vova/Documents/visual studio 2017/Projects/Tank/Debug/tank1.png", 100);
	Tank *t3 = new Tank(68, 17, "C:/Users/Vova/Documents/visual studio 2017/Projects/Tank/Debug/tank1.png", 100);
	Tank *t4 = new Tank(55, 63, "C:/Users/Vova/Documents/visual studio 2017/Projects/Tank/Debug/tank1.png", 100);

	game_rects.push_back(t2);
	game_rects.push_back(t3);
	game_rects.push_back(t4);

	generate_map_from_file("C:/Users/Vova/Documents/visual studio 2017/Projects/Tank/Debug/map1.mp", game_rects);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::W) {
					t1->move(0, -1);
					#ifdef DEBUGMODE
					printf("(%2f;%2f)\n", t1->xpos, t1->ypos);
					#endif // DEBUGMODE
				}
				if (event.key.code == Keyboard::A) {
					t1->move(-1, 0);
					#ifdef DEBUGMODE
					printf("(%2f;%2f)\n", t1->xpos, t1->ypos);
					#endif // DEBUGMODE
				}
				if (event.key.code == Keyboard::D) {
					t1->move(1, 0);
					#ifdef DEBUGMODE
					printf("(%2f;%2f)\n", t1->xpos, t1->ypos);
					#endif // DEBUGMODE
				}
				if (event.key.code == Keyboard::S) {
					t1->move(0, 1);
					#ifdef DEBUGMODE
					printf("(%2f;%2f)\n", t1->xpos, t1->ypos);
					#endif // DEBUGMODE
				}
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					delete t2;
					delete t3;
					delete t4;
				}
			}
		}
		
		window.clear();
		t1->update(game_rects);
		t1->draw(window);
		for (auto &obj : game_rects) {
			obj->draw(window);
		}
		window.display();
		
		
	}

	return 0;
}