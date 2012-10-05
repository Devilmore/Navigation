using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tao.OpenGl;

namespace Navigation_OpenGL.EZPathFollowing
{
    public class PathPart
    {
        protected bool m_initialized;
        protected Point2D m_startpoint;
        protected Point2D m_endpoint;
        protected bool m_reverse;
        protected double m_pathlength;
        protected double m_speed;

        // Empty Constructor
        public PathPart()
        {
            this.m_pathlength = 0.0;
            this.m_speed = 0.0;
            this.m_initialized = false;
        }

        // Non-Empty Constructor delegates to setAttribute function after setting the Empty-Constructor values
        public PathPart(Point2D startpoint, Point2D endpoint, bool reverse, double speed)
        {
            this.m_pathlength = 0.0;
            this.m_initialized = false;
            setAttributes(startpoint, endpoint, reverse, speed);
        }

        // Returns the length of the path
        public double pathlength()
        {
            return m_pathlength;
        }

        // Returns the end of the path
        public Point2D getEnd()
        {
            return m_endpoint;
        }

        //// Returns the Orientation at the end of the path
        //public double endOrientation()
        //{
        //    return orientation(pathlength());
        //}

        //// Returns the Orientation at the beginning of the path
        //public double startOrientation()
        //{
        //    return orientation(0.0);
        //}

        public virtual bool move(Point2D difference)
        {
            m_startpoint = Point2D.add(m_startpoint, difference);
            m_endpoint = Point2D.add(m_endpoint, difference);
            return true;
        }

        public virtual bool rotate(Point2D mPoint, double beta)
        {
            m_startpoint = Numerics.rotate(m_startpoint, mPoint, beta);
            m_endpoint = Numerics.rotate(m_endpoint, mPoint, beta);
            return true;
        }

        public virtual void setAttributes(Point2D startpoint, Point2D endpoint, bool reverse, double speed)
        {
            if (!m_initialized)
            {
                m_startpoint = startpoint;
                m_endpoint = endpoint;
                m_reverse = reverse;
                m_speed = speed;
            }
        }

        public virtual void draw()
        {
        }

        // Method Stubs. Implement Later!
        public static Point2D angleWrapper(double angle)
        {
            return new Point2D(0, 0);
            throw new NotImplementedException();
        }
    }
}
