#include <bits/stdc++.h>
#include <ensmallen.hpp>
#include <chrono>

using namespace ens;
using namespace ens::test;
using namespace std;

int main()
{
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  arma::arma_rng::set_seed_random();

  ZDT3<> ZDT_THREE(100);

  typedef decltype(ZDT_THREE.objectiveF1) ObjectiveTypeA;
  typedef decltype(ZDT_THREE.objectiveF2) ObjectiveTypeB;

  arma::mat coordsNSGA2 = ZDT_THREE.GetInitialPoint();
  arma::mat coordsMOEAD(coordsNSGA2);
  std::tuple<ObjectiveTypeA, ObjectiveTypeB> objectives = ZDT_THREE.GetObjectives();
  size_t numVariables = coordsNSGA2.size();

  const size_t populationSize = 300;
  const size_t maxGenerations = 500;
  const double crossoverRate = 1.0;
  //! 1 / numVariables
  const double mutationRate = 1.0 / (double) numVariables;
  const double lowerBound = 0;
  const double upperBound = 1;

  NSGA2 nsga2(populationSize,
              maxGenerations,
              crossoverRate,
              mutationRate,
              1.0 / (20.0 + 1.0),
              1e-6,
              lowerBound,
              upperBound);

  DefaultMOEAD moead(populationSize,
                     maxGenerations,
                     crossoverRate,
                     0.9,
                     20,
                     20,
                     0.5,
                     2,
                     1E-10,
                     lowerBound,
                     upperBound);

  //for (size_t i = 1000; i > 0; --i) std::cout << "[WARM UP] Process starts in: " << i << "itr." << std::endl;

  auto t1 = high_resolution_clock::now();
  nsga2.Optimize(objectives, coordsNSGA2);
  auto t2 = high_resolution_clock::now();

  auto t1_1 = high_resolution_clock::now();
  moead.Optimize(objectives, coordsMOEAD);
  auto t2_1 = high_resolution_clock::now();

  duration<double, std::milli> nsga2_ms_double = t2 - t1;

  duration<double, std::milli> moead_ms_double = t2_1 - t1_1;
  std::cout.precision(10);
  std::cout << "==============================================" << std::endl;
  std::cout << "Speed in milliseconds for ZDT3" << std::endl;
  std::cout << "NSGA2: " << nsga2_ms_double.count() << " ms or " << nsga2_ms_double.count() / 1000 << " seconds." << std::endl;
  std::cout << "MOEAD: " << moead_ms_double.count() << " ms or " << moead_ms_double.count() / 1000 << " seconds." << std::endl;
  std::cout << "MOEAD is faster than NSGA2 by: " << nsga2_ms_double.count() / moead_ms_double.count()  << " times!" << std::endl;
  std::cout << "==============================================" << std::endl;
}
