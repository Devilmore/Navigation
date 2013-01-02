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
        private int maxGenerationCount = 100;

        // Temporary path
        private LinkedList<EZPathFollowing.PathPart> tempPath = new LinkedList<EZPathFollowing.PathPart>();

        // glControl, given by Form1
        OpenTK.GLControl glcontrol;

        // TextBox, given by Form 1
        TextBox textbox;

        // Status Bar, given by Form 1
        System.Windows.Forms.ProgressBar status;

        // Best path ever created in this Run
        private string bestGenome;
        private double bestRating = 0;

        // Constructor
        public GeneticAlgorithm(OpenTK.GLControl glcontrol, TextBox textbox, System.Windows.Forms.ProgressBar status)
        {
            this.status = status;
            this.textbox = textbox;
            this.glcontrol = glcontrol;
        }

        // Main Method of the GA
        //public bool gaMain(BackgroundWorker worker, DoWorkEventArgs e)
        public bool gaMain()
        {
            status.Value = generationCount / maxGenerationCount;
            population = new Population[populationSize];

            textbox.Text = "0";
            initialize();

            if (Variables.popDebugging)
                maxGenerationCount = 5;

            while (generationCount < maxGenerationCount)
            {
                // Current generation
                generationCount++;
                textbox.Text = generationCount.ToString();

                // Copies over the population to oldPopulation so the current one can be freshly populated.

                oldPopulation = new Population[populationSize];
                clone();
                population = new Population[populationSize];

                // Runs all parts of the GA

                // Only run one of the available selection functions:
                rouletteWheelSelection();
                //selection();

                // Only run one of the available crossover functions:
                //singleBitCrossover();
                eightBitCrossover();
                //twoFixedPointCrossover();

                mutation();
                evaluation();

                // Reports progress. Only updates at the end for some reason.
                status.Value = (generationCount / maxGenerationCount) * 100;
                
                // Asks if you want to see the current Population if Population Debugging is activated
                if (Variables.popDebugging)
                    output();
            }
            return true;
        }

        // Copies all Elements from population to oldPopulation
        public void clone()
        {
            for (int i = 0; i < populationSize; i++)
            {
                oldPopulation[i] = new Population(population[i].Path, population[i].Genome, population[i].Rating, population[i].Mutated, population[i].Selected);
            }
        }

        // This function opens a new window containing the current population and an option to save all populations to a text file
        public void output()
        {
            Variables.paused = true;
            string s = "";
            for (int i = 0; i < populationSize; i++)
            {
                s += i + " : " + "Selected: " + population[i].Selected + " , Mutated: " + population[i].Mutated + " , Rating: " + population[i].Rating
                    + " = Distances: " + population[i].Distances + " + Collisions: " + population[i].Collisions + System.Environment.NewLine;
            }
            Output output = new Output(s);
            output.Show();
            Application.DoEvents();

            // Deactivates after first Generation
           // Variables.popDebugging = false;
        }


        // This function uses two fixed points for two-point crossover. For better performance these two points may be made random and/or adjusted over time
        // For example, in higher generations they could be moved further to the back
        public void twoFixedPointCrossover()
        {
            int selectionSize = Convert.ToInt32(0.4 * populationSize);
            Genome parent1 = new Genome();
            Genome parent2 = new Genome();
            Genome child1 = new Genome();
            Genome child2 = new Genome();
            int r;
            int fixpoint1 = 4;
            int fixpoint2 = 15;

            for (int i = selectionSize; i < populationSize; i++)
            {
                // Randomly selects first parent
                r = Variables.getRandomInt(0, selectionSize);
                parent1 = oldPopulation[r].Genome;

                // Randomly selects second parent
                r = Variables.getRandomInt(0, selectionSize);
                parent2 = oldPopulation[r].Genome;

                for (int j = 0; j < 20; j++)
                {
                    // Case 1: fixpoint 1 to fixpoint 2, fixpoints exclusive
                    if (j > fixpoint1 && j < fixpoint2)
                    {
                        // Iterates over the eight-bit-blocks and adds all bits to the respective parent
                        for (int k = j * 8; k < j * 8 + 8; k++)
                        {
                            child1.Genome1.Set(k, parent1.Genome1.Get(k));
                            child2.Genome1.Set(k, parent2.Genome1.Get(k));
                        }
                    }
                    // Case 2: Before fixpoint 1 and after fixpoint 2, fixpoints inclusive
                    else
                    {
                        // Iterates over the eight-bit-blocks and adds all bits to the respective parent
                        for (int k = j * 8; k < j * 8 + 8; k++)
                        {
                            child1.Genome1.Set(k, parent2.Genome1.Get(k));
                            child2.Genome1.Set(k, parent1.Genome1.Get(k));
                        }
                    }
                }

                Genome.genomeToPath(child1);
                population[i] = new Population(Variables.path, child1, 0, false, false);

                // Counts up since we are adding 2 children per iteration, not just one
                i++;

                // If we are not yet at maximum (which could happen due to double->int conversion) we add the second child too
                if (i < populationSize)
                {
                    Genome.genomeToPath(child2);
                    population[i] = new Population(Variables.path, child2, 0, false, false);
                }
            }
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

                for (int j = 0; j < 20; j++)
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

                Genome.genomeToPath(child1);
                population[i] = new Population(Variables.path, child1, 0, false, false);

                // Counts up since we are adding 2 children per iteration, not just one
                i++;

                // If we are not yet at maximum (which could happen due to double->int conversion) we add the second child too
                if (i < populationSize)
                {
                    Genome.genomeToPath(child2);
                    population[i] = new Population(Variables.path, child2, 0, false, false);
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

                // Adds the genome and its corresponding path to the population at position i. Also sets Selected to false.
                Genome.genomeToPath(child1);
                population[i] = new Population(Variables.path, child1, 0, false, false);

                // Counts up since we are adding 2 children per iteration, not just one
                i++;

                // If we are not yet at maximum (which could happen due to double->int conversion) we add the second child too
                if (i < populationSize)
                {
                    Genome.genomeToPath(child2);
                    population[i] = new Population(Variables.path, child2, 0, false, false);
                }
            }
        }

        public void rouletteWheelSelection2()
        {
            double totalFitness = 0;

            // New Population consists of 40% Selection
            int selectionSize = Convert.ToInt32(0.4 * populationSize);
            
            // Calculates toal Fitness of the old population
            for (int i = 0; i < populationSize; i++)
            {
                totalFitness += oldPopulation[i].Rating;
            }

            // Normalizes all fitness values
            for (int i = 0; i < populationSize; i++)
            {
                oldPopulation[i].Rating = oldPopulation[i].Rating / totalFitness;
            }

            Population[] tempPopulation = new Population[populationSize];
            double j;
            int d;

            // Sorts oldPopulation into temppOpulation by descending Fitness Rating
            for (int l = 0; l < populationSize; l++)
            {
                j = 0;
                d = 0;

                // Finds the member in oldPopulation with the highest rating
                for (int i = 0; i < populationSize; i++)
                {
                    if (oldPopulation[i].Rating > j)
                    {
                        j = oldPopulation[i].Rating;
                        d = i;
                    }
                }

                // oldPopulation[d], which is the member with the highest rating, goes to position i
                tempPopulation[l] = new Population(oldPopulation[d].Path, oldPopulation[d].Genome, oldPopulation[d].Rating, false, true);

                // Sets the current oldPopulation Rating to 0 so it is not selected again
                oldPopulation[d].Rating = 0;
            }

            double acc = 0;

            // Calculates the accumulated rating for every position so every member has it's own Rating + all previous ones as it's rating
            for (int i = 0; i < populationSize; i++)
            {
                acc += tempPopulation[i].Rating;
                tempPopulation[i].Rating = acc;
            }

            double r;

            for (int i = 0; i < selectionSize; i++)
            {
                r = Variables.getRandomNumber(0, 1);
                d = 0;

                while (tempPopulation[d].Rating <= r)
                    d++;

                population[i] = new Population(tempPopulation[d].Path, tempPopulation[d].Genome, tempPopulation[d].Rating, false, true);
            }
        }

        public void selection()
        {
            // New Population consists of 40% Selection
            int selectionSize = Convert.ToInt32(0.4 * populationSize);
            int d;

            // Iterates over the new population until selectionSize is met
            for (int i = 0; i < selectionSize; i++)
            {
                // Stores the highest rating
                d = 0;

                // Iterates over the old population, looking for the highest rating
                for (int j = 0; j < populationSize; j++)
                {
                    if (oldPopulation[j].Rating > oldPopulation[d].Rating)
                        d = j;
                }

                // Takes the path with the highest rating from old population and sets Selected/Mutated
                population[i] = new Population(oldPopulation[d].Path, oldPopulation[d].Genome, oldPopulation[d].Rating, false, true);

                // Sets the Rating of the selected path to 0 so it is not selected again
                oldPopulation[d].Rating = 0;
            }
        }

        public void rouletteWheelSelection()
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
                        c += oldPopulation[j].Rating;
                        j++;
                } while (c < r);

                // Selects j - 1 (since we did j++ after fulfilling the condition) from the oldPopulation and adds it to the new one at i
                population[i] = new Population(oldPopulation[j - 1].Path, oldPopulation[j - 1].Genome, oldPopulation[j - 1].Rating, false, true);
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
                        population[i].Mutated = true;
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

                if (Variables.popDebugging)
                {
                    population[i].Collisions = Variables.debugCollisions;
                    population[i].Distances = Variables.debugDistance;
                }

                // Writes the path to the global Variable for drawing
                Variables.path = population[i].Path;

                //if (population[i].Rating > bestRating)
                //{
                //    bestRating = population[i].Rating;
                //    bestGenome = population[i].Genome.ToString();
                //}

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
