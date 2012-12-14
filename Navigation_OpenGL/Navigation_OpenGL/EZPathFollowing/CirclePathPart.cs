using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenTK.Graphics.OpenGL;
using System.Drawing;

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

        public CirclePathPart(Point2D startpoint, Point2D endpoint, Point2D center, bool driveRight, bool reverse, double speed, double angle, double direction)
            : base(startpoint, endpoint, reverse, speed, direction)
        {
            setAttributes(startpoint, endpoint, center, driveRight, reverse, speed, angle, direction);
        }

        public void setAttributes(Point2D startpoint, Point2D endpoint, Point2D center, bool driveRight, bool reverse, double speed, double angle, double direction)
        {
            if (!m_initialized)
            {
                setAttributes(startpoint, endpoint, reverse, speed, direction);
                m_center = center;
                m_driveRight = driveRight;
                m_angle = angle;
                m_radius = Point2D.sub(m_center, m_startpoint).length();
                updateAngle(); //I saw no need to not simply give the angle with the remaining arguments. Fix if anything needs this
                m_initialized = true;
                m_direction = direction;
            }
        }

        public override double pathlength()
        {
            return m_driveRight == m_reverse
                ? (2 * Math.PI + m_angle) * m_radius
                : (2 * Math.PI - m_angle) * m_radius;
        }

        public override double getAngle()
        {
            return m_angle;
        }

        public override double getRadius()
        {
            return m_radius;
        }

        public override Point2D position(double d)
        {
            double angle = drivesInReverse() != drivesRight()
                ? startAngle() + d / radius()
                : startAngle() - d / radius();
            //while (angle < -Math.PI)
            //    angle += 2 * Math.PI;
            //while (angle > Math.PI)
            //    angle -= 2 * Math.PI;
            return Point2D.add(Point2D.multiplyBy(new Point2D(angle),radius()),center());
        }

        // Projection
        public override double referencePositionDefinitionValue(Point2D point)
        {
            if (point == m_center)
                // In this case no projection can happen
                return double.NaN;

            // Calculates the intersection point of the circle and the line between cneter and the given point
            Point2D intersection= new Point2D(0,0);
            double l = (point - m_center).length();
            intersection.x= m_center.x + (point.x - m_center.x)/l * m_radius;
            intersection.y = m_center.y + (point.y - m_center.y) / l * m_radius;
            // Calculates the absoulte angle of the line between center and the intersection point
            AngleWrapper intersectingAngle = new AngleWrapper(intersection - m_center);
            // Calculates the angle between the statpoint and the intersection point
            AngleWrapper angle = new AngleWrapper();
            angle = m_driveRight != m_reverse
                ? intersectingAngle - startAngle()
                : -intersectingAngle + startAngle();

            // Angle > 0.5*m_angle+PI give negative results
            if (angle.radian()>3*Math.PI/2)
                return (angle.radian() - 2 * Math.PI) * m_radius;
            else
                return angle.radian() * m_radius;
            
                
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


        public override double orientationDouble()
        {
            if (m_driveRight == true)
                return m_direction - m_angle;
            else
                return m_direction + m_angle;
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
            GL.Begin(BeginMode.Points);
            for (double i = 0; i <= pathlength(); i += 5)
            {
                Point2D p = position(i);
                GL.Vertex2(p.x, p.y);
            }
            GL.Vertex2(position(pathlength()).x, position(pathlength()).y);
            GL.End();
        }

        private double GetNumCircleSegments(double r)
        {
            return 10 * Math.Sqrt(r);
        }
    }
}
