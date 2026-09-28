#pragma once
#include<iostream>
#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include"Prozor.h"
#include"Igra.h"
#include"Protivnik.h"
#include"Igrac.h"

using namespace std;
using namespace sf;

class Zid {
    friend class Igra;
private:
 
    Sprite sprite;
    Texture tekstura;
    bool unisten;
    Vector2f pozicija;

public:
	Zid();
    Zid(float);
	void renderiraj_zid(Prozor*);
    void pogoden(Metak&, bool);
    void unisti_zid();
    void sredi_teksturu(Texture&);
    void PostaviBojuPiksela( unsigned int x, unsigned int y);
    void unisti( unsigned int, unsigned int);
    void unisti_p(unsigned int, unsigned int);

    void ucitaj_slike();

};

Zid::Zid(){

    sprite.setPosition(60, 800);  // Postavljanje pozicije pravokutnika
   pozicija = Vector2f(60.f, 800.f);
    unisten = false;
    
 
}

Zid::Zid(float pomak){

   
    sprite.setPosition(60.f + pomak, 800.f);
    pozicija = Vector2f(60.f + pomak, 800.f);
    unisten = false;


}

void Zid::ucitaj_slike() {

    tekstura.loadFromFile("ZID.png");
    sprite.setTexture(tekstura);

}

void Zid::PostaviBojuPiksela( unsigned int x, unsigned int y) {
    
    Image image = tekstura.copyToImage();
    if (x < image.getSize().x && y < image.getSize().y) {
        if (image.getPixel(x, y) != Color::Black) {
            image.setPixel(x, y, Color::Black);
            tekstura.loadFromImage(image);
        }
    }
}

inline void Zid::unisti(unsigned int a, unsigned int b)
{   
    int x = a - pozicija.x;
    int y = b - pozicija.y;
   
    for (int i = 0; i <= y + 5 && i < tekstura.getSize().y; i++) {
        if (i < 0) continue;
        for (int j = x - 5; j <= x + 5 && j < tekstura.getSize().x; j++) {
            if (j < 0) continue;
            PostaviBojuPiksela(j, i);
        }
    }

}

inline void Zid::unisti_p(unsigned int a, unsigned int b)
{  
    int x = a - pozicija.x;
    int y = b - pozicija.y + 30;
    
    for (int i = 0; i <= y + 5 && i < tekstura.getSize().y; i++) {
        if (i < 0) continue;
        for (int j = x - 5; j <= x + 5 && j < tekstura.getSize().x; j++) {
            if (j < 0) continue;
            PostaviBojuPiksela(j, i);
        }
    }
}


 void Zid::renderiraj_zid(Prozor *p)
{   
     if (!unisten)
     p->crtaj(sprite);
    
}

 void Zid::pogoden(Metak& m, bool vrsta) { //ako je metak od igraca onda vrsta = 0 a ako je od protivnika onda vrsta = 1

     IntRect zidRect(pozicija.x, pozicija.y, 140.f,40.f);
  
     if (!vrsta) { //metak je od igraca
         IntRect metakRect(m.x, m.y, 10, 10);

         if (zidRect.intersects(metakRect) && unisten == false) {
             
             m.aktivan = false;
             unsigned int a = (unsigned int)m.x;
             unsigned int b = (unsigned int)m.y;
             unisti(a,b);
            
         }

     }
     if (vrsta) { //metak je od protivnika

         IntRect metakRect(m.x, m.y, 6, 12);

         if (zidRect.intersects(metakRect) && unisten == false) {
             m.aktivan = false;
             
             unsigned int a = static_cast<unsigned int>(m.x);
             unsigned int b = static_cast<unsigned int>(m.y);
  
             unisti_p(a, b);
         }

    }

  
 }

