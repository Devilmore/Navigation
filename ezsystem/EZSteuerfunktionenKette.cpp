#include "EZStandard.h"
#include "EZSteuerfunktionen.h"
#include "EZSteuerfunktionenKette.h"
#include <vector>

using namespace std;

namespace EZ {


IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(SteuerfunktionenKette)
	IMPLEMENTIERT_SCHNITTSTELLE(sSteuerfunktionenKette)
	IMPLEMENTIERT_SCHNITTSTELLE(sUnaereReelleFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(SteuerfunktionenKette)

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
SteuerfunktionenKette::SteuerfunktionenKette( unsigned short _anzahlGlieder /*=0*/ )
	:	m_anzahlGlieder (_anzahlGlieder)
{
	KONSTRUIERE_SCHNITTSTELLE;
	for (int i=0;i<m_anzahlGlieder;i++)
	{
		sSteuerfunktionen::Zeiger steuerfunktionen = new Steuerfunktionen();
		steuerfunktionen->referenzEntfernen();
		m_steuerfunktionen[i]=steuerfunktionen;
	}
	aktualisiereRaender();
}

sUnaereReelleFunktion::Zeiger SteuerfunktionenKette::geschwindigkeitFunktion(unsigned short glied) const
{
	if (m_steuerfunktionen.count(glied)>0)
	{
		return m_steuerfunktionen.find(glied)->second->geschwindigkeitFunktion();
	}
	else
		return NULL;
}

sUnaereReelleFunktion::Zeiger SteuerfunktionenKette::lenkwinkelAenderungFunktion( unsigned short glied ) const
{
	if (m_steuerfunktionen.count(glied)>0)
	{
		return m_steuerfunktionen.find(glied)->second->lenkwinkelAenderungFunktion();
	}
	else
		return NULL;
}

double SteuerfunktionenKette::geschwindigkeit( unsigned short glied, double d ) const
{
	if (m_steuerfunktionen.count(glied)>0)
	{
		return m_steuerfunktionen.find(glied)->second->geschwindigkeit(d);
	}
	else
		return NaN();
}

double SteuerfunktionenKette::lenkwinkelAenderung( unsigned short glied, double d ) const
{
	if (m_steuerfunktionen.count(glied)>0)
	{
		return m_steuerfunktionen.find(glied)->second->lenkwinkelAenderung(d);
	}
	else
		return NaN();
}

bool SteuerfunktionenKette::setzeGeschwindigkeitFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (m_steuerfunktionen.count(glied)>0)
	{
		if (m_steuerfunktionen[glied]->setzeGeschwindigkeitFunktion(funktion))
		{
			aktualisiereRaender();
			return true;
		}
	}
	return false;
}

bool SteuerfunktionenKette::setzeLenkwinkelAenderungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (m_steuerfunktionen.count(glied)>0)
	{
		if (m_steuerfunktionen[glied]->setzeLenkwinkelAenderungFunktion(funktion))
		{
			aktualisiereRaender();
			return true;
		}
	}
	return false;
}

bool SteuerfunktionenKette::aktualisiereRaender()
{

	// die definierten Definitionsmaxima und -minima in Vektoren speichern,
	// um dann daraus den größten bzw. kleinsten Wert zu ermitteln.
	std::vector <double> minima;
	std::vector <double> maxima;

	for (  map<int,sSteuerfunktionen::Zeiger>::iterator iter = m_steuerfunktionen.begin();iter!=m_steuerfunktionen.end();iter++)
	{
		minima.push_back(iter->second->definitionsminimum());
		maxima.push_back(iter->second->definitionsmaximum());
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
