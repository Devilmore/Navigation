#include "EZGeradenwegstueckTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(GeradenwegstueckTransformation)
    IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(GeradenwegstueckTransformation)

//////////////////////////////////////////////////////////////////////

GeradenwegstueckTransformation::GeradenwegstueckTransformation()
{
    KONSTRUIERE_SCHNITTSTELLE;
}

//////////////////////////////////////////////////////////////////////

int GeradenwegstueckTransformation::version()
{
    return 1;
}

//////////////////////////////////////////////////////////////////////

Schnittstelle::Zeiger GeradenwegstueckTransformation::erzeugeObjekt()
{
    Schnittstelle::Zeiger objekt = new Geradenwegstueck();
    objekt->referenzEntfernen();
    
    return objekt;

}

//////////////////////////////////////////////////////////////////////

std::string GeradenwegstueckTransformation::typ()
{
    return "Geradenwegstueck";
}

//////////////////////////////////////////////////////////////////////

bool GeradenwegstueckTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
{
    if (version != 1)
        return false;

    Geradenwegstueck::Zeiger geradenwegstueckObjekt = Geradenwegstueck::Zeiger::konvertiere(objekt);

    if (geradenwegstueckObjekt == NULL)
        return false;

    Punkt2D startpunkt, endpunkt;
    bool    rueckwaerts;
    double  geschwindigkeit;

    if (  !Objekttransformation::lese(leser, "startpunkt", startpunkt)
        ||!Objekttransformation::lese(leser, "endpunkt", endpunkt)
        ||!Objekttransformation::lese(leser, "rueckwaerts", rueckwaerts)
        ||!Objekttransformation::lese(leser, "geschwindigkeit", geschwindigkeit))
        return false;
    
    geradenwegstueckObjekt->setzeAttribute(startpunkt,endpunkt,rueckwaerts,geschwindigkeit);

    return true;
}

//////////////////////////////////////////////////////////////////////

bool GeradenwegstueckTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
{
    Geradenwegstueck::Zeiger geradenwegstueckObjekt = Geradenwegstueck::Zeiger::konvertiere(objekt);

    if (geradenwegstueckObjekt == NULL)
        return false;

    return  Objekttransformation::schreibe(schreiber, "startpunkt", geradenwegstueckObjekt->startpunkt()) &&
            Objekttransformation::schreibe(schreiber, "endpunkt", geradenwegstueckObjekt->endpunkt()) &&
            Objekttransformation::schreibe(schreiber, "rueckwaerts", geradenwegstueckObjekt->rueckwaerts()) &&
            Objekttransformation::schreibe(schreiber, "geschwindigkeit", geradenwegstueckObjekt->geschwindigkeit());

}

//////////////////////////////////////////////////////////////////////


};
