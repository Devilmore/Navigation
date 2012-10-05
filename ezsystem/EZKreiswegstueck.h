#ifndef EZ_KREISWEGSTUECK_H
#define EZ_KREISWEGSTUECK_H

/////////////////////////////////////////////////////////////////////////////////////////////////

#include "EZWegstueck.h"
#include "EZsFahrzeugbeschreibungskette.h"
#include "EZsFahrzeugdatenkette.h"
#include "EZPunkt2D.h"

////////////////////////////////////////////////////////////////////////////////////////////////



namespace EZ
{

////////////////////////////////////////////////////////////////////////////////////////////////
/// Implementerung von Kreiswegstueck
/// @see Wegstueck
///
/// @ingroup    Pfad
//---------------------------------------------------------------------------------------------


class Kreiswegstueck : public Wegstueck
{

    SCHNITTSTELLENREIMPLEMENTATION(Kreiswegstueck, Wegstueck);

protected:
    /// enthält den Kreiswinkel, der abgefahren wird,
    /// nicht den Winkel zwischen den zwei Vektoren, die
    /// den Start- und Endpunkt bilden
    double m_winkel;

	/// enthält den Winkel vom Mittelpunkt zum Startpunkt 
	double m_startwinkel;
	/// enthält den Winkel vom Mittelpunkt zum Endpunkt
	double m_endwinkel;
	/// berechnet den m_startwinkel, m_endwinkel und m_winkel
	void aktualisiereWinkel();

	////////////////////////////////////////////////////////////////////////////////////////////////
	/// Gibt den Winkel vom Mittelpunkt zum Startpunkt zurück.
	/// @result der Winkel vom Mittelpunkt zum Startpunkt
	double startwinkel() const {return m_startwinkel;}

	////////////////////////////////////////////////////////////////////////////////////////////////
	/// Gibt den Winkel vom Mittelpunkt zum Endwinkel zurück.
	/// @result der Winkel vom Mittelpunkt zum Endwinkel
	double endwinkel() const {return m_endwinkel;}

    /// enthält den Radius
    double m_radius;

    /// enthält die Richtung des Kreisbogens
    bool m_rechtsfahrt;

    /// enthält den Mittelpunkt des Kreises
    Punkt2D m_mittelpunkt;

public:    
	////////////////////////////////////////////////////////////////////////////////////////////////
	/// Default-Konstruktor (für die Transformation) auf jeden Fall muss nach Aufrufen dieses
	/// Konstruktors setzeAttribute() aufgerufen werden.
	//----------------------------------------------------------------------------------------------
	Kreiswegstueck();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Konstruktor
    ///     @param startpunkt               definiert den Startpunkt des Kreisstücks
    ///     @param endpunkt                 definiert den Endpunkt des Kreisstücks
    ///     @param radius                   definiert den Radius des Kreisstücks
    ///     @param rechtsfahrt              definiert die Rechts-Links-Richtung des Kreisbogen
    ///     @param rueckwaerts              definiert die Vorwaerts-Rueckwaerts-Fahrt im Kreis
    ///     @param geschwindigkeit          definiert die Geschwindigkeit, mit der der Kreis
    ///                                     durchfahren werden soll
    //----------------------------------------------------------------------------------------------
    Kreiswegstueck( Punkt2D startpunkt,
					Punkt2D endpunkt,
					Punkt2D mittelpunkt,
					bool	rechtsfahrt,
					bool	rueckwaerts,
					double	geschwindigkeit);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///     Destruktor
    ///---------------------------------------------------------------------------------------------
    virtual ~Kreiswegstueck();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Setzt die Attribute des Kreisweges
    ///     @param startpunkt               definiert den Startpunkt des Kreisstücks
    ///     @param endpunkt                 definiert den Endpunkt des Kreisstücks
    ///     @param radius                   definiert den Radius des Kreisstücks
    ///     @param rechtsfahrt              definiert die Rechts-Links-Richtung des Kreisbogen
    ///     @param rueckwaerts              definiert die Vorwaerts-Rueckwaerts-Fahrt im Kreis
    ///     @param geschwindigkeit          definiert die Geschwindigkeit, mit der der Kreis
    ///                                     durchfahren werden soll
    //----------------------------------------------------------------------------------------------
    virtual void setzeAttribute(    Punkt2D startpunkt,
                                    Punkt2D endpunkt,
	                                Punkt2D mittelpunkt,
                                    bool rechtsfahrt,
                                    bool rueckwaerts,
                                    double geschwindigkeit);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Liefert den Mittelpunkt des Kreisstücks
    ///     @result der Mittelpunkt des Kreiswegstücks
    //----------------------------------------------------------------------------------------------
	virtual Punkt2D mittelpunkt() const {return m_mittelpunkt;}

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Liefert den Radius des Kreisstücks
    /// @result der Radius des Kreiswegstücks.
    //----------------------------------------------------------------------------------------------
	virtual double radius() const {return m_radius;}

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Liefert die Richtung, in welche der Kreis durchfahren wird
    /// @result true gdw. das Wegstück eine Rechtskurve beschreibt
    //----------------------------------------------------------------------------------------------
	virtual bool rechtsfahrt() const {return m_rechtsfahrt;}

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Sollposition an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollposition.
	//--------------------------------------------------------------------
	virtual Punkt2D position(double d) const;

	//////////////////////////////////////////////////////////////////////
	///	Liefert den Definitionswert im Wegstück, die am nächsten
	///	zur aktuellen Position ist.
	/// @param punkt	die aktuelle Position
	/// @result der gesuchte Definitionswert.
	//--------------------------------------------------------------------
	virtual double sollPositionDefinitionswert(Punkt2D punkt) const;

	//////////////////////////////////////////////////////////////////////
	///	Liefert den Kreiswinkel, der abgefahren wird
	/// @param punkt	die aktuelle Position
	/// @result der gesuchte Definitionswert.
	//--------------------------------------------------------------------
	virtual double winkel() const {return m_winkel;}

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Sollausrichtung an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollausrichtung.
	//--------------------------------------------------------------------
	double ausrichtung(double d) const;

	//////////////////////////////////////////////////////////////////////
	///	Rotiert das Wegstück um einen Punkt und einen gegebenen Winkel
	/// @param mPunkt		der Mittelpunkt der Rotation
	/// @param beta			der Winkel
	/// @result				true bei Erfolg.
	//--------------------------------------------------------------------
	bool rotiere(Punkt2D mPunkt, double beta);

	//////////////////////////////////////////////////////////////////////
	///	Rotiert das Wegstück um einen Punkt und einen gegebenen Winkel
	/// @param differenz	der Vektor um den verschoben werden soll.
	/// @result				true bei Erfolg.
	//--------------------------------------------------------------------
	bool verschiebe(Punkt2D differenz);
};

};
#endif // EZ_KREISWEGSTUECK_H