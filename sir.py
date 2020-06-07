import numpy as np
import pandas as pd
from scipy.integrate import odeint
from scipy.optimize import minimize
import matplotlib.pyplot as plt

def SIR_EQ(v, t, beta, gamma):
	return [-beta*v[0]*v[1], beta * v[0] * v[1] - gamma *v[1], gamma * v[1]]

def main():
	t_max = 100
	dt = 1.0 / t_max
	beta_const = 0.001
	gamma_const = 0.350

	S_0 = 950
	I_0 = 50
	R_0 = 0
	ini_state = [S_0, I_0, R_0]

	times = np.arange(0, t_max, dt)
	args = (beta_const, gamma_const)

	result = odeint(SIR_EQ, ini_state, times, args)


	dict_output = {}
	dict_output['TimeStep'] = times
	dict_output['Susceptible'] = [result[i][0] for i in range(0, len(result), 1)]
	dict_output['Infectious'] = [result[i][1] for i in range(0, len(result), 1)]
	dict_output['Recovered'] = [result[i][2] for i in range(0, len(result), 1)]
	df_output = pd.DataFrame(dict_output.values(), index=dict_output.keys()).T
	df_output.to_csv('./sir_python.txt', sep='\t', index=False, header=False)

if __name__=='__main__':
	main()
