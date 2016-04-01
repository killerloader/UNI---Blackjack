#pragma once

//Remember the RUle of three!

class Card
{
public:
	Card(int cardId);

	//Probably wont be used, but for the rule of three.
	Card::Card(Card &Ocard);//Copy constructor.
	void operator=(Card &Ocard)//Also copy constructor
	{
		if (m_myName != nullptr)
			delete[] m_myName;//Delete old card name if it is already created (pretty much certain)
		
		m_cardId = Ocard.getCardId();
		m_cardSuit = m_cardId / 13;
		m_cardNum = m_cardId - m_cardSuit * 13;
	}
	~Card();

	int getCardValue();
	void generateName(int cardID);
	const char* getName();
	int getCardId();

private:
	int m_cardId;
	int m_cardNum;//2 - 10, ace, jack, queen or king. (0-12)
	int m_cardSuit;
	char *m_myName;
};

