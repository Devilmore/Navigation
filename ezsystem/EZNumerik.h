#ifndef NUMERIK_H
#define NUMERIK_H

/////////////////////////////////////////////////////////////////////////////

#include "EZStandard.h"
#include "EZPunkt2D.h"

namespace EZ
{

/////////////////////////////////////////////////////////////////////////////

class Numerik
{
    
protected:


	
public:
	//////////////////////////////////////////////////////////////////////
	/// Berechnet den absoluten Winkel eines Vektors
	/// @param mittelpunkt	Startpunkt des Vektors
	/// @param punkt		Endpunkt des Vektors
	/// @result				der gesuchte Winkel im Bogenmaß
	//--------------------------------------------------------------------
	static double winkelZuPunkt(Punkt2D punkt, Punkt2D mittelpunkt);
	
	//////////////////////////////////////////////////////////////////////
	/// Projeziert einen Punkt auf eine Gerade. Rundet die Länge der Gerade
	/// danach auf einen Rundungsfaktor (falls dieser != 0)
	/// @param punkt			der zu projezierende Punkt
	/// @param richtungsvektor	ein Richtungsvektor der Gerade
	/// @param stuetzvektor		ein Stützvektor der Gerade
	/// @param rundungsfaktor	der Faktor auf dessen Vielfache der Abstand
	///							zwischen Stützvektor und dem Ergebnis ge-
	///							rundet werden soll
	/// @result					der gesuchte Punkt
	//--------------------------------------------------------------------	
	static Punkt2D projezierePunktAufGerade(Punkt2D punkt, Punkt2D richtungsvektor, Punkt2D stuetzvektor, double rundungsfaktor = 0.0);
	
	//////////////////////////////////////////////////////////////////////
	/// Normiert einen Winkel im Bogenmaß in das Intervall [0..2*PI[
	/// @param winkel		der zu normierende Winkel im Bogenmaß
	/// @result				der gesuchte Winkel im Bogenmaß
	//--------------------------------------------------------------------
	static double winkelIn2PI(double winkel);

	//////////////////////////////////////////////////////////////////////
	/// Rundet einen Wert auf das nächste vielfache von Rundungsfaktor.
	/// @param wert				der zu rundende Wert.
	/// @param rundungsfaktor	der Faktor auf dessen Vielfache gerundet
	///							werden soll. Keine Rundung, falls == 0.0
	/// @result					der gerundete Wert.
	//--------------------------------------------------------------------
	static double runde(double wert, double rundungsfaktor);

	//////////////////////////////////////////////////////////////////////
	/// Rotiert einen Punkt um einen Mittelpunkt und einen Winkel.
	/// @param punkt			der zu drehende Punkt.
	/// @param mittelpunkt		der Mittelpunkt der Rotation
	/// @param winkel			der Winkel der Rotation im Bogenmaß
	/// @result					der gesuchte Punkt
	//--------------------------------------------------------------------
	static Punkt2D rotiere(Punkt2D punkt, Punkt2D mittelpunkt, double winkel);
   
};

/////////////////////////////////////////////////////////////////////////////
};
#endif
