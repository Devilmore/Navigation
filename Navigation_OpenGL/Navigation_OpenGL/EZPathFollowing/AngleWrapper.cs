using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL.EZPathFollowing
{
    class AngleWrapper
    {
        protected double m_radian;

        // Default Constructor
        public AngleWrapper()
        {
            m_radian = 0.0;
        }

        public AngleWrapper(AngleWrapper angle)
        {
            setRadian(angle.radian());
        }

        public AngleWrapper(double radian)
        {
            setRadian(radian);
        }

        public AngleWrapper(Point2D vector)
        {
            vector = vector.normalize();
            if (vector.y < 0)
                setRadian(2 * Math.PI - Math.Acos(vector.x));
            else
                setRadian(Math.Acos(vector.x));
        }

        public void setRadian(double value)
        {
            m_radian = (value >= 0)
                ? Math.IEEERemainder(value, 2 * Math.PI)
                : Math.IEEERemainder(value, 2 * Math.PI) + 2 * Math.PI;
        }

        public double radian()
        {
            return m_radian;
        }

        public double degree()
        {
            return m_radian * 180 / Math.PI;
        }

        public void setDegree(double value)
        {
            setRadian(value * Math.PI / 180);
        }

        public Point2D unitVector()
        {
            return new Point2D(Math.Cos(m_radian), Math.Sin(m_radian));
        }

        public AngleWrapper perpendicularLeft()
        {
            return new AngleWrapper(m_radian + Math.PI / 2);
        }

        public AngleWrapper perpendicularRight()
        {
            return new AngleWrapper(m_radian - Math.PI / 2);
        }

        public static bool operator <(AngleWrapper angle, AngleWrapper angle2)
        {
            return angle.radian()<angle2.radian();
        }

        public static bool operator >(AngleWrapper angle, AngleWrapper angle2)
        {
            return angle.radian() > angle2.radian();
        }

        // Adds two angles
        public static AngleWrapper operator +(AngleWrapper angle1, AngleWrapper angle2)
        {
            return new AngleWrapper(angle1.radian() + angle2.radian());
        }

        // Adds a double value to an angle
        public static AngleWrapper operator +(AngleWrapper angle, double bm)
        {
            return new AngleWrapper(angle.radian() + bm);
        }

        // Subtracts a double value from an angle
        public static AngleWrapper operator -(AngleWrapper angle, double bm)
        {
            return new AngleWrapper(angle.radian() + (-bm));
        }

        // Reverses the angle
        public static AngleWrapper operator -(AngleWrapper angle)
        {
            return new AngleWrapper(-angle.radian());
        }

        //Implement more Operators here later as needed 
    }
}
