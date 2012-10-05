using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tao.OpenGl;

namespace Navigation_OpenGL.EZPathFollowing
{
    class CirclePathPart : PathPart
    {
        double m_angle;
        double m_startangle;
        double m_endangle;
        double m_radius;
        bool m_driveRight;
        Point2D m_center;

        // Getter functions for later use

        public bool drivesRight()
        {
            return m_driveRight;
        }

        public bool drivesInReverse()
        {
            return m_reverse;
        }

        public double radius()
        {
            return m_radius;
        }

        public double startAngle()
        {
            return m_startangle;
        }

        public double endAngle()
        {
            return m_endangle;
        }

        public Point2D center()
        {
            return m_center;
        }

        public CirclePathPart()
            : base()
        {
        }

        public CirclePathPart(Point2D startpoint, Point2D endpoint, Point2D center, bool driveRight, bool reverse, double speed)
            : base(startpoint, endpoint, reverse, speed)
        {
            setAttributes(startpoint, endpoint, center, driveRight, reverse, speed);
        }

        public void setAttributes(Point2D startpoint, Point2D endpoint, Point2D center, bool driveRight, bool reverse, double speed)
        {
            if (!m_initialized)
            {
                setAttributes(startpoint, endpoint, reverse, speed);
                m_center = center;
                m_driveRight = driveRight;
                m_radius = Point2D.sub(m_center, m_startpoint).length();
                updateAngle();
                m_pathlength = m_radius * m_angle;
                m_initialized = true;
            }
        }

        public double getAngle()
        {
            return m_angle;
        }

        public Point2D position(double d)
        {
            double angle = drivesInReverse() == drivesRight()
                ? startAngle() + d / radius()
                : startAngle() - d / radius();
            return Point2D.add(Point2D.multiplyBy(angleWrapper(angle).normalize(),radius()),center());
        }

        // Projection
        public double wantedPositionDefinitionValue(Point2D point)
        {
            if (point == m_center)
                // In this case no projection can happen
                return double.NaN;

            // Calculates the intersection point of the circle and the line between cneter and the given point
            Point2D intersection = m_center + (point - m_center).normalize() * m_radius;
            // Calculates the absoulte angle of the line between center and the intersection point
            AngleWrapper intersectingAngle = new AngleWrapper(intersection - m_center);
            // Calculates the angle between the statpoint and the intersection point
            AngleWrapper angle = new AngleWrapper();
            angle = m_driveRight == m_reverse
                ? intersectingAngle - startAngle()
                : -intersectingAngle + startAngle();

            // Angle > 0.5*m_angle+PI give negative results
            if (angle.radian() <= 0.5 * m_angle + Math.PI)
                return angle.radian() * m_radius;
            else
                return (angle.radian() - 2 * Math.PI) * m_radius;
        }

        // Gives the orientation
        public double orientation(double d)
        {
            AngleWrapper angle = new AngleWrapper(startAngle());
            // Calculates the absolute angle
            angle += (m_driveRight == m_reverse)
                ? d / m_radius
                : -d / m_radius;
            // If in a left curve the orientation is perpencicular to the left and the other way around
            if (m_reverse)
                return angle.perpendicularRight().radian();
            else
                return angle.perpendicularLeft().radian();
        }

        public override bool move(Point2D difference)
        {
            base.move(difference);
            m_center = Point2D.add(m_center, difference);
            return true;
        }

        public override bool rotate(Point2D mPoint, double beta)
        {
            base.rotate(mPoint, beta);
            m_center = Numerics.rotate(m_center, mPoint, beta);
            updateAngle();
            return true;
        }

        // updates the start and endangles
        public void updateAngle()
        {
            m_endangle = new AngleWrapper(m_endpoint - m_center).radian();
            m_startangle = new AngleWrapper(m_startpoint - m_center).radian();
            m_angle = m_driveRight == m_reverse
                ? new AngleWrapper(endAngle() - startAngle()).radian()
                : new AngleWrapper(startAngle() - endAngle()).radian();
        }

        // Draws the CirclePathPart
        public override void draw()
        {
            const double DEG2RAD = Math.PI/180;

            // circles until it (almost) hits the starting point. Change for proper calculation later
            double i2 = 0;
            double degInRad2 = i2 * DEG2RAD;
            while (!Point2D.closeTo(new Point2D(m_center.x + Math.Cos(degInRad2) * m_radius, m_center.y + Math.Sin(degInRad2) * m_radius),m_startpoint))
            {
                i2++;
                degInRad2 = i2 * DEG2RAD;
            }

            // Draws from (about) starting point for the length of m_angle
            Gl.glBegin(Gl.GL_LINE_STRIP);
            for (double i = i2; i < m_angle + i2; i++)
            {
                double degInRad = i * DEG2RAD;
                Gl.glVertex2d(m_center.x + Math.Cos(degInRad) * m_radius, m_center.y + Math.Sin(degInRad) * m_radius);
            }
            Gl.glEnd();
          
        }

        // Draws an arc from with m_radius around m_center with m_startangle.
        // does not yet draw only a partial circle
        //public override void draw()
        //{
        //    double segments = GetNumCircleSegments(m_radius);
        //    //int real_segments = int(fabsf(d_angle) / (2 * Math.PI) * (float)segments) + 1;   or -1?
        //    int real_segments = (int)(m_angle / (2 * Math.PI) * (float)segments) + 1;

        //    double theta = m_angle / real_segments;
        //    double tangetial_factor = Math.Tan(theta);
        //    double radial_factor = 1 - Math.Cos(theta);
        //    double x = m_center.x + m_radius * Math.Cos(m_startangle);
        //    double y = m_center.y + m_radius * Math.Sin(m_startangle);
        //    Gl.glBegin(Gl.GL_LINE_STRIP);

        //    for(int ii = 0; ii < real_segments + 1; ii++)
        //        {
        //        Gl.glVertex2d(x, y);
   
        //        double tx = -(y - m_center.y);
        //        double ty = x - m_center.x;
	        
        //        x += tx * tangetial_factor;
        //        y += ty * tangetial_factor;
	        
        //        double rx = m_center.x - x;
        //        double ry = m_center.y - y;
	        
        //        x += rx * radial_factor;
        //        y += ry * radial_factor;
        //        }
        //        Gl.glEnd();
        //}

        private double GetNumCircleSegments(double r)
        {
            return 10 * Math.Sqrt(r);
        }
    }
}
