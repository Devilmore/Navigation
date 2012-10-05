#include "EZStandard.h"
#include "EZWegstueck.h"
#include "EZNumerik.h"

namespace EZ {

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Wegstueck)
	IMPLEMENTIERT_SCHNITTSTELLE(sWegstueck)
	IMPLEMENTIERT_SCHNITTSTELLE(sUnaerePlanareFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(Wegstueck)

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Wegstueck::Wegstueck()
	:	m_weglaenge			(0.0),
		m_geschwindigkeit	(0.0),
		m_initialisiert		(false)
{
	KONSTRUIERE_SCHNITTSTELLE;
}

Punkt2D Wegstueck::operator () (double t)
{
	return position(t);
}


Punkt2D Wegstueck::sollPosition(Punkt2D p) const
{
	return position(sollPositionDefinitionswert(p));
}

Wegstueck::Wegstueck(Punkt2D startpunkt, Punkt2D endpunkt, bool rueckwaerts,
        double geschwindigkeit)
	:	m_weglaenge			(0.0),
		m_initialisiert		(false)
{
	KONSTRUIERE_SCHNITTSTELLE;
	setzeAttribute(startpunkt,endpunkt,rueckwaerts,geschwindigkeit);
}

double Wegstueck::definitionsminimum()
{
	return 0.0;
}

double Wegstueck::definitionsmaximum()
{
	return m_weglaenge;
}


///////////////////////////////////////////////////////////////////////////////
// Destruktor

Wegstueck::~Wegstueck()
{

}


double Wegstueck::endausrichtung() const
{
	return ausrichtung(weglaenge());
}

double Wegstueck::startausrichtung() const
{
	return ausrichtung(0.0);
}

bool Wegstueck::verschiebe( Punkt2D differenz )
{
	m_startpunkt	+= differenz;
	m_endpunkt		+= differenz;
	return true;
}

bool Wegstueck::rotiere( Punkt2D mPunkt, double beta )
{
	m_startpunkt	= Numerik::rotiere(m_startpunkt,mPunkt,beta);
	m_endpunkt		= Numerik::rotiere(m_endpunkt,  mPunkt,beta);
	return true;
}

void Wegstueck::setzeAttribute( Punkt2D startpunkt, Punkt2D endpunkt, bool rueckwaerts, double geschwindigkeit )
{
	if (!m_initialisiert)
	{
		m_startpunkt		= startpunkt;
		m_endpunkt			= endpunkt;
		m_rueckwaerts		= rueckwaerts;
		m_geschwindigkeit	= geschwindigkeit;
	}
}
};
