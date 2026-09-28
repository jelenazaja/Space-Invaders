#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<ctime>
#include <SFML/Graphics.hpp>
#include "Prozor.h"
#include "Igra.h"


using namespace sf;
using namespace std;

enum class Smjer { Lijevo, Desno, Nista };

struct Metak {

	float x;
	float y;
	bool aktivan;

};

class Igrac {
	friend class Igra;
private:

	Smjer smjer;
	
	Vector2f pozicija;
	float brzina;
	float brzina_metka;
	int brzivota;
	int broj_bodova;

	Sprite sprite, sprite_metak;
	Texture tekstura, tekstura_metak;
    Metak metak;
	Time vrijeme;
	

public:

	Igrac();
	void reset();
	void PostaviSmjer(Smjer s) {
		 smjer = s;
	}

	void renderiraj(Prozor*);
	void update();
	void ucitaj_slike();
	void pucaj();
	void update_metak();
	void crtaj_metak(Prozor*);
	bool pogoden(Metak& m);

};

Igrac::Igrac(){ 
	
	reset();
	
}

inline void Igrac::reset()
{   
	smjer = Smjer::Nista;
	pozicija = Vector2f(500.f, 1000.f - 100.f);
	brzina = 250.f;
	brzina_metka = 500.f;
	sprite.setPosition(pozicija);
	metak.aktivan = false;
	brzivota = 3;
	broj_bodova = 0;

}

void Igrac::update() {

	if (smjer == Smjer::Lijevo) {
		pozicija.x = max<float>(pozicija.x - (brzina * vrijeme.asSeconds()) ,40); 
	}
	else if (smjer == Smjer::Desno) {
		pozicija.x = min<float>((brzina * vrijeme.asSeconds()) + pozicija.x, 1000 - 40);
	}

}

void Igrac::renderiraj(Prozor* p){

	sprite.setPosition(pozicija);
	p->crtaj(sprite);
	crtaj_metak(p);

}

void Igrac::ucitaj_slike() {

	tekstura.loadFromFile("playerzeleni.png");
	sprite.setTexture(tekstura);
	sprite.setTextureRect(IntRect(0, 0, 74, 60));
	sprite.setOrigin(37,30);

	tekstura_metak.loadFromFile("Metaknovi.png");
	sprite_metak.setTexture(tekstura_metak);
	sprite_metak.setOrigin(24, 24);


	
}

void Igrac::update_metak() {

	if (metak.aktivan) {
		metak.y -= brzina_metka * vrijeme.asSeconds();
		if (metak.y < 0) {
			metak.aktivan = false; // Deaktiviraj metak ako izaðe izvan ekrana
		}
	}
}

void Igrac::pucaj() {

	if (!metak.aktivan) { //ako nije aktivan
		metak.x = pozicija.x;
		metak.y = pozicija.y - 30.f;
		metak.aktivan = true;
	}
	
}

void Igrac::crtaj_metak(Prozor* p) {

	if (metak.aktivan) {
		sprite_metak.setPosition(metak.x, metak.y);
		p->crtaj(sprite_metak);
	}

}

 bool Igrac::pogoden(Metak& m)
{
	
	 IntRect igracRect(pozicija.x-37.f, pozicija.y-30.f, 75, 60); //provjeri jos malo ovo
	 IntRect metakRect(m.x, m.y, 6, 12);

	 if (igracRect.intersects(metakRect) && m.aktivan == true) {
		 m.aktivan = false;
		 return true;
	 }

	 return false;

}
