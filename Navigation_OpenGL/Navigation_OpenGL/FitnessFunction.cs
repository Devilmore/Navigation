using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL
{
    public class FitnessFunction
    {
        // Returns the fitness of a path
        // NOT YET DONE
        public static double fitness(List<EZPathFollowing.Point2D> path)
        {
            int collisions = getCollisions(path, Variables.map);

            // Calculates the rating of the last simulated end configuration
            double configurationRating = rateConfigurationNoMaximum(Variables.configuration_end, configuration.getConfig(new EZPathFollowing.Point2D(Variables.x * 27, Variables.y * 27), Variables.orientation));

            // Adds the Inverse of collisions and configurtionRating since those values go up for bad paths but rating should go up for good paths
            // TODO: Proper weighting
            double rating = 1 / collisions + 1 / configurationRating;

            return rating;
        }

        // Returns the number of collisions between a given path and a given map
        public static int getCollisions(List<EZPathFollowing.Point2D> path, bool[,] map)
        {
            int count = 0;
            int x, y = 0;
            foreach (EZPathFollowing.Point2D point in path)
            {
                // Get int values
                x = Convert.ToInt32(point.x);
                y = Convert.ToInt32(point.y);

                // If vehicle leaves the map, count up. May split this into an extra counter later
                if (x < 0 || y < 0 || x > map.GetUpperBound(0) || y > map.GetUpperBound(1))
                {
                    count++;
                }
                // If the point isn't of the map it can be checked for collision
                else
                {
                    // map[x,y] == false means there is a wall, thus counter++
                    if (map[x, y] == false)
                        count++;
                }
            }

            // Retuns the number of collisions.
            return count;
        }

        // Rates how close the given configuration at the end of the path is to the desired ending configuration
        public static double rateConfigurationNoMaximum(configuration wantedConfiguration, configuration givenConfiguration)
        {
            double[] distances = new double[Variables.vehicle_size];
            EZPathFollowing.LinePathPart line = null;

            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                line = new EZPathFollowing.LinePathPart(wantedConfiguration.getPoint(i), givenConfiguration.getPoint(i), false, 0, 0);
                distances[i] = line.pathlength();
            }

            double rating = average(distances);

            return rating;
        }

        // Rates how close the given configuration at the end of the path is to the desired ending configuration.
        // This function values the first point higher than the rest and has a maximum of 100
        public static double rateConfiguration(configuration wantedConfiguration, configuration givenConfiguration)
        {
            double distance;
            double[] distances = new double[Variables.vehicle_size - 1];
            double rating = 100;

            // Distance between first axle of wanted and given configuration ("start" and "end" point of our path)
            EZPathFollowing.LinePathPart line = new EZPathFollowing.LinePathPart(wantedConfiguration.getPoint(0), givenConfiguration.getPoint(0), false, 0, 0);
            distance = line.pathlength();

            // If the distance of start and end is over 100 the path is so bad we don't even care anymore about the rest
            if (distance < 100)
            {
                // Iterates over all axles except the first one and writes the distance to distances[i - 1]
                for (int i = 1; i < Variables.vehicle_size; i++)
                {
                    line = new EZPathFollowing.LinePathPart(wantedConfiguration.getPoint(i), givenConfiguration.getPoint(i), false, 0, 0);
                    distances[i - 1] = line.pathlength();
                }
                // The rating is 50% distance between the start/end point and 50% the average distance between all other points
                rating = (distance + average(distances)) / 2;
            }

            // Makes sure the rating does not go above 100. This could happen if the distances between the other points of the configuration are > 100 but the
            // Distance between the 0 axles are not.
            if (rating > 100)
                rating = 100;

            // Returns rating, which is either 100 (worst case value) if distance is > 100 or the average of all distances.
            // Thus 100 is the worst and the lower the number the better
            return rating;
        }

        // Returns the average of a array of doubles
        public static double average(double[] array)
        {
            double value = 0;
            foreach (double d in array)
              value += d;
            value /= array.Length;
            return value;
        }
    }
}
