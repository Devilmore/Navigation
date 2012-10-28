using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tao.OpenGl;

namespace Navigation_OpenGL.EZPathFollowing
{
    class LinePathPart : PathPart
    {
        // Empty Constructor for Transformation. Requires setAttributes to be called afterwards
        public LinePathPart() : base()
        {
        }

        // Constructor for the Line
        public LinePathPart(Point2D startpoint, Point2D endpoint, bool reverse, double speed, double direction) 
            : base(startpoint, endpoint, reverse, speed, direction)
        {
        }

        public override double pathlength()
        {
            return Point2D.sub(m_startpoint, m_endpoint).length();
        }

        // setAttrobutes for LinePathParts
        public override void setAttributes(Point2D startpoint, Point2D endpoint, bool reverse, double speed, double direction)
        {
                //m_pathlength = Point2D.sub(startpoint, endpoint).length();
                m_startpoint = startpoint;
                m_endpoint = endpoint;
                m_reverse = reverse;
                m_speed = speed;
                m_direction = direction;
        }

        public override Point2D position(double d)
        {
            return Point2D.add(m_startpoint,Point2D.multiplyBy((Point2D.sub(m_endpoint,m_startpoint).normalize()),d));
        }

        // Projection 

        public override double referencePositionDefinitionValue(Point2D point)
        {
            Point2D directionalVector = new AngleWrapper(m_endpoint - m_startpoint).unitVector();
            return directionalVector.point(point - m_startpoint);
        }

        // Draws the LinePathPart
        public override void draw()
        {
            Gl.glBegin(Gl.GL_LINES);
            Gl.glVertex2d(m_startpoint.x, m_startpoint.y);
            Gl.glVertex2d(m_endpoint.x, m_endpoint.y);
            Gl.glEnd();
        }

        ////// Returns the orientation
        //public double orientation()
        //{
        //    if (!m_reverse)
        //        return new AngleWrapper(m_endpoint - m_startpoint).radian();
        //    else
        //        return new AngleWrapper(m_startpoint - m_endpoint).radian();
        //}

        // Returns the orentation for what I need it to do. Rename if the above function is needed.
        public override Point2D orientation()
        {
            return (m_endpoint - m_startpoint).normalize();
        }

        public override double orientationDouble()
        {
            return m_direction;
        }
    }
}
