using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Windows.Forms;

namespace Navigation_OpenGL
{
    // This class contains the entire genome of a given path and functions to new PathParts to the genome
    public class Genome
    {
        private BitArray genome;

        public BitArray Genome1
        {
            get { return genome; }
            set { genome = value; }
        }

        private int length;

        public Genome()
        {
            genome = new BitArray(160); // Empty bit array with 160 bit (20 PathParts), all set to false. 
            length = 0; // Number of PathParts already added to this genome, maximum 19
        }

        // Random Genome function. Make this faster later
        public Genome(bool random)
        {
            if (random)
            {
                bool k;
                genome = new BitArray(160);
                for (int i = 0; i<160; i++)
                {
                    k = Variables.getRandomBoolean();
                    genome.Set(i, k);
                }
            }
        }

        public void add(GenomePart value)
        {
            // Paths have a maximum lengths of 20
            if (this.length < 20)
            {
                // Get the BitArray from the GenomePart
                BitArray array = value.getBitArray();

                // Temporary array of bools since BitArrays don't have the needed functions
                bool[] temp = new bool[8];

                // Copy the BitArray from GenomePart to the array of bool
                array.CopyTo(temp,0);

                // Copy the values to the Genome, offset by length * 8
                for (int i = 0; i < 8; i++)
                {
                    genome.Set(length * 8 + i, temp[i]);
                }

                // Increment the length
                this.length++;
            }
        }

        public static void genomeToPath(Genome pathGenome)
        {
            // Initialize Path List
            //LinkedList<EZPathFollowing.PathPart> output = new LinkedList<EZPathFollowing.PathPart>();

            // Resets the global path
            Variables.resetPath();
            // Resets the gloabl genome
            Variables.resetGenome();

            // Initialize Variables
            double length; // Length is a number n from 0 to 7. 0.5 + n * 0.5 is the length of a Pathpart
            double angle; // Angle a is a number from 0 to 7, 10 + a * 5 is the angle in DEGREE
            bool driveRight;
            double direction = (360 - Variables.configuration_start.Theta[0]) * Math.PI / 180;
            EZPathFollowing.Point2D start = Variables.start;

            // Iterate over all 20 GenomeParts
            for (int i = 0; i < 20; i++)
            {
                // Length is saved in Bits 1,2 and 3 and is required for both PathParts
                length = GenomePart.getDouble(pathGenome.genome.Get(i * 8 + 1), pathGenome.genome.Get(i * 8 + 2), pathGenome.genome.Get(i * 8 + 3));
                length = 0.5 + length * 0.5;

                // Bit 0 says whether its a curve or line
                if (pathGenome.genome.Get(i * 8) == false)
                {
                    // The first Pathpart needs a start and direction
                    if (i == 0)
                    {
                        Variables.path.AddLast(EZPathFollowing.PathPrimitives.line(length, direction, start));
                    }
                    else
                    {
                        Variables.path.AddLast(EZPathFollowing.PathPrimitives.line(length));
                    }
                }
                else
                {
                    // Angle and driveRight are only necessary for curves (Bit 0 = true)
                    angle = GenomePart.getDouble(pathGenome.genome.Get(i * 8 + 4), pathGenome.genome.Get(i * 8 + 5), pathGenome.genome.Get(i * 8 + 6));
                    angle = (10 + angle * 5) * Math.PI / 180;

                    driveRight = pathGenome.genome.Get(i * 8 + 7);

                    // Again, first PathPart needs a start and direction
                    if (i == 0)
                    {
                        Variables.path.AddLast(EZPathFollowing.PathPrimitives.curve(length, direction, angle, driveRight, start));
                    }
                    else
                    {
                        Variables.path.AddLast(EZPathFollowing.PathPrimitives.curve(length, angle, driveRight));
                    }
                }
            }
        }

        public int getLength()
        {
            return length;
        }

        // Why do I have to do this instead of return genome.toString(); ? It doesn't work.
        public string write()
        {
            string output = "";
            for (int i = 0; i < 160; i++)
            {
                if (genome.Get(i) == false)
                    output += "0";
                else
                    output += "1";
            }
            return output;
        }
    }
}
