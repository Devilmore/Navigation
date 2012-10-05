#ifndef EZ_KONFIGURATIONSFUNKTIONEN_H
#define EZ_KONFIGURATIONSFUNKTIONEN_H

///////////////////////////////////////////////////////////////////////////

#include "EZsKonfigurationsfunktionen.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ {

//////////////////////////////////////////////////////////////////////
/// Implementierung von Konfigurationsfunktionen.
/// @see sKonfigurationsfunktionen.
///
/// @ingroup    Pfad
//--------------------------------------------------------------------
class KonfigurationsfunktionenTransformation;
class Konfigurationsfunktionen : VERWENDE_SCHNITTSTELLE(sKonfigurationsfunktionen)
{
    SCHNITTSTELLENIMPLEMENTATION(Konfigurationsfunktionen);
	friend class KonfigurationsfunktionenTransformation;
protected:
	/// die gespeicherten Funktionen
	sUnaereReelleFunktion::Zeiger m_ausrichtungFunktion;
	sUnaereReelleFunktion::Zeiger m_lenkwinkelFunktion;
	//sUnaereReelleFunktion::Zeiger m_zweiterLenkwinkelFunktion;
	sUnaerePlanareFunktion::Zeiger m_positionFunktion;
	
	/// zwischengespeicherte Werte für Definitionsminimum und -maximum
	double m_definitionsminimum;
	double m_definitionsmaximum;

	/// aktualisiere die Werte für m_definitionsminimum und m_definitionsmaximum
	bool aktualisiereRaender();

public:
	/* --- Konstruktoren/Destruktoren --- */

	//////////////////////////////////////////////////////////////////////
	/// Konstruktor
	/// @param _positionFunktion			die Funktion für die Position
	/// @param _ausrichtungFunktion			die Funktion für die Ausrichtung
	/// @param _ersterLenkwinkelFunktion	die Funktion für den ersten Lenkwinkel
	/// @param _zweiterLenkwinkelFunktion	die Funktion für den zweiten Lenkwinkel
	//--------------------------------------------------------------------
	Konfigurationsfunktionen( sUnaerePlanareFunktion::Zeiger _positionFunktion = NULL, sUnaereReelleFunktion::Zeiger _ausrichtungFunktion = NULL, sUnaereReelleFunktion::Zeiger _lenkwinkelFunktion = NULL);

	virtual ~Konfigurationsfunktionen() {}


	/* --- Implementation von sKonfigurationsfunktionen --- */

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Ausrichtung
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger ausrichtungFunktion() const { return m_ausrichtungFunktion;}

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den Lenkwinkel
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelFunktion() const { return m_lenkwinkelFunktion;}

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Position
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaerePlanareFunktion::Zeiger positionFunktion() const { return m_positionFunktion;}

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Ausrichtung am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double ausrichtung( double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den ersten Lenkwinkel am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkel ( double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Position am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Position 
	///						(Punkt2D(NaN(),NaN()), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual Punkt2D position ( double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Ausrichtung
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeAusrichtungFunktion( sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für den ersten Lenkwinkel
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelFunktion( sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Position
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzePositionFunktion( sUnaerePlanareFunktion::Zeiger funktion );



	/* --- Implementation sUnaerePlanareFunktion --- */

	//////////////////////////////////////////////////////////////////////
	///	Liefert das Definitionsminimum 
	/// @result Das Maximum aller Definitionsminima
	//--------------------------------------------------------------------
	double definitionsminimum() { return m_definitionsminimum;}

	//////////////////////////////////////////////////////////////////////
	///	Liefert das Definitionsmaximum 
	/// @result Das Minimum aller Definitionsmaxima
	//--------------------------------------------------------------------
	double definitionsmaximum() {return m_definitionsmaximum;}

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Sollposition an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollposition.
	//--------------------------------------------------------------------
	Punkt2D operator() (double d) {return position(d);}
};


};
#endif // EZ_KONFIGURATIONSFUNKTIONEN_H