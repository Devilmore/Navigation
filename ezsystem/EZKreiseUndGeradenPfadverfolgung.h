#ifndef EZ_KREISEUNDGERADENPFADVERFOLGUNG_H
#define EZ_KREISEUNDGERADENPFADVERFOLGUNG_H

//////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"
#include "EZPfadverfolgung.h"
#include "EZsUhr.h"
#include "EZsEreignisverteiler.h"
#include "EZsAbstrakteFahrzeugdaten.h"
#include "EZsFahrzeugdatenkette.h"
#include "EZsFahrzeugbeschreibungskette.h"
#include "EZsWegstueck.h"
#include <deque>
#include "EZsWegstueckSchlange.h"

//////////////////////////////////////////////////////////////////////

using namespace std;

namespace EZ
{
	//////////////////////////////////////////////////////////////////////
	/// Empfängt Wegstuecke und regelt den Lenkwinkel, so dass diese
	/// Wege abgefahren werden.
	//--------------------------------------------------------------------
	class KreiseUndGeradenPfadverfolgung : public Pfadverfolgung
	{
		SCHNITTSTELLENREIMPLEMENTATION(KreiseUndGeradenPfadverfolgung, Pfadverfolgung);

	private:
		sWegstueckSchlange::Zeiger				m_wegSchlange;
		

	protected:
		virtual bool verarbeiteStartEreignis			(sEreignis::Zeiger ereignis);
		virtual bool verarbeiteStopEreignis				(sEreignis::Zeiger ereignis);
		virtual bool verarbeitePfadHinzufuegenEreignis	(sEreignis::Zeiger ereignis);
		virtual void verarbeiteModusWartend();
		sWegstueckSchlange::Zeiger wegSchlange() const { return m_wegSchlange; }

	public:
		//////////////////////////////////////////////////////////////////////
		/// Konstruktor.
		//--------------------------------------------------------------------
		KreiseUndGeradenPfadverfolgung();

		//////////////////////////////////////////////////////////////////////
		/// Destruktor.
		//--------------------------------------------------------------------
		virtual ~KreiseUndGeradenPfadverfolgung();

		//////////////////////////////////////////////////////////////////////
		/// Initialisiert das Objekt.
		//--------------------------------------------------------------------
		virtual bool initialisiere(sUhr::Zeiger uhr, std::string ereignistyp, sEreignisverteiler::Zeiger ereignisverteiler);
	};

	//////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////

#endif
