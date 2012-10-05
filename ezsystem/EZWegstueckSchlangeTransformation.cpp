#include "EZWegstueckSchlangeTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(WegstueckSchlangeTransformation)
    IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(WegstueckSchlangeTransformation)

//////////////////////////////////////////////////////////////////////

WegstueckSchlangeTransformation::WegstueckSchlangeTransformation()
{
    KONSTRUIERE_SCHNITTSTELLE;
}

//////////////////////////////////////////////////////////////////////

int WegstueckSchlangeTransformation::version()
{
    return 1;
}

//////////////////////////////////////////////////////////////////////

Schnittstelle::Zeiger WegstueckSchlangeTransformation::erzeugeObjekt()
{
    Schnittstelle::Zeiger objekt = new WegstueckSchlange();
    objekt->referenzEntfernen();
    
    return objekt;

}

//////////////////////////////////////////////////////////////////////

std::string WegstueckSchlangeTransformation::typ()
{
    return "WegstueckSchlange";
}

//////////////////////////////////////////////////////////////////////

bool WegstueckSchlangeTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
{
    if (version != 1)
        return false;

    WegstueckSchlange::Zeiger wegstueckSchlangeObjekt = WegstueckSchlange::Zeiger::konvertiere(objekt);

    if (wegstueckSchlangeObjekt == NULL)
        return false;
	
	int anzahl;

	if (!Objekttransformation::lese(leser,"anzahl",anzahl))
		return false;

	for (int i = 0; i < anzahl; i++)
	{
		sWegstueck::Zeiger wegstueck;
		if (!Objekttransformation::lese(leser,"wegstueck"+std::to_string(i),wegstueck))
			return false;
		wegstueckSchlangeObjekt->fuegeWegstueckHinzu(wegstueck);
	}
   
    return true;
}

//////////////////////////////////////////////////////////////////////

bool WegstueckSchlangeTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
{
    WegstueckSchlange::Zeiger wegstueckSchlangeObjekt = WegstueckSchlange::Zeiger::konvertiere(objekt);

    if (wegstueckSchlangeObjekt == NULL)
        return false;

	if (!Objekttransformation::schreibe(schreiber,"anzahl",wegstueckSchlangeObjekt->anzahl()))
		return false;

	for (int i = 0; i<wegstueckSchlangeObjekt->anzahl();i++)
	{
		if (!Objekttransformation::schreibe(schreiber,"wegstueck"+std::to_string(i),wegstueckSchlangeObjekt->wegstueck(i)))
			return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////


};
