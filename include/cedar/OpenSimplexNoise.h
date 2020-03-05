//
// Created by masy on 28.02.20.
//

#ifndef CEDAR_OPENSIMPLEXNOISE_H
#define CEDAR_OPENSIMPLEXNOISE_H

#define STRETCH_CONSTANT_2D -0.211324865405187    //(1/Math.sqrt(2+1)-1)/2;
#define SQUISH_CONSTANT_2D 0.366025403784439      //(Math.sqrt(2+1)-1)/2;
#define STRETCH_CONSTANT_3D -1.0 / 6              //(1/Math.sqrt(3+1)-1)/3;
#define SQUISH_CONSTANT_3D 1.0 / 3                //(Math.sqrt(3+1)-1)/3;
#define STRETCH_CONSTANT_4D -0.138196601125011    //(1/Math.sqrt(4+1)-1)/4;
#define SQUISH_CONSTANT_4D 0.309016994374947      //(Math.sqrt(4+1)-1)/4;

#define NORM_CONSTANT_2D 47.0
#define NORM_CONSTANT_3D 103.0
#define NORM_CONSTANT_4D 30.0

#define DEFAULT_SEED 0L
#define PERMUTATION_LENGTH 256

/**
 * Base namespace for mathematical functions.
 */
namespace cedar::math
{
	/**
	 * OpenSimplex Noise in c++ based on Kurt Spencer's java implementation.
	 *
	 * <p>Original Header:<br>
	 * OpenSimplex Noise in Java.
	 * by Kurt Spencer
	 *
	 * v1.1 (October 5, 2014)
	 * - Added 2D and 4D implementations.
	 * - Proper gradient sets for all dimensions, from a
	 *   dimensionally-generalizable scheme with an actual
	 *   rhyme and reason behind it.
	 * - Removed default permutation array in favor of
	 *   default seed.
	 * - Changed seed-based constructor to be independent
	 *   of any particular randomization library, so results
	 *   will be the same when ported to other languages.</p>
	 */
	class OpenSimplexNoise
	{
	private:
		/**
		 * The length of the {@link #gradients2D} array.
		 */
		static const int gradients2DLength = 4 * 4;
		/**
		 * Gradients for 2D.
		 *
		 * <p>They approximate the directions to the vertices of an octagon from the center.</p>
		 */
		static constexpr signed char gradients2D[] = {
				5, 2, 2, 5,
				-5, 2, -2, 5,
				5, -2, 2, -5,
				-5, -2, -2, -5
		};
		/**
		 * The length of the {@link #gradients3D} array.
		 */
		static const int gradients3DLength = 9 * 8;
		/**
		 * Gradients for 3D.
		 *
		 * <p>They approximate the directions to the vertices of a rhombicuboctahedron from the center, skewed so that the triangular
		 * and square facets can be inscribed inside circles of the same radius.</p>
		 */
		static constexpr signed char gradients3D[] = {
				-11, 4, 4, -4, 11, 4, -4, 4, 11,
				11, 4, 4, 4, 11, 4, 4, 4, 11,
				-11, -4, 4, -4, -11, 4, -4, -4, 11,
				11, -4, 4, 4, -11, 4, 4, -4, 11,
				-11, 4, -4, -4, 11, -4, -4, 4, -11,
				11, 4, -4, 4, 11, -4, 4, 4, -11,
				-11, -4, -4, -4, -11, -4, -4, -4, -11,
				11, -4, -4, 4, -11, -4, 4, -4, -11
		};
		/**
		 * The length of the {@link #gradients4D} array.
		 */
		static const int gradients4DLength = 16 * 16;
		/**
		 * Gradients for 4D.
		 *
		 * <p>They approximate the directions to the vertices of a disprismatotesseractihexadecachoron from the center, skewed so
		 * that the tetrahedral and cubic facets can be inscribed inside spheres of the same radius.</p>
		 */
		static constexpr signed char gradients4D[] = {
				3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3,
				-3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3,
				3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3,
				-3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3,
				3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3,
				-3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3,
				3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3,
				-3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3,
				3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3,
				-3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3,
				3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3,
				-3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3,
				3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3,
				-3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3,
				3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3,
				-3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3
		};

		/**
		 * The permutation table of the open simplex noise.
		 */
		short *m_perm;
		/**
		 * The permutation table of the 3D open simplex noise.
		 */
		short *m_permGradIndex3D;

