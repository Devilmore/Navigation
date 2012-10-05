#include "EZKonfigurationsfunktionenKetteTransformation.h"
#include "EZGeometrieTransformationen.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////

	IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(KonfigurationsfunktionenKetteTransformation)
		IMPLEMENTIERT_SCHNITTSTELLE(sObjekttransformation)
	IMPLEMENTIERE_SCHNITTSTELLE_ENDE(KonfigurationsfunktionenKetteTransformation)

	//////////////////////////////////////////////////////////////////////

	KonfigurationsfunktionenKetteTransformation::KonfigurationsfunktionenKetteTransformation()
	{
		KONSTRUIERE_SCHNITTSTELLE;
	}

	//////////////////////////////////////////////////////////////////////

	int KonfigurationsfunktionenKetteTransformation::version()
	{
		return 1;
	}

	//////////////////////////////////////////////////////////////////////

	Schnittstelle::Zeiger KonfigurationsfunktionenKetteTransformation::erzeugeObjekt()
	{
		Schnittstelle::Zeiger objekt = new KonfigurationsfunktionenKette();
		objekt->referenzEntfernen();

		return objekt;

	}

	//////////////////////////////////////////////////////////////////////

	std::string KonfigurationsfunktionenKetteTransformation::typ()
	{
		return "KonfigurationsfunktionenKette";
	}

	//////////////////////////////////////////////////////////////////////

	bool KonfigurationsfunktionenKetteTransformation::transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt)
	{
		if (version != 1)
			return false;

		KonfigurationsfunktionenKette::Zeiger kette = KonfigurationsfunktionenKette::Zeiger::konvertiere(objekt);

		if (kette == NULL)
			return false;
		
		int _anzahlGlieder;
		if (	!Objekttransformation::lese(leser, "anzahlGlieder",_anzahlGlieder)
			 ||	!Objekttransformation::lese(leser, "definitionsminimum",kette->m_definitionsminimum)
			 ||	!Objekttransformation::lese(leser, "definitionsmaximum",kette->m_definitionsmaximum))
			return false;

		kette->m_anzahlGlieder=(unsigned short int)_anzahlGlieder;

		int i = 0;
		int gliednummer;
		Schnittstelle::Zeiger funktionobjekt;
		
		while (	Objekttransformation::lese(leser, "konfigurationsfunktionengliednummer_"+std::to_string(i),gliednummer)
			||	Objekttransformation::lese(leser, "konfigurationsfunktionen_"+std::to_string(i),funktionobjekt))
		{
			kette->m_konfigurationsfunktionen[gliednummer]=sKonfigurationsfunktionen::Zeiger::konvertiere(funktionobjekt);
			i++;
		}

		i = 0;
		while (	Objekttransformation::lese(leser, "kupplungsnummer_"+std::to_string(i),gliednummer)
			||	Objekttransformation::lese(leser, "einknickwinkelfunktion_"+std::to_string(i),funktionobjekt))
		{
			kette->m_einknickwinkelfunktion[gliednummer]=sUnaereReelleFunktion::Zeiger::konvertiere(funktionobjekt);
			i++;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////

	bool KonfigurationsfunktionenKetteTransformation::transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber)
	{
		KonfigurationsfunktionenKette::Zeiger ketteObjekt = KonfigurationsfunktionenKette::Zeiger::konvertiere(objekt);

		if (ketteObjekt == NULL)
			return false;
		if (	!Objekttransformation::schreibe(schreiber, "anzahlGlieder",ketteObjekt->anzahlGlieder())
			 ||	!Objekttransformation::schreibe(schreiber, "definitionsminimum",ketteObjekt->definitionsminimum())
			 || !Objekttransformation::schreibe(schreiber, "definitionsmaximum",ketteObjekt->definitionsmaximum()))
			return false;
		int i=0;
		for (map<int, sKonfigurationsfunktionen::Zeiger>::iterator iter = ketteObjekt->m_konfigurationsfunktionen.begin();iter!=ketteObjekt->m_konfigurationsfunktionen.end();iter++,i++)
		{
			if (	!Objekttransformation::schreibe(schreiber, "konfigurationsfunktionengliednummer_"+std::to_string(i),iter->first)
				 ||	!Objekttransformation::schreibe(schreiber, "konfigurationsfunktionen_"+std::to_string(i),iter->second))
			return false;
		}
		i = 0;
		for (map<int, sUnaereReelleFunktion::Zeiger>::iterator iter = ketteObjekt->m_einknickwinkelfunktion.begin();iter!=ketteObjekt->m_einknickwinkelfunktion.end();iter++,i++)
		{
			if (	!Objekttransformation::schreibe(schreiber, "kupplungsnummer_"+std::to_string(i),iter->first)
				||	!Objekttransformation::schreibe(schreiber, "einknickwinkelfunktion_"+std::to_string(i),iter->second))
				return false;
		}
		
		return true;
	}

	//////////////////////////////////////////////////////////////////////


};
