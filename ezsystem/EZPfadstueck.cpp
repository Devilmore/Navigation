#include "EZStandard.h"
#include "EZPfadstueck.h"
#include <vector>
#include "EZSteuerfunktionenKette.h"
#include "EZKonfigurationsfunktionenKette.h"
#include "EZUnaerePlanareFunktionsvisualisierung.h"

namespace EZ {

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Pfadstueck)
	IMPLEMENTIERT_SCHNITTSTELLE(sZeitVarianterPfad)
	IMPLEMENTIERT_SCHNITTSTELLE(sZeitInvarianterPfad)
	IMPLEMENTIERT_SCHNITTSTELLE(sUnaerePlanareFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(Pfadstueck)

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
Pfadstueck::Pfadstueck(bool _rueckwaerts, sFahrzeugbeschreibungskette::Zeiger _fahrzeugbeschreibung, sUnaereReelleFunktion::Zeiger _zeitfunktion)
	:	m_initialisiert (false)
{
	KONSTRUIERE_SCHNITTSTELLE;
	ASSERT(_fahrzeugbeschreibung != NULL)
	setzeAttribute(_rueckwaerts,_fahrzeugbeschreibung,NULL,NULL,_zeitfunktion);
}

Pfadstueck::Pfadstueck()
	:	m_initialisiert (false)
{
	KONSTRUIERE_SCHNITTSTELLE
}

double Pfadstueck::ausrichtung( unsigned short glied, double d ) const
{
	return m_konfigurationsfunktionen->ausrichtung(glied,d-definitionsOffset());
}

EZ::Punkt2D Pfadstueck::position( unsigned short glied, double d ) const
{
	return m_konfigurationsfunktionen->position(glied,d-definitionsOffset());
}

double Pfadstueck::lenkwinkel( unsigned short glied, double d ) const
{
	return m_konfigurationsfunktionen->lenkwinkel(glied,d-definitionsOffset());
}

double Pfadstueck::einknickwinkel( unsigned short kupplung, double d ) const
{
	return m_konfigurationsfunktionen->einknickwinkel(kupplung, d-definitionsOffset());
}

bool Pfadstueck::setzeAusrichtungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (   !(glied<anzahlGlieder())
		 ||(!m_konfigurationsfunktionen->setzeAusrichtungFunktion(glied,funktion)))
		return false;
	
	aktualisiereRaender();
	return true;
}

bool Pfadstueck::setzePositionFunktion( unsigned short glied, sUnaerePlanareFunktion::Zeiger funktion )
{
	if (   !(glied<anzahlGlieder())
		 ||(!m_konfigurationsfunktionen->setzePositionFunktion(glied,funktion)))
		return false;
	aktualisiereRaender();
	return true;
}

bool Pfadstueck::setzeLenkwinkelFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (   !(glied<anzahlGlieder())
		|| (m_fahrzeugbeschreibungen->beschreibung(glied)->ersterLenkwinkel()==0.0)
		|| !(m_konfigurationsfunktionen->setzeLenkwinkelFunktion(glied,funktion)))
		return false;
	
	aktualisiereRaender();
	return true;
}

bool Pfadstueck::setzeEinknickwinkelFunktion( unsigned short kupplung, sUnaereReelleFunktion::Zeiger funktion )
{
	if (   !(kupplung<anzahlGlieder()-1)
		 ||!(m_konfigurationsfunktionen->setzeEinknickwinkelFunktion(kupplung,funktion)))
		return false;

	aktualisiereRaender();
	return true;
}

double Pfadstueck::zeit( double d ) const
{
	return (*m_zeitfunktion)(d-definitionsOffset());
}

double Pfadstueck::startzeit() const
{
	if (m_zeitfunktion==NULL)
		return NaN();
	return (*m_zeitfunktion)(m_definitionsminimumInnen);
}

double Pfadstueck::endzeit() const
{
	if (m_zeitfunktion==NULL)
		return NaN();
	return (*m_zeitfunktion)(m_definitionsmaximumInnen);
}

double Pfadstueck::definitionswert( double zeit ) const
{
	// STUB
	return zeit;
}

double Pfadstueck::geschwindigkeit( unsigned short glied, double d ) const
{
	return m_steuerfunktionen->geschwindigkeit(glied,d-definitionsOffset());
}

double Pfadstueck::lenkwinkelAenderung( unsigned short glied, double d ) const
{
	return m_steuerfunktionen->lenkwinkelAenderung(glied,d-definitionsOffset());
}

