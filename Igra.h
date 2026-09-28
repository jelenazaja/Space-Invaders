#pragma once
#include <iostream>
#include <string>
#include<vector>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Prozor.h"
#include"Igrac.h"
#include"Protivnik.h"
#include"Textbox.h"
#include"Zid.h"


using namespace sf;
using namespace std;


class Igra {
public:
	 Igra();
	~Igra();
	void update();
	void obradiUlaz();
	void renderiraj();
	Prozor* dohvatiProzor() {
		return &p;
	}
	Time protekloVrijeme();
	void restartSata();

private:

	Prozor p;
	Textbox textbox, textbox2;
	Sprite sprite_pocetna;
	Texture tekstura_pocetna;
	Clock sat;
	Time vrijeme;

	Igrac igrac_;
	Protivnik protivnik;
	vector<Zid> zidovi;
	vector<Protivnik> protivnici;
	bool rub;
	bool pocetna, kraj_igre;
	bool zastavica;
	bool svi_unisteni;
	float brzina;
	
	//fje
	void ucitaj_slike();
	void pomakni_protivnike();
	void renderiraj_protivnike();
	void renderiraj_zidove();
	void pomakni_sve_dole();
	void ubi_protivnika();
	void brisi_pogodenog(Protivnik&);
	void protivnik_puca();
	void jel_igrac_pogoden();
	void povecaj_brzinu();
	void salji_vrijeme();
	void pogoden_zid();
	void reset_igre();
	void brza_igra(float);

};


Igra::Igra(): p("SpaceInvaders", sf::Vector2u(1000, 1000)), textbox2(1,40,100, Vector2f(190,0)){

	ucitaj_slike();
	reset_igre();
	
}

Igra::~Igra() {

}

void Igra::reset_igre() { //na pocetku igre

	protivnici.clear();
	protivnik.reset();

	for (int i = 5; i >= 0; i--) {
		for (int j = 10; j >= 0; j--) {
			protivnik.x = 160.f + 80 * j;
			protivnik.y = 150.f + 40.f * i;
			protivnik.smjer = 1;//na pocetku igre svi krecu prema desno
			protivnici.push_back(protivnik);
		}
	}
	zidovi.clear();

	for (int i = 0; i < 4; i++) {
		float pomak = i * 250.f;
		Zid z(pomak);
		zidovi.push_back(z);
	}

	for (Zid& i : zidovi) {
		i.ucitaj_slike();
	}

	brzina = 0; //za ubrzanje posli
	rub = false;
	pocetna = true;
	kraj_igre = false;
	textbox.dodaj("BODOVI: " + to_string(igrac_.broj_bodova));
	textbox2.dodaj("ZIVOTI: " + to_string(igrac_.brzivota));
	zastavica = false;
	svi_unisteni = false;
    igrac_.reset();

}

void Igra::brza_igra(float b) { //ubrzana igra za b i pomaknuti vanzemaljvi dolje za 2*b
	protivnici.clear();
	protivnik.reset();

	for (int i = 5; i >= 0; i--) {
		for (int j = 10; j >= 0; j--) {
			protivnik.x = 160.f + 80 * j;
			protivnik.y = 120.f + (b*2.f) + 40.f * i;
			protivnik.smjer = 1;//na pocetku igre svi krecu prema desno
			protivnik.brzina += b;
			protivnici.push_back(protivnik);
		}
	}
	zidovi.clear();

	for (int i = 0; i < 4; i++) {
		float pomak = i * 250.f;
		Zid z(pomak);
		zidovi.push_back(z);
	}

	for (Zid& i : zidovi) {
		i.ucitaj_slike();
	}

	rub = false;
	pocetna = false;
	kraj_igre = false;
	textbox.dodaj("BODOVI: " + to_string(igrac_.broj_bodova));
	textbox2.dodaj("ZIVOTI: " + to_string(igrac_.brzivota));
	zastavica = true;
	svi_unisteni = false;
	
}

inline void Igra::update()
{
	if (zastavica) {

		salji_vrijeme();
		igrac_.update(); //pomakni igraca lijevo/desno
		igrac_.ucitaj_slike();
        pomakni_protivnike(); //pomici sve protivnike
		protivnik_puca();
		jel_igrac_pogoden();
		igrac_.update_metak();
		ubi_protivnika();
		pogoden_zid();

	}
	
}

inline void Igra::obradiUlaz()
{   
	Event d;

	while (p.dogadaji(d)) {

		if (d.type == Event::Closed) {
			p.zatvori();
		}
		if (pocetna) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (d.mouseButton.x > 416 && d.mouseButton.x < 570) {
					if (d.mouseButton.y > 408 && d.mouseButton.y < 465) {
						pocetna = false;
						zastavica = true;
					}
	
				}
			}
		}
		else {

			if (d.type == sf::Event::KeyPressed) {

				if (d.key.code == sf::Keyboard::Left)
				{
					igrac_.PostaviSmjer(Smjer::Lijevo);
				}
				else if (d.key.code == sf::Keyboard::Right)
				{
					igrac_.PostaviSmjer(Smjer::Desno);
				}
				else if (d.key.code == sf::Keyboard::Space) {

					igrac_.pucaj();

				}

			}
			else {

				igrac_.PostaviSmjer(Smjer::Nista);
			}
		}
	}
}

