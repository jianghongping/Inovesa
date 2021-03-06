// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright (c) Patrik Schönfeldt
 * Copyright (c) Karlsruhe Institute of Technology
 */

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "CL/OpenCLHandler.hpp"
#include "defines.hpp"
#include "PS/Ruler.hpp"

namespace vfps
{

class Impedance
{
public:
    Impedance() = delete;

    /**
     * @brief Impedance copy constructor
     * @param other
     */
    Impedance(const Impedance &other);

    /**
     * @brief Impedance basic constructor that initializes everything
     * @param axis
     * @param z
     */
    Impedance(Ruler<frequency_t> &&axis
             , const std::vector<impedance_t> &z
             , oclhptr_t oclh = nullptr
             );


    /**
     * @brief Impedance
     * @param z
     * @param f_max
     *
     * Note that we will use this for DFT,
     * so n>z.size()/2 is defined to be equivalent to n<0.
     */
    Impedance( const std::vector<impedance_t>& z
             , const frequency_t f_max
             , oclhptr_t oclh = nullptr
             );


    Impedance( const size_t nfreqs
             , const frequency_t f_max
             , oclhptr_t oclh = nullptr
             );


    /**
     * @brief Impedance
     * @param name of datafile in the format "n Re(Z) Im(Z)",
     *        where n=f/f_rev is the revolution harmonic
     */
    Impedance( std::string datafile, double f_max, oclhptr_t oclh = nullptr);

    inline const impedance_t* data() const
        { return _data.data(); }

    inline const std::vector<impedance_t>& impedance() const
        { return _data; }

    inline const impedance_t operator[](size_t n) const
        { return _data[n]; }

    inline size_t nFreqs() const
        { return _nfreqs; }

    inline size_t size() const
        { return _data.size(); }

    inline const Ruler<frequency_t>* getRuler() const
        { return &_axis; }

    #if INOVESA_USE_OPENCL == 1
    cl::Buffer data_buf;
    #endif // INOVESA_USE_OPENCL

    static constexpr double factor4Ohms = 1;

    /// vacuum impedance (in Ohms)
    static constexpr double Z0 = 376.730313461;

public:
    /**
     * @brief operator = unifying assignment operator
     * @param other
     * @return
     */
    Impedance& operator=(Impedance other);

    /**
     * @brief operator +=
     * @param rhs
     * @return
     *
     * assumes size() equals rhs.size()
     */
    Impedance& operator+=(const Impedance& rhs);

    void swap(Impedance& other);

private:
    size_t _nfreqs;

    const Ruler<frequency_t> _axis;

protected:
    std::vector<impedance_t> _data;

    #if INOVESA_USE_OPENCL == 1
    void syncCLMem();
    #endif // INOVESA_USE_OPENCL

    oclhptr_t _oclh;

private:
    static std::vector<impedance_t> readData(std::string fname);
};

/**
 * @brief operator +
 * @param lhs
 * @param rhs
 * @return
 *
 * As soon as a move constructor is available, it will make sence to add
 * overloads that can use these.
 */
inline Impedance operator+(const Impedance& lhs, const Impedance& rhs)
{
    auto rv = Impedance(lhs);
    return rv += rhs;
}

} // namespace vfps

