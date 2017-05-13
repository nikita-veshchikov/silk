#include"tracer.hpp"

std::vector<double> Tracer::_trace = std::vector<double>();
unsigned Tracer::_leakagePointsNbr = 0;
double (*Tracer::_leakageDistributionFunc)(double, double) = NULL;
double Tracer::_leakageInterval = 0.0;
unsigned Tracer::_leakageOverlap = 0;
double Tracer::_noiseVariance = 0.0;
std::default_random_engine Tracer::_randomGenerator = std::default_random_engine(0);

Tracer::Tracer(){
	//nothing to do here
}

Tracer::~Tracer(){
	//nothing to do here
}

void Tracer::clearTrace(){
	_trace = std::vector<double>();
}

std::vector<double> Tracer::getTrace(){
	return _trace;
}

std::vector<double> Tracer::getNoisyTrace(){
	std::vector<double> noisyTrace(_trace);
	//add noise
	if (_noiseVariance != 0){
		std::normal_distribution<double> distribution(0,sqrt(_noiseVariance));
		for (unsigned i=0;i<noisyTrace.size();++i){
			noisyTrace[i]+= distribution(_randomGenerator);
		}
	}
	
	return noisyTrace;
}

void Tracer::traceToFile(const char* filename){
	saveVector(filename, _trace);
}

void Tracer::noisyTraceToFile(const char* filename){
	//make noisy trace
	saveVector(filename, getNoisyTrace());
}

void Tracer::setLeakageInterval(unsigned interval){
	_leakageInterval = interval;
}

void Tracer::setLeakagePointsNbr(unsigned pts_nbr){
	_leakagePointsNbr = pts_nbr;
}

void Tracer::setLeakageDistributionFunc(double (*leakageDistributionFunc)(double, double), double pts_nbr){
	_leakageDistributionFunc = leakageDistributionFunc;
	_leakageInterval = pts_nbr;
}

void Tracer::setLeakageOverlap(unsigned overlap){
	//TODO : add exceptions
	if (overlap < _leakagePointsNbr){
		_leakageOverlap = overlap;
	}
}

void Tracer::setNoiseVariance(double var){
	//TODO :  add exceptions
	if(var>=0.0){
		_noiseVariance = var;
	}
}


// ------- private methods -------

void Tracer::saveVector(const char* filename, const std::vector<double> &vec){
	std::ofstream outputFile;
	outputFile.open(filename);
	for(unsigned int i=0; i<vec.size()-1;++i){
		outputFile<<vec[i]<<", ";
	}
	outputFile<<vec[vec.size()-1]<<"\n";
	outputFile.close();
}

void Tracer::setRandomSeed(unsigned seed){
	_randomGenerator = std::default_random_engine(seed);
}
