using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL.EZPathFollowing
{
    class PathPrimitives
    {
        public static LinePathPart LineInMeter(double length)
        {
            // Speed and reverse always false for our purposes
            double speed = 0.0;
            bool reverse = false;

            // The startpoint is always equal to last element's endpoint.
            // For this purpose a LinePathPart of length 0 is added to the Linked List at the beginning.
            // Should this cause trouble with the pathlength: remove and fix.
            Point2D startpoint = Variables.path.Last.Value.getEnd();

            // This function searches for an endpoint with the give length as a distance to the startpoint
            // This does not fit the given datastructure at all, replace later if possible.
            const double DEG2RAD = Math.PI / 180;
            double i = Variables.getRandomNumber(0, 360);
            i = 0;
            
            // 1 meter is euqal to 27 pixels, the length here is calculated in pixels.
            double degInRad = i * DEG2RAD;
            Point2D endpoint = new Point2D(startpoint.x + Math.Cos(degInRad) * length, startpoint.y + Math.Sin(degInRad) * length);

            return new LinePathPart(startpoint, endpoint, reverse, speed);
        }

        public static CirclePathPart CircleInMeter(double radius)
        {
            // Speed and reverse always false for our purposes
            double speed = 0.0;
            bool reverse = false;

            // The startpoint is always equal to last element's endpoint.
            // For this purpose a LinePathPart of length 0 is added to the Linked List at the beginning.
            // Should this cause trouble with the pathlength: remove and fix.
            Point2D startpoint = Variables.path.Last.Value.getEnd();

            bool driveRight = Variables.getRandomBoolean();

            // Currently only using 90° angles. Fix later.
            Point2D endpoint = new Point2D(startpoint.x + radius, startpoint.y + radius);
            Point2D center = new Point2D(startpoint.x + radius, startpoint.y);

            return new CirclePathPart(startpoint, endpoint, center, driveRight, reverse, speed);
        }
    }
}
