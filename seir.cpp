#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>

namespace
{
	const char cTAB = '\t';
	const std::string sFileName = "./seir_c++.txt";

	constexpr int iTimeMax = 100;
	constexpr double dDeltaT = 1.0 / (double)iTimeMax;

	constexpr double dM = 0.025;
	constexpr double dA = 0.200;
	constexpr double dB = 0.001;
	constexpr double dG = 0.350;

	constexpr double dS0 = 950;
	constexpr double dE0 = 40;
	constexpr double dI0 = 10;
	constexpr double dR0 = 0;
	constexpr double dN = dS0 + dE0 + dI0 + dR0;
}

double CalculationNextSusceptible(const double& dPreviousS, const double& dPreviousI);
double CalculationNextExposed(const double& dPreviousS, const double& dPreviousE, const double& dPreviousI);
double CalculationNextInfectious(const double& dPreviousS, const double& dPreviousI);
double CalculationNextRecovered(const double& dPreviousR, const double& dPreviousI);
void OutputSEIR(std::vector<double>& vecS, std::vector<double>& vecE, std::vector<double>& vecI, std::vector<double>& vecR, const int iEnd);
void EquationSEIR(std::vector<double>& vecS, std::vector<double>& vecE, std::vector<double>& vecI, std::vector<double>& vecR);

int main()
{
	std::vector<double> vecS;
	std::vector<double> vecE;
	std::vector<double> vecI;
	std::vector<double> vecR;

	vecS.push_back(dS0);
	vecE.push_back(dE0);
	vecI.push_back(dI0);
	vecR.push_back(dR0);

	EquationSEIR(vecS, vecE, vecI, vecR);
	return 0;
}

double CalculationNextSusceptible(const double& dPreviousS, const double& dPreviousI)
{
	return (dPreviousS + dDeltaT * (dM * (dN - dPreviousS) - dB * dPreviousS * dPreviousI));
}

double CalculationNextExposed(const double& dPreviousS, const double& dPreviousE, const double& dPreviousI)
{
	return (dPreviousE + dDeltaT * (dB * dPreviousS * dPreviousI - (dM + dA) * dPreviousE));
}

double CalculationNextInfectious(const double& dPreviousE, const double& dPreviousI) 
{
	return (dPreviousI + dDeltaT * (dA * dPreviousE - (dM + dG) * dPreviousI));
}

double CalculationNextRecovered(const double& dPreviousR, const double& dPreviousI) 
{
	return (dPreviousR + dDeltaT * (dG * dPreviousI - dM * dPreviousR));
}

void OutputSEIR(std::vector<double>& vecS, std::vector<double>& vecE, std::vector<double>& vecI, std::vector<double>& vecR, const int iEnd)
{
	std::ofstream ofs(sFileName);
	for (int iStart = 0; iStart <= iEnd; ++iStart)
	{
		ofs << double(iStart * dDeltaT) << cTAB << vecS[iStart] << cTAB << vecE[iStart] << cTAB << vecI[iStart] << cTAB << vecR[iStart] << '\n';
	}
	ofs.close();
}

void EquationSEIR(std::vector<double>& vecS, std::vector<double>& vecE, std::vector<double>& vecI, std::vector<double>& vecR)
{
	int iNumber = 0;
	for (double dTimeStep = 0.00; dTimeStep <= iTimeMax; dTimeStep+=dDeltaT)
	{
		vecS.push_back(CalculationNextSusceptible(vecS[iNumber], vecI[iNumber]));
		vecE.push_back(CalculationNextExposed(vecS[iNumber], vecE[iNumber], vecI[iNumber]));
		vecI.push_back(CalculationNextInfectious(vecE[iNumber], vecI[iNumber]));
		vecR.push_back(CalculationNextRecovered(vecR[iNumber], vecI[iNumber]));
		++iNumber;
	}
	OutputSEIR(vecS, vecE, vecI, vecR, iNumber);
}

