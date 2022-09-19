

#include <vector>
#include "Vector3D.h"

template<class T>
void swap(T& value1, T& value2)
{
	T temp;
	temp = value1;
	value1 = value2;
	value2 = temp;
}

//struct Vector3D
//{
//	Vector3D() : x(0), y(0), z(0) {}
//	Vector3D(float val) : x(val), y(val), z(val) {}
//
//	friend Vector3D operator-(Vector3D& V1, Vector3D& V2);
//
//	float x;
//	float y;
//	float z;
//};
//
//// Overator overloading function definition
//Vector3D operator-(Vector3D& V1, Vector3D& V2)
//{
//	Vector3D V;
//
//	V.x = V1.x - V2.x;
//	V.y = V1.y - V2.y;
//	V.z = V1.z - V2.z;
//
//	return V;
//}

// This function returns dot product of two vector arrays
double dot_product(Vector3D v1, Vector3D v2)
{
	return (v1.m_fX * v2.m_fX + v1.m_fY * v2.m_fY + v1.m_fZ * v2.m_fZ);
}

class Sphere 
{
	public:

		Sphere() 
		{
			id = 0;
			center = Vector3D(0);
			radius = 1.f;
		}

		Sphere(unsigned int _id, Vector3D _center, float _radius) : 
			id(_id), center(_center), radius(_radius) { }

		unsigned int id;
		Vector3D center;
		float radius;
};

bool point_vs_sphere_3d(const Vector3D& point, const Sphere& sphere)
{
	// Expensive operation
	float distance = sqrt(
		(point.m_fX - sphere.center.m_fX) * (point.m_fX - sphere.center.m_fX) +
		(point.m_fY - sphere.center.m_fY) * (point.m_fY - sphere.center.m_fY) +
		(point.m_fZ - sphere.center.m_fZ) * (point.m_fZ - sphere.center.m_fZ));

	return (distance <= sphere.radius);
}

double distance_between_sphere_centers_3d(const Sphere& sphere1, const Sphere& sphere2)
{
	// Expensive operation
	//float distance_between_centers_3D_1 = sqrt(
	//	(sphere1.center.m_fX - sphere2.center.m_fX) * (sphere1.center.m_fX - sphere2.center.m_fX) +
	//	(sphere1.center.m_fY - sphere2.center.m_fY) * (sphere1.center.m_fY - sphere2.center.m_fY) +
	//	(sphere1.center.m_fZ - sphere2.center.m_fZ) * (sphere1.center.m_fZ - sphere2.center.m_fZ));

	double distance_between_centers_3D_2 = hypot(hypot(sphere1.center.m_fX - sphere2.center.m_fX,
		sphere1.center.m_fY - sphere2.center.m_fY), sphere1.center.m_fZ - sphere2.center.m_fZ);

	return distance_between_centers_3D_2;
}

// This function calculates the distance between the centers of the spheres and compares it to the sum of their radii. 
// If this distance between the centers of the spheres is less than the sum of their radii, 
// then the spheres are overlapping. If it is the same, then the spheres are just touching.
bool sphere_vs_sphere_3d_1(const Sphere* sphere1_ptr, const Sphere* sphere2_ptr)
{
	if ((sphere1_ptr == nullptr) || (sphere2_ptr == nullptr))
	{
		throw ("null exception");
	}

	// Expensive operation
	double distance = sqrt(
		(sphere1_ptr->center.m_fX - sphere2_ptr->center.m_fX) * (sphere1_ptr->center.m_fX - sphere2_ptr->center.m_fX) +
		(sphere1_ptr->center.m_fY - sphere2_ptr->center.m_fY) * (sphere1_ptr->center.m_fY - sphere2_ptr->center.m_fY) +
		(sphere1_ptr->center.m_fZ - sphere2_ptr->center.m_fZ) * (sphere1_ptr->center.m_fZ - sphere2_ptr->center.m_fZ));

	// If the distance between the centers of the spheres is less than or equal to the sum of their radii then there is a collision
	return (distance <= (sphere1_ptr->radius + sphere2_ptr->radius));
}

// Collisions between spheres are very simple and easy to perform.
// An advantage that spheres have over things like AABBs (Axis - Aligned Bounding Boxes) is that 
// it does not matter if the object rotates, the sphere will remain the same.

