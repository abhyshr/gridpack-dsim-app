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
     * @param [output] values - array where initialized generator variables should be set
     */
    virtual void init(gridpack::ComplexType *values);

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
     * Return the values of the generator vector block
     * @param values: pointer to vector values
     * @return: false if generator does not contribute
     *        vector element
     */
    virtual bool vectorValues(gridpack::ComplexType *values);

    /**
     * return the bolean indicating whether the gen is ON or OFF
     */
    bool getGenStatus() {return status;}

    /**
     * set mode
     */
    void setMode(DSMode inmode) { mode = inmode; }

    /**
     * Set bus voltage
     */
    void setVoltage(double busVD, double busVQ) {VD = busVD; VQ = busVQ; }

    /**
     * Set TSshift: This parameter is passed by PETSc and is to be used in the Jacobian calculation only.
     */
    void setTSshift(double inshift) {shift = inshift;}

    /**
     * Return the generator current injection (in rectangular form) 
     * @param [output] IGD - real part of the generator current
     * @param [output] IGQ - imaginary part of the generator current
     */
    virtual void getCurrent(double *IGD, double *IGQ);

    /**
     * Return the matrix entries
     * @param [output] nval - number of values set
     * @param [output] row - row indices for matrix entries
     * @param [output] col - col indices for matrix entries
     * @param [output] values - matrix entries
     * return true when matrix entries set
     */
    virtual bool matrixDiagEntries(int *nval,int *row, int *col, gridpack::ComplexType *values);

 protected:
  double        pg; /**< Generator active power output */
  double        qg; /**< Generator reactive power output */
  double        mbase; /**< MVA base of the machine */
  int           status; /**< Machine status */
  double        sbase;  /** The system MVA base */
  DSMode        mode;  // Insert mode for the vector and matrix values
  double        shift; // shift (multiplier) used in the Jacobian calculation.
  bool          hasExciter;
  bool          hasGovernor;
  double        VD, VQ;
};

#endif
