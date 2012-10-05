#include "EZStandard.h"
#include "EZKreiswegstueck.h"
#include "EZPunkt3D.h"
#include "EZRotation2D.h"
#include "EZFahrzeugdatenkette.h"
#include "EZNumerik.h"
#include "EZWinkelWrapper.h"

namespace EZ
{


REIMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Kreiswegstueck, Wegstueck)
    IMPLEMENTIERT_SCHNITTSTELLE_BASISKLASSE(Wegstueck)
REIMPLEMENTIERE_SCHNITTSTELLE_ENDE(Kreiswegstueck, Wegstueck)


//////////////////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////

Kreiswegstueck::Kreiswegstueck()
	:	Wegstueck()
{
}



Kreiswegstueck::Kreiswegstueck(Punkt2D startpunkt, Punkt2D endpunkt,
	     Punkt2D mittelpunkt, bool rechtsfahrt, bool rueckwaerts,
         double geschwindigkeit)
         : Wegstueck (startpunkt, endpunkt, rueckwaerts, geschwindigkeit)
{
	setzeAttribute(startpunkt, endpunkt, mittelpunkt, rechtsfahrt, rueckwaerts, geschwindigkeit);
}


/////////////////////////////////////////////////////////////////////////////////


void Kreiswegstueck::setzeAttribute(Punkt2D startpunkt, Punkt2D endpunkt,
	     Punkt2D mittelpunkt, bool rechtsfahrt, bool rueckwaerts,
         double geschwindigkeit)
{
	// setzeAttribute darf nur einmal aufgerufen werden
	if (!m_initialisiert)
	{
		// Setze die Attribute
		Wegstueck::setzeAttribute(startpunkt,endpunkt,rueckwaerts,geschwindigkeit);
		//m_startpunkt		= startpunkt;
		//m_endpunkt			= endpunkt;
		m_mittelpunkt		= mittelpunkt;
		m_rechtsfahrt		= rechtsfahrt;
		//m_rueckwaerts		= rueckwaerts;
		//m_geschwindigkeit	= geschwindigkeit;

		// Berechne den Radius
		m_radius = (m_mittelpunkt-m_startpunkt).laenge();

		// Berechne Startwinkel, Endwinkel und Kurvenwinkel
		aktualisiereWinkel();

		m_weglaenge = m_radius * m_winkel;
		m_initialisiert = true;
	}
}


/////////////////////////////////////////////////////////////////////////////////


Kreiswegstueck::~Kreiswegstueck()
{
}


////////////////////////////////////////////////////////////////////////////////


Punkt2D Kreiswegstueck::position(double d) const
{
	// Berechne (absoluten) Winkel der Strecke (Mittelpunkt,Position)
	double winkel = rechtsfahrt()==rueckwaerts() ?
							startwinkel()+d/radius()	// Rechts-Rueckwaerts oder Links-Vorwaerts
						:	startwinkel()-d/radius();	// Links-Rueckwaerts oder Rechts-Vorwaerts
	// Berechne damit die Position
	return WinkelWrapper(winkel).einheitsvektor()*radius()+mittelpunkt();
}

double Kreiswegstueck::sollPositionDefinitionswert(Punkt2D punkt) const
{
	if (punkt == m_mittelpunkt)
	{
		// In diesem Fall kann der sollPositionDefinitionswert
		// nicht bestimmt werden
		return NaN();
	}

	// Berechne den Schnittpunkt zwischen Kreis und der Strecke zwischen Mittelpunkt und
	// dem gegebenen Punkt
	Punkt2D schnittpunkt = m_mittelpunkt + (punkt-m_mittelpunkt).normalisiere()*m_radius;

	// Berechne den (absoluten) Winkel der Strecke zwischen Mittelpunkt und dem Schnittpunkt
	WinkelWrapper schnittwinkel(schnittpunkt-m_mittelpunkt);

	// Berechne den Winkel zwischen dem Startpunkt und dem Schnittpunkt
	WinkelWrapper winkel = m_rechtsfahrt==m_rueckwaerts ?
								schnittwinkel-startwinkel()		// Rechts-Rueckwaerts oder Links-Vorwaerts
							:	-schnittwinkel+startwinkel();	// Links-Rueckwaerts oder Rechts-Vorwaerts

	// Winkel > 0.5*m_winkel+PI ergeben negativen Rückgabewert
	if (winkel.bogenmass() <= 0.5*m_winkel+PI)
		return winkel.bogenmass()*m_radius;
	else
		return (winkel.bogenmass()-2*PI)*m_radius;
}

double Kreiswegstueck::ausrichtung( double d ) const
{
	// Berechne (absoluten) Winkel der Strecke (Mittelpunkt,Position)
	WinkelWrapper winkel(startwinkel());
	winkel += (m_rechtsfahrt==m_rueckwaerts) ? d/m_radius : -d/m_radius;
	// Bei einer Rechtskurve liegt die Ausrichtung senkrecht-rechts dazu,
	// bei einer Linkskurve entsprechend senkrecht-links
	if (m_rechtsfahrt)
		return winkel.senkrechteRechts().bogenmass();
	else
		return winkel.senkrechteLinks().bogenmass();
}

bool Kreiswegstueck::verschiebe( Punkt2D differenz )
{
	// verschiebe Start- und Endpunkt
	Wegstueck::verschiebe(differenz);
	// verschiebe Mittelpunkt
	m_mittelpunkt	+= differenz;
	return true;
}

bool Kreiswegstueck::rotiere( Punkt2D mPunkt, double beta )
{
	// rotiere Start und Endpunkt
	Wegstueck::rotiere(mPunkt, beta);
	// rotiere Mittelpunkt
	m_mittelpunkt = Numerik::rotiere(m_mittelpunkt,mPunkt,beta);
	// aktualisiere Start- und Endwinkel
	aktualisiereWinkel();
	return true;

}

void Kreiswegstueck::aktualisiereWinkel()
{
	m_endwinkel		= WinkelWrapper(m_endpunkt-m_mittelpunkt).bogenmass();
	m_startwinkel	= WinkelWrapper(m_startpunkt-m_mittelpunkt).bogenmass();
	m_winkel		= m_rechtsfahrt==m_rueckwaerts?
							WinkelWrapper(endwinkel()-startwinkel()).bogenmass()
						:	WinkelWrapper(startwinkel()-endwinkel()).bogenmass();
}
/////////////////////////////////////////////////////////////////////////////


};