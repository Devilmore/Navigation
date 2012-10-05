#ifndef EZ_STEUERFUNKTIONENKETTETRANSFORMATION_H
#define EZ_STEUERFUNKTIONENKETTETRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZSteuerfunktionenKette.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////
	/// Transformation zwischen Objekten der Klasse 
	/// Wegstueckschlange und Objektspeichern.
	///
	/// @ingroup    Persistenz
	//--------------------------------------------------------------------
	class SteuerfunktionenKetteTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
	{
		SCHNITTSTELLENIMPLEMENTATION(SteuerfunktionenKetteTransformation);

	public:

		//////////////////////////////////////////////////////////////////////
		/// Konstruktor.
		//--------------------------------------------------------------------
		SteuerfunktionenKetteTransformation();

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
