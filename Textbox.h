#pragma once
#include<iostream>
#include<string>
#include<deque>
#include"Prozor.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Textbox {
public: 
	void Postavi(int, int, float, Vector2f);
	Textbox(); //Textbox t;
	Textbox(int, int, float, Vector2f);
	~Textbox();
	void ocisti();
	void dodaj(string);
	void renderiraj(Prozor*);
private:
	Font font;
	Text tekst;
	int brLinija;
	deque<string> poruke;
	RectangleShape pozadina;
};

 void Textbox::Postavi(int brL, int velZ, float sirina, Vector2f pozicija)
{  
	 brLinija = brL;
	 font.loadFromFile("font.ttf");
	 tekst.setFont(font);
	 tekst.setString("");
	 tekst.setCharacterSize(velZ);
	 tekst.setFillColor(Color::White);
	 tekst.setPosition(pozicija + Vector2f(2.f, 2.f));
	 pozadina.setPosition(pozicija);
	 pozadina.setFillColor(Color::Black);
	 pozadina.setSize(Vector2f(sirina, brL * (velZ * 1.2f)));
}

Textbox::Textbox()
{ 
	Postavi(1, 40, 100, Vector2f(0, 0));
}

Textbox::Textbox(int brL, int velZ, float sirina, Vector2f pozicija)
{  
	Postavi(brL, velZ, sirina, pozicija);
}

Textbox::~Textbox()
{  
	ocisti();
}

void Textbox::ocisti() {
	poruke.clear();
}

void Textbox::dodaj(string nova) {
	poruke.push_back(nova);
	if (poruke.size() > brLinija) {
		poruke.pop_front();
	} 
}

 void Textbox::renderiraj(Prozor* p)
 {
	 string sadrzaj;
	 for (auto& it : poruke) {
		 sadrzaj.append(it + "\n");
	 }
	 if (sadrzaj != "") {
		 tekst.setString(sadrzaj);
		 p->crtaj(pozadina);
		 p->crtaj(tekst);
	 }
}
