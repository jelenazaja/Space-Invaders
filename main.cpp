#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Igra.h"

using namespace std;

int main() {

	Igra igra;

	while (!igra.dohvatiProzor()->jelGotov()) {

		igra.obradiUlaz();
		igra.update();
		igra.renderiraj();
		igra.restartSata();

	}
	return 0;
}