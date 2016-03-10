#pragma once

//Remember the RUle of three!

class Card
{
public:
	Card(int cardId);
	~Card();

	void generateName(int cardID);
	const char* getName();
	int getCardId();

private:
	int m_cardId;
	char *m_myName;
};

