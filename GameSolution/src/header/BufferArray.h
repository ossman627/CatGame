#pragma once
#include <vector>
#include "Debugger.h"

//Struktur um das LAyout zu speichern
struct Layout {
	unsigned int index;					//Index der ersten Werte des Strides
	int size;							//Anzahl der Werte die sich in dem Index befinden
	int stride;							//die Größe eines Vertexes
	int offset;
};

class BufferArray {
private:
	std::vector<Layout>bufferLayouts;	//Speichert die eingestellten Layouts

public:
	BufferArray();
	~BufferArray();

	//Definition eines Floatlayouts
	void addLayoutF(unsigned int index, int size, int stride, int offset);

	//Bestimmtes Layout wird aktiviert
	void aktivateLayout(unsigned int index);

	//Alle definierten Layouts werden aktiviert
	void aktivateAllLayouts();
};