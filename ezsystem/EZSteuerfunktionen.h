#ifndef EZ_STEUERFUNKTIONEN_H
#define EZ_STEUERFUNKTIONEN_H

///////////////////////////////////////////////////////////////////////////

#include "EZsSteuerfunktionen.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ 
{

//////////////////////////////////////////////////////////////////////
/// Implementierung von Steuerfunktionen.
/// @see sSteuerfunktionen.
///
/// @ingroup    Pfad
//--------------------------------------------------------------------
class SteuerfunktionenTransformation;
class Steuerfunktionen : VERWENDE_SCHNITTSTELLE(sSteuerfunktionen)
{
    SCHNITTSTELLENIMPLEMENTATION(Steuerfunktionen);
	friend class SteuerfunktionenTransformation;
protected:
	/// die gespeicherten Funktionen
	sUnaereReelleFunktion::Zeiger m_geschwindigkeitFunktion;
	sUnaereReelleFunktion::Zeiger m_lenkwinkelAenderungFunktion;
	
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
	Steuerfunktionen(  sUnaereReelleFunktion::Zeiger _geschwindigkeitFunktion = NULL,
					   sUnaereReelleFunktion::Zeiger _ersterLenkwinkelAenderungFunktion = NULL);
		
	virtual ~Steuerfunktionen() {}


	/* --- Implementation von sSteuerfunktionen --- */

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Geschwindigkeit
	/// beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger geschwindigkeitFunktion() const {return m_geschwindigkeitFunktion;}

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den Änderung des
	/// ersten Lenkwinkels beschreibt.
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelAenderungFunktion() const {return m_lenkwinkelAenderungFunktion;}

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Geschwinigkeit am gewünschten Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Geschwindigkeit 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double geschwindigkeit( double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Änderung des ersten Lenkwinkels am gewünschten 
	/// Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel 
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkelAenderung ( double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Geschwindigkeit.
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeGeschwindigkeitFunktion( sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Änderung des ersten Lenkwinkels.
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelAenderungFunktion( sUnaereReelleFunktion::Zeiger funktion );


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
	double operator() (double d) {return geschwindigkeit(d);}
};


};
#endif // EZ_STEUERFUNKTIONEN_H