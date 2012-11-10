using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL.EZPathFollowing
{
    // Describes a point on the 2D map
    // Original: "EZPunkt2D.h", see for more functions if necessary
    public class Point2D
    {
        public double x;
        public double y;

        // Constructor with both values
        public Point2D(double x, double y)
        {
            this.x = x;
            this.y = y;
        }

        public Point2D(double angle)
        {
            this.x = Math.Cos(angle);
            this.y = Math.Sin(angle);
        }

        // Constructor via copy
        public Point2D(Point2D point)
        {
            x = point.x;
            y = point.y;
        }

        // Sets the coordinates
        public void set(double x, double y)
        {
            this.x = x;
            this.y = y;
        }

        // Copies from another Point2D
        public Point2D copyFrom(Point2D point)
        {
            x = point.x;
            y = point.y;
            return this;
        }

        // Normalizes this point and returns it
        public Point2D normalize()
        {
            double l = Math.Sqrt(x * x + y * y);
            if (l == 0.0)
                return this;
            return new Point2D(x / l, y / l);
        }

        // Adds one point to another, thereby moving it
        public static Point2D add (Point2D point, Point2D difference)
        {
            return new Point2D(point.x + difference.x, point.y + difference.y);
        }

        // Adds one point to antoher, thereby moving it in short
        public static Point2D operator +(Point2D point1, Point2D point2)
        {
            return new Point2D(point1.x + point2.x, point1.y + point2.x);
        }

        // Subtracts one point from another, moving it
        public static Point2D sub(Point2D point, Point2D difference)
        {
            return new Point2D(point.x - difference.x, point.y - difference.y);
        }

        public static Point2D operator -(Point2D point1, Point2D point2)
        {
            return new Point2D(point1.x - point2.x, point1.y - point2.y);
        }

        // Multiplies a point with a factor, thereby moving it
        public static Point2D multiplyBy(Point2D point, double factor)
        {
            return new Point2D(point.x * factor, point.y * factor);
        }

        // Multiplies a vector with a point in short
        public static Point2D operator *(Point2D point, double scalar)
        {
            return new Point2D(point.x * scalar, point.y * scalar);
        }

        // Returns the length of a vector
        public double length()
        {
            return Math.Sqrt(x*x + y*y);
        }

        public double point(Point2D point)
        {
            return x * point.x + y * point.y;
        }

        public static bool closeTo(Point2D point1, Point2D point2)
        {
            return (Math.Abs(point1.x - point2.x) < 1 && Math.Abs(point1.y - point2.y) < 1);
        }

        public static bool closeTo(Point2D point1, Point2D point2, int delta)
        {
            return (Math.Abs(point1.x - point2.x) < delta && Math.Abs(point1.y - point2.y) < delta);
        }

        // This function searches for an endpoint with the give length as a distance to the startpoint
        // This does not fit the given datastructure at all, replace later if possible.
        // 1 meter is euqal to 27 pixels, the length here is calculated in pixels.
        public static Point2D circleAround(Point2D start, double radius, double angle)
        {
            const double DEG2RAD = Math.PI / 180;
            double degInRad = angle * DEG2RAD;
            return new Point2D(start.x + Math.Cos(degInRad) * radius, start.y + Math.Sin(degInRad) * radius);
        }

        // Moves point around center by theta (clockwise)
        public static Point2D rotateAround(Point2D point, Point2D center, double theta)
        {
            Point2D returnpoint = new Point2D(0,0);
            returnpoint.x = Math.Cos(theta) * (point.x - center.x) - Math.Sin(theta) * (point.y - center.y) + center.x;
            returnpoint.y = Math.Sin(theta) * (point.x - center.x) + Math.Cos(theta) * (point.y - center.y) + center.y;
            return returnpoint;
        }
    }
}
