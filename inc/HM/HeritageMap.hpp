#ifndef HERITAGEMAP_HPP
#define HERITAGEMAP_HPP

#include "PhaseSpace.hpp"

namespace vfps
{

class HeritageMap
{
protected:
	typedef struct {
		unsigned int index;
		interpol_t weight;
	} hi;

public:
	/**
	 * @brief The INTERPOL_TYPE enum
	 */
	enum INTERPOL_TYPE
	{
		NONE=1,
		LINEAR=2,
		QUADRATIC=3,
		CUBIC=4
	};
	static constexpr INTERPOL_TYPE it = INTERPOL_TYPE::CUBIC;

public:
	HeritageMap(PhaseSpace* in, PhaseSpace* out, size_t xsize, size_t ysize);

	~HeritageMap();

	/**
	 * @brief apply
	 *
	 * @todo get rid of copying from/to host RAM every step
	 */
	void apply();

protected:
	std::array<hi,it*it>** _heritage_map;
	std::array<hi,it*it>* const _heritage_map1D;

	const size_t _size;
	const size_t _xsize;
	const size_t _ysize;

	#ifdef INOVESA_USE_CL
	cl::Buffer _heritage_map1D_buf;
	cl::Kernel applyHM;

	/**
	 * @brief __initOpenCL initialize OpenCL
	 * (use after _heritage_map1D has been filled)
	 */
	void __initOpenCL();
	#else
	meshdata_t* _data_in;
	meshdata_t* _data_out;
	#endif // INOVESA_USE_CL

	PhaseSpace* _in;
	PhaseSpace* _out;
};

}

#endif // HERITAGEMAP_HPP