#include "EZKreiswegstueckTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(KreiswegstueckTransformation)
    IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(KreiswegstueckTransformation)

//////////////////////////////////////////////////////////////////////

KreiswegstueckTransformation::KreiswegstueckTransformation()
{
    KONSTRUIERE_SCHNITTSTELLE;
}

//////////////////////////////////////////////////////////////////////

int KreiswegstueckTransformation::version()
{
    return 1;
}

//////////////////////////////////////////////////////////////////////

Schnittstelle::Zeiger KreiswegstueckTransformation::erzeugeObjekt()
{
    Schnittstelle::Zeiger objekt = new Kreiswegstueck();
    objekt->referenzEntfernen();
    
    return objekt;

}

//////////////////////////////////////////////////////////////////////

std::string KreiswegstueckTransformation::typ()
{
    return "Kreiswegstueck";
}

//////////////////////////////////////////////////////////////////////

bool KreiswegstueckTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
{
    if (version != 1)
        return false;

    Kreiswegstueck::Zeiger kreiswegObjekt = Kreiswegstueck::Zeiger::konvertiere(objekt);

    if (kreiswegObjekt == NULL)
        return false;

    Punkt2D startpunkt, endpunkt, mittelpunkt;
    bool    rueckwaerts, rechtsfahrt;
    double  geschwindigkeit;

    if (  !Objekttransformation::lese(leser, "startpunkt", startpunkt)
        ||!Objekttransformation::lese(leser, "endpunkt", endpunkt)
        ||!Objekttransformation::lese(leser, "mittelpunkt", mittelpunkt)
        ||!Objekttransformation::lese(leser, "rechtsfahrt", rechtsfahrt)
        ||!Objekttransformation::lese(leser, "rueckwaerts", rueckwaerts)
        ||!Objekttransformation::lese(leser, "geschwindigkeit", geschwindigkeit))
        return false;
    
    kreiswegObjekt->setzeAttribute(startpunkt,endpunkt,mittelpunkt,rechtsfahrt,rueckwaerts,geschwindigkeit);

    return true;
}

//////////////////////////////////////////////////////////////////////

bool KreiswegstueckTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
{
    Kreiswegstueck::Zeiger kreiswegObjekt = Kreiswegstueck::Zeiger::konvertiere(objekt);

    if (kreiswegObjekt == NULL)
        return false;

    return  Objekttransformation::schreibe(schreiber, "startpunkt", kreiswegObjekt->startpunkt()) &&
            Objekttransformation::schreibe(schreiber, "endpunkt", kreiswegObjekt->endpunkt()) &&
            Objekttransformation::schreibe(schreiber, "mittelpunkt", kreiswegObjekt->mittelpunkt()) &&
            Objekttransformation::schreibe(schreiber, "rechtsfahrt", kreiswegObjekt->rechtsfahrt()) &&
            Objekttransformation::schreibe(schreiber, "rueckwaerts", kreiswegObjekt->rueckwaerts()) &&
            Objekttransformation::schreibe(schreiber, "geschwindigkeit", kreiswegObjekt->geschwindigkeit());

}

//////////////////////////////////////////////////////////////////////


};
