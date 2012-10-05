#include "EZPfadstueckTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(PfadstueckTransformation)
    IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(PfadstueckTransformation)

//////////////////////////////////////////////////////////////////////

PfadstueckTransformation::PfadstueckTransformation()
{
    KONSTRUIERE_SCHNITTSTELLE;
}

//////////////////////////////////////////////////////////////////////

int PfadstueckTransformation::version()
{
    return 1;
}

//////////////////////////////////////////////////////////////////////

Schnittstelle::Zeiger PfadstueckTransformation::erzeugeObjekt()
{
    Schnittstelle::Zeiger objekt = new Pfadstueck();
    objekt->referenzEntfernen();
    
    return objekt;

}

//////////////////////////////////////////////////////////////////////

std::string PfadstueckTransformation::typ()
{
    return "Pfadstueck";
}

//////////////////////////////////////////////////////////////////////

bool PfadstueckTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
{
    if (version != 1)
        return false;

    Pfadstueck::Zeiger pfadstueckObjekt = Pfadstueck::Zeiger::konvertiere(objekt);

    if (pfadstueckObjekt == NULL)
        return false;
	bool rueckwaerts;
	Schnittstelle::Zeiger beschreibungObjekt,konfigurationsfunktionenObjekt,steuerfunktionenObjekt,zeitfunktionObjekt;

	if (	!Objekttransformation::lese(leser, "rueckwaerts",rueckwaerts)
		||	!Objekttransformation::lese(leser, "beschreibung",beschreibungObjekt)
		||	!Objekttransformation::lese(leser, "konfigurationsfunktionen",konfigurationsfunktionenObjekt)
		||	!Objekttransformation::lese(leser, "steuerfunktionen",steuerfunktionenObjekt)
		||	!Objekttransformation::lese(leser, "zeitfunktion",zeitfunktionObjekt))
	{
		return false;
	}
	sFahrzeugbeschreibungskette::Zeiger beschreibung = sFahrzeugbeschreibungskette::Zeiger::konvertiere(beschreibungObjekt);
	sKonfigurationsfunktionenKette::Zeiger konfigurationsfunktionen = sKonfigurationsfunktionenKette::Zeiger::konvertiere(konfigurationsfunktionenObjekt);
	sSteuerfunktionenKette::Zeiger steuerfunktionen = sSteuerfunktionenKette::Zeiger::konvertiere(steuerfunktionenObjekt);
	sUnaereReelleFunktion::Zeiger zeitfunktion = sUnaereReelleFunktion::Zeiger::konvertiere(zeitfunktionObjekt);
	pfadstueckObjekt->setzeAttribute( rueckwaerts, beschreibung, konfigurationsfunktionen, steuerfunktionen, zeitfunktion );

    return true;
}

//////////////////////////////////////////////////////////////////////

bool PfadstueckTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
{
    Pfadstueck::Zeiger pfadstueckObjekt = Pfadstueck::Zeiger::konvertiere(objekt);

    if (pfadstueckObjekt == NULL)
        return false;

    return		Objekttransformation::schreibe(schreiber, "rueckwaerts",				pfadstueckObjekt->rueckwaerts(0.0))
			&&	Objekttransformation::schreibe(schreiber, "beschreibung",				pfadstueckObjekt->m_fahrzeugbeschreibungen)
			&&	Objekttransformation::schreibe(schreiber, "konfigurationsfunktionen",	pfadstueckObjekt->m_konfigurationsfunktionen)
			&&	Objekttransformation::schreibe(schreiber, "steuerfunktionen",			pfadstueckObjekt->m_steuerfunktionen)
			&&	Objekttransformation::schreibe(schreiber, "zeitfunktion",				pfadstueckObjekt->m_zeitfunktion);
}

//////////////////////////////////////////////////////////////////////


};
