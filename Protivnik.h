#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<cmath>
#include<ctime>
#include <SFML/Graphics.hpp>
#include "Prozor.h"
#include"Igrac.h"

using namespace sf;
using namespace std;


class Protivnik {
	friend class Igra;
private:

	float x;
	float y;
	float brzina;
	float brzina_metka;

	Sprite sprite_protivnik, sprite2, sprite_metak, sprite3, sprite33, sprite4, sprite44;
	Texture tekstura_protivnik, tekstura2, tekstura_metak, tekstura3, tekstura33, tekstura4, tekstura44;
	int smjer;
	bool narubu;
	bool mrtav;
	Metak metak;
	Time vrijeme;
	int put;
	int frame;
	

public:

	Protivnik();
	Protivnik(float a, float b, int s);
	bool operator==(Protivnik&);
	void reset();
	void renderiraj(Prozor* p,int);
	void ucitaj_slike();
	void pomakni();
	void pomakni_dole();
	bool pogoden(Metak& m);
	void pucaj();
	void update_metak();
	void crtaj_metak(Prozor* p);
	void animacija();



};

inline Protivnik::Protivnik()
{  
	
	reset();

}

Protivnik::Protivnik(float a, float b, int s) 
{
	x = a;
	y = b;
	brzina = 50.f;
	brzina_metka = 350.f;
	narubu = false; 
	mrtav = false; 
	smjer = s;
	ucitaj_slike();
	metak.aktivan = false;
	put = 0;
	frame = 1;

}

bool Protivnik::operator==( Protivnik &p)
{   
	if (x == p.x && y == p.y) return true;
	return false;
}

 void Protivnik::reset()
{   
	 brzina = 50.f;
	 brzina_metka = 350.f;
	 x = 160.f;
	 y = 40.f;
	 smjer = 0;
	 narubu = false; //na pocetku nitko nije na rubu
	 mrtav = false; //svi protivnici zivi na pocetku
	 ucitaj_slike();
	 metak.aktivan = false;
	 put = 0;
	 frame = 1;
}

inline void Protivnik::renderiraj(Prozor* p, int br)
{    
	if (mrtav == false) {
		if (put == 0) {
			if (br >= 0 && br <= 10) {
				sprite_protivnik.setPosition(x, y);
				p->crtaj(sprite_protivnik);
				crtaj_metak(p);
			}
			if (br >= 11 && br <= 21) {
				sprite3.setPosition(x, y);
				p->crtaj(sprite3);
				crtaj_metak(p);
			}
			else {
				sprite4.setPosition(x, y);
				p->crtaj(sprite4);
				crtaj_metak(p);
			}
		}
		else {
			if (put == 1) {
				if (br >= 0 && br <= 10) {
					sprite2.setPosition(x, y);
					p->crtaj(sprite2);
					crtaj_metak(p);
				}
				if (br >= 11 && br <= 21) {
					sprite33.setPosition(x, y);
					p->crtaj(sprite33);
					crtaj_metak(p);
				}
				else {
					sprite44.setPosition(x, y);
					p->crtaj(sprite44);
					crtaj_metak(p);
				}
			}
		}

	}
}

 void Protivnik::ucitaj_slike()
{    
	tekstura_protivnik.loadFromFile("Protivniknovi.png");
	sprite_protivnik.setTexture(tekstura_protivnik);
	sprite_protivnik.setTextureRect(IntRect(0, 0, 80, 80));
	sprite_protivnik.setOrigin(40, 40);
    
	tekstura2.loadFromFile("pomaknutP.png");
	sprite2.setTexture(tekstura2);
	sprite2.setOrigin(40, 40);

	tekstura3.loadFromFile("protivnik1.png");
	sprite3.setTexture(tekstura3);
	sprite3.setOrigin(40, 40);

	tekstura33.loadFromFile("protivnik11.png");
	sprite33.setTexture(tekstura33);
	sprite33.setOrigin(40, 40);

	tekstura4.loadFromFile("protivnik2.png");
	sprite4.setTexture(tekstura4);
	sprite4.setOrigin(40, 40);

	tekstura44.loadFromFile("protivnik22.png");
	sprite44.setTexture(tekstura44);
	sprite44.setOrigin(40, 40);

	tekstura_metak.loadFromFile("projektilnovi.png");
	sprite_metak.setTexture(tekstura_metak);
	sprite_metak.setTextureRect(IntRect(0, 0, 6, 12));
	sprite_metak.setOrigin(3,6 );
	
}

 void Protivnik::pomakni() { 

	
	 frame++;


		 if ((1 == smjer & x == 1000 - 40) || (-1 == smjer && x == 40) ) //ako smo dosli na rub
		 {

			 narubu = true;

		 }
		 else
		 {
			 if (1 == smjer) { //ide desno

				 if (x + brzina * vrijeme.asSeconds() < 40) x = 40;
				 else if (x + brzina * vrijeme.asSeconds() > 1000 - 40) x = 1000 - 40;
				 else x = x + brzina * vrijeme.asSeconds();

			 }
			 else if (-1 == smjer) {// ide lijevo
				
				 if (x - brzina * vrijeme.asSeconds() < 40) x = 40;
				 else if (x - brzina * vrijeme.asSeconds() > 1000 - 40) x = 1000 - 40;
				 else x = x - brzina * vrijeme.asSeconds();

			 }

		 }
		
 }

 inline void Protivnik::pomakni_dole()
 {   
	 y += 20.f; 
	 //treba promijeniti smjer
	 smjer = (smjer == 1) ? -1 : 1;
	
	 
 }

 bool Protivnik::pogoden(Metak& m)
 {  
	 IntRect protivnikRect(x, y, 80, 80); 
	 IntRect metakRect(m.x, m.y, 48, 48); 

	 if (protivnikRect.intersects(metakRect) && mrtav == false && m.aktivan == true) {
		 mrtav = true;
		 m.aktivan = false;
		 return true;
	 }

	 return false;
 }

 void Protivnik::pucaj()
 {  
	 if (!metak.aktivan) { //ako nije aktivan
		 metak.x = x;
		 metak.y = y + 40.f;
		 metak.aktivan = true;
	 }

 }

 void Protivnik::update_metak()
 { 
	 if (metak.aktivan) {
		 metak.y += brzina_metka * vrijeme.asSeconds();
		 if (metak.y > 1000) {
			 metak.aktivan = false; // Deaktiviraj metak ako izaðe izvan ekrana
		
		 }
	 }
 }

 void Protivnik::crtaj_metak(Prozor* p)
 {   
	 if (metak.aktivan) {
		 sprite_metak.setPosition(metak.x, metak.y);
		 p->crtaj(sprite_metak);
	 }
 }

 void Protivnik::animacija()
 {   
	 if (frame == 150) {
		 put = (put == 0) ? 1 : 0;
		 frame = 1;
	 }
 }

 



