#include "EZStandard.h"
#include "EZWinkelWrapper.h"


using namespace EZ;

WinkelWrapper::WinkelWrapper( double bogenmass )
{
	setzeBogenmass(bogenmass);
}

WinkelWrapper::~WinkelWrapper()
{

}

WinkelWrapper::WinkelWrapper( Punkt2D vektor )
{
	vektor = vektor.normalisiere();
	if (vektor.y<0)
		setzeBogenmass(2*PI - acos(vektor.x));
	else
		setzeBogenmass(acos(vektor.x));
}

WinkelWrapper::WinkelWrapper()
{
	m_bogenmass=0.0;
}

WinkelWrapper::WinkelWrapper( const WinkelWrapper& winkel )
{
	setzeBogenmass(winkel.bogenmass());
}
void WinkelWrapper::setzeBogenmass( double wert )
{
	m_bogenmass = (wert>=0) ?
						fmod(wert,2*PI)
					:	fmod(wert,2*PI)+2*PI;
}

double WinkelWrapper::bogenmass() const
{
	return m_bogenmass;
}

double WinkelWrapper::gradmass() const
{
	return m_bogenmass*180/PI;
}

void WinkelWrapper::setzeGradmass( double wert )
{
	setzeBogenmass(wert*PI/180);
}

EZ::Punkt2D WinkelWrapper::einheitsvektor() const
{
	return Punkt2D(cos(m_bogenmass),sin(m_bogenmass));
}

WinkelWrapper WinkelWrapper::senkrechteLinks() const
{
	return WinkelWrapper(m_bogenmass+PI/2);
}

WinkelWrapper WinkelWrapper::senkrechteRechts() const
{
	return WinkelWrapper(m_bogenmass-PI/2);
}

bool WinkelWrapper::operator<( const WinkelWrapper& winkel) const
{
	return bogenmass()<winkel.bogenmass();
}

bool WinkelWrapper::operator>( const WinkelWrapper& winkel ) const
{
	return winkel<*this;
}

bool WinkelWrapper::operator==( const WinkelWrapper& winkel) const
{
	return (*this<winkel) && (winkel<*this);
}

bool WinkelWrapper::operator!=( const WinkelWrapper& winkel) const
{
	return !(*this == winkel);
}

bool WinkelWrapper::operator<=( const WinkelWrapper& winkel) const
{
	return (*this<winkel)||(*this==winkel);
}

WinkelWrapper& WinkelWrapper::operator=( const WinkelWrapper& winkel )
{
	setzeBogenmass(winkel.bogenmass());
	return *this;
}

WinkelWrapper& WinkelWrapper::operator=( double bogenmass )
{
	setzeBogenmass(bogenmass);
	return *this;
}
bool WinkelWrapper::operator>=( const WinkelWrapper& winkel) const
{
	return (winkel<=*this);
}

WinkelWrapper WinkelWrapper::operator+( const WinkelWrapper& winkel ) const
{
	return WinkelWrapper(bogenmass()+winkel.bogenmass());
}

WinkelWrapper WinkelWrapper::operator+() const
{
	return WinkelWrapper(bogenmass());
}

WinkelWrapper WinkelWrapper::operator+( double bm ) const
{
	return Winkel(bogenmass()+bm);
}
WinkelWrapper WinkelWrapper::operator-() const
{
	return WinkelWrapper(-bogenmass());
}

WinkelWrapper WinkelWrapper::operator-( const WinkelWrapper& winkel ) const
{
	return (*this)+(-winkel);
}

WinkelWrapper& WinkelWrapper::operator+=( const WinkelWrapper& winkel )
{
	setzeBogenmass((*this+winkel).bogenmass());
	return *this;
}

WinkelWrapper& WinkelWrapper::operator+=( double bm )
{
	setzeBogenmass(bogenmass()+bm);
	return *this;
}
WinkelWrapper& WinkelWrapper::operator-=( const WinkelWrapper& winkel )
{
	setzeBogenmass((*this-winkel).bogenmass());
	return *this;
}

WinkelWrapper WinkelWrapper::operator-( double bm ) const
{
	return *this + (-bm);
}

WinkelWrapper& WinkelWrapper::operator-=( double bm )
{
	setzeBogenmass(bogenmass()-bm);
	return *this;
}

