#ifndef EZ_KORREKTURKREISPFADVERFOLGUNG_H
#define EZ_KORREKTURKREISPFADVERFOLGUNG_H

//////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"
#include "EZKreiseUndGeradenPfadverfolgung.h"
#include "EZsUhr.h"
#include "EZsEreignisverteiler.h"
#include "EZsAbstrakteFahrzeugdaten.h"
#include "EZsFahrzeugdatenkette.h"
#include "EZsFahrzeugbeschreibungskette.h"
#include "EZsWegstueck.h"
#include <deque>
#include "EZsWegstueckSchlange.h"
#include "EZsPidRegler.h"

//////////////////////////////////////////////////////////////////////

using namespace std;

namespace EZ
{

//////////////////////////////////////////////////////////////////////
/// Empfängt Wegstuecke und regelt den Lenkwinkel, so dass diese
/// Wege abgefahren werden.
//--------------------------------------------------------------------
class KorrekturKreisPfadverfolgung : public KreiseUndGeradenPfadverfolgung
{
     SCHNITTSTELLENREIMPLEMENTATION(KorrekturKreisPfadverfolgung, KreiseUndGeradenPfadverfolgung);

private:
	double	m_m1,m_l1,m_l2;
	double  m_kp;

	bool			m_festerSollEinknickwinkelVorhanden;
	double			m_festerSollEinknickwinkel;

	double			m_lenkgeschwindigkeit;
	bool			m_treffpunktWandert;
	double			m_vorraussichtRueckwaerts;
	double			m_vorraussichtVorwaerts;

	//////////////////////////////////////////////////////////////////////
	///	Führt die Pfadverfolgung aus
	/// @result true gdw. noch Pfadstuecke übrig sind.
	//--------------------------------------------------------------------
	bool verfolgePfad();

	double beschraenkeSollLenkwinkel( double sollLenkwinkel );

	//////////////////////////////////////////////////////////////////////
	///	Berechne den Solllenkwinkel für die Rueckwaertsfahrt.
	/// Dafür wird zunächst der Lenkwinkel berechnet, um den SollEinknickwinkel
	/// zu halten. Dieser Winkel wird je nach Größe der Differenz zwischen
	/// Ist- und Solleinknickwinkel und des Regelungsparameters modifiziert.
	/// @param beschreibungen		die Fahrzeugbeschreibungen.
	/// @param istEinknickwinkel	die aktuelle Einknickwinkel.
	/// @param sollEinknickwinkel	der zuvor berechnete Solleinknickwinkel.
	/// @param regelparameter		der Regelungsparameter.
	/// @result						der SollLenkwinkel.
	//--------------------------------------------------------------------
	double berechneSollLenkwinkel(sFahrzeugdatenkette::Zeiger daten,sFahrzeugbeschreibungskette::Zeiger beschreibungen,sWegstueckSchlange::Zeiger wege);
protected:
	virtual bool verarbeiteStartEreignis			(sEreignis::Zeiger ereignis);

public:


    //////////////////////////////////////////////////////////////////////
    /// Konstruktor.
    //--------------------------------------------------------------------
    KorrekturKreisPfadverfolgung();

    //////////////////////////////////////////////////////////////////////
    /// Destruktor.
    //--------------------------------------------------------------------
    virtual ~KorrekturKreisPfadverfolgung();


	//////////////////////////////////////////////////////////////////////
	///	Berechnet den Mittelpunkt des Korrekturkreises.
	/// Das ist derjenige Kreis, der durch die aktuelle Position und durch
	/// den TreffPunkt verläuft und darüberhinaus die folgende Eigenschaft
	/// hat:
	/// Die Gerade ,die der Verlängerung der aktuellen Ausrichtung durch
	/// die aktuelle Position enspricht, verläuft liegt tangential am Kreis.
	/// TODO: Skizze hierzu verlinken.
	/// @param treffpunkt		der Treffpunkt.
	/// @param istPunkt			die aktuelle Position des Fahrzeuges.
	/// @param istAusrichtung	die aktuelle Ausrichtung des Fahrzeuges im
	///							Bogenmaß.
	/// @result					der berechnete Mittelpunkt.
	//--------------------------------------------------------------------
	static Punkt2D berechneKorrekturkreisMittelpunkt(Punkt2D treffPunkt, Punkt2D istPunkt, double istAusrichtung);

	//////////////////////////////////////////////////////////////////////
	///	Berechnet den Solleinknickwinkel. Das ist derjenige Einknickwinkel
	/// der anliegen muss, damit der Korrekturkreis gefahren wird.
	/// Der Korrekturkreis ist der Kreis, der durch den Istpunkt und durch
	/// den Treffpunkt verläuft. Zusätzlich soll die Ausrichtung durch den
	/// Istpunkt tangetial an diesem Kreis liegen.
	/// @param beschreibungen   die Fahrzeugbeschreibungskette
	/// @param treffpunkt		der Treffpunkt
	/// @param istPunkt			die aktuelle Position des Fahrzeuges
	/// @param istAusrichtung	die aktuelle Ausrichtung des Fahrzeuges im
	///							Bogenmaß
	/// @result					der berechnete Treffpunkt
	//--------------------------------------------------------------------
	double berechneSollEinknickwinkel( sFahrzeugdatenkette::Zeiger daten, sFahrzeugbeschreibungskette::Zeiger beschreibungen, Punkt2D treffPunkt, sWegstueckSchlange::Zeiger wege);

	//////////////////////////////////////////////////////////////////////
	///	Berechnet den Treffpunkt. Dies entspricht dem Idealpunkt, der um
	/// "vorraussicht" auf dem Pfad verschoben wurde. Sollte dabei der
	///  Punkt aus dem aktuellen Wegstück herausgeschoben werden, wird er
	/// a) auf dem nächsten Wegstück weiter geschoben (falls eines existiert
	///    und in die gleiche Richtung verläuft)
	/// b) auf dem aktuellen Wegstück weiter geschoben (sonst)
	/// @param idealwert    Definitionswert des aktuellen Wegstückes, der
	///						dem Idealpunkt entspricht.
	/// @param vorraussicht	Länge um die der Idealpunkt auf dem Weg ver-
	///						schoben werden soll.
	/// @param wege			Die beidseitige Schlange, die die Wegstücken ent-
	///						hält
	/// @result				der berechnete Treffpunkt
	//--------------------------------------------------------------------
	static Punkt2D berechneTreffpunkt( double vorraussicht, sWegstueckSchlange::Zeiger wege, double istAusrichtung,Punkt2D istPosition, bool treffpunktWandert);

	//////////////////////////////////////////////////////////////////////
	///	Entfernt abgefahrene Wegstücken aus der Schlange der Wegstücken.
	/// @param istPunkt     die aktuelle Position des Fahrzeuges.
	/// @param wege			die sollWegSchlange, die verändert wird.
	/// @result				true gdw. nach der Ausführung noch Wegstücke
	///						in der Schlange übrig sind.
	//--------------------------------------------------------------------
	static bool entferneAbgefahreneWegstuecke( sFahrzeugdatenkette::Zeiger daten, sFahrzeugbeschreibungskette::Zeiger beschreibungen, sWegstueckSchlange::Zeiger wege, double* entfernteLaenge = NULL);

	static double berechneKorrekturkreisRadius(Punkt2D treffPunkt, Punkt2D istPunkt, double istAusrichtung);
};

//////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////

#endif
