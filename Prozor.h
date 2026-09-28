#pragma once
#include <SFML/Graphics.hpp> 

using namespace sf;

class Prozor {
private:
	sf::RenderWindow prozor;
	sf::Vector2u velicina;
	std::string naslov;
	bool gotov;
	bool cijeliZaslon;
	void Stvori();
	void Unisti();
	void Postavi(const std::string&, const sf::Vector2u&);


public:
	Prozor();
	Prozor(const std::string&, const sf::Vector2u&);
	~Prozor();

	bool jelGotov() {
		return gotov;
	}

	void ocisti();
	void crtaj(sf::Drawable&);
	void prikazi();
	void update();
	bool dogadaji(sf::Event&);
	void zatvori();
	

	//void prebaciNaCijeli();
	bool jelCijeli() {
		return cijeliZaslon;
	}

	sf::Vector2u dohvatiVelicinu() {
		return velicina;
	}
};

Prozor::Prozor() {
	Postavi("SpaceInvaders", sf::Vector2u(1000, 1000));
}

Prozor::Prozor(const std::string& n,
	const sf::Vector2u& v) {
	Postavi(n, v);
}

void Prozor::Postavi(const std::string& n, const sf::Vector2u& v) {
	naslov = n;
	velicina = v;
	cijeliZaslon = false;
	gotov = false;
	Stvori();
}

void Prozor::Stvori() {
	auto stil = (cijeliZaslon ? sf::Style::Fullscreen
		: sf::Style::Default);
	prozor.create(sf::VideoMode(velicina.x, velicina.y, 32),
		naslov, stil);
} 

Prozor::~Prozor() {
	Unisti();
}

void Prozor::Unisti() {
	prozor.close();
}

void Prozor::ocisti() {
	prozor.clear(sf::Color::Black);
}

void Prozor::crtaj(sf::Drawable& d) {
	prozor.draw(d);
}

void Prozor::prikazi() {
	prozor.display();
}



/*void Prozor::prebaciNaCijeli() {
	cijeliZaslon = !cijeliZaslon;
	Unisti();
	Stvori();
}*/

inline void Prozor::zatvori()
{
	gotov = true;
	prozor.close();
}

bool Prozor::dogadaji(sf::Event& d) {
	return prozor.pollEvent(d);
}


