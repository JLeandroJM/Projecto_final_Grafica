#ifndef VECTORES_H
#define VECTORES_H

#include <cmath>

  static const int MAX_NUM_VERTICES = 1000000; 
	static const int MAX_NUM_EDGES = 20000000; 
	static const double EPS = 1e-8;
  static const double INF = 123456789;

class Vec3d
{
	
public:
	Vec3d(double X = 0 , double Y = 0 , double Z = 0 ) : x( X ) , y( Y ) , z( Z ) {};
	~Vec3d(void);
	double x,y,z;
    
	friend Vec3d operator - ( const Vec3d& );
	friend Vec3d operator + ( const Vec3d& , const Vec3d& );
	friend Vec3d operator - ( const Vec3d& , const Vec3d& );
	friend Vec3d operator * ( const Vec3d& , const Vec3d& );
	friend Vec3d operator / ( const Vec3d& , const Vec3d& );
	friend Vec3d operator + ( const Vec3d& , const double& );
	friend Vec3d operator - ( const Vec3d& , const double& );
	friend Vec3d operator * ( const Vec3d& , const double& );
	friend Vec3d operator / ( const Vec3d& , const double& );

	Vec3d getUnitVectorOfThis();
	Vec3d getVerticalVectorCrossed001();
	Vec3d getCross(const Vec3d&);
	double getDot(const Vec3d&);
};



class Vector4
{
public:
	double v[5];
	Vector4(double X = 0, double Y = 0, double Z = 0, double W = -99){
		v[0] = X; v[1] = Y; v[2] = Z; v[3] = W;
	}
	~Vector4(void);
	friend Vector4 operator + (const Vector4&, const Vector4&);
};



#endif

