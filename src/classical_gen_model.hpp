/*
 *     Copyright (c) 2013 Battelle Memorial Institute
 *     Licensed under modified BSD License. A copy of this license can be found
 *     in the LICENSE file in the top level directory of this distribution.
 */
// -------------------------------------------------------------
/**
 * @file   classical_generator_model.hpp
 * @author Shrirang Abhyankar
 * @Last modified:   02/17/19
 * 
 * @brief  
 * 
 * 
 */

#ifndef _classical_gen_model_h_
#define _classical_gen_model_h_

#include <base_gen_model.hpp>
#include <gridpack/include/gridpack.hpp>
#include "boost/smart_ptr/shared_ptr.hpp"
#include "gridpack/component/base_component.hpp"


class ClassicalGen: public BaseGenModel
{
   public:
  /**
     * Basic constructor
     */
    ClassicalGen();

    /**
     * Basic destructor
     */
    ~ClassicalGen();

    /**
     * Load parameters from DataCollection object into generator model
     * @param data collection of generator parameters from input files
     * @param index of generator on bus
     * TODO: might want to move this functionality to BaseGeneratorModel
     */
    void load(boost::shared_ptr<gridpack::component::DataCollection>
        data, int idx);

    /**
     * Initialize generator model before calculation
     * @param mag voltage magnitude
     * @param ang voltage angle
     */
    void init(double mag, double ang);

    /**
     * Write output from generators to a string.
     * @param string (output) string with information to be printed out
     * @param bufsize size of string buffer in bytes
     * @param signal an optional character string to signal to this
     * routine what about kind of information to write
     * @return true if bus is contributing string to output, false otherwise
     */
    bool serialWrite(char *string, const int bufsize,
        const char *signal);

    double getAngle();

    /**
     * Write out generator state
     * @param signal character string used to determine behavior
     * @param string buffer that contains output
     */
    void write(const char* signal, char* string);

  private:
    // Machine parameters
    double p_Rs; // Machine stator resistance
    double p_Xdp;  // Machine transient reactance
    double p_H;      // Machine Inertia constant
    double p_D;      // Machine damping coefficient

    // Internal constants
    double p_Pm;  // Mechanical power input
    double p_Ep;  // Internal emf


    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar &
	& p_Rs
	& p_Xdp
	& p_H
	& p_D;
     }
};

#endif