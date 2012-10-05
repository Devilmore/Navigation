#ifndef EZ_PUNKT2D_H
#define EZ_PUNKT2D_H

//////////////////////////////////////////////////////////////////////

#include <math.h>

//////////////////////////////////////////////////////////////////////

namespace EZ
{

//////////////////////////////////////////////////////////////////////
/// Beschreibt eine Punkt im 2D Raum.
///
/// @ingroup    Geometrie
//--------------------------------------------------------------------

class Punkt2D
{
public:
    /// x Koordinate.
    double  x;
    /// y Koordinate.
    double  y;

public:

    //////////////////////////////////////////////////////////////////////
    /// Konstruktor mit Angabe der einzelnen Koordinaten.
    /// @param  x:  Die x Koordinate.
    /// @param  y:  Die y Koordinate.
    //--------------------------------------------------------------------
    explicit Punkt2D(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
    }

    //////////////////////////////////////////////////////////////////////
    /// Kopier-Konstruktor.
    /// @param  punkt:  Der zu kopierende 2D-Punkt.
    //--------------------------------------------------------------------
    Punkt2D(const Punkt2D& punkt)
    {
        x   = punkt.x;
        y   = punkt.y;
    }

    //////////////////////////////////////////////////////////////////////
    /// Setzt die Koordinaten.
    /// @param  x:  Die x Koordinate.
    /// @param  y:  Die y Koordinate.
    //--------------------------------------------------------------------
    void setze(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    //////////////////////////////////////////////////////////////////////
    /// Zuweisungsoperator.
    /// @param  punkt:  Punkt dessen Werte übernommen werden.
    /// @result *this.
    //--------------------------------------------------------------------
    Punkt2D& operator = (const Punkt2D& punkt)
    {
        x   = punkt.x;
        y   = punkt.y;
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    /// Zuweisungsoperator mit Vektoraddition.
    /// @param  punkt:  Punkt dessen Werte addiert werden.
    /// @result *this.
    //--------------------------------------------------------------------
    Punkt2D& operator += (const Punkt2D& punkt)
    {
        x   += punkt.x;
        y   += punkt.y;
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    /// Zuweisungsoperator mit Vektorsubtraktion.
    /// @param  punkt:  Punkt dessen Werte subtrahiert werden.
    /// @result *this.
    //--------------------------------------------------------------------
    Punkt2D& operator -= (const Punkt2D& punkt)
    {
        x   -= punkt.x;
        y   -= punkt.y;
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    /// Zuweisungsoperator mit Skalarmultiplikation.
    /// @param  skalar: Der Skalar.
    /// @result *this.
    //--------------------------------------------------------------------
    Punkt2D& operator *= (double skalar)
    {
        x   *= skalar;
        y   *= skalar;
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    /// Zuweisungsoperator mit Skalardivision.
    /// @param  skalar: Der Skalar.
    /// @result *this.
    //--------------------------------------------------------------------
    Punkt2D& operator /= (double skalar)
    {
        ASSERT(skalar != 0);
        x   /= skalar;
        y   /= skalar;
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    /// Identität.
    /// @result *this.
    //--------------------------------------------------------------------
    Punkt2D operator + () const
    {
        return Punkt2D(x, y);
    }

    //////////////////////////////////////////////////////////////////////
    /// Negation.
    /// @result Am Ursprung gespiegelter Punkt.
    //--------------------------------------------------------------------
    Punkt2D operator - () const
    {
        return Punkt2D(-x, -y);
    }

    //////////////////////////////////////////////////////////////////////
    /// Vektoraddition.
    /// @param  punkt:  Zweiter Operand.
    /// @result Vektorsumme.
    //--------------------------------------------------------------------
    Punkt2D operator + (const Punkt2D& punkt) const
    {
        return Punkt2D(x + punkt.x, y + punkt.y);
    }

    //////////////////////////////////////////////////////////////////////
    /// Vektorsubtraktion.
    /// @param  punkt:  Zweiter Operand.
    /// @result Vektordifferenz.
    //--------------------------------------------------------------------
    Punkt2D operator - (const Punkt2D& punkt) const
    {
        return Punkt2D(x - punkt.x, y - punkt.y);
    }

    //////////////////////////////////////////////////////////////////////
    /// Skalarprodukt.
    /// @param  skalar: Der Skalar.
    /// @result Skalierter Punkt.
    //--------------------------------------------------------------------
    Punkt2D operator * (double skalar) const
    {
        return Punkt2D(x * skalar, y * skalar);
    }

    //////////////////////////////////////////////////////////////////////
    /// Skalardivision.
    /// @param  skalar: Der Skalar.
    /// @result Skalierter Punkt.
    //--------------------------------------------------------------------
    Punkt2D operator / (double skalar) const
    {
        ASSERT(skalar != 0);
        return Punkt2D(x / skalar, y / skalar);
    }

    //////////////////////////////////////////////////////////////////////
    /// Punktprodukt.
    /// @param  punkt:  Zweiter Operand.
    /// @result Punktprodukt der Vektoren.
    //--------------------------------------------------------------------
    double punkt(const Punkt2D& punkt) const
    {
        return x * punkt.x + y * punkt.y;
    }

    //////////////////////////////////////////////////////////////////////
    /// Bestimmt die Länge des Vektor von (0,0) zu diesem Punkt.
    /// @result Die Länge.
    //--------------------------------------------------------------------
    double laenge() const
    {
        return sqrt(x*x + y*y);
    }

    //////////////////////////////////////////////////////////////////////
    /// Normalisieren.
    /// @result Normalisierter Punkt.
    //--------------------------------------------------------------------
    Punkt2D normalisiere() const
    {
        double  l   = sqrt(x*x + y*y);
        if (l == 0.0)
            return *this;
        return Punkt2D(x / l, y / l);
    }

	//////////////////////////////////////////////////////////////////////
	/// Lexikographisch Vergleich (zuerst x-Koordinate dann y-Koordinate).
	/// @param punkt: Punkt, mit dem verglichen wird.
    /// @result true, wenn this lexikographisch echt kleiner als Punkt ist, sonst false.
    //--------------------------------------------------------------------
	bool operator < (const Punkt2D& punkt) const
	{  
		if (x < punkt.x)
			return true;

		if (x == punkt.x && y < punkt.y)
			return true;

		return false;
	}

	//////////////////////////////////////////////////////////////////////
    /// Prüfung, ob Punkt 1 kleiner als Punkt 2 ist.
	/// @param punkt1: Punkt 1
	/// @param punkt2: Punkt 2
    /// @result true, wenn Punkt 1 lexikographisch kleiner als Punkt 2 ist, sonst false.
    //--------------------------------------------------------------------
	bool operator() (const Punkt2D &punkt1, const Punkt2D &punkt2) const
	{  
		return punkt1 < punkt2;
	}


#ifdef WIN32
    //////////////////////////////////////////////////////////////////////
    /// Konvertierung in Windows-Datentyp.
    /// @result Konvertierter Punkt.
    //--------------------------------------------------------------------
    operator POINT () const
    {
        POINT   p;
        p.x = (LONG)x;
        p.y = (LONG)y;
        return p;
    }
#endif

    //////////////////////////////////////////////////////////////////////
    /// Vergleichsoperator.
    /// @param  punkt:  Zweiter Operand.
    /// @result true wenn die Operanden gleich sind, andernfalls false.
    //--------------------------------------------------------------------
    bool operator == (const Punkt2D& punkt) const
    {
        return x == punkt.x && y == punkt.y;
    }

    //////////////////////////////////////////////////////////////////////
    /// Vergleichsoperator.
    /// @param  punkt:  Zweiter Operand.
    /// @result false wenn die Operanden gleich sind, andernfalls true.
    //--------------------------------------------------------------------
    bool operator != (const Punkt2D& punkt) const
    {
        return x != punkt.x || y != punkt.y;
    }

};

//////////////////////////////////////////////////////////////////////

/// Für die Angabe von relativen Positionen.
typedef Punkt2D Offset2D;

/// Für die Verwendung als Vektor.
typedef Punkt2D Vektor2D;

//////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////

#endif
