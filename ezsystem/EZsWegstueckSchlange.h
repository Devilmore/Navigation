#ifndef EZ_SWEGSTUECKSCHLANGE_H
#define EZ_SWEGSTUECKSCHLANGE_H

///////////////////////////////////////////////////////////////////////////
#include "EZStandard.h"
#include "EZsWegstueck.h"
#include "EZPunkt2D.h"
#include "EZBasiszeichenflaeche.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ {


	class sWegstueckSchlange:VERWENDE_SCHNITTSTELLE(sUnaerePlanareFunktion)
	{
		DEKLARIERE_SCHNITTSTELLE(sWegstueckSchlange)

	public:
		//////////////////////////////////////////////////////////////////////
		/// Gibt den Zeiger auf das letzte Wegstück zurück.
		/// @result				der Zeiger auf das letzte Wegstück.
		//--------------------------------------------------------------------
		virtual sWegstueck::Zeiger	letztesWegstueck()=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Zeiger auf das erste Wegstück zurück.
		/// @result				der Zeiger auf das erste Wegstück.
		//--------------------------------------------------------------------
		virtual sWegstueck::Zeiger	erstesWegstueck	()=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Zeiger auf das n-te Wegstück zurück.
		/// @param	n			Nummer des Wegstückes, das zurück gegeben werden soll.
		/// @result				der Zeiger auf das n-te Wegstück.
		//--------------------------------------------------------------------
		virtual sWegstueck::Zeiger	wegstueck(int n)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Zeiger auf das Wegstück zurück, dass dem Definitionswert
		/// d entspricht.
		/// @param	d			der Definitionswert.
		/// @result				der Zeiger auf das entsprechende Wegstück.
		//--------------------------------------------------------------------
		virtual sWegstueck::Zeiger	wegstueck(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Anzahl der Wegstücke zurück.
		/// @result				die Anzahl der Wegstücke.
		//--------------------------------------------------------------------
		virtual int					anzahl()=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Position an der Stelle zurück, die dem Definitionswert d
		/// entspricht.
		/// @param	d			der Definitionswert.
		/// @result				die entsprechende Position.
		//--------------------------------------------------------------------
		virtual Punkt2D				position(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Ausrichtung an der Stelle zurück, die dem Definitionswert d
		/// entspricht.
		/// @param	d			der Definitionswert.
		/// @result				die entsprechende Ausrichtung.
		//--------------------------------------------------------------------
		virtual double				ausrichtung(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Endausrichtung des Wegstückes zurück, das dem Definitions-
		/// Wert d enspricht.
		/// @param	d			der Definitionswert.
		/// @result				die Endausrichtung des entsprechenden Wegstücks.
		//--------------------------------------------------------------------
		virtual double				endausrichtung(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Endausrichtung des n-ten Wegstückes zurück.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				die Endausrichtung des entsprechende Wegstückes.
		//--------------------------------------------------------------------
		virtual double				endausrichtung(int nummer)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Endausrichtung des letzten Wegstückes zurück.
		/// @result				die Endausrichtung des letzten Wegstückes.
		//--------------------------------------------------------------------
		virtual double				endausrichtung()=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Startausrichtung des Wegstückes zurück, das dem Definitions-
		/// Wert d enspricht.
		/// @param	d			der Definitionswert.
		/// @result				die Startausrichtung des entsprechenden Wegstücks.
		//--------------------------------------------------------------------
		virtual double				startausrichtung(double definionswert)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Startausrichtung des n-ten Wegstückes zurück.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				die Startausrichtung des entsprechende Wegstückes.
		//--------------------------------------------------------------------
		virtual double				startausrichtung(int nummer)=0;
		
		//////////////////////////////////////////////////////////////////////
		/// Fügt ein Wegstück am Ende der Schlange hinzu.
		/// @param	weg			das hinzuzufügendene Wegstück.
		/// @result				true gdw. erfolgreich.
		//--------------------------------------------------------------------
		virtual bool				fuegeWegstueckHinzu(sWegstueck::Zeiger weg)=0;

		//////////////////////////////////////////////////////////////////////
		/// Fügt eine andere Wegstückschlange am Ende der Schlange hinzu.
		/// @param	weg			die hinzuzufügendene Wegstückschlange.
		/// @result				true gdw. erfolgreich.
		//--------------------------------------------------------------------
		virtual bool				fuegeWegstueckSchlangeHinzu(sWegstueckSchlange::Zeiger schlange)=0;

		//////////////////////////////////////////////////////////////////////
		/// Entfernt n Wegstücke vorne in der Schlange. 
		/// Entfernt alle Wegstücke, falls n > anzahl().
		/// @param	n			Anzahl der Wegstücke, die entfernt werden sollen.
		///						Standard: 1
		/// @result				true gdw. erfolgreich.
		//--------------------------------------------------------------------
		virtual bool				entferneWegstueckVorne(int n = 1)=0;

		//////////////////////////////////////////////////////////////////////
		/// Entfernt n Wegstücke hinten in der Schlange. 
		/// Entfernt alle Wegstücke, falls n > anzahl().
		/// @param	n			Anzahl der Wegstücke, die entfernt werden sollen.
		///						Standard: 1
		/// @result				true gdw. erfolgreich.
		//--------------------------------------------------------------------
		virtual bool				entferneWegstueckHinten(int n = 1)=0;

		//////////////////////////////////////////////////////////////////////
		/// Entfernt alle Wegstücke in der Schlange. 
		/// @result				true gdw. erfolgreich.
		//--------------------------------------------------------------------
		virtual bool				entferneWegstuecke()=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt an, ob das Wegstück, das dem Definitionswert d enspricht,
		/// rückwärts verläuft.
		/// @param	d			der Definitionswert.
		/// @result				true, wenn das entsprechende Wegstück rückwaerts
		///						verläuft.
		//--------------------------------------------------------------------
		virtual bool				rueckwaerts(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt an, ob das n-ten Wegstückes rückwärts verläuft.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				true, wenn das entsprechende Wegstück rückwaerts
		///						verläuft.
		//--------------------------------------------------------------------
		virtual bool				rueckwaerts(int n)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt an, ob das Wegstück, das dem Definitionswert d enspricht,
		/// eine Rechtskurve beschreibt.
		/// @param	d			der Definitionswert.
		/// @result				true, wenn das entsprechende Wegstück eine
		///						Rechtskurve beschreibt.
		//--------------------------------------------------------------------
		virtual bool				rechtsfahrt(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt an, ob das n-ten Wegstückes eine Rechtskurve beschreibt.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				true, wenn das entsprechende Wegstück eine
		///						Rechtskurve beschreibt.
		//--------------------------------------------------------------------
		virtual bool				rechtsfahrt(int n)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt an, ob das Wegstück, das dem Definitionswert d enspricht,
		/// einen Kreisbogenfahrt beschreibt.
		/// @param	d			der Definitionswert.
		/// @result				true, wenn das entsprechende Wegstück eine
		///						Kreisbogenfahrt beschreibt.
		//--------------------------------------------------------------------
		virtual bool				kreis(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt an, ob das n-ten Wegstückes einen Kreisbogenfahrt beschreibt.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				true, wenn das entsprechende Wegstück eine
		///						Kreisbogenfahrt beschreibt.
		//--------------------------------------------------------------------
		virtual bool				kreis(int n)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Radius des Wegstücks, das dem Definitionswert d enspricht,
		/// zurück.
		/// @param	d			der Definitionswert.
		/// @result				der Radius des entsprechenden Wegstücks
		//--------------------------------------------------------------------
		virtual double				radius(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Radius des n-ten Wegstückes zurück.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				der Radius des entsprechenden Wegstücks
		//--------------------------------------------------------------------
		virtual double				radius(int n)=0;
		
		//////////////////////////////////////////////////////////////////////
		/// Gibt die Länge des Wegstücks, das dem Definitionswert d enspricht,
		/// zurück.
		/// @param	d			der Definitionswert.
		/// @result				die Länge des entsprechenden Wegstücks
		//--------------------------------------------------------------------
		virtual double				laenge(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt die Länge des n-ten Wegstückes zurück.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				die Länge des entsprechenden Wegstücks
		//--------------------------------------------------------------------
		virtual double				laenge(int n)=0;
		
		//////////////////////////////////////////////////////////////////////
		/// Gibt den Kurvenwinkel des Wegstücks, das dem Definitionswert d enspricht,
		/// zurück.
		/// @param	d			der Definitionswert.
		/// @result				der Winkel des entsprechenden Wegstücks
		//--------------------------------------------------------------------
		virtual double				winkel(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Kurvenwinkel des n-ten Wegstückes zurück.
		/// @param	n			die Nummer des Wegstückes.
		/// @result				der Winkel des entsprechenden Wegstücks
		//--------------------------------------------------------------------
		virtual double				winkel(int n)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den kleinsten Definitionswert des Wegstücks, das dem 
		/// Definitionswert d enspricht, zurück.
		/// @param	d			der Definitionswert.
		/// @result				der Startdefinitionswert des entsprechenden
		///						Wegstücks.
		//--------------------------------------------------------------------
		virtual double				startDefinitionswert(double d)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den kleinsten Definitionswert des n-ten Wegstücks zurück.
		/// @param	n			die Nummer des Wegstücks.
		/// @result				der Startdefinitionswert des entsprechenden
		///						Wegstücks.
		//--------------------------------------------------------------------
		virtual double				startDefinitionswert(int n)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den größten Definitionswert des Wegstücks, das dem 
		/// Definitionswert d enspricht, zurück.
		/// @param	d			der Definitionswert.
		/// @result				der Enddefinitionswert des entsprechenden
		///						Wegstücks.
		//--------------------------------------------------------------------
		virtual double				endDefintionswert(double defintionswert)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den größten Definitionswert des n-ten Wegstücks zurück.
		/// @param	n			die Nummer des Wegstücks.
		/// @result				der Enddefinitionswert des entsprechenden
		///						Wegstücks.
		//--------------------------------------------------------------------
		virtual double				endDefintionswert(int nummer)=0;
		

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Startpunkt des Wegstücks, das dem Definitionswert d 
		/// enspricht, zurück.
		/// @param	d			der Definitionswert.
		/// @result				Startpunkt des entsprechenden Wegstücks.
		//--------------------------------------------------------------------
		virtual Punkt2D				startpunkt(double definitionswert)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Startpunkt des n-ten Wegstücks zurück.
		/// @param	n			die Nummer des Wegstücks. Standard: 0.
		/// @result				der Startpunkt des entsprechenden Wegstücks.
		//--------------------------------------------------------------------
		virtual Punkt2D				startpunkt(int nummer=0)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Endpunkt des Wegstücks, das dem Definitionswert d 
		/// enspricht, zurück.
		/// @param	d			der Definitionswert.
		/// @result				Endpunkt des entsprechenden Wegstücks.
		//--------------------------------------------------------------------
		virtual Punkt2D				endpunkt(double defintionswert)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Endpunkt des n-ten Wegstücks zurück.
		/// @param	n			die Nummer des Wegstücks.
		/// @result				der Endpunkt des entsprechenden Wegstücks.
		//--------------------------------------------------------------------
		virtual Punkt2D				endpunkt(int nummer)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt den Endpunkt des letzten Wegstücks zurück.
		/// @result				der Endpunkt des letzten Wegstücks.
		//--------------------------------------------------------------------
		virtual Punkt2D				endpunkt()=0;

		//////////////////////////////////////////////////////////////////////
		/// Zeichnet die enthaltenen Wegstücke auf eine Zeichenfläche.
		/// @param zeichenflaeche	die Zeichenfläche.
		//--------------------------------------------------------------------
		virtual void				zeichne(sZeichenflaeche::Zeiger zeichenflaeche)=0;

		//////////////////////////////////////////////////////////////////////
		/// Gibt an, ob die Wegschlange leer ist.
		/// @result true gdw. die Schlange leer ist.
		//--------------------------------------------------------------------
		virtual bool				leer()=0;

		//////////////////////////////////////////////////////////////////////
		/// Setzt die Startlage der Wegschlange und dreht und verschiebt
		///	die enthaltenen Wegstücke entsprechend. Dabei wird für die Rückwärtsfahrt
		/// als Bezugspunkt der Mittelpunkt der Anhängerachse und bei der Vorwärtsfahrt
		/// der Mittelpunkt der Hinterachse des Zugfahrzeuges gewählt.
		/// @param pos		die neue Startposition
		/// @param aus		die neue Startausrichtung
		/// @result true gdw. erfolgreich.
		//--------------------------------------------------------------------
		virtual bool				setzeStartlage(Punkt2D pos, double aus)=0;
	};


};
#endif // EZ_SWEGSTUECKSCHLANGE_H