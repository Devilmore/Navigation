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

            // Angle (i) is random
            double i = Variables.getRandomNumber(0, 360);
            
            // 1 meter is euqal to 27 pixels, the length here is calculated in pixels.
            Point2D endpoint = EZPathFollowing.Point2D.circleAround(startpoint, length, i);

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

            // Direction is random
            bool driveRight = Variables.getRandomBoolean();

            // Angle (i) is random
            double i = Variables.getRandomNumber(0, 360);

            // From Start to Center
            Point2D center = EZPathFollowing.Point2D.circleAround(startpoint, radius, i);

            // From Center to End, i is still random
            i = Variables.getRandomNumber(0, 360);
            Point2D endpoint = EZPathFollowing.Point2D.circleAround(center, radius, i);

            return new CirclePathPart(startpoint, endpoint, center, driveRight, reverse, speed);
        }
    }
}
