#ifndef EZ_PFADSTUECKTRANSFORMATION_H
#define EZ_PFADSTUECKTRANSFORMATION_H

///////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZSchnittstelle.h"
#include "EZsObjektarchiv.h"
#include "EZPfadstueck.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

	//////////////////////////////////////////////////////////////////////
	/// Transformation zwischen Objekten der Klasse 
	/// Wegstueckschlange und Objektspeichern.
	///
	/// @ingroup    Persistenz
	//--------------------------------------------------------------------
	class PfadstueckTransformation : VERWENDE_SCHNITTSTELLE(sObjekttransformation)
	{
		SCHNITTSTELLENIMPLEMENTATION(PfadstueckTransformation);

	public:

		//////////////////////////////////////////////////////////////////////
		/// Konstruktor.
		//--------------------------------------------------------------------
		PfadstueckTransformation();

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
