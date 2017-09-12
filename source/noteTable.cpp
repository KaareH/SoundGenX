#include "noteTable.hpp"

#include <cmath>
#include <iostream>

NoteTable::NoteTable(double aHz1) : aHz(aHz1) {
	m_table = new double[noteNum];

	for(int i = 0; i < noteNum; i++) {
		const int relativeToC = i - lowestNote - middleC;
		m_table[i] = aHz * std::pow(2, (relativeToC - 9) / 12.0f);
		std::cout << "Array pos: " << i << " Relative to c: " << relativeToC << " Freq: " << m_table[i] << " Midi num:" << i + lowestNote << std::endl;
	}
}

NoteTable::~NoteTable() {
	delete[] m_table;
};

const double NoteTable::getFreq(int note) {

}

const double NoteTable::getTuning() {
	return aHz;
}
