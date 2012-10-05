#ifndef EZ_PFADAUFBEREITUNG_H
#define EZ_PFADAUFBEREITUNG_H

///////////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"
#include "EZPfadstueck.h"
#include "EZAggregierterPfad.h"
#include "EZsWegstueckSchlange.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

	///////////////////////////////////////////////////////////////////////////
	/// Pfadaufbereitung.
	///
	/// @ingroup    Pfad
	//-------------------------------------------------------------------


	class Pfadaufbereitung : VERWENDE_SCHNITTSTELLE(Schnittstelle)
	{
		SCHNITTSTELLENIMPLEMENTATION(Pfadaufbereitung);
	private:
		static sWegstueckSchlange::Zeiger konvertiereAggregiertenPfad(AggregierterPfad::Zeiger pfad,double schrittweite);
		static sWegstueckSchlange::Zeiger konvertierePfadstueck(Pfadstueck::Zeiger pfad,double schrittweite);
	public:
		static sWegstueckSchlange::Zeiger konvertiere(sZeitInvarianterPfad::Zeiger pfad,double schrittweite);
		
	};

};

#endif