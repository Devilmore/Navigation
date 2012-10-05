#ifndef EZ_PFADSTUECK_H
#define EZ_PFADSTUECK_H

///////////////////////////////////////////////////////////////////////////

#include "EZsZeitVarianterPfad.h"
#include "EZsFahrzeugbeschreibungskette.h"
#include "EZsKonfigurationsfunktionenKette.h"
#include "EZsSteuerfunktionenKette.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ {

//////////////////////////////////////////////////////////////////////
/// Implementierung von Pfadstueck.
/// @see sZeitVarianterPfad.
///
/// @ingroup    Pfad
//--------------------------------------------------------------------
class PfadstueckTransformation;
class Pfadstueck : VERWENDE_SCHNITTSTELLE(sZeitVarianterPfad)
{
    SCHNITTSTELLENIMPLEMENTATION(Pfadstueck);
	friend class PfadstueckTransformation;
protected:
	sFahrzeugbeschreibungskette::Zeiger m_fahrzeugbeschreibungen;
	unsigned short m_anzahlGlieder;
	sKonfigurationsfunktionenKette::Zeiger m_konfigurationsfunktionen;
	sSteuerfunktionenKette::Zeiger m_steuerfunktionen;
	bool m_rueckwaerts;
	sUnaereReelleFunktion::Zeiger m_zeitfunktion;
	double m_definitionsminimumInnen;
	double m_definitionsmaximumInnen;
	bool aktualisiereRaender();
	bool m_initialisiert;
	double m_definitionsminimumAussen;
	double definitionsOffset() const {return m_definitionsminimumAussen-m_definitionsminimumInnen;}
	Pfadstueck();
	void setzeAttribute(bool _rueckwaerts, sFahrzeugbeschreibungskette::Zeiger _fahrzeugbeschreibung, sKonfigurationsfunktionenKette::Zeiger _konfigurationsfunktionen = NULL, sSteuerfunktionenKette::Zeiger _steuerfunktionen = NULL, sUnaereReelleFunktion::Zeiger _zeitfunktion = NULL);

public:
	/* --- Konstruktoren/Destruktoren --- */

	Pfadstueck(bool _rueckwaerts, sFahrzeugbeschreibungskette::Zeiger _fahrzeugbeschreibung, sUnaereReelleFunktion::Zeiger _zeitfunktion=NULL);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/// Destruktor.
	//-----------------------------------------------------------------------------------------------
	virtual ~Pfadstueck() {}
	


	/* --- Setter-Methoden f�r sZeitInvarianterPfad --- */
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion f�r die Ausrichtung des gew�nschten Fahrzeuggliedes.
	/// @param glied		die Nummer des Fahrzeuggliedes. [0,anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeAusrichtungFunktion ( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion);

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion f�r die Position des gew�nschten Fahrzeuggliedes.
	/// @param glied		die Nummer des Fahrzeuggliedes. [0,anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzePositionFunktion ( unsigned short glied, sUnaerePlanareFunktion::Zeiger funktion);

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion f�r den ersten Lenkwinkel des gew�nschten Fahrzeuggliedes.
	/// @param glied		die Nummer des Fahrzeuggliedes. [0,anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelFunktion ( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion);

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion f�r die gew�nschte Kupplung.
	/// @param kupplung		die Nummer der Kupplung [0,anzahlGlieder()-2]
	/// @param funktion		die neue Funktion
	/// @result				true gdw. erfolgreich.
	//--------------------------------------------------------------------
	virtual bool setzeEinknickwinkelFunktion( unsigned short kupplung, sUnaereReelleFunktion::Zeiger funktion);

	/* --- Implementation von sZeitInvarianterPfad --- */
	//////////////////////////////////////////////////////////////////////
	/// Verschiebt alle Funktionen so auf der x-Achse, dass die Definition
	/// bei d beginnt.
	/// @param d Das neue Minimum des Definitionsbereichs.
	//--------------------------------------------------------------------
	void setzeDefinitionsminimum(double d);

