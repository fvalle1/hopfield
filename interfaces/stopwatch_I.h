#ifndef STOPWATCH_I_H
#define STOPWATCH_I_H

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include <chrono>
#include <string>
#endif

#if defined(_OPENMP) 
#include <omp.h>     // Open Multiprocessing
#endif


struct Seconds{
    inline static std::string GetMU(){return "seconds";};
};

struct Milliseconds
{
    inline static std::string GetMU() { return "milliseconds"; };
};

template <typename time_measure, typename unit_measure>
class Stopwatch_I
{
public:
    inline Stopwatch_I(std::string name) : fName(name)
    {
        fSystemTime = std::chrono::system_clock::now();
        fCPUTime = std::clock();
#if defined(_OPENMP)
        fomptime = omp_get_wtime();
#endif
    };
    inline ~Stopwatch_I()
    {
        std::cout << std::endl;
        std::cout << fName << " runned in: " << GetWall() << " " << unit_measure::GetMU() << " [Wall time]" << std::endl;
        std::cout << fName << " runned in: " << GetCPU() << " " << unit_measure::GetMU() << " [CPU time]" << std::endl;
#if defined(_OPENMP)
        std::cout << fName << " runned in: " << GetOMP() << " sec [OMP time]" << std::endl;
#endif
        std::cout << std::endl;
    }

protected:
    inline double GetWall() const { return std::chrono::duration_cast<time_measure>(std::chrono::system_clock::now() - fSystemTime).count(); };
    inline double GetCPU() const { return (std::clock() - fCPUTime) / (double)CLOCKS_PER_SEC; }
#if defined(_OPENMP)
    inline double GetOMP() const
    {
        return (omp_get_wtime() - fomptime);
    }
#endif

private:
    std::chrono::time_point<std::chrono::system_clock> fSystemTime;
    std::clock_t fCPUTime;
#if defined(_OPENMP)
    double fomptime;
#endif
    std::string fName;
};

#endif //STOPWATCH_I_H