import numpy as np
import pandas as pd
from scipy.integrate import odeint
from scipy.optimize import minimize
import matplotlib.pyplot as plt

def SEIR_EQ(v, t, n, m, a, b, g):

	next_s = m * (n - v[0]) - b * v[0] * v[2]
	next_e = b * v[0] * v[2] - (m + a) * v[1]
	next_i = a * v[1] - (m + g) * v[2]
	next_r = g * v[2] - m * v[3]

	return [next_s, next_e, next_i, next_r]

def main():
	t_max = 100
	dt = 1.0 / t_max
	m_const = 0.025
	a_const = 0.200
	b_const = 0.001
	g_const = 0.350

	S_0 = 950
	E_0 = 40   
	I_0 = 10   
	R_0 = 0   
	n_const = S_0 + E_0 + I_0 + R_0
	ini_state = [S_0, E_0, I_0, R_0]

	times = np.arange(0, t_max, dt)
	args = (n_const, m_const, a_const, b_const, g_const)

	result = odeint(SEIR_EQ, ini_state, times, args)

	dict_output = {}
	dict_output['TimeStep'] = times
	dict_output['Susceptible'] = [result[i][0] for i in range(0, len(result), 1)]
	dict_output['Exposed'] = [result[i][1] for i in range(0, len(result), 1)]
	dict_output['Infectious'] = [result[i][2] for i in range(0, len(result), 1)]
	dict_output['Recovered'] = [result[i][3] for i in range(0, len(result), 1)]
	df_output = pd.DataFrame(dict_output.values(), index=dict_output.keys()).T
	df_output.to_csv('./seir_python.txt', sep='\t', index=False, header=False)


if __name__=='__main__':
	main()
