#include "EZStandard.h"
#include "EZSteuerfunktionen.h"
#include <vector>


namespace EZ {

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Steuerfunktionen)
	IMPLEMENTIERT_SCHNITTSTELLE(sSteuerfunktionen)
	IMPLEMENTIERT_SCHNITTSTELLE(sUnaereReelleFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(Steuerfunktionen)

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
Steuerfunktionen::Steuerfunktionen( sUnaereReelleFunktion::Zeiger _geschwindigkeitFunktion /*= NULL*/,
									sUnaereReelleFunktion::Zeiger _ersterLenkwinkelAenderungFunktion /*= NULL*/)
{
	KONSTRUIERE_SCHNITTSTELLE;
	m_geschwindigkeitFunktion			= _geschwindigkeitFunktion;
	m_lenkwinkelAenderungFunktion	= _ersterLenkwinkelAenderungFunktion;
	aktualisiereRaender();
}

double Steuerfunktionen::geschwindigkeit( double d ) const
{
	if (m_geschwindigkeitFunktion == NULL)
		return NaN();
	return (*m_geschwindigkeitFunktion)(d);
}

double Steuerfunktionen::lenkwinkelAenderung( double d ) const
{
	if (m_lenkwinkelAenderungFunktion == NULL)
		return NaN();
	return (*m_lenkwinkelAenderungFunktion)(d);
}

bool Steuerfunktionen::setzeGeschwindigkeitFunktion( sUnaereReelleFunktion::Zeiger funktion )
{
	m_geschwindigkeitFunktion = funktion;
	aktualisiereRaender();
	return true;
}

bool Steuerfunktionen::setzeLenkwinkelAenderungFunktion( sUnaereReelleFunktion::Zeiger funktion )
{
	m_lenkwinkelAenderungFunktion = funktion;
	aktualisiereRaender();
	return true;
}

bool Steuerfunktionen::aktualisiereRaender()
{
	// die definierten Definitionsmaxima und -minima in Vektoren speichern,
	// um dann daraus den größten bzw. kleinsten Wert zu ermitteln.
	
	std::vector <double> minima;
	std::vector <double> maxima;

	if (m_geschwindigkeitFunktion!=NULL)
	{
		minima.push_back(m_geschwindigkeitFunktion->definitionsminimum());
		maxima.push_back(m_geschwindigkeitFunktion->definitionsmaximum());
	}

	if (m_lenkwinkelAenderungFunktion!=NULL)
	{
		minima.push_back(m_lenkwinkelAenderungFunktion->definitionsminimum());
		maxima.push_back(m_lenkwinkelAenderungFunktion->definitionsmaximum());
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
};

};
