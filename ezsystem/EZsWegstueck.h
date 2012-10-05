#ifndef EZ_SWEGSTUECK_H
#define EZ_SWEGSTUECK_H

///////////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"
#include "EZsFahrzeugdatenkette.h"
#include "EZsFahrzeugbeschreibungskette.h"
#include "EZLage.h"
#include "EZsUnaerePlanareFunktion.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

///////////////////////////////////////////////////////////////////////////
/// Schnittstelle für ein Wegstück.
///
/// @ingroup    Pfad
//-------------------------------------------------------------------


class sWegstueck : VERWENDE_SCHNITTSTELLE(sUnaerePlanareFunktion)
{
	DEKLARIERE_SCHNITTSTELLE(sWegstueck)

public:
    /////////////////////////////////////////////////////////////////////
    ///	Liefert die Geschwindigkeit auf dem Wegstück.
    /// @result die Geschwindigkeit auf Wegstück
    //--------------------------------------------------------------------
    virtual double geschwindigkeit() const = 0;

    //////////////////////////////////////////////////////////////////////
    ///	Liefert die Weglänge.
    //--------------------------------------------------------------------
    virtual double weglaenge() const = 0;

    //////////////////////////////////////////////////////////////////////
    ///	Liefert die Sollposition an der Definitionsstelle d.
	/// @param d	der Definitionswert
    /// @result		die Sollposition.
    //--------------------------------------------------------------------
    virtual Punkt2D	position(double d) const = 0;

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Sollausrichtung an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollausrichtung.
	//--------------------------------------------------------------------
	virtual double ausrichtung(double d) const = 0;

    //////////////////////////////////////////////////////////////////////
    ///	Liefert den Definitionswert im Wegstück, die am nächsten
    ///	zur aktuellen Position ist.
	/// @param punkt	die aktuelle Position
    /// @result der gesuchte Definitionswert.
    //--------------------------------------------------------------------
    virtual double sollPositionDefinitionswert(Punkt2D punkt) const = 0;

    //////////////////////////////////////////////////////////////////////
    ///	Liefert die Position im Wegstück, die am nächsten
    ///	zur aktuellen Position ist.
	/// @param punkt	die aktuelle Position
    /// @result			der gesuchte Punkt
    //--------------------------------------------------------------------
    virtual Punkt2D sollPosition(Punkt2D punkt) const = 0;

    //////////////////////////////////////////////////////////////////////
    ///	Liefert den Startpunkt des Wegstücks.
    /// @result Startpunkt des Wegstücks
    //--------------------------------------------------------------------
    virtual Punkt2D startpunkt() const = 0;

    //////////////////////////////////////////////////////////////////////
    ///	Liefert den Endpunkt des Wegstücks.
    /// @result Endpunkt des Wegstücks
    //--------------------------------------------------------------------
    virtual Punkt2D endpunkt() const = 0;

    //////////////////////////////////////////////////////////////////////
    ///	Gibt an, ob der Weg rueckwaerts abgefahren wird.
	/// @result		true gdw. der Weg rückwärts abgefahren wird.
    //--------------------------------------------------------------------
    virtual bool rueckwaerts() const = 0;
	
	//////////////////////////////////////////////////////////////////////
	///	Liefert die Ausrichtung am Ende des Wegstücks
	/// @result Ausrichtung am Ende des Wegstücks
	//--------------------------------------------------------------------
	virtual double endausrichtung() const = 0;

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Ausrichtung am Anfang des Wegstücks
	/// @result Ausrichtung am Anfang des Wegstücks
	//--------------------------------------------------------------------
	virtual double startausrichtung() const = 0;

	//////////////////////////////////////////////////////////////////////
	///	Rotiert das Wegstück um einen Punkt und einen gegebenen Winkel
	/// @param mPunkt		der Mittelpunkt der Rotation
	/// @param beta			der Winkel
	/// @result				true bei Erfolg.
	//--------------------------------------------------------------------
	virtual bool rotiere(Punkt2D mPunkt, double beta) = 0;

	//////////////////////////////////////////////////////////////////////
	///	Verschiebt das Wegstück um einen Vektor
	/// @param differenz	der Vektor um den verschoben werden soll.
	/// @result				true bei Erfolg.
	//--------------------------------------------------------------------
	virtual bool verschiebe(Punkt2D differenz)=0;
	
};

};

#endif