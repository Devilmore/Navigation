#include "EZSteuerfunktionenTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////

	IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(SteuerfunktionenTransformation)
		IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
	IMPLEMENTIERE_SCHNITTSTELLE_ENDE(SteuerfunktionenTransformation)

	//////////////////////////////////////////////////////////////////////

	SteuerfunktionenTransformation::SteuerfunktionenTransformation()
	{
		KONSTRUIERE_SCHNITTSTELLE;
	}

	//////////////////////////////////////////////////////////////////////

	int SteuerfunktionenTransformation::version()
	{
		return 1;
	}

	//////////////////////////////////////////////////////////////////////

	Schnittstelle::Zeiger SteuerfunktionenTransformation::erzeugeObjekt()
	{
		Schnittstelle::Zeiger objekt = new Steuerfunktionen();
		objekt->referenzEntfernen();

		return objekt;

	}

	//////////////////////////////////////////////////////////////////////

	std::string SteuerfunktionenTransformation::typ()
	{
		return "Steuerfunktionen";
	}

	//////////////////////////////////////////////////////////////////////

	bool SteuerfunktionenTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
	{
		if (version != 1)
			return false;

		Steuerfunktionen::Zeiger funktionen = Steuerfunktionen::Zeiger::konvertiere(objekt);

		if (funktionen == NULL)
			return false;
		Schnittstelle::Zeiger objekt1,objekt2;
		if (	!Objekttransformation::lese(leser,"definitionsminimum",funktionen->m_definitionsminimum)
			 ||	!Objekttransformation::lese(leser,"definitionsmaximum",funktionen->m_definitionsmaximum)
			 || !Objekttransformation::lese(leser,"lenkwinkelaenderungfunktion",objekt1)
			 || !Objekttransformation::lese(leser,"geschwindigkeitfunktion",objekt2))
			return false;
		
		funktionen->m_lenkwinkelAenderungFunktion=sUnaereReelleFunktion::Zeiger::konvertiere(objekt1);
		funktionen->m_geschwindigkeitFunktion=sUnaereReelleFunktion::Zeiger::konvertiere(objekt2);
		return true;
	}

	//////////////////////////////////////////////////////////////////////

	bool SteuerfunktionenTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
	{
		Steuerfunktionen::Zeiger funktionen = Steuerfunktionen::Zeiger::konvertiere(objekt);

		if (funktionen == NULL)
			return false;
		if (	!Objekttransformation::schreibe(schreiber,"definitionsminimum",funktionen->m_definitionsminimum)
			 ||	!Objekttransformation::schreibe(schreiber,"definitionsmaximum",funktionen->m_definitionsmaximum)
			 ||	!Objekttransformation::schreibe(schreiber,"lenkwinkelaenderungfunktion",funktionen->m_lenkwinkelAenderungFunktion)
			 ||	!Objekttransformation::schreibe(schreiber,"geschwindigkeitfunktion",funktionen->m_geschwindigkeitFunktion))
			return false;

		return true;
	}

	//////////////////////////////////////////////////////////////////////


};
