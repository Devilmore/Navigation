#include "EZKonfigurationsfunktionenTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////

	IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(KonfigurationsfunktionenTransformation)
		IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
	IMPLEMENTIERE_SCHNITTSTELLE_ENDE(KonfigurationsfunktionenTransformation)

	//////////////////////////////////////////////////////////////////////

	KonfigurationsfunktionenTransformation::KonfigurationsfunktionenTransformation()
	{
		KONSTRUIERE_SCHNITTSTELLE;
	}

	//////////////////////////////////////////////////////////////////////

	int KonfigurationsfunktionenTransformation::version()
	{
		return 1;
	}

	//////////////////////////////////////////////////////////////////////

	Schnittstelle::Zeiger KonfigurationsfunktionenTransformation::erzeugeObjekt()
	{
		Schnittstelle::Zeiger objekt = new Konfigurationsfunktionen();
		objekt->referenzEntfernen();

		return objekt;

	}

	//////////////////////////////////////////////////////////////////////

	std::string KonfigurationsfunktionenTransformation::typ()
	{
		return "Konfigurationsfunktionen";
	}

	//////////////////////////////////////////////////////////////////////

	bool KonfigurationsfunktionenTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
	{
		if (version != 1)
			return false;

		Konfigurationsfunktionen::Zeiger funktionen = Konfigurationsfunktionen::Zeiger::konvertiere(objekt);

		if (funktionen == NULL)
			return false;
		Schnittstelle::Zeiger objekt1,objekt2,objekt3;
		if (	!Objekttransformation::lese(leser,"definitionsminimum",funktionen->m_definitionsminimum)
			 ||	!Objekttransformation::lese(leser,"definitionsmaximum",funktionen->m_definitionsmaximum)
			 || !Objekttransformation::lese(leser,"ausrichtungfunktion",objekt1)
			 || !Objekttransformation::lese(leser,"lenkwinkelfunktion",objekt2)
			 ||	!Objekttransformation::lese(leser,"positionfunktion",objekt3))
			return false;
		
		funktionen->m_ausrichtungFunktion=sUnaereReelleFunktion::Zeiger::konvertiere(objekt1);
		funktionen->m_lenkwinkelFunktion=sUnaereReelleFunktion::Zeiger::konvertiere(objekt2);
		funktionen->m_positionFunktion=sUnaerePlanareFunktion::Zeiger::konvertiere(objekt3);
		
		

		return true;
	}

	//////////////////////////////////////////////////////////////////////

	bool KonfigurationsfunktionenTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
	{
		Konfigurationsfunktionen::Zeiger funktionen = Konfigurationsfunktionen::Zeiger::konvertiere(objekt);

		if (funktionen == NULL)
			return false;
		if (	!Objekttransformation::schreibe(schreiber,"definitionsminimum",funktionen->m_definitionsminimum)
			 ||	!Objekttransformation::schreibe(schreiber,"definitionsmaximum",funktionen->m_definitionsmaximum)
			 ||	!Objekttransformation::schreibe(schreiber,"ausrichtungfunktion",funktionen->m_ausrichtungFunktion)
			 ||	!Objekttransformation::schreibe(schreiber,"lenkwinkelfunktion",funktionen->m_lenkwinkelFunktion)
			 ||	!Objekttransformation::schreibe(schreiber,"positionfunktion",funktionen->m_positionFunktion))
			return false;

		return true;
	}

	//////////////////////////////////////////////////////////////////////


};
