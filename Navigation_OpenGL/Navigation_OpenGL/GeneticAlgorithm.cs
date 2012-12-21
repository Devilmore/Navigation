using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace Navigation_OpenGL
{
    public class GeneticAlgorithm
    {
        // Saves the size of the population
        // TODO: Adjust this number
        private static int populationSize = 1000;
         
        // Array representing the population, this contains the paths, genomes and ratings
        private Population[] population = new Population[populationSize];
        private Population[] oldPopulation = new Population[populationSize];

        // Counts up with each Generation
        private int generationCount = 0;

        // TODO: Adjust this number
        private int maxGenerationCount = 50;

        // Temporary path
        private LinkedList<EZPathFollowing.PathPart> tempPath = new LinkedList<EZPathFollowing.PathPart>();

        // glControl, given by Form1
        OpenTK.GLControl glcontrol;

        // TextBox, given by Form 1
        TextBox textbox;

        // Constructor
        public GeneticAlgorithm(OpenTK.GLControl glcontrol, TextBox textbox)
        {
            this.textbox = textbox;
            this.glcontrol = glcontrol;
        }

        // Main Method of the GA
        //public bool gaMain(BackgroundWorker worker, DoWorkEventArgs e)
        public bool gaMain()
        {
            population = new Population[populationSize];
            oldPopulation = new Population[populationSize];

            textbox.Text = "0";
            initialize();

            while (generationCount < maxGenerationCount)
            {
                // Current generation
                generationCount++;
                textbox.Text = generationCount.ToString();

                // Copies over the population to oldPopulation so the current one can be freshly populated.
                oldPopulation = population;

                // Runs all parts of the GA
                selection();
                // singleBitCrossover();
                eightBitCrossover();
                mutation();
                evaluation();
            }
            return true;
        }

        // This function uses genomePart Uniform Crossover. It works like a crossover function but uses a significantly shorter mask genome
        // because it always chooses an entire 8bit block
        public void eightBitCrossover()
        {
            // Size of current new generation is 40% of old generation (before crossover)
            int selectionSize = Convert.ToInt32(0.4 * populationSize);
            int r;
            Genome parent1 = new Genome();
            Genome parent2 = new Genome();
            bool[] mask;
            Genome child1 = new Genome();
            Genome child2 = new Genome();

            // Iterates from selection Size (current maximum of the new population) to population size, the wanted maximum. That means 60% come from crossover
            for (int i = selectionSize; i < populationSize; i++)
            {
                // Randomly selects first parent
                r = Variables.getRandomInt(0, selectionSize);
                parent1 = oldPopulation[r].Genome;

                // Randomly selects second parent
                r = Variables.getRandomInt(0, selectionSize);
                parent2 = oldPopulation[r].Genome;

                // Crates a random mask genome in form of a char[]. char[] is much faster than bool[], genome or bitarray and for our purpose the format doesn't matter
                mask = GenomePart.getRandomGenome();

                for (int j = 0; j < 8; j++)
                {
                    // Checks the mask
                    if (mask[j])
                    {
                        // If mask == 1 then the i'th 8bit block will be selected from parent1 for child1 and from parent2 for child2
                        // k = j*8 since every position in the mask genome covers 8 positions in the actual genome
                        for (int k = j * 8; k < j * 8 + 8; k++)
                        {
                            child1.Genome1.Set(k, parent1.Genome1.Get(k));
                            child2.Genome1.Set(k, parent2.Genome1.Get(k));
                        }
                    }
                    else
                    {
                        // If mask == 0 then the i'th 8bit block will be selected from parent1 for child2 and from parent2 for child1
                        // k = j*8 since every position in the mask genome covers 8 positions in the actual genome
                        for (int k = j * 8; k < j * 8 + 8; k++)
                        {
                            child1.Genome1.Set(k, parent2.Genome1.Get(k));
                            child2.Genome1.Set(k, parent1.Genome1.Get(k));
                        }
                    }
                }

                // Adds the genome and its corresponding path to the population at position i
                population[i].Genome = child1;
                Genome.genomeToPath(child1);
                population[i].Path = Variables.path;

                // Counts up since we are adding 2 children per iteration, not just one
                i++;

                // If we are not yet at maximum (which could happen due to double->int conversion) we add the second child too
                if (i < populationSize)
                {
                    population[i].Genome = child2;
                    Genome.genomeToPath(child2);
                    population[i].Path = Variables.path;
                }
            }
        }

        // This function uses single-bit Uniform Crossover.
        public void singleBitCrossover()
        {
            // Size of current new generation is 40% of old generation (before crossover)
            int selectionSize = Convert.ToInt32(0.4 * populationSize);
            int r;
            Genome parent1 = new Genome();
            Genome parent2 = new Genome();
            Genome mask = new Genome();
            Genome child1 = new Genome();
            Genome child2 = new Genome();

            // Iterates from selection Size (current maximum of the new population) to population size, the wanted maximum. That means 60% come from crossover
            for (int i = selectionSize; i < populationSize; i ++)
            {
                // Randomly selects first parent
                r = Variables.getRandomInt(0,selectionSize);
                parent1 = oldPopulation[r].Genome;
                
                // Randomly selects second parent
                r = Variables.getRandomInt(0, selectionSize);
                parent2 = oldPopulation[r].Genome;

                // Crates a random mask genome. This function sucks.
                mask = new Genome(true);

                // Generates children
                for (int j = 0; j < 160; j++)
                {
                    if (mask.Genome1.Get(j))
                    {
                        // If mask(i) is 1 then child1 gets the value at that point from parent1, child2 from parent2
                        child1.Genome1.Set(j, parent1.Genome1.Get(j));
                        child2.Genome1.Set(j, parent2.Genome1.Get(j));
                    }
                    else
                    {
                        // If mask(i) is 0 then child1 gets the value at that point from parent2, child2 from parent1 
                        child1.Genome1.Set(j, parent2.Genome1.Get(j));
                        child2.Genome1.Set(j, parent1.Genome1.Get(j));
                    }
                }

                // Adds the genome and its corresponding path to the population at position i
                population[i].Genome = child1;
                Genome.genomeToPath(child1);
                population[i].Path = Variables.path;

                // Counts up since we are adding 2 children per iteration, not just one
                i++;

                // If we are not yet at maximum (which could happen due to double->int conversion) we add the second child too
                if (i < populationSize)
                {
                    population[i].Genome = child2;
                    Genome.genomeToPath(child2);
                    population[i].Path = Variables.path;
                }
            }
        }

        public void selection()
        {
            // Sums up all ratings to a total
            double totalFitness = 0;
            double r;
            double c;
            int j;

            // Calculates toal Fitness of the old population
            for (int i = 0; i < populationSize; i++)
            {
                totalFitness += oldPopulation[i].Rating;
            }

            // New Population consists of 40% Selection
            int selectionSize = Convert.ToInt32(0.4 * populationSize);

            // Creates <selectionSize> new members for the new population
            for (int i = 0; i < selectionSize; i++)
            {
                // Random Number
                r = Variables.getRandomNumber(0, totalFitness);

                // Current Sum and iterator are 0
                c = 0;
                j = 0;

                // Sums over oldPopulation until the sum is bigger than the random number
                do
                {
                    try
                    {
                        c += oldPopulation[j].Rating;
                        j++;
                    }
                    catch (IndexOutOfRangeException)
                    {
                        break;
                    }
                } while (c < r);

                // Selects j - 1 (since we did j++ after fulfilling the condition) from the oldPopulation and adds it to the new one at i
                population[i] = oldPopulation[j - 1];
            }
        }

        public void mutation()
        {
            BitArray array;
            int r;

            // Iterates over the entire population
            for (int i = 0; i < populationSize; i++)
            {
                // Gets the genome from member i and puts it in a bitarray
                array = population[i].Genome.Genome1;

                // Iterates over the bitarray
                for (int j = 0; j < 160; j++)
                {
                    // Genereates a random number between 0 and 1000
                    r = Variables.getRandomInt(0, 1000);

                    // If that value is 1  (chance = 0,1%), switch the number at that point
                    if (r == 1){
                        if (array.Get(j))
                            array.Set(j, false);
                        else
                            array.Set(j, true);

                        // Something was done, so write back the changed array
                        population[i].Genome.Genome1 = array;
                    }
                }
            }
        }

        public void evaluation()
        {
            // Creates a Simulation and a rating for each path in the current population and adds it to the ratings List
            for (int i = 0; i < populationSize; i++)
            {
                // Creates a new simulation and runs it
                Variables.simulation = new Simulation(Variables.vehicle, population[i].Path);
                Variables.simulation.run();

                // Gets the rating for the current simulation
                population[i].Rating = FitnessFunction.fitness(Variables.simulation.getPath());

                // Writes the path to the global Variable for drawing
                Variables.path = population[i].Path;

                // Draws.
                glcontrol.Refresh();
            }
        }

        public void initialize()
        {
            double rating;

            // Generates an initial population of size <PopulationSize> along with their fitness
            for (int i = 0; i < populationSize; i++)
            {
                // Generates a random path of length 20 and saves it to the global path
                EZPathFollowing.PathPrimitives.generatePath();

                // Creates a Simulation for this path
                Variables.simulation = new Simulation(Variables.vehicle, Variables.path);
                Variables.simulation.run();

                // Rates the Path and adds the rating to the ratings List
                rating = FitnessFunction.fitness(Variables.simulation.getPath());

                // Adds the path, genome and rating to the population
                population[i] = new Population(Variables.path, Variables.genome, rating);

                // Draws.
                glcontrol.Refresh();
            }
        }
    }
}
