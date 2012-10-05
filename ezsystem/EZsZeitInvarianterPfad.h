#ifndef EZ_SZEITINVARIANTERPFAD_H
#define EZ_SZEITINVARIANTERPFAD_H

///////////////////////////////////////////////////////////////////////////

#include "EZsUnaerePlanareFunktion.h"
#include "EZsUnaereReelleFunktion.h"
#include "EZsZeichenflaeche.h"
#include "EZPunkt2D.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ
{

///////////////////////////////////////////////////////////////////////////
/// Schnittstelle für einen zeitinvarianten Pfad.
///
/// @ingroup    Pfad
//-------------------------------------------------------------------


class sZeitInvarianterPfad : VERWENDE_SCHNITTSTELLE(sUnaerePlanareFunktion)
{
	DEKLARIERE_SCHNITTSTELLE(sZeitInvarianterPfad)

public:
	//////////////////////////////////////////////////////////////////////
	/// Zeichnet den Verlauf der Position auf die angebenene Zeichenflaeche.
	/// @param zeichenflaeche Die Zeichenflaeche
	//--------------------------------------------------------------------
	virtual void zeichne(sZeichenflaeche::Zeiger zeichenflaeche)=0;

	//////////////////////////////////////////////////////////////////////
	/// Verschiebt alle Funktionen so auf der x-Achse, dass die Definition
	/// bei d beginnt.
	/// @param d Das neue Minimum des Definitionsbereichs.
	//--------------------------------------------------------------------
	virtual void setzeDefinitionsminimum(double d) = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Anzahl der Fahrzeugglieder zurück.
	/// @result				die Anzahl der Fahrzeugglieder
	//--------------------------------------------------------------------
	virtual unsigned short anzahlGlieder ( )	const =	0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Ausrichtung des gewünschten Fahrzeuggliedes am
	/// gewünschten Definitionswert zurück.
	/// @param glied		die Nummer des Fahrzeuggliedes. [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual double ausrichtung		( unsigned short glied,		double d ) const = 0;
	
	//////////////////////////////////////////////////////////////////////
	/// Gibt die Position des gewünschten Fahrzeuggliedes am
	/// gewünschten Definitionswert zurück.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Position 
	///						(Punkt2D(NaN(),NaN()), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual Punkt2D position		( unsigned short glied,		double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den ersten Lenkwinkel des gewünschten Fahrzeuggliedes am
	/// gewünschten Definitionswert zurück.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual	double lenkwinkel	( unsigned short glied,		double d ) const = 0;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Einknickwinkel der gewünschten Kupplung am
	/// gewünschten Definitionswert zurück.
	/// @param kupplung		die Nummer der Kupplung [0,anzahlGlieder()-2]
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Einknickwinkel
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual	double einknickwinkel	( unsigned short kupplung,	double d ) const = 0;
	
	//////////////////////////////////////////////////////////////////////
	/// Gibt die Fahrtrichtung am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				true gdw. die Fahrtrichtung rueckwaerts ist.
	//--------------------------------------------------------------------
	virtual bool rueckwaerts ( double d ) const = 0;
};

};

#endif