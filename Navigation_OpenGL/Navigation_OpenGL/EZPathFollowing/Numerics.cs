using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL.EZPathFollowing
{
    class Numerics
    {
        // Calculates the angle of a vektor
        public static double angleToPoint(Point2D point, Point2D centerPoint)
        {
            Point2D p1 = new Point2D(1, 0);
            Point2D p2 = new Point2D(centerPoint.normalize());
            if (point.y < centerPoint.y)
                return 2 * Math.PI - Math.Acos(p1.point(p2));
            else
                return Math.Acos(p1.point(p2));
        }

        // Normalizes an angle in Radian to the Interval [0..2PI]
        public double angleIn2PI(double angle)
        {
            angle = Math.IEEERemainder(angle, 2 * Math.PI);
            if (angle < 0)
                angle += 2 * Math.PI;
            return angle;
        }

        // Projects a Point onto a Line. Afterwards rounds the Line onto a rounding factor (unless the rounding factor is 0)
        public Point2D projectPointToLine(Point2D point, Point2D directionalVector, Point2D supportVector, double roundingFactor)
        {
            directionalVector = directionalVector.normalize();
            double lamda = round(directionalVector.point(supportVector), roundingFactor);
            return new Point2D(Point2D.add(Point2D.multiplyBy(directionalVector, lamda), supportVector));
        }

        //Rounds a value to the next multiple of the rounding factor
        public double round(double value, double roundingFactor)
        {
            if (roundingFactor == 0.0)
                return value;
            else
                return Math.Floor(value / roundingFactor + 0.5) * roundingFactor;
        }

        //rotates a point around a center and an angle
        public static Point2D rotate(Point2D point, Point2D center, double angle)
        {
            double length = Point2D.sub(point, center).length();
            double oldAngle = angleToPoint(point, center);
            return new Point2D(
                Point2D.add(
                Point2D.multiplyBy(
                new Point2D(Math.Cos(oldAngle + angle), Math.Sin(oldAngle + angle)),length),
                center));
        }
    }
}
