#ifndef EZ_SKONFIGURATIONSFUNKTIONEN_H
#define EZ_SKONFIGURATIONSFUNKTIONEN_H

///////////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"
#include "EZsUnaerePlanareFunktion.h"
#include "EZsUnaereReelleFunktion.h"

///////////////////////////////////////////////////////////////////////////
namespace EZ 
{

///////////////////////////////////////////////////////////////////////////
/// Schnitstelle für Konfigurationsfunktionen
///
/// @ingroup    Pfad
//-------------------------------------------------------------------

class sKonfigurationsfunktionen : VERWENDE_SCHNITTSTELLE(sUnaerePlanareFunktion) 
{
    DEKLARIERE_SCHNITTSTELLE(sKonfigurationsfunktionen);
public:
	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Ausrichtung
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger ausrichtungFunktion() const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den ersten Lenkwinkel
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelFunktion() const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Position
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaerePlanareFunktion::Zeiger positionFunktion() const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Ausrichtung am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double ausrichtung( double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den ersten Lenkwinkel am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkel ( double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Position am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Position 
	///						(Punkt2D(NaN(),NaN()), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual Punkt2D position ( double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Ausrichtung
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeAusrichtungFunktion( sUnaereReelleFunktion::Zeiger funktion ) =0;
	
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für den ersten Lenkwinkel
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelFunktion( sUnaereReelleFunktion::Zeiger funktion ) =0;
	
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Position
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzePositionFunktion( sUnaerePlanareFunktion::Zeiger funktion ) =0;

};

};
#endif // EZ_SKONFIGURATIONSFUNKTIONEN_H
