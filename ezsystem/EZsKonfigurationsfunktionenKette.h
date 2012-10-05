#ifndef EZ_SKONFIGURATIONSFUNKTIONENKETTE_H
#define EZ_SKONFIGURATIONSFUNKTIONENKETTE_H

///////////////////////////////////////////////////////////////////////////

#include "EZsUnaerePlanareFunktion.h"
#include "EZsKonfigurationsfunktionen.h"

///////////////////////////////////////////////////////////////////////////
namespace EZ 
{

///////////////////////////////////////////////////////////////////////////
/// Schnitstelle für KonfigurationsfunktionenKette
///
/// @ingroup    Pfad
//-------------------------------------------------------------------

class sKonfigurationsfunktionenKette : VERWENDE_SCHNITTSTELLE(sUnaerePlanareFunktion) 
{
    DEKLARIERE_SCHNITTSTELLE(sKonfigurationsfunktionenKette);
public:
	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Ausrichtung
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger ausrichtungFunktion(unsigned short glied) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den ersten Lenkwinkel
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelFunktion(unsigned short glied) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Position
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @result				die entsprechende Funktion.
	//--------------------------------------------------------------------
	virtual sUnaerePlanareFunktion::Zeiger positionFunktion(unsigned short glied) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den Einknickwinkel
	/// in der gewünschten Kupplung beschreibt.
	/// @param kupplung		die gewünschte Kupplung.
	/// @result				die entsprechende Funktion.
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger einknickwinkelFunktion(unsigned short glied) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Ausrichtung des gewünschten Gliedes am gewünschten 
	/// Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double ausrichtung( unsigned short glied, double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den ersten Lenkwinkel des gewünschten Gliedes am gewünschten 
	/// Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkel ( unsigned short glied, double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Position des gewünschten Gliedes am gewünschten 
	/// Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @result				die entsprechende Position 
	///						(Punkt2D(NaN(),NaN()), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual Punkt2D position (  unsigned short glied, double d) const = 0;
	
	//////////////////////////////////////////////////////////////////////
	/// Gibt den Einknickwinkel in der gewünschten Kupplung am gewünschten
	/// Definitionswert zurück.
	/// @param kupplung		die gewünschte Kupplung  [0..anzahlGlieder()-2]
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Einknickwinkel 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double einknickwinkel ( unsigned short kupplung, double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Ausrichtung des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied.  [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeAusrichtungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion ) =0;
	
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für den ersten Lenkwinkel des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied. [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion ) =0;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Position des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied. [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzePositionFunktion( unsigned short glied, sUnaerePlanareFunktion::Zeiger funktion ) =0;
	
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für den Einknickwinkel in der gewünschten Kupplung.
	/// @param kupplung		die gewünschte Kupplung. [0..anzahlGlieder()-2]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeEinknickwinkelFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion ) =0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Anzahl der Fahrzeugglieder zurück.
	/// @result				die Anzahl der Fahrzeugglieder
	//--------------------------------------------------------------------
	virtual unsigned short anzahlGlieder () const = 0;
};

};
#endif // EZ_SKONFIGURATIONSFUNKTIONENKETTE_H