double Pfadstueck::setzeGeschwindigkeitFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (m_steuerfunktionen->setzeGeschwindigkeitFunktion(glied,funktion))
	{
		aktualisiereRaender();
		return true;
	}
	return false;
}

bool Pfadstueck::setzeLenkwinkelAenderungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (m_steuerfunktionen->setzeLenkwinkelAenderungFunktion(glied,funktion))
	{
		aktualisiereRaender();
		return true;
	}
	return false;
}

bool Pfadstueck::aktualisiereRaender()
{
	// die Definitionsmaxima und -minima in Vektoren speichern,
	// um dann daraus den größten bzw. kleinsten Wert zu ermitteln.
	
	std::vector <double> minima;
	std::vector <double> maxima;
	
	minima.push_back(m_konfigurationsfunktionen->definitionsminimum());
	maxima.push_back(m_konfigurationsfunktionen->definitionsmaximum());
	minima.push_back(m_steuerfunktionen->definitionsminimum());
	maxima.push_back(m_steuerfunktionen->definitionsmaximum());

	// Alle NaN Werte entfernen
	minima.erase(remove_if(minima.begin(),minima.end(),&istNaN),minima.end());
	maxima.erase(remove_if(maxima.begin(),maxima.end(),&istNaN),maxima.end());

	if (minima.empty()||maxima.empty())
	{
		// Ränder können nicht bestimmt werden
		m_definitionsmaximumInnen = m_definitionsmaximumInnen = NaN();
		return false;
	}
	else
	{
		m_definitionsminimumInnen = *std::max_element(minima.begin(),minima.end());	// Maximum der Minima
		m_definitionsmaximumInnen = *std::min_element(maxima.begin(),maxima.end());	// Minimum der Maxima
		m_definitionsmaximumInnen = std::max(m_definitionsmaximumInnen,m_definitionsminimumInnen); // Maximum >= Minimum
		return true;
	}
}

void Pfadstueck::setzeAttribute( bool _rueckwaerts, sFahrzeugbeschreibungskette::Zeiger _fahrzeugbeschreibung, sKonfigurationsfunktionenKette::Zeiger _konfigurationsfunktionen, sSteuerfunktionenKette::Zeiger _steuerfunktionen, sUnaereReelleFunktion::Zeiger _zeitfunktion )
{
	ASSERT(!m_initialisiert); 
	ASSERT(_fahrzeugbeschreibung!=NULL);
	m_fahrzeugbeschreibungen = _fahrzeugbeschreibung;
	m_anzahlGlieder = (unsigned short) m_fahrzeugbeschreibungen->beschreibungsanzahl();
	
	m_rueckwaerts = _rueckwaerts;
	m_fahrzeugbeschreibungen = _fahrzeugbeschreibung;
	if (_steuerfunktionen==NULL)
	{
		m_steuerfunktionen = new SteuerfunktionenKette(anzahlGlieder());
		m_steuerfunktionen->referenzEntfernen();
	}
	else
		m_steuerfunktionen = _steuerfunktionen;

	if (_konfigurationsfunktionen==NULL)
	{
		m_konfigurationsfunktionen = new KonfigurationsfunktionenKette(anzahlGlieder());
		m_konfigurationsfunktionen->referenzEntfernen();
	}
	else
		m_konfigurationsfunktionen = _konfigurationsfunktionen;

	m_zeitfunktion = _zeitfunktion;
	aktualisiereRaender();
	m_initialisiert = true;
}

void Pfadstueck::setzeZeitfunktion( sUnaereReelleFunktion::Zeiger _zeitfunktion )
{
	m_zeitfunktion = _zeitfunktion;
}

void Pfadstueck::setzeDefinitionsminimum(double d)
{
	m_definitionsminimumAussen = d;
}

void Pfadstueck::zeichne( sZeichenflaeche::Zeiger zeichenflaeche )
{
	UnaerePlanareFunktionsvisualisierung::Zeiger visualisierung = new UnaerePlanareFunktionsvisualisierung(this);
	visualisierung->referenzEntfernen();

	visualisierung->setzeSchrittweite(0.01);
	visualisierung->setzeBeginn(definitionsminimum());
	visualisierung->setzeEnde  (definitionsmaximum());
	visualisierung->zeichne(zeichenflaeche);

}

EZ::Punkt2D Pfadstueck::operator()( double d )
{
	if (m_rueckwaerts)
		return position(anzahlGlieder()-1,d);
	else
		return position(0,d);
}
};
