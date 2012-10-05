#ifndef EZ_STEUERFUNKTIONENKETTE_H
#define EZ_STEUERFUNKTIONENKETTE_H

///////////////////////////////////////////////////////////////////////////

#include "EZsSteuerfunktionenKette.h"
#include "EZsSteuerfunktionen.h"
#include <map>

using namespace std;

///////////////////////////////////////////////////////////////////////////
namespace EZ
{

///////////////////////////////////////////////////////////////////////////
/// Implementation von KonfigurationsfunktionenKette
///
/// @see sKonfigurationsfunktionenKette
/// @ingroup    Pfad
//-------------------------------------------------------------------
class SteuerfunktionenKetteTransformation;
class SteuerfunktionenKette : VERWENDE_SCHNITTSTELLE(sSteuerfunktionenKette)
{
	SCHNITTSTELLENIMPLEMENTATION(SteuerfunktionenKette);
	friend class SteuerfunktionenKetteTransformation;
protected:
	unsigned short m_anzahlGlieder;
	double m_definitionsminimum;
	double m_definitionsmaximum;
	map<int, sSteuerfunktionen::Zeiger> m_steuerfunktionen;
	bool aktualisiereRaender();
public:
	/* --- Konstruktoren/Destruktoren --- */
	SteuerfunktionenKette(unsigned short _anzahlGlieder = 0);
	virtual ~SteuerfunktionenKette() {};


	/* --- Implementation von sSteuerfunktionenKette --- */

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Geschwindigkeit
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger geschwindigkeitFunktion(unsigned short glied) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die Änderung des
	/// ersten Lenkwinkels des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelAenderungFunktion(unsigned short glied) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Geschwindigkeit des gewünschten Gliedes am gewünschten
	/// Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double geschwindigkeit( unsigned short glied, double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Änderung des ersten Lenkwinkesl des gewünschten Gliedes
	/// am gewünschten Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkelAenderung ( unsigned short glied, double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Geschwindigkeit des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied.  [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeGeschwindigkeitFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Änderung des ersten Lenkwinkel des
	/// gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied. [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelAenderungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Anzahl der Fahrzeugglieder zurück.
	/// @result				die Anzahl der Fahrzeugglieder
	//--------------------------------------------------------------------
	virtual unsigned short anzahlGlieder () const {return m_anzahlGlieder;}

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
	///	Liefert die SollGeschwindigkeit an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollposition.
	//--------------------------------------------------------------------
	double operator() (double d) {return geschwindigkeit(0,d);}
};

};
#endif // EZ_SKONFIGURATIONSFUNKTIONENKETTE_H
