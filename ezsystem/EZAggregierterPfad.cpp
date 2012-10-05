#include "EZStandard.h"
#include "EZAggregierterPfad.h"
#include <vector>
#include "EZSteuerfunktionenKette.h"
#include "EZKonfigurationsfunktionenKette.h"

namespace EZ {

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(AggregierterPfad)
	IMPLEMENTIERT_SCHNITTSTELLE(sZeitVarianterPfad)
	IMPLEMENTIERT_SCHNITTSTELLE(sZeitInvarianterPfad)
	IMPLEMENTIERT_SCHNITTSTELLE(sUnaerePlanareFunktion)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(AggregierterPfad)



AggregierterPfad::AggregierterPfad()
{
	KONSTRUIERE_SCHNITTSTELLE
}

unsigned short AggregierterPfad::anzahlGlieder() const
{
	return m_pfade.empty()	? 0 
							: m_pfade.front()->anzahlGlieder();
}

double AggregierterPfad::ausrichtung( unsigned short glied, double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
	return (pfad!=NULL)	? pfad->ausrichtung(glied,d)
						: NaN(); 
}

EZ::Punkt2D AggregierterPfad::position( unsigned short glied, double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
	return (pfad!=NULL)	?	pfad->position(glied,d)
						:	Punkt2D(NaN(),NaN());
}

double AggregierterPfad::lenkwinkel( unsigned short glied, double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
	return (pfad!=NULL)	?	pfad->lenkwinkel(glied,d)
						:	NaN();
}

double AggregierterPfad::einknickwinkel( unsigned short kupplung, double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
	return (pfad!=NULL) ?	pfad->einknickwinkel(kupplung,d)
						:	NaN();
}

bool AggregierterPfad::rueckwaerts( double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
	return (pfad!=NULL) ? pfad->rueckwaerts(d)
						: false;
}

double AggregierterPfad::zeit( double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
	return (pfad!=NULL) ? pfad->zeit(d)
						: NaN();
}

double AggregierterPfad::startzeit() const
{
	return m_pfade.empty()	?	NaN()
							:	m_pfade.front()->startzeit();
}

double AggregierterPfad::endzeit() const
{
	return m_pfade.empty()	?	NaN()
							:	m_pfade.back()->endzeit();
}

double AggregierterPfad::definitionswert( double zeit ) const
{
	// STUB
	return zeit;
}

double AggregierterPfad::geschwindigkeit( unsigned short glied, double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
	return (pfad!=NULL)	?	pfad->geschwindigkeit(glied,d)
						:	NaN();
}

double AggregierterPfad::lenkwinkelAenderung( unsigned short glied, double d ) const
{
	sZeitVarianterPfad* pfad = findePfad(d);
		return (pfad!=NULL) ? pfad->lenkwinkelAenderung(glied,d)
							: NULL;
}

bool AggregierterPfad::fuegePfadHinzu( sZeitVarianterPfad::Zeiger pfad )
{
	if (m_pfade.empty())
	{
		pfad->setzeDefinitionsminimum(0.0);
		m_definitionsminimum = pfad->definitionsminimum();
		m_definitionsmaximum = pfad->definitionsmaximum();
		m_pfade.push_back(pfad);
		return true;
	}
	else if (anzahlGlieder()==pfad->anzahlGlieder())
	{
		pfad->setzeDefinitionsminimum(m_definitionsmaximum);
		m_definitionsmaximum = pfad->definitionsmaximum();
		m_pfade.push_back(pfad);
		return true;
	}
	else
		return false;
}

bool AggregierterPfad::entfernePfad()
{
	if (!m_pfade.empty())
	{
		m_pfade.pop_back();
		if (m_pfade.empty())
		{
			m_definitionsmaximum = m_definitionsminimum  = NaN();
			return false;
		}
		else
		{
			m_definitionsmaximum = m_pfade.back()->definitionsmaximum();
			m_definitionsminimum = m_pfade.front()->definitionsminimum();
			return true;
		}
	}
	return false;
}

sZeitVarianterPfad* AggregierterPfad::findePfad( double definitionswert ) const
{
	for (Pfadliste::const_iterator iter = m_pfade.begin();iter!=m_pfade.end();)
	{
		sZeitVarianterPfad* pfad = &**iter;
		iter++;
		if (definitionswert>=pfad->definitionsminimum())
			if ((iter)==m_pfade.end()||definitionswert<(*iter)->definitionsminimum())	
				return pfad;
	}
	return NULL;
}

EZ::Punkt2D AggregierterPfad::operator()( double d )
{
	Punkt2D zugfahrzeugPosition(position(0,d));
	return istNaN(zugfahrzeugPosition.x)	?	position(1,d)
											:	zugfahrzeugPosition;
}

void AggregierterPfad::setzeDefinitionsminimum( double d )
{
	for (Pfadliste::iterator iter = m_pfade.begin();iter!=m_pfade.end();iter++)
	{
		double alterMinDefAbstand = (*iter)->definitionsminimum()-m_definitionsminimum;
		(*iter)->setzeDefinitionsminimum(d+alterMinDefAbstand);
	}
	m_definitionsmaximum += d-m_definitionsminimum;
	m_definitionsminimum = d;
}

void AggregierterPfad::zeichne( sZeichenflaeche::Zeiger zeichenflaeche )
{
	for (Pfadliste::iterator iter = m_pfade.begin();iter!=m_pfade.end();iter++)
	{
		(*iter)->zeichne(zeichenflaeche);
	}
}

EZ::sZeitInvarianterPfad::Zeiger AggregierterPfad::pfad( size_t nummer )
{
	if (nummer>anzahlPfade())
		return *m_pfade.end();
	size_t i = 0;
	Pfadliste::iterator iter = m_pfade.begin();

	while (i++<nummer)
	{
		iter++;
	}

	return *iter;
}
};
	