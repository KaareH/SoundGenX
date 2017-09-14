#pragma once

class NoteTable {
public:
	NoteTable(double aHz1 = 440);
	NoteTable(const NoteTable &obj);
	~NoteTable();

	const double getNoteFreq(int note);
	const double getTuning();

private:
	const int middleC = 60;
	const int middleA = middleC + 9;
	const int middleCMidi = 60;
	const int lowestNote = 0;
	const int highestNote = 127;
	const unsigned int noteNum = highestNote - lowestNote;

	const double aHz;

	double* m_table;
};