/*
 *     Copyright (c) 2013 Battelle Memorial Institute
 *     Licensed under modified BSD License. A copy of this license can be found
 *     in the LICENSE file in the top level directory of this distribution.
 */
// -------------------------------------------------------------
/**
 * @file   base_gen_model.hpp
 * @author Shrirang Abhyankar
 * @Last modified:   02/17/19
 * 
 * @brief  
 * 
 * 
 */

#ifndef _base_gen_model_h_
#define _base_gen_model_h_

#include "boost/smart_ptr/shared_ptr.hpp"
#include "gridpack/component/base_component.hpp"
#include <constants.hpp>

// Same as DSMode in dsimnetwork.hpp
//enum DSGenMode{INIT_X,RESIDUAL_EVAL,XVECTOBUS,XDOTVECTOBUS,FAULT_EVAL};

class BaseGenModel
{
  public:
    /**
     * Basic constructor
     */
    BaseGenModel();

    /**
     * Basic destructor
     */
    virtual ~BaseGenModel();

    /**
     * Load parameters from DataCollection object into generator model
     * @param data collection of generator parameters from input files
     * @param index of generator on bus
     * TODO: might want to move this functionality to BaseGenModel
     */
    virtual void load(boost::shared_ptr<gridpack::component::DataCollection>
        data, int idx);

    /**
     * Initialize generator model before calculation
     * @param mag voltage magnitude
     * @param ang voltage angle
     * @param [output] values - array where initialized generator variables should be set
     */
    virtual void init(double mag, double ang,gridpack::ComplexType *values);

    /**
     * Write output from generators to a string.
     * @param string (output) string with information to be printed out
     * @param bufsize size of string buffer in bytes
     * @param signal an optional character string to signal to this
     * routine what about kind of information to write
     * @return true if bus is contributing string to output, false otherwise
     */
    virtual bool serialWrite(char *string, const int bufsize,
        const char *signal);

    virtual double getAngle();

    /**
     * Write out generator state
     * @param signal character string used to determine behavior
     * @param string buffer that contains output
     */
    virtual void write(const char* signal, char* string);

    /**
     *  Set the number of variables for this generator model
     *  @param [output] number of variables for this model
     */
    virtual int getNvar();

    /**
     * Set the internal values of the voltage magnitude and phase angle. Need this
     * function to push values from vectors back onto generators
     * @param values array containing generator state variables
     */
    virtual void setValues(gridpack::ComplexType*);

    /**
     * return the bolean indicating whether the gen is ON or OFF
     */
    bool getGenStatus() {return status;}

    /**
     * set mode
     */
    void setMode(DSMode inmode) { mode = inmode; }

 protected:
  double        pg; /**< Generator active power output */
  double        qg; /**< Generator reactive power output */
  double        mbase; /**< MVA base of the machine */
  int           status; /**< Machine status */
  double        sbase;  /** The system MVA base */

  DSMode        mode;  // Insert mode for the vector and matrix values
  bool          hasExciter;
  bool          hasGovernor;

  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
        ar &
          & pg
          & qg
          & mbase
          & status
          & sbase
          & hasExciter
          & hasGovernor;
  }
};

#endif
