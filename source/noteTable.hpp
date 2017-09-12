#pragma once

class NoteTable {
public:
	NoteTable(double aHz1 = 440);
	~NoteTable();

	const double getFreq(int note);
	const double getTuning();

private:
	const int middleA = 69;
	const int middleC = middleA - 9;
	const int middleOctave = 4;
	const int lowestOctave = -2;
	const int highestOctave = 10;
	const int octaveSpan = lowestOctave + 1 + highestOctave;
	const int noteNum = 12 * octaveSpan;
	const int lowestNote = middleC + 12 * (lowestOctave - middleOctave);
	const int higestNote = middleC + 12 * (highestOctave - middleOctave);
	const double aHz;

	double* m_table;
};