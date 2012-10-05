#ifndef EZ_KONFIGURATIONSFUNKTIONENKETTETRANSFORMATION_H
#define EZ_KONFIGURATIONSFUNKTIONENKETTETRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZKonfigurationsfunktionenKette.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////
	/// Transformation zwischen Objekten der Klasse 
	/// Wegstueckschlange und Objektspeichern.
	///
	/// @ingroup    Persistenz
	//--------------------------------------------------------------------
	class KonfigurationsfunktionenKetteTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
	{
		SCHNITTSTELLENIMPLEMENTATION(KonfigurationsfunktionenKetteTransformation);

	public:

		//////////////////////////////////////////////////////////////////////
		/// Konstruktor.
		//--------------------------------------------------------------------
		KonfigurationsfunktionenKetteTransformation();

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
