#ifndef EZ_KONFIGURATIONSFUNKTIONENKETTE_H
#define EZ_KONFIGURATIONSFUNKTIONENKETTE_H

///////////////////////////////////////////////////////////////////////////

#include "EZsKonfigurationsfunktionenKette.h"
#include "EZKonfigurationsfunktionen.h"
#include <map>

///////////////////////////////////////////////////////////////////////////

using namespace std;

namespace EZ
{

///////////////////////////////////////////////////////////////////////////
/// Implementation von KonfigurationsfunktionenKette
///
/// @see sKonfigurationsfunktionenKette
/// @ingroup    Pfad
//-------------------------------------------------------------------
class KonfigurationsfunktionenKetteTransformation;
class KonfigurationsfunktionenKette : VERWENDE_SCHNITTSTELLE(sKonfigurationsfunktionenKette)
{
	SCHNITTSTELLENIMPLEMENTATION(KonfigurationsfunktionenKette);
	friend class KonfigurationsfunktionenKetteTransformation;
protected:
	unsigned short m_anzahlGlieder;
	double m_definitionsminimum;
	double m_definitionsmaximum;
	map<int, sKonfigurationsfunktionen::Zeiger> m_konfigurationsfunktionen;
	map<int, sUnaereReelleFunktion::Zeiger> m_einknickwinkelfunktion;
	bool aktualisiereRaender();
public:
	/* --- Konstruktoren/Destruktoren --- */
	KonfigurationsfunktionenKette(unsigned short _anzahlGlieder = 0);
	virtual ~KonfigurationsfunktionenKette() {};


	/* --- Implementation von sKonfigurationsfunktionenKette --- */

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Ausrichtung
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger ausrichtungFunktion(unsigned short glied) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den ersten Lenkwinkel
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied
	/// @result				die entsprechende Funktion
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger lenkwinkelFunktion(unsigned short glied) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die die Position
	/// des gewünschten Gliedes beschreibt.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @result				die entsprechende Funktion.
	//--------------------------------------------------------------------
	virtual sUnaerePlanareFunktion::Zeiger positionFunktion(unsigned short glied) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeiger auf die Funktion zurück, die den Einknickwinkel
	/// in der gewünschten Kupplung beschreibt.
	/// @param kupplung		die gewünschte Kupplung.
	/// @result				die entsprechende Funktion.
	//--------------------------------------------------------------------
	virtual sUnaereReelleFunktion::Zeiger einknickwinkelFunktion(unsigned short kupplung) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Ausrichtung des gewünschten Gliedes am gewünschten
	/// Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double ausrichtung( unsigned short glied, double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den ersten Lenkwinkel des gewünschten Gliedes am gewünschten
	/// Definitionswert zurück.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkel ( unsigned short glied, double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Position des gewünschten Gliedes am gewünschten
	/// Definitionswert zurück.
	/// @param d			der Definitionswert.
	/// @param glied		das gewünschte Fahrzeugglied.
	/// @result				die entsprechende Position
	///						(Punkt2D(NaN(),NaN()), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual Punkt2D position (  unsigned short glied, double d) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Einknickwinkel in der gewünschten Kupplung am gewünschten
	/// Definitionswert zurück.
	/// @param kupplung		die gewünschte Kupplung  [0..anzahlGlieder()-2]
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Einknickwinkel
	///						(NaN(), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual double einknickwinkel ( unsigned short kupplung, double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Ausrichtung des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied.  [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeAusrichtungFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für den ersten Lenkwinkel des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied. [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelFunktion( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für die Position des gewünschten Gliedes.
	/// @param glied		das gewünschte Fahrzeugglied. [0..anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzePositionFunktion( unsigned short glied, sUnaerePlanareFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion für den Einknickwinkel in der gewünschten Kupplung.
	/// @param kupplung		die gewünschte Kupplung. [0..anzahlGlieder()-2]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeEinknickwinkelFunktion( unsigned short kupplung, sUnaereReelleFunktion::Zeiger funktion );

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Anzahl der Fahrzeugglieder zurück.
	/// @result				die Anzahl der Fahrzeugglieder
	//--------------------------------------------------------------------
	virtual unsigned short anzahlGlieder () const;

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
	Punkt2D operator() (double d);
};

};
#endif // EZ_SKONFIGURATIONSFUNKTIONENKETTE_H