		/**
		 * Extrapolates the value defined by the current contribution.
		 *
		 * @param xsb X grid coordinate of the rhombus super-cell origin of the currently evaluated noise value.
		 * @param ysb Y grid coordinate of the rhombus super-cell origin of the currently evaluated noise value.
		 * @param dx X coordinate of the currently calculated contribution.
		 * @param dy Y coordinate of the currently calculated contribution.
		 * @return the extrapolated value.
		 */
		[[nodiscard]] double extrapolate(int xsb, int ysb, double dx, double dy) const;

		/**
		 * Extrapolates the value defined by the current contribution.
		 *
		 * @param xsb X simplectic honeycomb coordinate of the rhombo-hypercube super-cell origin of the currently evaluated noise value.
		 * @param ysb Y simplectic honeycomb coordinate of the rhombo-hypercube super-cell origin of the currently evaluated noise value.
		 * @param zsb Z simplectic honeycomb coordinate of the rhombo-hypercube super-cell origin of the currently evaluated noise value.
		 * @param dx X coordinate of the currently calculated contribution.
		 * @param dy Y coordinate of the currently calculated contribution.
		 * @param dz Z coordinate of the currently calculated contribution.
		 * @return the extrapolated value.
		 */
		[[nodiscard]] double extrapolate(int xsb, int ysb, int zsb, double dx, double dy, double dz) const;

		/**
		 * Extrapolates the value defined by the current contribution.
		 *
		 * @param xsb X grid coordinate of the rhombus super-cell origin of the currently evaluated noise value.
		 * @param ysb Y grid coordinate of the rhombus super-cell origin of the currently evaluated noise value.
		 * @param zsb Z grid coordinate of the rhombus super-cell origin of the currently evaluated noise value.
		 * @param wsb W grid coordinate of the rhombus super-cell origin of the currently evaluated noise value.
		 * @param dx X coordinate of the currently calculated contribution.
		 * @param dy Y coordinate of the currently calculated contribution.
		 * @param dz Z coordinate of the currently calculated contribution.
		 * @param wz Z coordinate of the currently calculated contribution.
		 * @return the extrapolated value.
		 */
		[[nodiscard]] double extrapolate(int xsb, int ysb, int zsb, int wsb, double dx, double dy, double dz, double dw) const;

	public:
		/**
		 * Creates a new open simplex noise generator with 0 as seed.
		 */
		OpenSimplexNoise();

		/**
		 * Creates a new open simplex noise generator with the given permutation table.
		 *
		 * @param perm The permutation table of the noise generator.
		 */
		explicit OpenSimplexNoise(short *perm);

		/**
		 * Creates a new open simplex noise generator with the given seed.
		 *
		 * @param seed The seed of the noise generator.
		 */
		explicit OpenSimplexNoise(long seed);

		/**
		 * Destroys the open simplex noise generator.
		 */
		~OpenSimplexNoise();

		/**
		 * Evaluates a noise value based on 2 coordinates.
		 *
		 * <p>Contrary to popular believe, the output range of this method is <b>not</b> ±1.
		 * The output range is ±½√n, where n is the number of dimensions. So this method will return
		 * values between -0.707106781 and +0.707106781.</p>
		 *
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 * @return the noise value at the given coordinates.
		 */
		[[nodiscard]] double eval(double x, double y) const;

		/**
		 * Evaluates a noise value based on 3 coordinates.
		 *
		 * <p>Contrary to popular believe, the output range of this method is <b>not</b> ±1.
		 * The output range is ±½√n, where n is the number of dimensions. So this method will return
		 * values between -0.866025404 and +0.866025404.</p>
		 *
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 * @param z The z coordinate.
		 * @return the noise value at the given coordinates.
		 */
		[[nodiscard]] double eval(double x, double y, double z) const;

		/**
		 * Evaluates a noise value based on 4 coordinates.
		 *
		 * <p>The output range is ±½√n, where n is the number of dimensions. So this method will return
		 * values between -1 and +1.</p>
		 *
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 * @param z The z coordinate.
		 * @return the noise value at the given coordinates.
		 */
		[[nodiscard]] double eval(double x, double y, double z, double w) const;
	};
}

#endif //CEDAR_OPENSIMPLEXNOISE_H