void Igra::renderiraj()
{
	p.ocisti();
	if (pocetna) {
		p.crtaj(sprite_pocetna);
		
	}
	else {
		if (kraj_igre) {
			p.crtaj(sprite_pocetna);
			reset_igre();
		}
		else {
			if (svi_unisteni) {
				brza_igra(brzina);

			}
			else {
				renderiraj_protivnike();
				igrac_.renderiraj(&p);
				textbox.renderiraj(&p);
				textbox2.renderiraj(&p);
				renderiraj_zidove();
			}
		}
	}
	
	p.prikazi();
}

inline void Igra::ucitaj_slike()
{  
	tekstura_pocetna.loadFromFile("pocetna.png");
	sprite_pocetna.setTexture(tekstura_pocetna);
}

void Igra::pomakni_protivnike() {

	for (Protivnik& i : protivnici) {
		i.pomakni();
		if (i.narubu) rub = true; //prvi koji je dosao do ruba dovoljno jer je onda i svaki iznad njega
		i.narubu = false;
	}

	if (rub) {
		pomakni_sve_dole();
		if (protivnici[0].y > 740.f) {
			for (Zid& i : zidovi) {
				i.unisten = true; //unisti sve zidove ako dodu do tu protivnici 
			}
		}
		povecaj_brzinu();
		//provjera jesmo li dosli do donjeg dijela ekrana
		if (protivnici[0].y > 850.f) {
			reset_igre();
		}
		rub = false;
	}

}

void Igra::povecaj_brzinu() {

	for (Protivnik& i : protivnici) {
		i.brzina += 0.01;
	}

}

void Igra::renderiraj_protivnike() {
	int br = 0;
	for (Protivnik& i : protivnici) {
		
			i.renderiraj(&p, br);
			br++;
			i.animacija();

		}
	
}

void Igra::renderiraj_zidove() {

	for (Zid& i : zidovi) {
		i.renderiraj_zid(&p);
	}

}

void Igra::pomakni_sve_dole() {
	 
	for (Protivnik& i : protivnici) {
		i.pomakni_dole();
	}
}

void Igra::ubi_protivnika() {
	int br = 0;
	for (Protivnik& i : protivnici) {
		if (i.pogoden(igrac_.metak)) {
			//brisi protivnika i igrac dobiva bodove
			if (br >= 0 && br <= 10) {
				igrac_.broj_bodova += 20;
				brisi_pogodenog(i);
				textbox.dodaj("BODOVI: " + to_string(igrac_.broj_bodova));
				break;
			}
			if (br >= 11 && br <= 21) {
				igrac_.broj_bodova += 30;
				brisi_pogodenog(i);
				textbox.dodaj("BODOVI: " + to_string(igrac_.broj_bodova));
				break;
			}
			else {
				igrac_.broj_bodova += 10;
				brisi_pogodenog(i);
				textbox.dodaj("BODOVI: " + to_string(igrac_.broj_bodova));
				break;
			}
			
		}
		br++;
	}
}

void Igra::brisi_pogodenog(Protivnik& p) {

	p.mrtav = true;
	
}

void Igra::protivnik_puca() {
	int nasli = 0;

	vector<Protivnik*> zivi_protivnici; //dohvatimo sve zive protivnike koji mogu pucati
	for (Protivnik& p : protivnici) {
		if (!p.mrtav) {
			zivi_protivnici.push_back(&p);
		}
	}

	if (!zivi_protivnici.empty()) {

		uniform_int_distribution<> dis(0, zivi_protivnici.size() - 1);
		static default_random_engine e(time(0));

		Protivnik* randomProtivnik = zivi_protivnici[dis(e)];

		for (Protivnik& p : protivnici) {
			if (p.metak.aktivan == true) { //netko vec puca --  ne radi nista
				nasli = 1;
				p.update_metak();
			}
		}
		if (!nasli) { //nitko ne puca
			randomProtivnik->pucaj();
			randomProtivnik->update_metak();
		}	
	}
	else {
	
	   //svi umrli protivnici
		svi_unisteni = true;
	
	}

}
 
void Igra::jel_igrac_pogoden() {

	for (Protivnik& i : protivnici) {
		if (i.mrtav == false && i.metak.aktivan == true) { //nasli protivnika koji je pucao
			if (igrac_.pogoden(i.metak)) {
				igrac_.brzivota--;
				textbox2.dodaj("ZIVOTI: " + to_string(igrac_.brzivota));
			}
		}
	}
	if (igrac_.brzivota == 0) {
		kraj_igre = true;
	}
}

Time Igra::protekloVrijeme() {
	return vrijeme;
}

void Igra::restartSata() {
	vrijeme = sat.restart();
}

void Igra::salji_vrijeme() {

	igrac_.vrijeme = protekloVrijeme();

	for (Protivnik& i : protivnici) {
		i.vrijeme = protekloVrijeme();
	}
}

void Igra::pogoden_zid() {

	if (igrac_.metak.aktivan == true) {
		for (Zid& i : zidovi) {
			i.pogoden(igrac_.metak, 0);
		}
	}
	for (Protivnik& i : protivnici) {
		if (i.metak.aktivan == true) {
			for (Zid& j : zidovi) {
				j.pogoden(i.metak, 1);
			}
		}
	}
}

