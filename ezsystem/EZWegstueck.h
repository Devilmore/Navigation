#ifndef EZ_WEGSTUECK_H
#define EZ_WEGSTUECK_H

///////////////////////////////////////////////////////////////////////////

#include "EZsWegstueck.h"
#include "EZPunkt2D.h"
#include "EZsFahrzeugdatenkette.h"
#include "EZsFahrzeugbeschreibungskette.h"
#include "EZFahrzeugbeschreibungskette.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ {

//////////////////////////////////////////////////////////////////////
/// Implementierung von Wegstueck.
/// @see sWegstueck.
///
/// @ingroup    Pfad
//--------------------------------------------------------------------

class Wegstueck : VERWENDE_SCHNITTSTELLE(sWegstueck)
{
    SCHNITTSTELLENIMPLEMENTATION(Wegstueck);

protected:
	/// true, wenn setzeAttribute() bereits aufgerufen wurde (dann haben weitere Aufrufe
	/// dieser Funktion keine Auswirkungen mehr.
	bool m_initialisiert;

    /// enthält die Startposition
    Punkt2D m_startpunkt;

    /// enthält die Endposition
    Punkt2D m_endpunkt;

    /// bestimmt die Längsrichtung, bei TRUE rückwärts, FALSE vorwärts
    bool m_rueckwaerts;

    /// enthält die Weglänge
    double m_weglaenge;

    /// enthält die zu fahrende Geschwindigkeit im Wegstück
    double m_geschwindigkeit;

	virtual void setzeAttribute(Punkt2D     startpunkt,
								Punkt2D     endpunkt,
								bool        rueckwaerts,
								double      geschwindigkeit);

    //////////////////////////////////////////////////////////////////////
    ///	Konstruktor.
    /// @param startpunkt               definiert den Startpunkt des Wegstückes
    /// @param endlage	                definiert den Startpunkt des Wegstückes
    /// @param rueckwaerts	            bestimmt, ob das Wegstück rückwärts
    ///                                 abgefahren werden soll
    /// @param geschwindigkeit          definiert die Geschwindigkeit, mit der
    ///                                 der Weg abgefahren werden soll
    //--------------------------------------------------------------------
    Wegstueck(  Punkt2D     startpunkt,
				Punkt2D     endpunkt,
				bool        rueckwaerts,
				double      geschwindigkeit);

    //////////////////////////////////////////////////////////////////////
    ///	Standardkonstruktor privat, da abstrakte Klasse.
    //--------------------------------------------------------------------
    Wegstueck();

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destruktor.
    //-----------------------------------------------------------------------------------------------
    virtual ~Wegstueck();

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Liefert die Geschwindigkeit, mit der das Wegstück befahren werden soll.
    /// @result Geschwindigkeit
    //-----------------------------------------------------------------------------------------------
	double geschwindigkeit() const {return m_geschwindigkeit;}

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Liefert die Länge von der Start- bis zur Endposition des Wegstücks.
    /// @result Weglänge
    //-----------------------------------------------------------------------------------------------
	double weglaenge() const {return m_weglaenge;}

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Liefert den Startpunkt des Wegstücks.
    /// @result Startpunkt
    //-----------------------------------------------------------------------------------------------
	Punkt2D startpunkt() const {return m_startpunkt;}

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Liefert den Endpunkt des Wegstücks.
    /// @result Endpunkt
    //-----------------------------------------------------------------------------------------------
	Punkt2D endpunkt() const {return m_endpunkt;}

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Ausrichtung am Ende des Wegstücks
	/// @result Ausrichtung am Ende des Wegstücks
	//--------------------------------------------------------------------
	virtual double endausrichtung() const;

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Ausrichtung am Anfang des Wegstücks
	/// @result Ausrichtung am Anfang des Wegstücks
	//--------------------------------------------------------------------
	virtual double startausrichtung() const;

	//////////////////////////////////////////////////////////////////////
	///	Liefert das Definitionsminimum (wird benötigt für die Implementation
	/// von sPlanareFunktion)
	/// @result 0.0
	//--------------------------------------------------------------------
	double definitionsminimum();

	//////////////////////////////////////////////////////////////////////
	///	Liefert das Definitionsmaximum (wird benötigt für die Implementation
	/// von sPlanareFunktion)
	/// @result weglaenge()
	//--------------------------------------------------------------------
	double definitionsmaximum();

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Sollposition an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollposition.
	//--------------------------------------------------------------------
	Punkt2D operator() (double d);

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Position im Wegstück, die am nächsten
	///	zur aktuellen Position ist.
	/// @param punkt	die aktuelle Position
	/// @result			der gesuchte Punkt
	//--------------------------------------------------------------------
	Punkt2D sollPosition(Punkt2D) const;

	//////////////////////////////////////////////////////////////////////
	///	Gibt an, ob der Weg rueckwaerts abgefahren wird.
	/// @result		true gdw. der Weg rückwärts abgefahren wird.
	//--------------------------------------------------------------------
	virtual bool rueckwaerts() const {return m_rueckwaerts;}

	//////////////////////////////////////////////////////////////////////
	///	Rotiert das Wegstück um einen Punkt und einen gegebenen Winkel
	/// @param mPunkt		der Mittelpunkt der Rotation
	/// @param beta			der Winkel
	/// @result				true bei Erfolg.
	//--------------------------------------------------------------------
	virtual bool rotiere(Punkt2D mPunkt, double beta);

	//////////////////////////////////////////////////////////////////////
	///	Verschiebt das Wegstück um einen Vektor
	/// @param differenz	der Vektor um den verschoben werden soll.
	/// @result				true bei Erfolg.
	//--------------------------------------------------------------------
	virtual bool verschiebe(Punkt2D differenz);
};


};
#endif // EZ_WEGSTUECK_H