	//////////////////////////////////////////////////////////////////////
	/// Zeichnet den Verlauf der Position auf die angebenene Zeichenflaeche.
	/// @param zeichenflaeche Die Zeichenflaeche
	//--------------------------------------------------------------------
	void zeichne(sZeichenflaeche::Zeiger zeichenflaeche);

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Anzahl der Fahrzeugglieder zur�ck.
	/// @result				die Anzahl der Fahrzeugglieder
	//--------------------------------------------------------------------
	virtual unsigned short anzahlGlieder ( ) const {return m_anzahlGlieder;}

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Ausrichtung des gew�nschten Fahrzeuggliedes am
	/// gew�nschten Definitionswert zur�ck.
	/// @param glied		die Nummer des Fahrzeuggliedes. [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Ausrichtung
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual double ausrichtung		( unsigned short glied,		double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Position des gew�nschten Fahrzeuggliedes am
	/// gew�nschten Definitionswert zur�ck.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Position 
	///						(Punkt2D(NaN(),NaN()), falls nicht definitiert)
	//--------------------------------------------------------------------
	virtual Punkt2D position		( unsigned short glied,		double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den ersten Lenkwinkel des gew�nschten Fahrzeuggliedes am
	/// gew�nschten Definitionswert zur�ck.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Lenkwinkel
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual	double lenkwinkel	( unsigned short glied,		double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Einknickwinkel der gew�nschten Kupplung am
	/// gew�nschten Definitionswert zur�ck.
	/// @param kupplung		die Nummer der Kupplung [0,anzahlGlieder()-2]
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Einknickwinkel
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual	double einknickwinkel	( unsigned short kupplung,	double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Fahrtrichtung am gew�nschten Definitionswert zur�ck.
	/// @param d			der Definitionswert.
	/// @result				true gdw. die Fahrtrichtung rueckwaerts ist.
	//--------------------------------------------------------------------
	virtual bool rueckwaerts ( double /*d*/) const {return m_rueckwaerts;}

	/* --- Settermethoden f�r sZeitVarianterPfad --- */
	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion f�r die �nderung des ersten Lenkwinkels des 
	/// gew�nschten Fahrzeuggliedes.
	/// @param glied		die Nummer des Fahrzeuggliedes. [0,anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual bool setzeLenkwinkelAenderungFunktion ( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion);

	virtual void setzeZeitfunktion (sUnaereReelleFunktion::Zeiger _zeitfunktion);

	/* --- Implementation von sZeitVarianterPfad --- */
	//////////////////////////////////////////////////////////////////////
	/// Gibt den Zeitpunkt der einem Definitionswert zugeordnet ist
	/// zur�ck.
	/// @param d			der Definitionswert.
	/// @result				der entsprechende Zeitpunkt.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double zeit ( double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Startzeitpunkt f�r diesen Pfad zur�ck.
	/// @result				der Startzeitpunkt f�r diesen Pfad.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double startzeit ( ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Endzeitpunkt f�r diesen Pfad zur�ck.
	/// @result				der Endzeitpunkt f�r diesen Pfad.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double endzeit ( ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt den Definitionswert der einem Zeitpunkt zugeordnet ist
	/// zur�ck.
	/// @param zeit			der Zeitpunkt.
	/// @result				der entsprechende Definitionswert.
	///						( NaN(), falls nicht defininiert )
	//--------------------------------------------------------------------
	virtual double definitionswert ( double zeit ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Geschwindigkeit des gew�nschten Fahrzeuggliedes am
	/// gew�nschten Definitionswert zur�ck.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Geschwindigkeit
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual double geschwindigkeit ( unsigned short glied, double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Gibt die Aenderung des ersten Lenkwinkels des gew�nschten 
	/// Fahrzeuggliedes am gew�nschten Definitionswert zur�ck.
	/// @param glied		die Nummer des Fahrzeuggliedes [0,anzahlGlieder()-1]
	/// @param d			der Definitionswert.
	/// @result				die entsprechende Lenkwinkel�nderung
	//						(NaN(), falls nicht definiert)
	//--------------------------------------------------------------------
	virtual double lenkwinkelAenderung ( unsigned short glied, double d ) const;

	//////////////////////////////////////////////////////////////////////
	/// Setzt die Funktion f�r die Geschwindigkeit des gew�nschten Fahrzeuggliedes.
	/// @param glied		die Nummer des Fahrzeuggliedes. [0,anzahlGlieder()-1]
	/// @param funktion		die neue Funktion.
	/// @result				true gdw. erfolgreich
	//--------------------------------------------------------------------
	virtual double setzeGeschwindigkeitFunktion	( unsigned short glied, sUnaereReelleFunktion::Zeiger funktion);

	/* --- Implementation von sPlanareUnaereFunktion --- */
	//////////////////////////////////////////////////////////////////////
	///	Liefert das Definitionsminimum
	/// @result 0.0
	//--------------------------------------------------------------------
	double definitionsminimum() {return m_definitionsminimumInnen+definitionsOffset();}

	//////////////////////////////////////////////////////////////////////
	///	Liefert das Definitionsmaximum
	/// @result weglaenge()
	//--------------------------------------------------------------------
	double definitionsmaximum() {return m_definitionsmaximumInnen+definitionsOffset();}

	//////////////////////////////////////////////////////////////////////
	///	Liefert die Sollposition an der Definitionsstelle d.
	/// @param d	der Definitionswert
	/// @result		die Sollposition.
	//--------------------------------------------------------------------
	Punkt2D operator() (double d);
};


};
#endif // EZ_PFADSTUECK_H
