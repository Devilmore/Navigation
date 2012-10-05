#include "EZSteuerfunktionenKetteTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////

	IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(SteuerfunktionenKetteTransformation)
		IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
	IMPLEMENTIERE_SCHNITTSTELLE_ENDE(SteuerfunktionenKetteTransformation)

	//////////////////////////////////////////////////////////////////////

	SteuerfunktionenKetteTransformation::SteuerfunktionenKetteTransformation()
	{
		KONSTRUIERE_SCHNITTSTELLE;
	}

	//////////////////////////////////////////////////////////////////////

	int SteuerfunktionenKetteTransformation::version()
	{
		return 1;
	}

	//////////////////////////////////////////////////////////////////////

	Schnittstelle::Zeiger SteuerfunktionenKetteTransformation::erzeugeObjekt()
	{
		Schnittstelle::Zeiger objekt = new SteuerfunktionenKette();
		objekt->referenzEntfernen();

		return objekt;

	}

	//////////////////////////////////////////////////////////////////////

	std::string SteuerfunktionenKetteTransformation::typ()
	{
		return "SteuerfunktionenKette";
	}

	//////////////////////////////////////////////////////////////////////

	bool SteuerfunktionenKetteTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
	{
		if (version != 1)
			return false;

		SteuerfunktionenKette::Zeiger kette = SteuerfunktionenKette::Zeiger::konvertiere(objekt);

		if (kette == NULL)
			return false;
		
		int _anzahlGlieder;
		if (	!Objekttransformation::lese(leser, "anzahlGlieder",_anzahlGlieder)
			 ||	!Objekttransformation::lese(leser, "definitionsminimum",kette->m_definitionsminimum)
			 ||	!Objekttransformation::lese(leser, "definitionsmaximum",kette->m_definitionsmaximum))
			return false;

		kette->m_anzahlGlieder=(unsigned short int)_anzahlGlieder;

		int gliednummer;
		Schnittstelle::Zeiger funktionobjekt;
		
		for  ( int i = 0; Objekttransformation::lese(leser, "steuerfunktionengliednummer_"+std::to_string(i),gliednummer) && Objekttransformation::lese(leser, "steuerfunktionen_"+std::to_string(i),funktionobjekt);i++)
		{
			kette->m_steuerfunktionen[gliednummer]=sSteuerfunktionen::Zeiger::konvertiere(funktionobjekt);
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////

	bool SteuerfunktionenKetteTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
	{
		SteuerfunktionenKette::Zeiger ketteObjekt = SteuerfunktionenKette::Zeiger::konvertiere(objekt);

		if (ketteObjekt == NULL)
			return false;
		if (	!Objekttransformation::schreibe(schreiber, "anzahlGlieder",ketteObjekt->anzahlGlieder())
			 ||	!Objekttransformation::schreibe(schreiber, "definitionsminimum",ketteObjekt->definitionsminimum())
			 || !Objekttransformation::schreibe(schreiber, "definitionsmaximum",ketteObjekt->definitionsmaximum()))
			return false;
		int i=0;
		for (map<int, sSteuerfunktionen::Zeiger>::iterator iter = ketteObjekt->m_steuerfunktionen.begin();iter!=ketteObjekt->m_steuerfunktionen.end();iter++,i++)
		{
			if (	!Objekttransformation::schreibe(schreiber, "steuerfunktionengliednummer_"+std::to_string(i),iter->first)
				 ||	!Objekttransformation::schreibe(schreiber, "steuerfunktionen_"+std::to_string(i),iter->second))
			return false;
		}
		
		return true;
	}

	//////////////////////////////////////////////////////////////////////


};
