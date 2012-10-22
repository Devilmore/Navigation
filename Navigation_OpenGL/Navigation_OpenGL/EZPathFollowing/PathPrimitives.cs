using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL.EZPathFollowing
{
    /** 
     * This class contains functions to easily create new Pathparts
     * All but the first PathPart only need a few parameters as they
     * retain direction and location from the previous pathpart.
     * 
     * Right now there is no PathPlanning Algorithm so all values needed
     * are random.
     * **/
    class PathPrimitives
    {

        /** Creates a Line from the given start with the given length in the given direction
         * This function should only be used for the first pathpart which needs a startpoint. 
         * All other pathparts should take their start and direction from the previous pathpart,
         * see the other functions.
         * 
         * - Direction is given in degree, starting at 3 o'clock (0) and rotating clockwise
         * - Direction can be any number but should be between 0-360
         * **/
        public static LinePathPart line(double length, double direction, Point2D start)
        {
            // Default values, not needed right now. May need to fix later
            double speed = 0.0;
            bool reverse = false;
            
            // 27 Pixels are 1 meter
            length *= 27;

            // Angle needs to be converted to Radian
            double directionR = direction;

            // The new endpoint is to the right of the startpoint ("3 o'clock) and will be rotated later
            Point2D endpoint = new Point2D(start.x + length, start.y);

            // Endpoint is rotated by 'direction' around the start
            endpoint = EZPathFollowing.Point2D.rotateAround(endpoint, start, directionR);
            return new LinePathPart(start, endpoint, reverse, speed, direction);
        }

        /** Same as above function, only to be used for the first element.
         * Direction is the "line" which is perpendicular to the circle and runs through start.
         * This is the line that, rotated by 90°, goes from start to center
         * Direction can here be anything from 0-360
         * **/
        public static CirclePathPart curve(double radius, double direction, double angle, bool driveRight, Point2D start)
        {
            // Default values, not needed right now. May need to fix later
            double speed = 0.0;
            bool reverse = false;

            // 27 Pixels are 1 meter
            radius *= 27;

            // To Radian
            double directionR = direction;

            // The new center is to the right of the startpoint ("3 o'clock) and will be rotated later
            Point2D center = new Point2D(start.x + radius, start.y);

            // Center is rotated by 'direction' around the start
            center = EZPathFollowing.Point2D.rotateAround(center, start, directionR);

            // To get the center the current center point has to be moved by 90° or -90° around the start, depending on driveRight
            double rightAngle = (driveRight == true)
                ? Math.PI / 2
                : -Math.PI / 2;

            center = EZPathFollowing.Point2D.rotateAround(center, start, rightAngle);

            // Initializes the endpoint
            Point2D endpoint = new Point2D(0, 0);

            // Again, for driveRight = false the angles have to reversed and angle has to be converted to radian
            double angleR = (driveRight == true)
                ? angle
                : -angle;

            double length = angle * radius;

            // Now the startpoint is rotated around the center by angle to get the endpoint
            endpoint = EZPathFollowing.Point2D.rotateAround(start, center, angleR);

            return new CirclePathPart(start, endpoint, center, driveRight, reverse, speed, angle, direction);
        }

        /**
         * This function is used for all lines except the first one. It needs neither direction nor
         * start since it starts at the end of the previous line/curve and also shares its direction
         * **/
        public static LinePathPart line(double length)
        {
            // Default values, not needed right now. May need to fix later
            double speed = 0.0;
            bool reverse = false;

            // 27 Pixels are 1 meter
            length *= 27;

            // Takes the start and direction from the previous pathpart
            Point2D start = Variables.path.Last.Value.getEnd();
            double direction = Variables.path.Last.Value.orientationDouble();
            double directionR = direction;

            // The new endpoint is to the right of the startpoint ("3 o'clock) and will be rotated later
            Point2D endpoint = new Point2D(start.x + length, start.y);

            // Endpoint is rotated by 'direction' around the start
            endpoint = EZPathFollowing.Point2D.rotateAround(endpoint, start, directionR);
            return new LinePathPart(start, endpoint, reverse, speed, direction);
        }

        /**
         * This function is used for all curves except the first one. It needs neither direction nor
         * start since it starts at the end of the previous line/curve and also shares its direction
         * **/
        public static CirclePathPart curve(double radius, double angle, bool driveRight)
        {
            // Default values, not needed right now. May need to fix later
            double speed = 0.0;
            bool reverse = false;

            // 27 Pixels are 1 meter
            radius *= 27;

            // Takes the start and direction from the previous pathpart
            Point2D start = Variables.path.Last.Value.getEnd();
            double direction = Variables.path.Last.Value.orientationDouble();
            double directionR = direction;

            // The new center is to the right of the startpoint ("3 o'clock) and will be rotated later
            Point2D center = new Point2D(start.x + radius, start.y);

            // Center is rotated by 'direction' around the start
            center = EZPathFollowing.Point2D.rotateAround(center, start, directionR);

            // To get the center the current center point has to be moved by 90° or -90° around the start, depending on driveRight
            double rightAngle = (driveRight == true)
                ? Math.PI / 2
                : -Math.PI / 2;

            center = EZPathFollowing.Point2D.rotateAround(center, start, rightAngle);

            // Initializes the endpoint
            Point2D endpoint;// = new Point2D(0, 0);

            // Again, for driveRight = false the angles have to reversed and angle has to be converted to radian
            double angleR = (driveRight == true)
                ? angle
                : -angle;

            // Now the startpoint is rotated around teh center by angle to get the endpoint
            endpoint = EZPathFollowing.Point2D.rotateAround(start, center, angleR);

            return new CirclePathPart(start, endpoint, center, driveRight, reverse, speed, angle, direction);
        }

        // Creates a random PathPart from a given start (only used for first PathPart)
        // Max/Min Values need to be adjusted.
        // For Testing only
        public static PathPart getRandomPathPart(Point2D start, double direction)
        {
            bool b = Variables.getRandomBoolean();
            bool driveRight = Variables.getRandomBoolean();
            double radius = Variables.getRandomNumber(3, 5);
            double length = Variables.getRandomNumber(1, 3);
            
            double angle = Variables.getRandomNumber(10, 45) * Math.PI / 180.0;// Variables.getRandomNumber(10, 45);
            //double direction = Variables.getRandomNumber(0,360);

            PathPart temp;// = new PathPart();
            if (b)
                temp = curve(radius, direction, angle, driveRight, start);
            else
                temp = line(length, direction, start);

            return temp;
        }

        // Creates a random PathPart continuing from the last PathPart
        // Max/Min Values need to be adjusted.
        // For Testing only
        public static PathPart getRandomPathPart()
        {
            bool b = Variables.getRandomBoolean();
            bool driveRight = Variables.getRandomBoolean();
            double radius = Variables.getRandomNumber(3, 5);
            double length = Variables.getRandomNumber(1, 3);

            double angle = Variables.getRandomNumber(10, 45) * Math.PI / 180.0;// Variables.getRandomNumber(10, 45);
            
            /*
            bool b = Variables.getRandomBoolean();
            bool driveRight = Variables.getRandomBoolean();
            double length = 5;// Variables.getRandomNumber(1, 3);
            double angle = 40*Math.PI/180.0;// Variables.getRandomNumber(10, 45);*/

            PathPart temp;// = new PathPart();
            if (b)
                temp = curve(radius, angle, driveRight);
            else
                temp = line(length);

            return temp;
        }
    }
}
