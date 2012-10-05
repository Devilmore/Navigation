#ifndef EZ_PFADVERFOLGUNG_H
#define EZ_PFADVERFOLGUNG_H

//////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"
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
class Pfadverfolgung : VERWENDE_SCHNITTSTELLE(sEreignisempfaenger)
{
    SCHNITTSTELLENIMPLEMENTATION(Pfadverfolgung);

private:
	std::string                             s_ereignisEinPeriode;
	std::string								s_ereignisEinEreignistypen;
	std::string                             s_ereignisEinFahrzeugdaten;
	std::string                             s_ereignisEinModus;
	std::string                             s_ereignisEinPing;
	std::string                             s_ereignisEinFahrzeugbeschreibungen;
	std::string                             s_ereignisAusModus;
	std::string								s_ereignisAusGeschwindigkeit;
	std::string 							s_ereignisAusLenkwinkel;
	std::string								s_ereignisEinStart;
	std::string								s_ereignisEinStop;
	std::string								s_ereignisEinPfadHinzufuegen;

	/// Modus
	std::string								m_modus;

	/// Uhr.
    sUhr::Zeiger                        m_uhr;

    /// Fahrzeugbeschreibungen.
    sFahrzeugbeschreibungskette::Zeiger m_fahrzeugbeschreibungen;
    /// Fahrzeugdaten.
    sFahrzeugdatenkette::Zeiger         m_fahrzeugdaten;

    /// Ereignisverteiler.
    sEreignisverteiler::Zeiger          m_ereignisverteiler;

    /// Beendet?
    bool                                m_beendet;

	/// Fahrt gestartet?
	bool m_gestartet;

	// kritischer Einknickwinkel
	double m_kritischerEinknickwinkel;

	bool verarbeiteModusEreignis			(sEreignis::Zeiger ereignis);

	//////////////////////////////////////////////////////////////////////
	///	Aktualisiert den kritischen Lenkwinkel.
	//--------------------------------------------------------------------
	void aktualisiereKritischenEinknickwinkel();



protected:
	bool gestartet() const { return m_gestartet; }
	void setzeGestartet(bool val);
	virtual bool verarbeiteStartEreignis			(sEreignis::Zeiger ereignis);
	virtual void verarbeiteModusWartend				();
	virtual bool verarbeiteStopEreignis				(sEreignis::Zeiger ereignis);
	virtual bool verarbeiteEreignistypenEreignis	(sEreignis::Zeiger ereignis);
	virtual bool verarbeitePfadHinzufuegenEreignis	(sEreignis::Zeiger ereignis) = 0;
	sFahrzeugdatenkette::Zeiger			fahrzeugdaten()			{return m_fahrzeugdaten;}
	sFahrzeugbeschreibungskette::Zeiger fahrzeugbeschreibungen(){return m_fahrzeugbeschreibungen;}
	sEreignisverteiler::Zeiger			ereignisverteiler()		{return m_ereignisverteiler;}
	double kritischerEinknickwinkel(){return m_kritischerEinknickwinkel;}
	virtual bool verfolgePfad()=0;

	//////////////////////////////////////////////////////////////////////
	///	Sendet ein Ereignis zur Änderung der Geschwindigkeit.
	/// @param geschwindigkeit		die gewünschte Geschwindigkeit.
	//--------------------------------------------------------------------
	void sendeGeschwindigkeitEreignis( double geschwindigkeit );

	//////////////////////////////////////////////////////////////////////
	///	Sendet ein Ereignis zur Änderung des Lenkwinkels.
	/// @param geschwindigkeit		der gewünschte Lenkwinkel.
	//--------------------------------------------------------------------
	void sendeLenkwinkelEreignis(double winkel);
public:


    //////////////////////////////////////////////////////////////////////
    /// Konstruktor.
    //--------------------------------------------------------------------
    Pfadverfolgung();

    //////////////////////////////////////////////////////////////////////
    /// Destruktor.
    //--------------------------------------------------------------------
    virtual ~Pfadverfolgung();

    //////////////////////////////////////////////////////////////////////
    /// Initialisiert das Objekt.
    //--------------------------------------------------------------------
    virtual bool initialisiere(sUhr::Zeiger uhr, std::string ereignistyp, sEreignisverteiler::Zeiger ereignisverteiler);

	//////////////////////////////////////////////////////////////////////
	///	Liefert die aktuelle Position des Bezugspunktes.
	/// Bei der Rückwärtsfahrt (wege->erstesWegstueck->rueckwaerts() ist true)
	/// wird der Mittelpunkt der Achse des Anhängers als bezugspunktes gewählt,
	/// sonst der Mittelpunkt der Hinterachse des Zugfahrzeugs.
	/// @param daten			die Fahrzeugdaten.
	/// @param beschreibungen	die Fahrzeugbeschreibungen.
	/// @result					die aktuelle Postion des Bezugspunktes.
	//--------------------------------------------------------------------
	static Punkt2D aktuellePosition(sFahrzeugdatenkette::Zeiger daten, sFahrzeugbeschreibungskette::Zeiger beschreibungen, bool rueckwaerts);

	//////////////////////////////////////////////////////////////////////
	///	Liefert die aktuelle Ausrichtung des Fahrzeuggliedes, auf dem der
	/// Bezugspunkt liegt.
	/// Bei der Rückwärtsfahrt (wege->erstesWegstueck->rueckwaerts() ist true)
	/// wird der Mittelpunkt der Achse des Anhängers als bezugspunktes gewählt,
	/// sonst der Mittelpunkt der Hinterachse des Zugfahrzeugs.
	/// @param daten			die Fahrzeugdaten.
	/// @param beschreibungen	die Fahrzeugbeschreibungen.
	/// @result					die aktuelle Postion des Bezugspunktes.
	//--------------------------------------------------------------------
	static double aktuelleAusrichtung(sFahrzeugdatenkette::Zeiger daten, bool rueckwaerts);

	//////////////////////////////////////////////////////////////////////
    /// Testen ob Verarbeitung beendet wurde.
    /// @result true wenn die Bearbeitung beendet wurde.
    //--------------------------------------------------------------------
    virtual bool beendet();

	//////////////////////////////////////////////////////////////////////
	/// Verarbeitet ein Ereignis
	/// @param	ereignis	ein Ereignis.
	/// @result				true wenn die Verarbeitung beendet wurde.
	//--------------------------------------------------------------------
    virtual bool verarbeiteEreignis(sEreignis::Zeiger ereignis);



};

//////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////

#endif
