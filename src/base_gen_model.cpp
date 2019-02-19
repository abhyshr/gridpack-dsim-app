#include <base_gen_model.hpp>
#include <gridpack/include/gridpack.hpp>

BaseGenModel::BaseGenModel(void)
{
  hasExciter = hasGovernor = false;
}

BaseGenModel::~BaseGenModel(void)
{
}

/**
 * Load parameters from DataCollection object into generator model
 * @param data collection of generator parameters from input files
 * @param index of generator on bus
 * TODO: might want to move this functionality to BaseGeneratorModel
 */
void BaseGenModel::load(boost::shared_ptr<gridpack::component::DataCollection>
        data, int idx)
{
  data->getValue(GENERATOR_STAT,&status,idx); // Generator status
  data->getValue(CASE_SBASE,&sbase); // System MVAbase, used in conversion from machine base to system base.
  if(status) {
    data->getValue(GENERATOR_PG,&pg,idx); // Generator real power
    data->getValue(GENERATOR_QG,&qg,idx); // Generator reactive power
    data->getValue(GENERATOR_MBASE,&mbase,idx); // Machine base (in MVA)
  } else {
    pg = qg = mbase = 0.0;
  }
}

/**
 * Initialize generator model before calculation
 * @param mag voltage magnitude
 * @param ang voltage angle
 * @param [output] values - array where initialized generator variables should be set
 */
void BaseGenModel::init(double mag, double ang,gridpack::ComplexType *values)
{
}

/**
 * Write output from generators to a string.
 * @param string (output) string with information to be printed out
 * @param bufsize size of string buffer in bytes
 * @param signal an optional character string to signal to this
 * routine what about kind of information to write
 * @return true if bus is contributing string to output, false otherwise
 */
bool BaseGenModel::serialWrite(char *string, const int bufsize,
			       const char *signal)
{
}

double BaseGenModel::getAngle()
{
}

/**
 *  Set the number of variables for this generator model
 *  @param [output] number of variables for this model
 */
int BaseGenModel::getNvar()
{
  int nvar = 0;
  return nvar;
}

/**
 * Write out generator state
 * @param signal character string used to determine behavior
 * @param string buffer that contains output
 */
void BaseGenModel::write(const char* signal, char* string)
{
}

/**
 * Set the internal values of the voltage magnitude and phase angle. Need this
 * function to push values from vectors back onto generators
 * @param values array containing generator state variables
*/
void BaseGenModel::setValues(gridpack::ComplexType *values)
{
}
