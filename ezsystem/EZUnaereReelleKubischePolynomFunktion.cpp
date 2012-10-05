#include "EZStandard.h"
#include "EZUnaereReelleKubischePolynomFunktion.h"
#include <algorithm>

/////////////////////////////////////////////////////////////////////////////

namespace EZ
{

/////////////////////////////////////////////////////////////////////////////

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(UnaereReelleKubischePolynomFunktion)
    IMPLEMENTIERT_SCHNITTSTELLE(sUnaereReelleFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(UnaereReelleKubischePolynomFunktion)

//////////////////////////////////////////////////////////////////////

UnaereReelleKubischePolynomFunktion::UnaereReelleKubischePolynomFunktion(double a, double b, double c, double d,
																		 double beginn, double ende)
{
    KONSTRUIERE_SCHNITTSTELLE;
	m_koeffizienten.push_back(a);
	m_koeffizienten.push_back(b);
	m_koeffizienten.push_back(c);
	m_koeffizienten.push_back(d);
	m_beginn= beginn; m_ende = ende;
}

//////////////////////////////////////////////////////////////////////

UnaereReelleKubischePolynomFunktion::~UnaereReelleKubischePolynomFunktion()
{
}

//////////////////////////////////////////////////////////////////////

double UnaereReelleKubischePolynomFunktion::definitionsminimum()
{
    return m_beginn;
}

//////////////////////////////////////////////////////////////////////

double UnaereReelleKubischePolynomFunktion::definitionsmaximum()
{
    return m_ende;
}

//////////////////////////////////////////////////////////////////////

Punkt3D UnaereReelleKubischePolynomFunktion::bestimmeAbleitungen(double definitionswert)
{
    double x = definitionswert - m_beginn;
	double y = 0;
	std::vector<double> ableitungskoeffizienten;
	std::vector<double> zweiteableitungskoeffizienten;

	// Hornerscheme zur Bestimmung des Funktionswertes
	for (std::vector<double>::iterator koeffizienten_iterator=m_koeffizienten.begin();
		koeffizienten_iterator<m_koeffizienten.end();
		koeffizienten_iterator++)
	{
		y *= x;
		y += *koeffizienten_iterator;
		if (koeffizienten_iterator<m_koeffizienten.end()-1)
			ableitungskoeffizienten.push_back(y);
	}

	double y_ableitung = 0;
	// Bestimmung der ersten Ableitung
	for (std::vector<double>::iterator koeffizienten_iterator=ableitungskoeffizienten.begin();
		koeffizienten_iterator<ableitungskoeffizienten.end();
		koeffizienten_iterator++)
	{
		y_ableitung *= x;
		y_ableitung += *koeffizienten_iterator;
		if (koeffizienten_iterator<ableitungskoeffizienten.end()-1)
			zweiteableitungskoeffizienten.push_back(y_ableitung);
	}

	double y_zweiteableitung = 0;

	// Bestimmung der zweiten Ableitung
	for (std::vector<double>::iterator koeffizienten_iterator=zweiteableitungskoeffizienten.begin();
		koeffizienten_iterator<zweiteableitungskoeffizienten.end();
		koeffizienten_iterator++)
	{
		y_zweiteableitung *= x;
		y_zweiteableitung += *koeffizienten_iterator;
	}

	return Punkt3D(y, y_ableitung, y_zweiteableitung);


}

//////////////////////////////////////////////////////////////////////

double UnaereReelleKubischePolynomFunktion::operator()(double definitionswert)
{
    double x = definitionswert - m_beginn;
	double y = 0;

	// Hornerscheme zur Bestimmung des Funktionswertes
	for (std::vector<double>::iterator koeffizienten_iterator=m_koeffizienten.begin();
		koeffizienten_iterator<m_koeffizienten.end();
		koeffizienten_iterator++)
	{
		y *= x;
		y += *koeffizienten_iterator;
	}
	return y;
}

/////////////////////////////////////////////////////////////////////////////

};

/////////////////////////////////////////////////////////////////////////////