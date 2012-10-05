
#include "EZNumerik.h"

//////////////////////////////////////////////////////////////////////

#include "EZStandard.h"

namespace EZ
{

	double Numerik::winkelZuPunkt(Punkt2D punkt, Punkt2D mittelpunkt)
	{
		Punkt2D p1(1,0);
		Punkt2D p2 = (punkt-mittelpunkt).normalisiere();
		if (punkt.y<mittelpunkt.y)
			return 2*PI - acos(p1.punkt(p2));
		else
			return acos(p1.punkt(p2));
	}

	double Numerik::winkelIn2PI( double winkel )
	{
		winkel = fmod(winkel,2*PI);
		if (winkel<0)
			winkel += 2*PI;
		return winkel;
	}

	EZ::Punkt2D Numerik::projezierePunktAufGerade( Punkt2D punkt, Punkt2D richtungsvektor, Punkt2D stuetzvektor, double rundungsfaktor /*= 0.0*/ )
	{
		richtungsvektor= richtungsvektor.normalisiere();
		double lamda = runde(richtungsvektor.punkt(punkt-stuetzvektor),rundungsfaktor);
		return richtungsvektor * lamda + stuetzvektor;
	}

	double Numerik::runde( double wert, double rundungsfaktor )
	{
		if (rundungsfaktor==0.0)
			return wert;
		else
			return floor(wert/rundungsfaktor+0.5)*rundungsfaktor;
	}

	EZ::Punkt2D Numerik::rotiere( Punkt2D punkt, Punkt2D mittelpunkt, double winkel )
	{
		double laenge = (punkt-mittelpunkt).laenge();
		double alterWinkel = winkelZuPunkt(punkt,mittelpunkt);
		return Punkt2D(cos(alterWinkel+winkel),sin(alterWinkel+winkel))*laenge+mittelpunkt;
	}
	//////////////////////////////////////////////////////////////////////
}