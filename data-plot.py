import sys
import pandas as pd
import matplotlib.pyplot as plt

def plot_sir(df_sir, file_str):
	df_sir.columns = ['TimeStep', 'Susceptible', 'Infectious', 'Recovered']

	print(df_sir.head())
	
	plt.figure()
	color_list = ['darkblue', 'darkred', 'darkgreen']
	df_sir.plot(x='TimeStep', color=color_list)
	plt.title('SIR model')
	plt.savefig('./sir_' + file_str + '.png')

def plot_seir(df_seir, file_str):
	df_seir.columns = ['TimeStep', 'Susceptible', 'Exposed', 'Infectious', 'Recovered']

	print(df_seir.head())
	
	plt.figure()
	color_list = ['darkblue', 'darkorange', 'darkred', 'darkgreen']
	df_seir.plot(x='TimeStep', color=color_list)
	plt.title('SEIR model')
	plt.savefig('./seir_' + file_str + '.png')

if __name__=='__main__':

	if sys.argv[1] == 'sir':
		df = pd.read_csv('./sir_c++.txt', header=None, sep='\t')
		plot_sir(df, 'c++')
		df = pd.read_csv('./sir_python.txt', header=None, sep='\t')
		plot_sir(df, 'python')

	if sys.argv[1] == 'seir':
		df = pd.read_csv('./seir_c++.txt', header=None, sep='\t')
		plot_seir(df, 'c++')
		df = pd.read_csv('./seir_python.txt', header=None, sep='\t')
		plot_seir(df, 'python')
