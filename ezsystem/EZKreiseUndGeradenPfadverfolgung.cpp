#include "EZStandard.h"
#include "EZKreiseUndGeradenPfadverfolgung.h"

#include "EZEreignis.h"
#include "EZFahrzeugbeschreibungskette.h"
#include "EZFahrzeugdatenkette.h"
#include "EZWegstueckSchlange.h"
#include "EZWinkelWrapper.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

/////////////////////////////////////////////////////////////////////////////

REIMPLEMENTIERE_SCHNITTSTELLE_BEGINN(KreiseUndGeradenPfadverfolgung, Pfadverfolgung)
	IMPLEMENTIERT_SCHNITTSTELLE_BASISKLASSE(Pfadverfolgung)
REIMPLEMENTIERE_SCHNITTSTELLE_ENDE(KreiseUndGeradenPfadverfolgung, Pfadverfolgung)

/////////////////////////////////////////////////////////////////////////////
KreiseUndGeradenPfadverfolgung::KreiseUndGeradenPfadverfolgung()
	: Pfadverfolgung()
{

}

//////////////////////////////////////////////////////////////////////

KreiseUndGeradenPfadverfolgung::~KreiseUndGeradenPfadverfolgung()
{

}

//////////////////////////////////////////////////////////////////////

bool KreiseUndGeradenPfadverfolgung::initialisiere( sUhr::Zeiger uhr, std::string ereignistyp, sEreignisverteiler::Zeiger ereignisverteiler)
{
	m_wegSchlange = new WegstueckSchlange();
	m_wegSchlange->referenzEntfernen();
	return Pfadverfolgung::initialisiere(uhr,ereignistyp,ereignisverteiler);
}

//////////////////////////////////////////////////////////////////////

bool KreiseUndGeradenPfadverfolgung::verarbeitePfadHinzufuegenEreignis(sEreignis::Zeiger ereignis)
{
	Schnittstelle::Zeiger   objekt;
	sWegstueck::Zeiger      weg;
	double					zeit;
	if (   !ereignis->attributObjekt("wert", objekt)
		|| ((weg = sWegstueck::Zeiger::konvertiere(objekt)) == NULL)
		|| !ereignis->attributDouble("zeit", zeit))
	{
		EZ::meldeWarnung("KreiseUndGeradenPfadverfolgung::verarbeiteEreignis: WegHinzufuegenEreignis unvollständig");
	}
	else
	{
		m_wegSchlange->fuegeWegstueckHinzu(weg);
	}
	return false;
}

//////////////////////////////////////////////////////////////////////

void KreiseUndGeradenPfadverfolgung::verarbeiteModusWartend()
{
	Pfadverfolgung::verarbeiteModusWartend();
	m_wegSchlange->entferneWegstuecke();
}

//////////////////////////////////////////////////////////////////////

bool KreiseUndGeradenPfadverfolgung::verarbeiteStopEreignis(sEreignis::Zeiger ereignis)
{
	Pfadverfolgung::verarbeiteStopEreignis(ereignis);

	bool pfadloeschen;
	if (ereignis->attributBool("pfadloeschen",pfadloeschen) && pfadloeschen)
	{
		m_wegSchlange->entferneWegstuecke();
	}
	return false;
}

bool KreiseUndGeradenPfadverfolgung::verarbeiteStartEreignis( sEreignis::Zeiger ereignis )
{
	return Pfadverfolgung::verarbeiteStartEreignis(ereignis);
}

}