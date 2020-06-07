#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>

namespace
{
	const char cTAB = '\t';
	const std::string sFileName = "./sir_c++.txt";

	constexpr int iTimeMax = 100;
	constexpr double dDeltaT = 1.0 / (double)iTimeMax;

	constexpr double dBeta = 0.001;
	constexpr double dGamma = 0.350;

	constexpr double dS0 = 950;
	constexpr double dI0 = 50;
	constexpr double dR0 = 0;
}

double CalculationNextSusceptible(const double& dPreviousS, const double& dPreviousI);
double CalculationNextInfectious(const double& dPreviousS, const double& dPreviousI);
double CalculationNextRecovered(const double& dPreviousR, const double& dPreviousI);
void OutputSIR(std::vector<double>& vecS, std::vector<double>& vecI, std::vector<double>& vecR, const int iEnd);
void EquationSIR(std::vector<double>& vecS, std::vector<double>& vecI, std::vector<double>& vecR);

int main()
{
	std::vector<double> vecS;
	std::vector<double> vecI;
	std::vector<double> vecR;

	vecS.push_back(dS0);
	vecI.push_back(dI0);
	vecR.push_back(dR0);

	EquationSIR(vecS, vecI, vecR);
	return 0;
}

double CalculationNextSusceptible(const double& dPreviousS, const double& dPreviousI)
{
	return (dPreviousS - dDeltaT * (dBeta * dPreviousS * dPreviousI));
}

double CalculationNextInfectious(const double& dPreviousS, const double& dPreviousI) 
{
	return (dPreviousI + dDeltaT * (dBeta * dPreviousS  * dPreviousI - dGamma * dPreviousI));
}

double CalculationNextRecovered(const double& dPreviousR, const double& dPreviousI) 
{
	return (dPreviousR + dDeltaT * (dPreviousI * dGamma));
}

void OutputSIR(std::vector<double>& vecS, std::vector<double>& vecI, std::vector<double>& vecR, const int iEnd)
{
	std::ofstream ofs(sFileName);
	for (int iStart = 0; iStart <= iEnd; ++iStart)
	{
		ofs << double(iStart * dDeltaT) << cTAB << vecS[iStart] << cTAB << vecI[iStart] << cTAB << vecR[iStart] << '\n';
	}
	ofs.close();
}

void EquationSIR(std::vector<double>& vecS, std::vector<double>& vecI, std::vector<double>& vecR)
{
	int iNumber = 0;
	for (double dTimeStep = 0.00; dTimeStep <= iTimeMax; dTimeStep+=dDeltaT)
	{
		vecS.push_back(CalculationNextSusceptible(vecS[iNumber], vecI[iNumber]));
		vecI.push_back(CalculationNextInfectious(vecS[iNumber], vecI[iNumber]));
		vecR.push_back(CalculationNextRecovered(vecR[iNumber], vecI[iNumber]));
		++iNumber;
	}
	OutputSIR(vecS, vecI, vecR, iNumber);
}

