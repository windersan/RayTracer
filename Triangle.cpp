#include "Triangle.h"
#include "TriangleMesh.h"
#include "Ray.h"


Triangle::Triangle(TriangleMesh * m, unsigned int i) :
    m_mesh(m), m_index(i)
{

}


Triangle::~Triangle()
{

}


void
Triangle::renderGL()
{
    TriangleMesh::TupleI3 ti3 = m_mesh->vIndices()[m_index];
    const Vector3 & v0 = m_mesh->vertices()[ti3.x]; //vertex a of triangle
    const Vector3 & v1 = m_mesh->vertices()[ti3.y]; //vertex b of triangle
    const Vector3 & v2 = m_mesh->vertices()[ti3.z]; //vertex c of triangle

    glBegin(GL_TRIANGLES);
        glVertex3f(v0.x, v0.y, v0.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
    glEnd();
}



bool
Triangle::intersect(HitInfo& result, const Ray& r, float tMin, float tMax)
{
	const Vector3 toO = ray.o - m_center;

	const float a = ray.d.length2();
	const float b = dot(2 * ray.d, toO);
	const float c = toO.length2() - m_radius*m_radius;

	const float discrim = b*b - 4.0f*a*c;

	if (discrim < 0)
		return false;   // quadratic equation would yield imaginary numbers

	const float sqrt_discrim = sqrt(discrim);

	// solve the quadratic equation
	const float t[2] = { (-b - sqrt_discrim) / (2.0f*a), (-b + sqrt_discrim) / (2.0f*a) };

	// since we know that discrim >= 0, t[0] < t{1]
	// return the t closest to us that is within range
	if ((t[0] > tMin) && (t[0] < tMax))
	{
		result.t = t[0];
	}
	else if ((t[1] > tMin) && (t[1] < tMax))
	{
		result.t = t[1];
	}
	else
	{
		// neither of the solutions are in the required range
		return false;
	}

	result.P = ray.o + result.t*ray.d;
	result.N = (result.P - m_center);
	result.N.normalize();
	result.material = this->m_material;

	return true;
}


bool
Triangle::intersect(HitInfo& result, const Ray& r, float tMin, float tMax)
{
	float tvalue;
	float A = v0.x() - v1.x();
	float B = v0.y() - v1.y();
	float C = v0.z() - v1.z();
	float D = v0.x() - v2.x();
	float E = v0.y() - v2.y();
	float F = v0.z() - v2.z();
	float G =
		float H =
		float J =
		float K =
		float L =

		float det1 = E*I - H*F;
	float det2 = G*F - D*I;
	float det3 = D*H - E*G;

	float dnom = (A*det1 + B*det2 + C*det3);
	float beta = (J*det1 + K*det1 + L*det3);

	if (beta <= 0.0f || beta >= 1.0f) return false;

	float det4 = A*K - J*B;
	float det5 = J*C - A*L;
	float det6 = B*L - K*C;

	float gamma = (I*det4 + H*det5 + G*det6) / dnom;
	if (gamma < 0.0f || beta + gamma >= 1.0f)return false;

	tvalue = -(F*det4 + E*det5 + D*det6) / dnom;
	if (tvalue > tmin && tvalue < tmax)
	{
		result.t = tvalue;
		result.N = cross((v1 - v0), (v2 - v0));
		result.N.normalize();
		result.material = this->m_material;
		return true;

	}




    return false;
}
