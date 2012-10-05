#include "EZStandard.h"
#include "EZKonfigurationsfunktionenKette.h"
#include <vector>

using namespace std;

namespace EZ {

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(KonfigurationsfunktionenKette)
	IMPLEMENTIERT_SCHNITTSTELLE(sKonfigurationsfunktionenKette)
	IMPLEMENTIERT_SCHNITTSTELLE(sUnaerePlanareFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(KonfigurationsfunktionenKette)

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
KonfigurationsfunktionenKette::KonfigurationsfunktionenKette( unsigned short _anzahlGlieder /*=0*/ )
	:	m_anzahlGlieder (_anzahlGlieder)
{
	KONSTRUIERE_SCHNITTSTELLE;
	for (int i=0;i<m_anzahlGlieder;i++)
	{
		sKonfigurationsfunktionen::Zeiger konfigurationsfunktionen = new Konfigurationsfunktionen();
		konfigurationsfunktionen->referenzEntfernen();
		m_konfigurationsfunktionen[i]=konfigurationsfunktionen;
	}
	aktualisiereRaender();
}

sUnaereReelleFunktion::Zeiger KonfigurationsfunktionenKette::ausrichtungFunktion(unsigned short glied) const
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		return m_konfigurationsfunktionen.find(glied)->second->ausrichtungFunktion();
	}
	else
		return NULL;
}

sUnaereReelleFunktion::Zeiger KonfigurationsfunktionenKette::lenkwinkelFunktion( unsigned short glied ) const
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		return m_konfigurationsfunktionen.find(glied)->second->lenkwinkelFunktion();
	}
	else
		return NULL;
}

sUnaerePlanareFunktion::Zeiger KonfigurationsfunktionenKette::positionFunktion( unsigned short glied ) const
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		return m_konfigurationsfunktionen.find(glied)->second->positionFunktion();
	}
	else
		return NULL;
}

sUnaereReelleFunktion::Zeiger KonfigurationsfunktionenKette::einknickwinkelFunktion( unsigned short kupplung ) const
{
	if (m_einknickwinkelfunktion.count(kupplung)>0)
	{
		return m_einknickwinkelfunktion.find(kupplung)->second;
	}
	else
		return NULL;
}

double KonfigurationsfunktionenKette::ausrichtung( unsigned short glied, double d ) const
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		return m_konfigurationsfunktionen.find(glied)->second->ausrichtung(d);
	}
	else
		return NaN();
}

double KonfigurationsfunktionenKette::lenkwinkel( unsigned short glied, double d ) const
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		return m_konfigurationsfunktionen.find(glied)->second->lenkwinkel(d);
	}
	else
		return NaN();
}


EZ::Punkt2D KonfigurationsfunktionenKette::position( unsigned short glied, double d ) const
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		return m_konfigurationsfunktionen.find(glied)->second->position(d);
	}
	else
		return Punkt2D(NaN(),NaN());
}

double KonfigurationsfunktionenKette::einknickwinkel( unsigned short kupplung, double d ) const
{
	sUnaereReelleFunktion::Zeiger funktion = einknickwinkelFunktion(kupplung);
	if (funktion != NULL)
		return (*funktion)(d);
	else
		return NaN();
}

bool KonfigurationsfunktionenKette::setzeAusrichtungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		if (m_konfigurationsfunktionen[glied]->setzeAusrichtungFunktion(funktion))
		{
			aktualisiereRaender();
			return true;
		}
	}
	return false;
}

bool KonfigurationsfunktionenKette::setzeLenkwinkelFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion )
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{
		if (m_konfigurationsfunktionen[glied]->setzeLenkwinkelFunktion(funktion))
		{
			aktualisiereRaender();
			return true;
		}
	}
	return false;
}


bool KonfigurationsfunktionenKette::setzePositionFunktion( unsigned short glied, sUnaerePlanareFunktion::Zeiger funktion )
{
	if (m_konfigurationsfunktionen.count(glied)>0)
	{

		if (m_konfigurationsfunktionen[glied]->setzePositionFunktion(funktion))
		{
			aktualisiereRaender();
			return true;
		}
	}
	return false;
}

bool KonfigurationsfunktionenKette::setzeEinknickwinkelFunktion( unsigned short kupplung, sUnaereReelleFunktion::Zeiger funktion )
{
	if (kupplung<m_anzahlGlieder-1)
	{
		m_einknickwinkelfunktion[kupplung] = funktion;
		aktualisiereRaender();
		return true;
	}
	else
		return false;
}

unsigned short KonfigurationsfunktionenKette::anzahlGlieder() const
{
	return m_anzahlGlieder;
}

EZ::Punkt2D KonfigurationsfunktionenKette::operator()( double d )
{
	Punkt2D zugfahrzeugPosition(position(0,d));
	if (istNaN(zugfahrzeugPosition.x))
		return position(1,d);
	else return zugfahrzeugPosition;
}

bool KonfigurationsfunktionenKette::aktualisiereRaender()
{

	// die definierten Definitionsmaxima und -minima in Vektoren speichern,
	// um dann daraus den größten bzw. kleinsten Wert zu ermitteln.
	std::vector <double> minima;
	std::vector <double> maxima;

	for (  map<int,sKonfigurationsfunktionen::Zeiger>::iterator iter = m_konfigurationsfunktionen.begin();iter!=m_konfigurationsfunktionen.end();iter++)
	{
		minima.push_back(iter->second->definitionsminimum());
		maxima.push_back(iter->second->definitionsmaximum());
	}
	for (  map<int,sUnaereReelleFunktion::Zeiger>::iterator iter = m_einknickwinkelfunktion.begin();iter!=m_einknickwinkelfunktion.end();iter++)
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
		m_definitionsmaximum = std::max(m_definitionsmaximum,m_definitionsminimum); // Maximum >= Minimum
		return true;
	}
}

};
