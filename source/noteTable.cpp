#include "noteTable.hpp"

#include <cmath>
#include <iostream>

NoteTable::NoteTable(double aHz1) : aHz(aHz1) {
	m_table = new double[noteNum];

	for(int i = 0; i <= noteNum; i++) {
		const int relativeToC = i - lowestNote - middleC;
		m_table[i] = aHz * std::pow(2, (relativeToC - 9) / 12.0f);
		//std::cout << "Array pos: " << i << " Relative to c: " << relativeToC << " Freq: " << m_table[i] << " Midi num:" << middleCMidi + relativeToC << std::endl;
	}
}

NoteTable::NoteTable(const NoteTable &obj) : aHz(obj.aHz) {
	m_table = new double[noteNum];
	memcpy(m_table, obj.m_table, noteNum * sizeof *m_table);
}

NoteTable::~NoteTable() {
	delete[] m_table;
};

const double NoteTable::getNoteFreq(int midiId) {
	return m_table[middleC - middleCMidi + midiId];
}

const double NoteTable::getTuning() {
	return aHz;
}
