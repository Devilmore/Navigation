#include "EZUnaerePlanareSplineFunktion.h"

//////////////////////////////////////////////////////////////////////

#include "EZStandard.h"

namespace EZ
{
//////////////////////////////////////////////////////////////////////

REIMPLEMENTIERE_SCHNITTSTELLE_BEGINN(UnaerePlanareSplineFunktion, DiskreteUnaerePlanareFunktion)
    IMPLEMENTIERT_SCHNITTSTELLE_BASISKLASSE(DiskreteUnaerePlanareFunktion)
REIMPLEMENTIERE_SCHNITTSTELLE_ENDE(UnaerePlanareSplineFunktion, DiskreteUnaerePlanareFunktion)

//////////////////////////////////////////////////////////////////////

/*bool berechneTeilfunktionen()
{
	berechneKoeffizienten();
	free(m_funktionx);
	free(m_funktiony);
}*/


UnaerePlanareSplineFunktion::UnaerePlanareSplineFunktion()
	: DiskreteUnaerePlanareFunktion()
{
	m_funktionx = new UnaereReelleSplineFunktion();
	m_funktionx->referenzEntfernen();
	m_funktiony = new UnaereReelleSplineFunktion();
	m_funktiony->referenzEntfernen();
}

//////////////////////////////////////////////////////////////////////

bool UnaerePlanareSplineFunktion::wertHinzufuegen(double definitionswert, Punkt2D funktionswert)
{
	DiskreteUnaerePlanareFunktion::wertHinzufuegen(definitionswert,funktionswert);
	
	m_funktionx->wertHinzufuegen(definitionswert,funktionswert.x);
	m_funktiony->wertHinzufuegen(definitionswert,funktionswert.y);

	//berechneTeilFunktionen();

	return true;
}

Punkt2D UnaerePlanareSplineFunktion::operator()(double definitionswert)
{
	return Punkt2D((*m_funktionx)(definitionswert),(*m_funktiony)(definitionswert));
}

UnaerePlanareSplineFunktion::~UnaerePlanareSplineFunktion()
{

}

EZ::Punkt2D UnaerePlanareSplineFunktion::bestimmeAbleitung( double d )
{
	Punkt3D ableitungenX = m_funktionx->bestimmeAbleitungen(d);
	Punkt3D ableitungenY = m_funktiony->bestimmeAbleitungen(d);
	return Punkt2D(ableitungenX.y,ableitungenY.y);
}
//////////////////////////////////////////////////////////////////////
}