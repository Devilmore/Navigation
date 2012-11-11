using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tao.OpenGl;

namespace Navigation_OpenGL.EZPathFollowing
{
    public abstract class PathPart
    {
        protected bool m_initialized;
        protected Point2D m_startpoint;
        protected Point2D m_endpoint;
        protected bool m_reverse;
        //protected double m_pathlength;
        protected double m_speed;
        protected double m_direction;

        public abstract double referencePositionDefinitionValue(Point2D point);
        public abstract Point2D position(double d);

        // Empty Constructor
        public PathPart()
        {
            //this.m_pathlength = 0.0;
            this.m_speed = 0.0;
            this.m_initialized = false;
        }

        // Non-Empty Constructor delegates to setAttribute function after setting the Empty-Constructor values
        public PathPart(Point2D startpoint, Point2D endpoint, bool reverse, double speed, double direction)
        {
            //this.m_pathlength = 0.0;
            this.m_initialized = false;
            setAttributes(startpoint, endpoint, reverse, speed, direction);
        }

        // Returns the length of the path
        public abstract double pathlength();
        
        // Returns the end of the path
        public Point2D getEnd()
        {
            return m_endpoint;
        }

        // Returns the end of the path
        public Point2D getStart()
        {
            return m_startpoint;
        }

        public double getDirection()
        {
            return m_direction;
        }

        public virtual Point2D orientation()
        {
            return new Point2D(0,0);
        }

        public virtual double orientationDouble()
        {
            return 0;
        }

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

        public virtual void setAttributes(Point2D startpoint, Point2D endpoint, bool reverse, double speed, double direction)
        {
            if (!m_initialized)
            {
                m_startpoint = startpoint;
                m_endpoint = endpoint;
                m_reverse = reverse;
                m_speed = speed;
                m_direction = direction;
            }
        }

        public virtual void draw()
        {
        }

        public virtual double getRadius()
        {
            return 0.0;
        }

        public virtual double getAngle()
        {
            return 0.0;
        }

        // Method Stubs. Implement Later!
        public static Point2D angleWrapper(double angle)
        {
            //return new Point2D(0, 0);
            throw new NotImplementedException();
        }
    }
}
