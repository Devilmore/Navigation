#ifndef EZ_SSTEUERFUNKTIONENKETTE_H
#define EZ_SSTEUERFUNKTIONENKETTE_H

///////////////////////////////////////////////////////////////////////////

#include "EZsUnaereReelleFunktion.h"
#include "EZsSteuerfunktionen.h"

///////////////////////////////////////////////////////////////////////////
namespace EZ 
{

///////////////////////////////////////////////////////////////////////////
/// Schnitstelle für SteuerfunktionenKette
///
/// @ingroup    Pfad
//-------------------------------------------------------------------

class sSteuerfunktionenKette : VERWENDE_SCHNITTSTELLE(sUnaereReelleFunktion) 
{
    DEKLARIERE_SCHNITTSTELLE(sSteuerfunktionenKette);
public:
	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Geschwindigkeit
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger geschwindigkeitFunktion(unsigned short glied) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die Änderung des
	/// ersten Lenkwinkels des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelAenderungFunktion(unsigned short glied) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Geschwindigkeit des gewünschten Gliedes am gewünschten 
	/// Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double geschwindigkeit( unsigned short glied, double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Änderung des ersten Lenkwinkesl des gewünschten Gliedes 
	/// am gewünschten Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkelAenderung ( unsigned short glied, double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Geschwindigkeit des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied.  [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeGeschwindigkeitFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion ) =0;
	
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Änderung des ersten Lenkwinkel des 
	/// gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied. [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelAenderungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion ) =0;
	

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Anzahl der Fahrzeugglieder zurück.
	/// @result				die Anzahl der Fahrzeugglieder
	//--------------------------------------------------------------------
	virtual unsigned short anzahlGlieder () const = 0;
};

};
#endif // EZ_SKONFIGURATIONSFUNKTIONENKETTE_H
