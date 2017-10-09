#ifndef CONSTANT_HPP
#define CONSTANT_HPP

static const double tau (0.02); //RC time constant (sec)
static const double cond (0.001); //capacitance of the neuron (farad)
static const double tau_rp (0.002); //RC time constant for the refractory period (not used yet) (sec)
static const double v_reset (0.0); //potential at which the neuron reset everytime a spike occurs (V)
static const double time_rest (0.002); //refractory time the neuron takes to 'rest' (sec)
static const double thresh (0.02); //threshold, if the neuron potential gets to that point, it creates a spike (V)
static const double dt (0.0001); //smallest time interval with which we computing the time (sec)
static const double time_stop (0.5); //arbitrary time at which the program stops (sec)

#endif

//resistance = 20
//tau_m = 20
//v_th=20
//t_ref= 2
//h=0.1
// biologically : v_reset=-70mV
//just subtract 70 to the V -> have real biological values
//real value : I-ext = 260 pA here : 1pA

//atof(argv ((1)))

/*TO DO
 * constant in units of 1
 * abs(a-b) < 10e-6
 * maybe change main functions
 * 
 * 
 * 
 */
