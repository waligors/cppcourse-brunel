#ifndef CONSTANT_HPP
#define CONSTANT_HPP

static const double tau (200.0); //RC time constant (10^-4 sec)
static const double cap (10.0); //capacitance of the neuron (10^-4 farad)
static const double tau_rp (200.0); //RC time constant for the refractory period (not used yet) (10^-4 sec)
static const double v_reset (0.0); //potential at which the neuron reset everytime a spike occurs (V)
static const double time_rest (20.0); //refractory time the neuron takes to 'rest' (10^-4 sec)
static const double thresh (200.0); //threshold, if the neuron potential gets to that point, it creates a spike (10^-4 V)
static const double dt (1); //smallest time interval with which we computing the time (10^-4 sec)
static const double time_stop (500.0); //arbitrary time at which the program stops (10^-4 sec)
static const double j_const (200.0); //(10^-4 V) 0.02mV
static const unsigned int n_neurons (2); //
static const unsigned int buffer_size (8); //
static const unsigned int delay (5); //

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
 * constant in units of 1 DONE
 * abs(a-b) < 10e-6
 * maybe change main functions
 * 
 * 
 * 
 */
