#include "EZAggregierterPfadTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(AggregierterPfadTransformation)
    IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(AggregierterPfadTransformation)

//////////////////////////////////////////////////////////////////////

AggregierterPfadTransformation::AggregierterPfadTransformation()
{
    KONSTRUIERE_SCHNITTSTELLE;
}

//////////////////////////////////////////////////////////////////////

int AggregierterPfadTransformation::version()
{
    return 1;
}

//////////////////////////////////////////////////////////////////////

Schnittstelle::Zeiger AggregierterPfadTransformation::erzeugeObjekt()
{
    Schnittstelle::Zeiger objekt = new AggregierterPfad();
    objekt->referenzEntfernen();
    
    return objekt;

}

//////////////////////////////////////////////////////////////////////

std::string AggregierterPfadTransformation::typ()
{
    return "AggregierterPfad";
}

//////////////////////////////////////////////////////////////////////

bool AggregierterPfadTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
{
    if (version != 1)
        return false;

    AggregierterPfad::Zeiger aggregierterPfadObjekt = AggregierterPfad::Zeiger::konvertiere(objekt);

    if (aggregierterPfadObjekt == NULL)
        return false;
	
	int anzahl;

	if (!Objekttransformation::lese(leser,"anzahl",anzahl))
		return false;

	for (int i = 0; i < anzahl; i++)
	{
		sZeitVarianterPfad::Zeiger pfad;
		if (!Objekttransformation::lese(leser,"pfad"+std::to_string(i),pfad))
			return false;
		aggregierterPfadObjekt->fuegePfadHinzu(pfad);
	}
   
    return true;
}

//////////////////////////////////////////////////////////////////////

bool AggregierterPfadTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
{
    AggregierterPfad::Zeiger aggregierterPfadObjekt = AggregierterPfad::Zeiger::konvertiere(objekt);

    if (aggregierterPfadObjekt == NULL)
        return false;

 	if (!Objekttransformation::schreibe(schreiber,"anzahl",(int) aggregierterPfadObjekt->m_pfade.size()))
 		return false;

	int i = 0;
 	for (AggregierterPfad::Pfadliste::iterator iter = aggregierterPfadObjekt->m_pfade.begin();iter!=aggregierterPfadObjekt->m_pfade.end();iter++,i++)
 	{
 		if (!Objekttransformation::schreibe(schreiber,"pfad"+std::to_string(i),*iter))
 			return false;
 	}
 	return true;
}

//////////////////////////////////////////////////////////////////////


};
