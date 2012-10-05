#ifndef EZ_STEUERFUNKTIONENTRANSFORMATION_H
#define EZ_STEUERFUNKTIONENTRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZSteuerfunktionen.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////
	/// Transformation zwischen Objekten der Klasse 
	/// Wegstueckschlange und Objektspeichern.
	///
	/// @ingroup    Persistenz
	//--------------------------------------------------------------------
	class SteuerfunktionenTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
	{
		SCHNITTSTELLENIMPLEMENTATION(SteuerfunktionenTransformation);

	public:

		//////////////////////////////////////////////////////////////////////
		/// Konstruktor.
		//--------------------------------------------------------------------
		SteuerfunktionenTransformation();

		virtual std::string typ();
		virtual int version();
		virtual Schnittstelle::Zeiger erzeugeObjekt();
		virtual bool transformiere(int version, sObjektleser::Zeiger leser, Schnittstelle::Zeiger objekt);
		virtual bool transformiere(Schnittstelle::Zeiger objekt, sObjektschreiber::Zeiger schreiber);   
	};

	//////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////

#endif
