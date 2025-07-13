#include<iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
class Collisions {
public:
	float initPosX;
	float initPosY;
	float xStep;
	float yStep;
	int R, G, B;
	std::string shape;
	std::string shapeName;
	float width;
	float height;
	sf::CircleShape circle;
	sf::RectangleShape rect;
	int windX; int windY;
	Collisions(std::string shape, std::string shapeName,
		float initPosX,
		float initPosY,
		float xStep,
		float yStep,
		int R, int G, int B, float width, float height, int windX, int windY) {

		this->shape = shape;
		this->shapeName = shapeName;

		this->initPosX = initPosX;
		this->initPosY = initPosY;
		this->xStep = xStep;
		this->yStep = yStep;
		this->R = R;
		this->G = G;
		this->B = B;
		this->windX = windX;
		this->windY = windY;
		if (shape == "Rectangle" || shape == "Square")
		{
			this->width = width;
			this->height = height;
		}
		else {
			this->width = width;
			this->height = 0.0f;
		}

	}

};

class Rectangle : public Collisions {
public:
	Rectangle(std::string shape, std::string shapeName,
		float initPosX,
		float initPosY,
		float xStep,
		float yStep,
		int R, int G, int B, float width, float height, int windX, int windY) :Collisions(shape, shapeName,
			initPosX,
			initPosY,
			xStep,
			yStep,
			R, G, B, width, height, windX, windY) {
	}


	const void createShape() {
		rect.setSize(sf::Vector2f(height, width));
		rect.setPosition(sf::Vector2f(initPosX, initPosY));
		rect.setFillColor(sf::Color(R, G, B));
	}
	void move() {
		if (rect.getPosition().x > windX - width) {
			xStep = -xStep;
		}
		if (rect.getPosition().x < 0) {
			xStep = -xStep;
		}
		if (rect.getPosition().y > windY - height) {
			yStep = -yStep;
		}
		if (rect.getPosition().y < 0) {
			yStep = -yStep;
		}
		rect.move(sf::Vector2f(xStep, yStep));

	}
	void display(sf::RenderWindow& window) {
		window.draw(rect);
	}
};

class Circle : public Collisions {
public:

	Circle(std::string shape, std::string shapeName,
		float initPosX,
		float initPosY,
		float xStep,
		float yStep,
		int R, int G, int B, float width, float height, int windX, int windY) :Collisions(shape, shapeName,
			initPosX,
			initPosY,
			xStep,
			yStep,
			R, G, B, width, height, windX, windY) {
	}

	const void createShape() {
		circle.setRadius(width);
		circle.setPosition(sf::Vector2f(initPosX, initPosY));
		circle.setFillColor(sf::Color(R, G, B));
	}
	void move() {
		if (circle.getPosition().x > windX - (2 * width)) {
			xStep = -xStep;
		}
		if (circle.getPosition().x < 0) {
			xStep = -xStep;
		}
		if (circle.getPosition().y > windY - (2 * width)) {
			yStep = -yStep;
		}
		if (circle.getPosition().y < 0) {
			yStep = -yStep;
		}
		circle.move(sf::Vector2f(xStep, yStep));
	}

	void display(sf::RenderWindow& window) {
		window.draw(circle);
	}
};

struct Config {
	std::string windowsKeyword = "";
	std::string fontKeyword = "";
	unsigned int winx, winy;
	std::string fontStyle = "";
	int fontSize = 12, fontR = 255, fontG = 255, fontB = 255;
	std::vector<Rectangle> rectangleVector;
	std::vector<Circle> circleVector;
};

/*

Window 800 600
Font fonts/arial.ttf 18 255 255 255
Circle CGreen 100 100 -0.03 0.02 0 255 0 50
Circle CBlue 200 200 0.02 0.04 0 0 255 100
Circle CPurple 300 300 -0.02 -0.01 255 0 255 75
Rectangle RRed 200 200 0.1 0.15 255 0 0 50 25
Rectangle RGrey 300 250 -0.02 0.02 100 100 100 50 100
Rectangle RTeal 25 100 -0.02 -0.02 0 255 255 100 100

*/



void readFile(const std::string fileName, Config& config) {

	std::ifstream fin(fileName);
	if (!fin.is_open()) {
		std::cout << "Error opening file for reading." << std::endl;
		std::cout << fileName << std::endl;
		exit(0);
	}
	std::string line;
	std::getline(fin, line);

	std::stringstream stream(line);
	stream >> config.windowsKeyword >> config.winx >> config.winy;
	std::getline(fin, line);
	stream >> config.fontKeyword >> config.fontStyle >> config.fontSize >> config.fontR >> config.fontG >> config.fontB;

	while (std::getline(fin, line)) {
		std::stringstream ss(line);
		std::string shape, shapeName;
		float x, y, sx, sy, width, height;
		int R, G, B;
		ss >> shape >> shapeName >> x >> y >> sx >> sy >> R >> G >> B >> width;

		if (shape == "Circle") {
			config.circleVector.push_back(Circle(shape, shapeName, x, y, sx, sy, R, G, B, width, 0.0f, config.winx, config.winy));
		}
		else if (shape == "Rectangle") {
			ss >> height;
			config.rectangleVector.push_back(Rectangle(shape, shapeName, x, y, sx, sy, R, G, B, width, height, config.winx, config.winy));
		}

	}
}


int main()
{

	Config config;
	readFile("config.txt", config);
	sf::RenderWindow window(sf::VideoMode({config.winx, config.winy}), "Shapes window");
	//sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");

	std::vector<Rectangle> rectangleVector;
	std::vector<Circle> circleVector;

	//Rectangle rect1("Rectangle", "RRed", 10.0f, 10.0f, 2.0f, 4.0f, 150, 50, 250, 50.0f, 70.f);
	//Rectangle rect2("Rectangle", "RGreen", 120.0f, 0.0f, 2.0f, 9.0f, 150, 50, 250, 25.0f, 25.f);
	//Circle circle("Circle", "RGreen", 120.0f, 100.0f, 2.0f, 1.0f, 200, 20, 250, 25.0f, 0.0f);
	//Circle circle2("Circle", "RGreen", 10.0f, 10.0f, 2.0f, 1.0f, 20, 20, 20, 50.0f, 0.0f);
	//Circle circle3("Circle", "RGreen", 10.0f, 120.0f, 20.0f, 10.0f, 230, 20, 80, 100.0f, 0.0f);

	//rectangleVector.push_back(rect1);
	//rectangleVector.push_back(rect1);
	//circleVector.push_back(circle);
	//circleVector.push_back(circle2);

	//circleVector.push_back(circle3);


	for (auto& i : config.circleVector) {
		i.createShape();
	}
	for (auto& i : config.rectangleVector) {
		i.createShape();
	}

	window.setFramerateLimit(60);


	while (window.isOpen()) {
		//sf::Event event;

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

		}
		window.clear(sf::Color::Black);
		for (auto& i : config.circleVector) {
			i.move();
			i.display(window);
		}
		for (auto& i : config.rectangleVector) {
			i.move();
			i.display(window);
		}
		window.display();

	}
	return 0;
}
