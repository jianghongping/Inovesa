/******************************************************************************/
/* Inovesa - Inovesa Numerical Optimized Vlasov-Equation Solver Application   */
/* Copyright (c) 2012-2016: Patrik Schönfeldt                                 */
/*                                                                            */
/* This file is part of Inovesa.                                              */
/* Inovesa is free software: you can redistribute it and/or modify            */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 3 of the License, or          */
/* (at your option) any later version.                                        */
/*                                                                            */
/* Inovesa is distributed in the hope that it will be useful,                 */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with Inovesa.  If not, see <http://www.gnu.org/licenses/>.           */
/******************************************************************************/

#ifndef OPENCLHANDLER_HPP
#define OPENCLHANDLER_HPP
#ifdef INOVESA_USE_CL

enum class clCopyDirection {
    cpu2dev,
    dev2cpu
};

#include <GL/glew.h>

#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_MINIMUM_OPENCL_VERSION 110
#define CL_HPP_TARGET_OPENCL_VERSION 120
#include "CL/local_cl.hpp"

#ifdef INOVESA_USE_CLFFT
#include <clFFT.h>
#endif // INOVESA_USE_CLFFT

#include <climits>
#include <iostream>

/**
 * @brief prepareCLEnvironment
 * @return true on successful initialization
 *
 * Picks the last available platform.
 * If several platforms are available,
 * AMD plattforms are prefered.
 *
 * @todo: update to recent OpenCL version
 *        (currently OpenCL 1.1 or 1.2 is  required)
 */
class OCLH
{
public:
    static void prepareCLEnvironment(bool glsharing, uint32_t device);

    static cl::Program prepareCLProg(std::string);

    static void teardownCLEnvironment();

    static void listCLDevices();

    static bool active;

    static cl::vector<cl::Platform> platforms;

    static cl::Context context;

    static cl::vector<cl::Device> devices;

    static cl_device_type devicetype;

    /**
     * @brief command queue for OpenCL
     */
    static cl::CommandQueue queue;

    static bool ogl_sharing;

private:
#ifdef INOVESA_USE_CLFFT
        static clfftSetupData fft_setup;
#endif // INOVESA_USE_CLFFT

    static const std::string custom_datatypes;

    static std::string datatype_aliases();
};

#endif // INOVESA_USE_CL
#endif // OPENCLHANDLER_HPP
