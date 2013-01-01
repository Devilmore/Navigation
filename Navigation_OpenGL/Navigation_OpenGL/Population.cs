using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL
{
    public class Population
    {
        private LinkedList<EZPathFollowing.PathPart> m_path = new LinkedList<EZPathFollowing.PathPart>();

        public LinkedList<EZPathFollowing.PathPart> Path
        {
            get { return m_path; }
            set { m_path = value; }
        }

        private Genome m_genome = new Genome();

        public Genome Genome
        {
            get { return m_genome; }
            set { m_genome = value; }
        }

        private double m_rating;

        public double Rating
        {
            get { return m_rating; }
            set { m_rating = value; }
        }

        private bool m_mutated;

        public bool Mutated
        {
            get { return m_mutated; }
            set { m_mutated = value; }
        }

        private bool m_selected;

        public bool Selected
        {
            get { return m_selected; }
            set { m_selected = value; }
        }

        private double m_collisions;

        public double Collisions
        {
            get { return m_collisions; }
            set { m_collisions = value; }
        }

        private double m_distances;

        public double Distances
        {
            get { return m_distances; }
            set { m_distances = value; }
        }

        public Population()
        {
        }

        public Population(LinkedList<EZPathFollowing.PathPart> path, Genome genome, double rating)
        {
            m_path = path;
            m_genome = genome;
            m_rating = rating;
        }

        public Population(LinkedList<EZPathFollowing.PathPart> path, Genome genome, double rating, bool mutated, bool selected)
        {
            m_path = path;
            m_genome = genome;
            m_rating = rating;
            m_selected = selected;
            m_mutated = mutated;
        }

        public Population(LinkedList<EZPathFollowing.PathPart> path, Genome genome, double rating, bool mutated, bool selected, double distances, double collisions)
        {
            m_path = path;
            m_genome = genome;
            m_rating = rating;
            m_selected = selected;
            m_mutated = mutated;
            m_collisions = collisions;
            m_distances = distances;
        }


    }
}
