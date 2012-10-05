#ifndef EZ_WINKELWRAPPER_H
#define EZ_WINKELWRAPPER_H
#include "EZPunkt2D.h"

///////////////////////////////////////////////////////////////////////////

using namespace EZ;
//////////////////////////////////////////////////////////////////////
/// Implementierung von Winkel.
/// @see sWinkel.
///
/// @ingroup    Pfad
//--------------------------------------------------------------------

class WinkelWrapper
{

protected:
    double m_bogenmass;


public:
	
    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destruktor.
    //-----------------------------------------------------------------------------------------------
    virtual ~WinkelWrapper();

	WinkelWrapper();
	
	WinkelWrapper(const WinkelWrapper& winkel);

	WinkelWrapper(double bogenmass);
	WinkelWrapper(const Punkt2D vektor);

	double bogenmass() const;
	double gradmass() const;
	void setzeBogenmass(double wert);
	void setzeGradmass(double wert);
	Punkt2D einheitsvektor() const;
	WinkelWrapper senkrechteLinks() const;
	WinkelWrapper senkrechteRechts() const;

	bool operator< (const WinkelWrapper&) const;
	bool operator> (const WinkelWrapper&) const;
	bool operator>= (const WinkelWrapper&) const;
	bool operator<= (const WinkelWrapper&) const;
	bool operator== (const WinkelWrapper&) const;
	bool operator!= (const WinkelWrapper&) const;

	WinkelWrapper& operator = (const WinkelWrapper& winkel);
	WinkelWrapper operator+ (const WinkelWrapper& winkel) const;
	WinkelWrapper operator- (const WinkelWrapper& winkel) const;
	WinkelWrapper& operator+= (const WinkelWrapper& winkel);
	WinkelWrapper& operator-= (const WinkelWrapper& winkel);
	WinkelWrapper operator- () const;
	WinkelWrapper operator+ () const;


	WinkelWrapper operator+ (double bogenmass) const;
	WinkelWrapper operator- (double bogenmass) const;
	WinkelWrapper& operator= (double bogenmass);
	WinkelWrapper& operator+= (double bogenmass);
	WinkelWrapper& operator-= (double bogenmass);


};


#endif // EZ_WINKELWRAPPER_H