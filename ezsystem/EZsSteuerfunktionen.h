#ifndef EZ_SSTEUERFUNKTIONEN_H
#define EZ_SSTEUERFUNKTIONEN_H

///////////////////////////////////////////////////////////////////////////

#include "EZSchnittstelle.h"
#include "EZsUnaereReelleFunktion.h"

///////////////////////////////////////////////////////////////////////////
namespace EZ 
{

///////////////////////////////////////////////////////////////////////////
/// Schnittstelle für Steuerfunktionen
///
/// @ingroup    Pfad
//-------------------------------------------------------------------

class sSteuerfunktionen : VERWENDE_SCHNITTSTELLE(sUnaereReelleFunktion) 
{
    DEKLARIERE_SCHNITTSTELLE(sSteuerfunktionen);
public:
	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Geschwindigkeit
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger geschwindigkeitFunktion() const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den Änderung des
	/// ersten Lenkwinkels beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelAenderungFunktion() const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Geschwinigkeit am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Geschwindigkeit 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double geschwindigkeit( double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Änderung des ersten Lenkwinkels am gewünschten 
	/// Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkelAenderung ( double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Geschwindigkeit.
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeGeschwindigkeitFunktion( sUnaereReelleFunktion::Zeiger funktion ) =0;
	
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Änderung des ersten Lenkwinkels.
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelAenderungFunktion( sUnaereReelleFunktion::Zeiger funktion ) =0;
};

};
#endif // EZ_SSTEUERFUNKTIONEN_H
