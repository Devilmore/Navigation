#include "EZStandard.h"
#include "EZKonfigurationsfunktionen.h"
#include <vector>


namespace EZ {

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Konfigurationsfunktionen)
	IMPLEMENTIERT_SCHNITTSTELLE(sKonfigurationsfunktionen)
	IMPLEMENTIERT_SCHNITTSTELLE(sUnaerePlanareFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(Konfigurationsfunktionen)

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
Konfigurationsfunktionen::Konfigurationsfunktionen( sUnaerePlanareFunktion::Zeiger _positionFunktion /*= NULL*/,
													sUnaereReelleFunktion::Zeiger _ausrichtungFunktion /*= NULL*/,
													sUnaereReelleFunktion::Zeiger _lenkwinkelFunktion /*= NULL*/)
{
	KONSTRUIERE_SCHNITTSTELLE;
	m_positionFunktion			= _positionFunktion;
	m_ausrichtungFunktion		= _ausrichtungFunktion;
	m_lenkwinkelFunktion	= _lenkwinkelFunktion;
	aktualisiereRaender();
}

double Konfigurationsfunktionen::ausrichtung( double d ) const
{
	if (m_ausrichtungFunktion == NULL)
		return NaN();
	return (*m_ausrichtungFunktion)(d);
}

double Konfigurationsfunktionen::lenkwinkel( double d ) const
{
	if (m_lenkwinkelFunktion == NULL)
		return NaN();
	return (*m_lenkwinkelFunktion)(d);
}

EZ::Punkt2D Konfigurationsfunktionen::position( double d ) const
{
	if (m_positionFunktion == NULL)
		return Punkt2D(NaN(),NaN());
	return (*m_positionFunktion)(d);
}

bool Konfigurationsfunktionen::setzeAusrichtungFunktion( sUnaereReelleFunktion::Zeiger funktion )
{
	m_ausrichtungFunktion = funktion;
	aktualisiereRaender();
	return true;
}

bool Konfigurationsfunktionen::setzeLenkwinkelFunktion( sUnaereReelleFunktion::Zeiger funktion )
{
	m_lenkwinkelFunktion = funktion;
	aktualisiereRaender();
	return true;
}


bool Konfigurationsfunktionen::setzePositionFunktion( sUnaerePlanareFunktion::Zeiger funktion )
{
	m_positionFunktion = funktion;
	aktualisiereRaender();
	return true;
}

bool Konfigurationsfunktionen::aktualisiereRaender()
{
	// die definierten Definitionsmaxima und -minima in Vektoren speichern,
	// um dann daraus den größten bzw. kleinsten Wert zu ermitteln.
	
	std::vector <double> minima;
	std::vector <double> maxima;

	if (m_positionFunktion!=NULL)
	{
		minima.push_back(m_positionFunktion->definitionsminimum());
		maxima.push_back(m_positionFunktion->definitionsmaximum());
	}

	if (m_ausrichtungFunktion!=NULL)
	{
		minima.push_back(m_ausrichtungFunktion->definitionsminimum());
		maxima.push_back(m_ausrichtungFunktion->definitionsmaximum());
	}

	if (m_lenkwinkelFunktion!=NULL)
	{
		minima.push_back(m_lenkwinkelFunktion->definitionsminimum());
		maxima.push_back(m_lenkwinkelFunktion->definitionsmaximum());
	}

	// Alle NaN Werte entfernen
	minima.erase(remove_if(minima.begin(),minima.end(),&istNaN),minima.end());
	maxima.erase(remove_if(maxima.begin(),maxima.end(),&istNaN),maxima.end());

	if (minima.empty()||maxima.empty())
	{
		// Ränder können nicht bestimmt werden
		m_definitionsmaximum = m_definitionsmaximum = NaN();
		return false;
	}
	else
	{
		m_definitionsminimum = *std::max_element(minima.begin(),minima.end());	// Maximum der Minima
		m_definitionsmaximum = *std::min_element(maxima.begin(),maxima.end());	// Minimum der Maxima
		m_definitionsmaximum = std::max(m_definitionsmaximum,m_definitionsminimum); //Maximum >= Minimum
		return true;
	}
}

};
