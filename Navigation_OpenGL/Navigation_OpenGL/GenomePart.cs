using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace Navigation_OpenGL
{
    // This class contains a genome part which equals 1 PathPart
    public class GenomePart
    {
        BitArray genome;

        // Empty Constructor
        public GenomePart()
        {
            genome = new BitArray(8);
        }

        // Constructor
        public GenomePart(bool b, double length, double angle, bool driveRight)
        {
            genome = new BitArray(8);
            bool[] bits = new bool[3];
            genome.Set(0, b); // Sets bit 0 to 1 (curve) or 0 (line)

            //for (int i = 0; i < 3; i++) // Sets the bits 1, 2 and 3 to the last 3 values of binary representation of the int value length (bits 29, 30 and 31)
            //    genome.Set(i + 1, GetIntBinaryString(length)[29 + i]);

            bits = GetIntBinaryField(length);

            for (int i = 1; i < 4; i++)
                genome.Set(i, bits[i - 1]);

            bits = GetIntBinaryField(angle);
            for (int i = 4; i < 7; i++)
                genome.Set(i, bits[i - 4]);

            //for (int i = 0; i < 3; i++) // Sets the bits 4, 5 and 6 to the last 3 values of binary representation of the int value angle (bits 29, 30 and 31)
            //    genome.Set(i + 4, GetIntBinaryString(length)[29 + i]);

            genome.Set(7, driveRight); // Sets the last bit to 1 for right and 0 for left //!! For some reason driveRight means the exact opposit, so 1 for left, 0 for right. Don't ask!
        }

        public BitArray getBitArray()
        {
            return genome;
        }

        //public BitArray getRandomBitArray()
        //{
        //    return 
        //}

        public static double getDouble(bool i, bool j, bool k)
        {
            double l = (i) ? 4 : 0; // 2^2
            double m = (j) ? 2 : 0; // 2^1
            double n = (k) ? 1 : 0; // 2^0
            return l + m + n;
        }

        public static bool[] getRandomGenome()
        {
            bool[] b = new bool[8];
            int i = Variables.getRandomInt(0, 255);
            string s = Convert.ToString(i, 2);
            char[] values = s.ToCharArray();

            for (int j = 0; j < values.Length; j++)
            {
                if (values[j] == '1')
                    b[j] = true;
            }

            return b;
        }

        static bool[] GetIntBinaryField(double m)
        {
            int d = 0;
            bool[] b = new bool[3];

            /** Iteration: 
             * i is 4, then 2, then 1. The third time it is set to 0.5 which aborts the iteration.
             * d counts up from 0 to 2, marking the position of the bit value
             * **/
            for (double i = 4; i >= 1; i /= 2)
            {
                if (m < i) // m greater than i (2², then 2, then 0) ?
                {
                    // If no, given bit must be false
                    b[d] = false;
                }
                else
                {
                    // If yes, given bit must be true and m must be set to m-i to compare the rest
                    b[d] = true;
                    m -= i;
                }
                // Next bit position
                d++;
            }
            return b;
        }
    }
}
