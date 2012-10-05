#ifndef EZ_AGGREGIERTERPFAD_H
#define EZ_AGGREGIERTERPFAD_H

///////////////////////////////////////////////////////////////////////////

#include "EZsZeitVarianterPfad.h"
#include <list>

///////////////////////////////////////////////////////////////////////////

namespace EZ {

	//////////////////////////////////////////////////////////////////////
	/// Implementierung von Pfadstueck.
	/// @see sZeitVarianterPfad.
	///
	/// @ingroup    Pfad
	//--------------------------------------------------------------------
	class AggregierterPfadTransformation;
	class AggregierterPfad : VERWENDE_SCHNITTSTELLE(sZeitVarianterPfad)
	{

		SCHNITTSTELLENIMPLEMENTATION(AggregierterPfad);
		friend class AggregierterPfadTransformation;
	protected:
		double m_definitionsminimum;
		double m_definitionsmaximum;
		typedef std::list<sZeitVarianterPfad::Zeiger> Pfadliste;
		Pfadliste m_pfade;
		sZeitVarianterPfad* findePfad( double definitionswert ) const;
		//bool m_initialisiert;

	public:
		/* --- Konstruktoren/Destruktoren --- */
		/////////////////////////////////////////////////////////////////////////////////////////////////
		/// Konstruktor.
		//-----------------------------------------------------------------------------------------------
		AggregierterPfad();

		/////////////////////////////////////////////////////////////////////////////////////////////////
		/// Destruktor.
		//-----------------------------------------------------------------------------------------------
		virtual ~AggregierterPfad() {}

		//////////////////////////////////////////////////////////////////////
		/// F�gt ein Pfadst�ck hinten an.
		/// @param pfad das anzuf�gende Pfadst�ck.
		/// @result true bei Erfolg.
		//--------------------------------------------------------------------
		bool fuegePfadHinzu(sZeitVarianterPfad::Zeiger pfad);

		//////////////////////////////////////////////////////////////////////
		/// Entfernt das letzte Pfadst�ck, falls eines vorhanden ist.
		/// @result true gdw. nach Ausf�hrung noch Pfade enthalten sind.
		//--------------------------------------------------------------------
		bool entfernePfad();

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
		virtual unsigned short anzahlGlieder ( ) const;

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
		virtual bool rueckwaerts ( double d) const;

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

		/* --- Implementation von sPlanareUnaereFunktion --- */
		//////////////////////////////////////////////////////////////////////
		///	Liefert das Definitionsminimum
		/// @result 0.0
		//--------------------------------------------------------------------
		double definitionsminimum() {return m_definitionsminimum;}

		//////////////////////////////////////////////////////////////////////
		///	Liefert das Definitionsmaximum
		/// @result weglaenge()
		//--------------------------------------------------------------------
		double definitionsmaximum() {return m_definitionsmaximum;}

		//////////////////////////////////////////////////////////////////////
		///	Liefert die Sollposition an der Definitionsstelle d.
		/// @param d	der Definitionswert
		/// @result		die Sollposition.
		//--------------------------------------------------------------------
		Punkt2D operator() (double d);

		size_t anzahlPfade(){return m_pfade.size();}
		sZeitInvarianterPfad::Zeiger pfad(size_t nummer);
	};
};
#endif
