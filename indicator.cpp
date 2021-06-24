#include <ensmallen.hpp>

using namespace ens;
using namespace ens::test;

int main()
{
    ZDT3<> ZDT_THREE(300);
    arma::arma_rng::set_seed_random();

    typedef decltype(ZDT_THREE.objectiveF1) ObjectiveTypeA;
    typedef decltype(ZDT_THREE.objectiveF2) ObjectiveTypeB;

    const arma::cube& referenceFront = ZDT_THREE.GetReferenceFront();

    arma::mat coordsNSGA2 = ZDT_THREE.GetInitialPoint();
    arma::mat coordsMOEAD(coordsNSGA2);
    std::tuple<ObjectiveTypeA, ObjectiveTypeB> objectives = ZDT_THREE.GetObjectives();
    size_t numVariables = coordsNSGA2.size();

    const size_t populationSize = 300;
    const size_t maxGenerations = 300;
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

    nsga2.Optimize(objectives, coordsNSGA2);
    moead.Optimize(objectives, coordsMOEAD);

    const arma::cube& nsga2Front = nsga2.ParetoFront();
    const arma::cube& moeadFront = moead.ParetoFront();

    const double nsga2IGDPlus = IGDPlus::Evaluate(nsga2Front, referenceFront);
    const double moeadIGDPlus = IGDPlus::Evaluate(moeadFront, referenceFront);
    const double idealIGDPlus = IGDPlus::Evaluate(referenceFront, referenceFront);

    const double nsga2Epsilon = Epsilon::Evaluate(nsga2Front, referenceFront);
    const double moeadEpsilon = Epsilon::Evaluate(moeadFront, referenceFront);
    const double idealEpsilon = Epsilon::Evaluate(referenceFront, referenceFront);

    std::cout << "========================================" << std::endl;
    std::cout << "Ideal IGD+ value: " << idealIGDPlus << std::endl;
    std::cout << "IGD+ value of NSGA2: " << nsga2IGDPlus << std::endl;
    std::cout << "IGD+ value of MOEAD: " << moeadIGDPlus << std::endl;
    std::cout << std::endl;
    std::cout << "Ideal Epsilon value: " << idealEpsilon << std::endl;
    std::cout << "Epsilon value of NSGA2: " << nsga2Epsilon << std::endl;
    std::cout << "Epsilon value of MOEAD: " << moeadEpsilon << std::endl;
    std::cout << "========================================" << std::endl;
}
