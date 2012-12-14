using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Windows.Forms;

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

            // Generates the genomePart equal to this PathPart and adds it to the genome
            // Length is length * 2 -1 because it is generated as a random number 0-7 and then multiplied by 0.5 and added 0.5
            // The original number 0-7 is needed here however for the genome
            // Same for the angle. (*(-10/5))
            GenomePart part = new GenomePart(false, length * 2 -1, 0, false);
            Variables.genome.add(part);

            // 27 Pixels are 1 meter
            length *= 27;

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

            // Generates the genomePart equal to this PathPart and adds it to the genome
            GenomePart part = new GenomePart(true, radius * 2 - 1, ((angle * 180 / Math.PI) - 10) / 5, driveRight);
            Variables.genome.add(part);

            // 27 Pixels are 1 meter
            radius *= 27;
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

            // Again, for driveRight = false the angles have to be reversed
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

            // Generates the genomePart equal to this PathPart and adds it to the genome
            GenomePart part = new GenomePart(false, length * 2 - 1, 0, false);
            Variables.genome.add(part);

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

            // Generates the genomePart equal to this PathPart and adds it to the genome
            GenomePart part = new GenomePart(true, radius * 2 - 1, ((angle * 180 / Math.PI) - 10) / 5, driveRight);
            Variables.genome.add(part);

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
            Point2D endpoint;

            // Again, for driveRight = false the angles have to be reversed and angle has to be converted to radian
            double angleR = (driveRight == true)
                ? angle
                : -angle;

            // Now the startpoint is rotated around the center by angle to get the endpoint
            endpoint = EZPathFollowing.Point2D.rotateAround(start, center, angleR);

            return new CirclePathPart(start, endpoint, center, driveRight, reverse, speed, angle, direction);
        }

        // Creates a random PathPart from a given start (only used for first PathPart)
        // Max/Min Values need to be adjusted.
        // For Testing only
        public static PathPart getRandomPathPart(Point2D start, double direction)
        {
            bool b = Variables.getRandomBoolean(); // First bit of genome, 1 = curve, 0 = line

            int lengthG = Convert.ToInt32(Variables.getRandomNumber(0, 7));
            double length = 0.5 + lengthG * 0.5; // Next 3 bits of genome, 0.5 (000) to 4 (111) meters

            int angleG = Convert.ToInt32(Variables.getRandomNumber(0, 7));
            double angle = (10 + angleG * 5)* Math.PI / 180; // Next 3 bits of genome, 10 (000) to 45 (111) degree

            bool driveRight = Variables.getRandomBoolean(); // Last bit of genome, 1 = right, 0 = left
            direction *= Math.PI / 180;

            //// Generates a genome from the given PathPart and appends it to the genome for the entire path
            //GenomePart part = new GenomePart(b, lengthG, angleG, driveRight);
            //Variables.genome.add(part);

            PathPart temp;// = new PathPart();
            if (b)
                temp = curve(length, direction, angle, driveRight, start);
            else
                temp = line(length, direction, start);

            return temp;
        }

        // Creates a random PathPart continuing from the last PathPart
        // Max/Min Values need to be adjusted.
        // For Testing only
        public static PathPart getRandomPathPart()
        {
            bool b = Variables.getRandomBoolean(); // First bit of genome, 1 = curve, 0 = line

            int lengthG = Convert.ToInt32(Variables.getRandomNumber(0, 7));
            double length = 0.5 + lengthG * 0.5; // Next 3 bits of genome, 0.5 (000) to 4 (111) meters

            int angleG = Convert.ToInt32(Variables.getRandomNumber(0, 7));
            double angle = (10 + angleG * 5) * Math.PI / 180; // Next 3 bits of genome, 10 (000) to 45 (111) degree

            bool driveRight = Variables.getRandomBoolean(); // Last bit of genome, 1 = right, 0 = left

            //// Generates a genome from the given PathPart and appends it to the genome for the entire path
            //GenomePart part = new GenomePart(b, lengthG, angleG, driveRight);
            //Variables.genome.add(part);


            PathPart temp;// = new PathPart();
            if (b)
                temp = curve(length, angle, driveRight);
            else
                temp = line(length);

            return temp;
        }

        // Generates a path of length 20 and returns it as a list
        public static void generatePath()
        {
            // Resets the Path, Genome and Simulation before calculating the new ones
            Variables.resetGenome();
            Variables.resetPath();
            if (Variables.simulation != null)
                Variables.simulation.reset();

            for (int i = 0; i < 20; i++)
            {
                EZPathFollowing.PathPart temp;
                if (Variables.pathlength == 0)
                    temp = EZPathFollowing.PathPrimitives.getRandomPathPart(Variables.start, 360 - Variables.configuration_start.Theta[0]);
                else
                    temp = EZPathFollowing.PathPrimitives.getRandomPathPart();

                Variables.path.AddLast(temp);
                Variables.pathlength++;
            }
        }
    }
}