// We need to calculate the distance between the centers of the spheres and compare it to the sum of their radii. 
// If this distance is less than the sum of their radii, then the spheres are overlapping. 
// If it is the same, then the spheres are just touching.

// To get the distance between the centers of the sphere, we need to create a vector between their centers.

// We then calculate the length of that vector against the sum of the radii.

// However, a more efficient way to do this would be the following:

// The dot product of a vector with itself equals the squared length of that vector.
// So, we can just calculate the squared length of our vector against the square of the sum of the radii, 
// that way we don’t need to calculate the length of the vector, which is an expensive operation!

// The dot product of a vector with itself equals the squared length of that vector. 
// So, we can just calculate the squared length of out vector against the square of the sum of the radii, 
// that way we do not need to calculate the length of the vector, which is an expensive operation.
bool sphere_vs_sphere_3d_2(const Sphere& sphere1, const Sphere& sphere2)
{
	// Calculate the squared distance between the centers of the spheres
	// ---------------------------------------------------------------------
	//double d[] = { abs(sphere1.center.m_fX - sphere2.center.m_fX), 
	//	abs(sphere1.center.m_fY - sphere2.center.m_fY), 
	//	abs(sphere1.center.m_fZ - sphere2.center.m_fZ) };

	//if (d[0] < d[1]) 
	//	swap(d[0], d[1]);

	//if (d[0] < d[2]) 
	//	swap(d[0], d[2]);

	//double distance_between_two_vectors_3D_1 = d[0] * sqrt(1.0 + d[1] / d[0] + d[2] / d[0]);

	// Calculate the squared distance between the centers of the spheres
	// The hypot function returns the hypotenuse of a right-angled triangle whose legs are x and y.
	// It returns what would be the square root of the sum of the squares of x and y (as per the Pythagorean theorem), 
	// but without incurring in undue overflow or underflow of intermediate values.
	double distance_between_two_vectors_3D = hypot(hypot(sphere1.center.m_fX - sphere2.center.m_fX, 
		sphere1.center.m_fY - sphere2.center.m_fY), sphere1.center.m_fZ - sphere2.center.m_fZ);

	double distance_squared(distance_between_two_vectors_3D * distance_between_two_vectors_3D);
	// ---------------------------------------------------------------------

	// Calculate the squared sum of both radii
	double radii_sum_squared(sphere1.radius + sphere2.radius);
	radii_sum_squared *= radii_sum_squared;

	// Check for collision
	// If the distance squared is less than or equal to the square sum of the radii, then there is a collision
	bool ret_val = false;
	if (distance_squared <= radii_sum_squared)
		ret_val = true;

	return ret_val;
}


// The center of mass is a position defined relative to an object or system of objects. 
// It is the average position of all the parts of the system, weighted according to their masses.
// For simple rigid objects with uniform density, the center of mass is located at the centroid. 
// For example, the center of mass of a uniform disc shape would be at its center. 
// Sometimes the center of mass doesn't fall anywhere on the object. 
// The center of mass of a ring for example is located at its center, where there isn't any material.
// For more complicated shapes, we need a more general mathematical definition of the center of mass. 
// It is the unique position at which the weighted position vectors of all the parts of a system sum up to zero.
// 
// The center of mass is a point in a system that responds to external forces as if the total mass of the system were concentrated at this point.
// The center of mass can be calculated by taking the masses you are trying to find the center of mass between and multiplying them by their positions.
// Then, you add these together and divide that by the sum of all the individual masses.
// COM = (sphere1.m * sphere1.r + sphere2.m * sphere2.r) / (sphere1.m * sphere2.m)

// Consider two particles with masses m1 and m2, positions x1 and x2, and velocities v1 and v2 colliding with each other.
// We merge the two particles based on an inelastic collision formulation, such that the total mass, position and velocity of the meta-particle become:
// m12 = m1 + m2
// x12 = (m1 * x1 + m2 * x2) / m12
// v12 = (m1 * v1 + m2 * v2) / m12
// While this merging operation conserves momentum, it does not conserve kinetic energy, because it is based on inelastic collision principles.

// The distance of centre of mass from any particle of the system is inversly proportional to the mass. That is, m1 < m2 => r2 < r1
// Xcm = (m1 * x1 + m2 * x2) / (m1 + m2)
// Distance of centre of mass from the position of particle of mass m1 and from the position of particle of mass m2.
// d = r1 + r2
// r1 = (m2 * d) / (m1 + m2)
// r2 = (m1 * d) / (m1 + m2)

