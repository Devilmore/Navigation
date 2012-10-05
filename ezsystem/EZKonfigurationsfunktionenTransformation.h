#ifndef EZ_KONFIGURATIONSFUNKTIONENTRANSFORMATION_H
#define EZ_KONFIGURATIONSFUNKTIONENTRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZKonfigurationsfunktionen.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////
	/// Transformation zwischen Objekten der Klasse 
	/// Wegstueckschlange und Objektspeichern.
	///
	/// @ingroup    Persistenz
	//--------------------------------------------------------------------
	class KonfigurationsfunktionenTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
	{
		SCHNITTSTELLENIMPLEMENTATION(KonfigurationsfunktionenTransformation);

	public:

		//////////////////////////////////////////////////////////////////////
		/// Konstruktor.
		//--------------------------------------------------------------------
		KonfigurationsfunktionenTransformation();

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
