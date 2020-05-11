#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
protected:
	unsigned int m_day;
public:
	//Commento prova
	Date(unsigned int=1, unsigned int=0, unsigned int=0);
	Date(std::string);
	Date(const Date&);
	~Date();

	/*Getters*/

	/*Setters*/

	/*Date class operators*/

	Date& operator=(const Date&);
	bool operator==(const Date&);
	bool operator!=(const Date&);
	bool operator<(const Date&);

};

#endif // DATE_H
