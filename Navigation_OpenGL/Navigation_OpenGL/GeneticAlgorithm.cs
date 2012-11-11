using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace Navigation_OpenGL
{
    public class GeneticAlgorithm
    {
        // Saves the size of the population
        // TODO: Adjust this number
        private static int populationSize = 100;
         
        // Array representing the population, this contains the paths, genomes and ratings
        private Population[] population = new Population[populationSize];
        private Population[] oldPopulation = new Population[populationSize];

        // Counts up with each Generation
        private int generationCount = 0;

        // TODO: Adjust this number
        private int maxGenerationCount = 50;

        // Temporary Simulation of the temporary path
        private Simulation tempSimulation = null;

        // Temporary path
        private LinkedList<EZPathFollowing.PathPart> tempPath = new LinkedList<EZPathFollowing.PathPart>();



        // Main Method of the GA
        public void gaMain()
        {
            initialize();

            while (generationCount < maxGenerationCount)
            {
                // Current generation
                generationCount++;

                // Copies over the population to oldPopulation so the current one can be freshly populated.
                oldPopulation = population;

                // Runs all parts of the GA
                selection();
                crossover();
                mutation();
                evaluation();
            }
        }

        // This function uses Uniform Crossover. Single point crossover would be significanly faster, but also less random.
        public void crossover()
        {
            // Site of current new generation is 40% of old generation (before crossover)
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
                population[i].Path = Genome.genomeToPath(child1);

                // Counts up since we are adding 2 children per iteration, not just one
                i++;

                // If we are not yet at maximum (which could happen due to double->int conversion) we add the second child too
                if (i < populationSize)
                {
                    population[i].Genome = child2;
                    population[i].Path = Genome.genomeToPath(child2);
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
            for (int i =0; i < populationSize; i++)
            {
                totalFitness += oldPopulation[i].Rating;
            }

            // New Population consists of 40% Selection
            int selectionSize = Convert.ToInt32(0.4 * populationSize);

            // Creates <selectionSite> new members for the new population
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
                    c += oldPopulation[j].Rating;
                    j++;
                } while (c < r);

                // Selects j from the oldPopulation and adds it to the new one at i
                population[i] = oldPopulation[j];
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
                tempSimulation = new Simulation(Variables.vehicle, population[i].Path);
                population[i].Rating = FitnessFunction.fitness(tempSimulation.getPath());
            }
        }

        public void initialize()
        {
            // Generates an initial population of size <PopulationSize> along with their fitness
            for (int i = 0; i < populationSize; i++)
            {
                // Resets the global genome. Might wanna fix this later
                Variables.genome = new Genome();

                // Generates a random path of length 20
                tempPath = EZPathFollowing.PathPrimitives.generatePath();

                // Adds it to the population
                population[i].Path = tempPath;

                // Adds the corresponding genome
                population[i].Genome = Variables.genome;

                // Creates a Simulation for this path
                tempSimulation = new Simulation(Variables.vehicle, tempPath);

                // Rates the Path and adds the rating to the ratings List
                population[i].Rating = FitnessFunction.fitness(tempSimulation.getPath());
            }
        }
    }
}
