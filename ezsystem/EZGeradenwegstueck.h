#ifndef EZ_GERADENWEGSTUECK_H
#define EZ_GERADENWEGSTUECK_H

///////////////////////////////////////////////////////////////////////////

#include "EZWegstueck.h"
#include "EZPunkt2D.h"

//////////////////////////////////////////////////////////////////////////

namespace EZ
{

///////////////////////////////////////////////////////////////////////////
/// Implementierung von Geradenwegstueck
///
/// @see Wegstueck
///
/// @ingroup    Pfad
//-------------------------------------------------------------------

class Geradenwegstueck  : public Wegstueck
{
    SCHNITTSTELLENREIMPLEMENTATION(Geradenwegstueck, Wegstueck);
public:
	////////////////////////////////////////////////////////////////////////////////////////////////
	/// Default-Konstruktor (für die Transformation) auf jeden Fall muss nach Aufrufen dieses
	/// Konstruktors setzeAttribute() aufgerufen werden.
	//----------------------------------------------------------------------------------------------
    Geradenwegstueck();

    //////////////////////////////////////////////////////////////////////
    ///	Konstruktor.
    /// @param startpunkt           definiert den Startpunkt des Wegstückes
    /// @param endpunkt	            definiert den Endpunkt des Wegstückes
    /// @param geschwindigkeit      definiert die Geschwindigkeit, mit der
    ///                             das Wegstück gefahren werden soll
    /// @param rueckwaerts	        bestimmt, ob das Wegstück rückwärts
    ///			                    abgefahren werden soll
    //--------------------------------------------------------------------
    Geradenwegstueck(	Punkt2D     startpunkt,
						Punkt2D     endpunkt,
						bool        rueckwaerts,
						double      geschwindigkeit);

    //////////////////////////////////////////////////////////////////////
    ///	Destruktor.
    //--------------------------------------------------------------------
    virtual ~Geradenwegstueck();

    //////////////////////////////////////////////////////////////////////
    ///	setzt die Attribute von Geradenwegstueck.
    /// @param startpunkt           definiert den Startpunkt des Wegstückes
    /// @param endpunkt	            definiert den Endpunkt des Wegstückes
    /// @param geschwindigkeit      definiert die Geschwindigkeit, mit der
    ///                             das Wegstück gefahren werden soll
    /// @param rueckwaerts	        bestimmt, ob das Wegstück rückwärts
    ///			                    abgefahren werden soll
    //--------------------------------------------------------------------
    virtual void setzeAttribute(    Punkt2D     startpunkt,
                                    Punkt2D     endpunkt,
                                    bool        rueckwaerts,
                                    double      geschwindigkeit);


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
	///	Liefert die Sollausrichtung an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollausrichtung.
	//--------------------------------------------------------------------
	double ausrichtung(double d) const;

}; 

};
#endif // EZ_GERADENWEGSTUECK_H