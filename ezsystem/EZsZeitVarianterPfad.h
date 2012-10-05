#ifndef EZ_SZEITVARIANTERPFAD_H
#define EZ_SZEITVARIANTERPFAD_H

///////////////////////////////////////////////////////////////////////////

#include "EZsZeitInvarianterPfad.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

///////////////////////////////////////////////////////////////////////////
/// Schnittstelle für einen zeitvarianten Pfad.
///
/// @ingroup    Pfad
//-------------------------------------------------------------------


class sZeitVarianterPfad : VERWENDE_SCHNITTSTELLE(sZeitInvarianterPfad)
{
	DEKLARIERE_SCHNITTSTELLE(sZeitVarianterPfad)

public:

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeitpunkt der einem Definitionswert zugeordnet ist
	/// zurück.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Zeitpunkt.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double zeit ( double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Startzeitpunkt für diesen Pfad zurück.
	/// @result				der Startzeitpunkt für diesen Pfad.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double startzeit ( ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Endzeitpunkt für diesen Pfad zurück.
	/// @result				der Endzeitpunkt für diesen Pfad.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double endzeit ( ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Definitionswert der einem Zeitpunkt zugeordnet ist
	/// zurück.
	/// @param zeit			der Zeitpunkt.
	/// @result				der entsprechende Definitionswert.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double definitionswert ( double zeit ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Geschwindigkeit des gewünschten Fahrzeuggliedes am
	/// gewünschten Definitionswert zurück.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Geschwindigkeit
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual double geschwindigkeit ( unsigned short glied, double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Aenderung des ersten Lenkwinkels des gewünschten 
	/// Fahrzeuggliedes am gewünschten Definitionswert zurück.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Lenkwinkeländerung
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkelAenderung ( unsigned short glied, double d ) const = 0;
};

};

#endif