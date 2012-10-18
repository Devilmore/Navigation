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
            Point2D endpoint = new Point2D(0,0);
           
            // The angle is random if the previous pathpart had no length (should only occur on the first pathpart)
            if (Variables.path.Count == 1)
            {
                double i = Variables.getRandomNumber(0, 360);
                endpoint = EZPathFollowing.Point2D.circleAround(startpoint, length, i);
            }
            // Otherwise it is the same as on the previous pathpart (no corners)
            // FIX: Does not yet work if the previous pathpart was a circle
            else
            {
                if (Variables.path.Last.Value.GetType() == EZPathFollowing.LinePathPart)
                endpoint = startpoint + (startpoint - Variables.path.Last.Value.getStart());

            }
            return new LinePathPart(startpoint, endpoint, reverse, speed);
        }

        public static CirclePathPart CircleInMeter(double radius)
        {
            // Speed and reverse always false for our purposes
            double speed = 0.0;
            bool reverse = false;
            bool driveRight = false;

            // The startpoint is always equal to last element's endpoint.
            // For this purpose a LinePathPart of length 0 is added to the Linked List at the beginning.
            // Should this cause trouble with the pathlength: remove and fix.
            Point2D startpoint = Variables.path.Last.Value.getEnd();

            // Direction is random
           // bool driveRight = Variables.getRandomBoolean();

            // From Start to Center
            // If this is the first element, it is random.
            Point2D center = new Point2D(0, 0);
            if (Variables.path.Count == 1)
            {
                double i = Variables.getRandomNumber(0, 360);
                center = EZPathFollowing.Point2D.circleAround(startpoint, radius, i);
            }
            else
            {
                // ct is a point which is an extension of the previous pathpart. ct is then circled around the start of the new pathpart
                // by 90°, leading to the new center point. 
                // FIX: Direction needs to be randomized
                // FIX: Does not yet work if the previous pathpart was a circle
                Point2D ct = new Point2D(0,0);
                ct = startpoint + (startpoint - Variables.path.Last.Value.getStart());
                center.x = Math.Cos(90) * (ct.x - startpoint.x) - Math.Sin(90) * (ct.y - startpoint.y) + startpoint.x;
                center.y = Math.Sin(90) * (ct.x - startpoint.x) - Math.Cos(90) * (ct.y - startpoint.y) + startpoint.y;
            } 
                
            // From Center to End, i is still random
            double j = Variables.getRandomNumber(0, 45);
            Point2D endpoint = EZPathFollowing.Point2D.circleAround(center, radius, j);

            return new CirclePathPart(startpoint, endpoint, center, driveRight, reverse, speed);
        }
    }
}
