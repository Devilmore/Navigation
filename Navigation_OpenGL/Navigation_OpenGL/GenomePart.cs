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
        public GenomePart(bool b, int length, int angle, bool driveRight)
        {
            genome = new BitArray(8);
            genome.Set(0, b); // Sets bit 0 to 1 (curve) or 0 (line)

            for (int i = 0; i < 3; i++) // Sets the bits 1, 2 and 3 to the last 3 values of binary representation of the int value length (bits 29, 30 and 31)
                genome.Set(i + 1, GetIntBinaryString(length)[29 + i]);

            for (int i = 0; i < 3; i++) // Sets the bits 4, 5 and 6 to the last 3 values of binary representation of the int value angle (bits 29, 30 and 31)
                genome.Set(i + 4, GetIntBinaryString(length)[29 + i]);

            genome.Set(7, driveRight); // Sets the last bit to 1 for right and 0 for left
        }

        public BitArray getBitArray()
        {
            return genome;
        }

        static bool[] GetIntBinaryString(int n)
        {
            bool[] b = new bool[32];
            int pos = 31;
            int i = 0;

            while (i < 32)
            {
                if ((n & (1 << i)) != 0)
                {
                    b[pos] = true;
                }
                else
                {
                    b[pos] = false;
                }
                pos--;
                i++;
            }
            return b;
        }
    }
}
