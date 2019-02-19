#include <classical_gen_model.hpp>
#include <gridpack/include/gridpack.hpp>

ClassicalGen::ClassicalGen(void)
{
}

ClassicalGen::~ClassicalGen(void)
{
}

/**
 * Load parameters from DataCollection object into generator model
 * @param data collection of generator parameters from input files
 * @param index of generator on bus
 * TODO: might want to move this functionality to BaseGeneratorModel
 */
void ClassicalGen::load(boost::shared_ptr<gridpack::component::DataCollection> data, int idx)
{
  BaseGenModel::load(data,idx); // load parameters in base generator model

  // load parameters for the model type
  data->getValue(GENERATOR_RESISTANCE,&p_Rs,idx);
  data->getValue(GENERATOR_TRANSIENT_REACTANCE,&p_Xdp,idx);
  data->getValue(GENERATOR_INERTIA_CONSTANT_H,&p_H,idx);
  data->getValue(GENERATOR_DAMPING_COEFFICIENT_0,&p_D,idx);

      // Convert generator parameters from machine base to MVA base
  p_H *= mbase/sbase;
  p_D *= mbase/sbase;
  p_Xdp /= mbase/sbase;

}

/**
 * Initialize generator model before calculation
 * @param mag voltage magnitude
 * @param ang voltage angle
 * @param [output] values - array where initialized generator variables should be set
 */
void ClassicalGen::init(double Vm, double Va,gridpack::ComplexType* values)
{
  double VD, VQ; // Bus voltage in cartesian coordinates
  double IGD,IGQ; // Machine currents in cartesian coordinates
  double Pg, Qg;  // Generator real and reactive power
  double delta,dw=0.0;  // Initial machine speed deviation

  Pg = pg/sbase;
  Qg = qg/sbase;

  VD = Vm*cos(Va);
  VQ = Vm*sin(Va);

  IGD = (VD*Pg + VQ*Qg)/(Vm*Vm);
  IGQ = (VQ*Pg - VD*Qg)/(Vm*Vm);
  
  delta = atan2(VQ + p_Xdp*IGD,VD-p_Xdp*IGQ);

  p_Ep = sqrt(pow((VD - p_Xdp*IGQ),2) + pow((VQ + p_Xdp*IGD),2));
  p_Pm = Pg;
	
  values[0] = delta;
  values[1] = dw;
}

/**
 * Write output from generators to a string.
 * @param string (output) string with information to be printed out
 * @param bufsize size of string buffer in bytes
 * @param signal an optional character string to signal to this
 * routine what about kind of information to write
 * @return true if bus is contributing string to output, false otherwise
 */
bool ClassicalGen::serialWrite(char *string, const int bufsize,const char *signal)
{
}

double ClassicalGen::getAngle(void)
{
}

/**
 * Write out generator state
 * @param signal character string used to determine behavior
 * @param string buffer that contains output
 */
void ClassicalGen::write(const char* signal, char* string)
{
}

/**
 *  Set the number of variables for this generator model
 *  @param [output] number of variables for this model
 */
int ClassicalGen::getNvar()
{
  int nvar = 2;
  return nvar;
}

/**
 * Set the internal values of the voltage magnitude and phase angle. Need this
 * function to push values from vectors back onto generators
 * @param values array containing generator state variables
*/
void ClassicalGen::setValues(gridpack::ComplexType *values)
{
  if(mode == XVECTOBUS) {
    p_delta = real(values[0]);
    p_dw    = real(values[1]);
  } else if(mode == XDOTVECTOBUS) {
    p_deltadot = real(values[0]);
    p_dwdot    = real(values[1]);
  }
}
