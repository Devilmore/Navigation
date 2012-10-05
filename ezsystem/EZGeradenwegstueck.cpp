#include "EZStandard.h"
#include "EZGeradenwegstueck.h"
#include "EZWinkelWrapper.h"

namespace EZ
{

REIMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Geradenwegstueck, Wegstueck)
	IMPLEMENTIERT_SCHNITTSTELLE_BASISKLASSE(Wegstueck)
REIMPLEMENTIERE_SCHNITTSTELLE_ENDE(Geradenwegstueck, Wegstueck)


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Geradenwegstueck::Geradenwegstueck(Punkt2D startpunkt, Punkt2D endpunkt,
        bool rueckwaerts, double geschwindigkeit)
		: Wegstueck(startpunkt, endpunkt, rueckwaerts, geschwindigkeit)
{
    m_weglaenge = (startpunkt-endpunkt).laenge();
}



Geradenwegstueck::Geradenwegstueck() : Wegstueck()
{

}

////////////////////////////////////////////////////////////////////////

Geradenwegstueck::~Geradenwegstueck()
{

}


///////////////////////////////////////////////////////////////////////////

void Geradenwegstueck::setzeAttribute(Punkt2D startpunkt, Punkt2D endpunkt, bool rueckwaerts, double geschwindigkeit)
{
    m_weglaenge = (startpunkt-endpunkt).laenge();
    m_rueckwaerts = rueckwaerts;
    m_startpunkt  = startpunkt;
    m_endpunkt    = endpunkt;
    m_geschwindigkeit = geschwindigkeit;
}


////////////////////////////////////////////////////////////////////////////


Punkt2D Geradenwegstueck::position(double d) const
{
	return m_startpunkt + (m_endpunkt-m_startpunkt).normalisiere()*d;
}


/////////////////////////////////////////////////////////////////////////////

double Geradenwegstueck::sollPositionDefinitionswert(Punkt2D punkt) const
{
    // gib Lotfusspunkt durch Punkt zurück
	Punkt2D richtungsvektor= WinkelWrapper(m_endpunkt-m_startpunkt).einheitsvektor();
	return richtungsvektor.punkt(punkt-m_startpunkt);
}

double Geradenwegstueck::ausrichtung( double) const
{
	if (!m_rueckwaerts)
		return WinkelWrapper(m_endpunkt-m_startpunkt).bogenmass();
	else
		return WinkelWrapper(m_startpunkt-m_endpunkt).bogenmass();
}

};