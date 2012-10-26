using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace Navigation_OpenGL
{
    // This class contains the entire genome of a given path and functions to new PathParts to the genome
    public class Genome
    {
        BitArray genome;
        int length;

        public Genome()
        {
            genome = new BitArray(160); // Empty bit array with 160 bit (20 PathParts), all set to false. 
            length = 0; // Number of PathParts already added to this genome, maximum 19
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

        public int getLength()
        {
            return length;
        }

        // Why do I have to do this instead of return genome.toString(); ? It doesn't work.
        public string write()
        {
            string output = "";
            for (int i = 0; i<160; i++)
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