// A = (x1, y1, z1)
// B = (x2, y2, z2)
// AB = (B - A) = [(x2 - x1), (y2 - y1), (z2 - z1)]
// AB = (B - A) = [(B.X - A.X), (B.Y - A.Y), (B.Z - A.Z)]

// Vector3D A = new Vector3D { X = 0, Y = 0, Z = 0 };
// Vector3D B = new Vector3D { X = 1, Y = 1, Z = 1 };
// distance_to_adjust = to be calculated
//
//Vector3D new_coordinate = new Vector3D {
//										A.X + ((B.X - A.X) * distance_to_adjust),
//										A.Y + ((B.Y - A.Y) * distance_to_adjust),
//										A.Z + ((B.Z - A.Z) * distance_to_adjust)
//}
// Changes in distance always need a reference point. In the above example, we assumed A. 
// That is why it appears as the first portion of each new_coordinate parameter initialization.

// A normalized Vector3D is a re-scaled vector of length of 1. It maintains its direction, but its magnitude becomes 1

// Divide each component by the length of the vector:
// length = sqrt(x^2 + y^2 + z^2)
// The normalized vector is:
// v = (x / length, y / length, z / length)

// Vector3D new_coordinate = A + ((B - A).Normalize() * distance_to_adjust); //move to origin, normalize, scale and move back

// Cross Product: A x B
// The cross product of two 3D vectors is another vector in the same 3D vector space.
// Since the result is a vector, we must specify both the length and the direction of the resulting vector: 
// length(A x B) = | A x B | = | A | | B | sin (theta)

// The cross product of any two vectors is a vector that is perpendicular to the two vectors. It has both magnitude and direction. 
// The magnitude of the resultant vector is equal to the parallelogram, whose side lengths are equal to the magnitude of the two given vectors.

// The cross product is mostly used to determine the vector, which is perpendicular to the plane surface spanned by two vectors, 
// whereas the dot product is used to find the angle between two vectors or the length of the vector. 

// The dot product, or inner product, of two vectors, is the sum of the products of corresponding components. 
// Equivalently, it is the product of their magnitudes, times the cosine of the angle between them. 
// The dot product of a vector with itself is the square of its magnitude.

// The difference between the dot product and the cross product of two vectors is that the result of the dot product is a scalar quantity, 
// whereas the result of the cross product is a vector quantity. The result is a scalar quantity, so it has only magnitude but no direction.

// https://www.youtube.com/watch?v=LPzyNOHY3A4

int main()
{
	std::vector<Sphere> spheres;

	for (auto& sphere : spheres)
	{
		for (auto& target : spheres)
		{
			if (sphere.id != target.id)
			{
				// Perform collision detection action

				//bool collision_detected = sphere_vs_sphere_3d_1(&sphere, &target);	// Expensive
				bool collision_detected = sphere_vs_sphere_3d_2(sphere, target);		// Optimized for performance

				if (collision_detected == true)
				{
					double distance = distance_between_sphere_centers_3d(sphere, target);

					double overlap = 0.5f * (distance - sphere.radius - sphere.radius);

					// To resolve the static collision completely ignore all laws of physics and displace 
					// the spheres so they do not overlap by altering the spheres' positins directly

					// Displace spheres in opposite directions 

					sphere.center.m_fX -= overlap * (sphere.center.m_fX - target.center.m_fX) / distance;
					sphere.center.m_fY -= overlap * (sphere.center.m_fY - target.center.m_fY) / distance;
					sphere.center.m_fZ -= overlap * (sphere.center.m_fZ - target.center.m_fZ) / distance;

					target.center.m_fX += overlap * (sphere.center.m_fX - target.center.m_fX) / distance;
					target.center.m_fY += overlap * (sphere.center.m_fY - target.center.m_fY) / distance;
					target.center.m_fZ += overlap * (sphere.center.m_fZ - target.center.m_fZ) / distance;
				}
			}
		}
	}
}

// Once it has been determined that the spheres have collided, resolve the static collision
// One sphere cannot exist in another sphere
// Need to displace the spheres away from each other by half the distance they overlap
// This displacement has a direction. 
// Normalize the distance vector between the spheres and use it to determine the direction of the displacement
// Normilized vector represents the direction


